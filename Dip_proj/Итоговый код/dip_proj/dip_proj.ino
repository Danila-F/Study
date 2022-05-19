#include <SPI.h>
#include <belt.h>

size_t len = 16; //длина ключа
octet key[16] = {0}; //объявление глобального массива для хранения ключа
const octet iv[16] = { 'z', 'j', 'l', 'b', 'y', ':', 'b', 'd', '0', 'q', 'f', 'l', 'h', 'e', 'u', '7' }; //синхропосылка

char* outData = { 0 }; //выходные данные, нуждающиеся в шифровании
void* stateEncr; //объявление состояния шифратора

char* inData = { 0 }; //входные данные, нуждающиеся в расшифровке
void* stateDecr; //состояние дешифратора

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

void loop() //функция, код которой выполняется бесконечным циклом
{
  if(Serial.available() > 0)
  {
    digitalWrite(SS, LOW); //указание, что устройство осуществляет передачу по SPI шине
    *outData = (char)Serial.read(); //получение нешифрованных данных
    beltCTRStepE(outData, 1, stateEncr); // шифрование
    *inData = SPI.transfer(*outData); //отправка и получение шифрованных данных по SPI
    beltCTRStepE(inData, 1, stateDecr); //расшифровка
    Serial.write((int)*inData); //отправка нешифрованных данных
    digitalWrite(SS, HIGH); //указание, что устройство прекращает передачу по SPI шине
  }
  else
    delay(10); //задержка на 10мс (1000мс/(9600битвсек/8бит/64байтбуф) = 53,3мс макс задержки на 1 итер)
}
