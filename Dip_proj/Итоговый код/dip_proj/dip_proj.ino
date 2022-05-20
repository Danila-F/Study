#include <SPI.h>
#include <belt.h>

size_t len = 16; //длина ключа
octet key[16] = {0}; //объявление глобального массива для хранения ключа
const octet iv[16] = { 'z', 'j', 'l', 'b', 'y', ':', 'b', 'd', '0', 'q', 'f', 'l', 'h', 'e', 'u', '7' }; //синхропосылка

char* outData = { 0 }; //выходные данные, нуждающиеся в шифровании
void* stateEncr; //объявление состояния шифратора

char* inData = { 0 }; //входные данные, нуждающиеся в расшифровке
void* stateDecr; //состояние дешифратора

bool SPI_is_receiving = false; //индикация получения данных по SPI

void setup() // функция, код которой выполняется единожды при запуске контроллера
{
  // инициализация UART:
  Serial.begin(9600); //установка частоты передачи данных
  for(int i = 0; i < len; i++) //считывание ключа с последовательного порта при запуске
  {
    while(Serial.available() == 0){} //ожидание начала передачи данных
    key[i] = Serial.read(); //считывание ключа с устройства посимвольно
  }
  
  // инициализация SPI:
  pinMode(SS, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // MSBFIRST – приоритет старшего бита, LSBFIRST – приоритет младшего бита
  
  // инициализация состояния шифратора
  stateEncr = malloc(blobActualSize(sizeof(belt_ctr_st)));
  memset(blobValueOf(stateEncr), 0, sizeof(belt_ctr_st));
  beltCTRStart(stateEncr, key, len, iv);

  // инициализация состояния дешифратора
  stateDecr = malloc(blobActualSize(sizeof(belt_ctr_st)));
  memset(blobValueOf(stateDecr), 0, sizeof(belt_ctr_st));
  beltCTRStart(stateDecr, key, len, iv);
}

void HandleSPI(char input) //обработка приём по SPI
{
  if(!SPI_is_receiving)
  {
    if(input == 0)
      return;
  
    if(input == 1)
    {
      SPI_is_receiving = true;
      return;
    }
  }

  SPI_is_receiving = false;
  beltCTRStepE(&input, 1, stateDecr); //расшифровка
  Serial.write(input); //отправка нешифрованных данных
}

void loop() //функция, код которой выполняется бесконечным циклом
{
  digitalWrite(SS, LOW); //указание, что устройство осуществляет передачу по SPI шине
  if(Serial.available() > 0)
  {
    *outData = Serial.read(); //получение нешифрованных данных
    beltCTRStepE(outData, 1, stateEncr); // шифрование
    HandleSPI(SPI.transfer(1)); //индикация того, что следующий байт значащий
    HandleSPI(SPI.transfer(*outData)); //отправка шифрованных данных по SPI
  }
    //delay(5); //задержка на 10мс (1000мс/(9600битвсек/8бит/64байтбуф) = 53,3мс макс задержки на 1 итер)
    //*inData = SPI.transfer(*outData); //отправка и получение шифрованных данных по SPI
  HandleSPI(SPI.transfer(0)); //получение шифрованных данных по SPI
  digitalWrite(SS, HIGH); //указание, что устройство прекращает передачу по SPI шине
  delay(5); //задержка на 10мс (1000мс/(9600битвсек/8бит/64байтбуф) = 53,3мс макс задержки на 1 итер)
}
