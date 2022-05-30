#include <SPI.h>
#include <belt.h>

size_t len = 16; //длина ключа
octet key[16] = {0}; //объявление глобального массива для хранения ключа
const octet iv[16] = { 'z', 'j', 'l', 'b', 'y', ':', 'b', 'd', '0', 'q', 'f', 'l', 'h', 'e', 'u', '7' }; //синхропосылка

char outData = 0; //выходные данные, нуждающиеся в шифровании
char inData = 0; //входные данные, нуждающиеся в расшифровке

bool SPI_is_receiving = false; //индикация получения данных по SPI

belt_ctr_st stateEncr = {0};
belt_ctr_st stateDecr = {0};

void setup() // функция, код которой выполняется единожды при запуске контроллера
{
  long time_counter = 0;
  unsigned long interval = 0;
  unsigned long c = 0;

  octet enc_data[16];

  // инициализация SPI:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // MSBFIRST – приоритет старшего бита, LSBFIRST – приоритет младшего бита
  SPI.setClockDivider(SPI_CLOCK_DIV4); //установка делителя частоты SPI (16Mhz/4 = 4Mhz)
  digitalWrite(SS, HIGH);

  // инициализация UART:
  Serial.begin(9600); //установка частоты передачи данных
  Serial.println("Ready");
  for(int i = 0; i < len; i++) //считывание ключа с последовательного порта при запуске
  {
    while(Serial.available() == 0){} //ожидание начала передачи данных
    key[i] = Serial.read(); //считывание ключа с устройства посимвольно
  }

  Serial.println("Key ok.");
 
  // инициализация состояния шифратора
  beltCTRStart(&stateEncr, key, len, iv);

  // инициализация состояния дешифратора
  beltCTRStart(&stateDecr, key, len, iv);

  digitalWrite(SS, LOW); //указание, что устройство осуществляет передачу по SPI шине

  for(int i = 0; i < len; i++) //считывание ключа с последовательного порта при запуске
  {
    while(Serial.available() == 0){} //ожидание начала передачи данных
    enc_data[i] = Serial.read();
    beltCTRStepE(enc_data + i, 1, &stateEncr);
    Serial.write(enc_data[i]);
  }

  for(int i = 0; i < len; i++) //считывание ключа с последовательного порта при запуске
  {
    beltCTRStepE(enc_data + i, 1, &stateDecr);
    Serial.write(enc_data[i]);
  }

  unsigned long start_time = millis();
  Serial.print("Current time: ");
  Serial.println(start_time);
  for(unsigned long k=0;k<200000;k++) {
    beltCTRStepE(&outData, 1, &stateDecr);
  }
  Serial.println("");
  
  unsigned long end_time = millis();
  Serial.print("After encryption time: ");
  Serial.println(end_time);
  unsigned long elapsed = end_time - start_time;
  Serial.print("Elapsed ms: ");
  Serial.println(elapsed);

  while(Serial.available() == 0){} //ожидание начала передачи данных
  
  /*time_counter = millis();
  SPI.transfer(0xAA);
  for(c = 0; c < 1000; c++) {
    beltCTRStepE(&outData, 1, &stateEncr);
  }
  SPI.transfer(0xBB);*/
  
  //interval = (millis() - time_counter);
  //byte buf[4];
  //buf[0] = interval & 255;
  //buf[1] = (interval >> 8)  & 255;
  //buf[2] = (interval >> 16) & 255;
  //buf[3] = (interval >> 24) & 255;

  //Serial.write(buf, sizeof(buf));
}

void HandleSPI(char input) //обработка приём по SPI
{
  if(!SPI_is_receiving) //если передача полезных данных не осуществляется
  {
    if(input == 0) //ожидание передачи
      return;
  
    if(input == 1) //сигнализация, что далее будет осуществляться передача полезных данных
    {
      SPI_is_receiving = true;
      return;
    }
  }

  SPI_is_receiving = false;
  beltCTRStepE(&input, 1, &stateDecr); //расшифровка
  Serial.write(input); //отправка нешифрованных данных
}

void loop() //функция, код которой выполняется бесконечным циклом
{
  if(Serial.available() == 0) {
    delay(10);
    return;
  }
  
  //digitalWrite(SS, LOW); //указание, что устройство осуществляет передачу по SPI шине
  outData = Serial.read(); //получение нешифрованных данных
  SPI.transfer(outData);
  beltCTRStepE(&outData, 1, &stateEncr); // шифрование
  SPI.transfer(outData);
  //HandleSPI(SPI.transfer(1)); //индикация того, что следующий байт значащий
  //HandleSPI(SPI.transfer(outData)); //отправка шифрованных данных по SPI
  //delay(10);

  //HandleSPI(SPI.transfer(0)); //получение шифрованных данных по SPI
  //digitalWrite(SS, HIGH); //указание, что устройство прекращает передачу по SPI шине
  delay(1000); //задержка на 10мс (1000мс/(9600битвсек/8бит/64байтбуф) = 53,3мс макс задержки на 1 итер)
}
