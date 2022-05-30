#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <belt.h>

#define ONE_WIRE_BUS 6

OneWire oneWire(ONE_WIRE_BUS); //Настройка 1wire для работы с 6-м выводом Ардуино
DallasTemperature sensors(&oneWire); //Подключаем датчик температуры

bool SPI_is_receiving = false; //индикация получения данных по SPI

size_t len = 16; //длина ключа
octet key[16] = {0}; //объявление глобального массива для хранения ключа
const octet iv[16] = { 'z', 'j', 'l', 'b', 'y', ':', 'b', 'd', '0', 'q', 'f', 'l', 'h', 'e', 'u', '7' }; //синхропосылка

char outData[256] = {0}; //выходные данные, нуждающиеся в шифровании
char inData[256] = {0}; //входные данные, нуждающиеся в расшифровке

belt_ctr_st stateEncr = {0};
belt_ctr_st stateDecr = {0};

int ii=1;
int ij=0;
byte r=0,g=0,b=0;
char buf[100];
char bb[40];

// задание MAC-адреса устройства
byte mac[] = {0x0E, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// Параметры сети по умолчанию при отсуствии DHCP-свервера
// Настройка IP-адреса, шлюза, DNS-сервера, и маски сети
IPAddress ip(192,168,1,30);
IPAddress myDns(8,8,8,8);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

EthernetClient client;
int addr_len=0;
int addr = 0;
char server[100];
int buttonState = 1;

unsigned long lastConnectionTime = 0; // время последнего подключения к серверу (в миллисекундах)
boolean lastConnected = false; // последнее состояние подключения
const unsigned long postingInterval = 10*1000; // задержка между обновлениями данных (в миллисекундах)

void setup() {
    int i;

    pinMode(3, OUTPUT); // LED 1
    pinMode(4, INPUT); // Кнопка PD4
    pinMode(5, OUTPUT); // LED 2
    pinMode(7, OUTPUT); // LED 3

    // инициализация SPI:
    SPI.begin();
    SPI.setBitOrder(MSBFIRST); // MSBFIRST – приоритет старшего бита, LSBFIRST – приоритет младшего бита
    SPI.setClockDivider(SPI_CLOCK_DIV4); //установка делителя частоты SPI (16Mhz/4 = 4Mhz)
    digitalWrite(SS, HIGH);

    // инициализация UART:
    Serial.begin(9600); //установка скорости передачи данных UART

    // Ожидание загрузки Ethernet-модуля
    delay(1000);
    buttonState = digitalRead(4);

    // Проверка, нажата ли кнопка PD4 сразу после включения питания
    if (buttonState == 0){ // Если нажата, необходимо ввести имя сервера и ключ шифрования
        for(ia=0;ia<100;ia++){
            addr=ia; EEPROM.write(addr, 0); // Обнуляем EEPROM
        }

        Serial.print("Input server name: ");
        while(Serial.available() <= 0){ ;} // Ожидание ввода
        delay(1000); // Задержка для передачи в буфер

        for(i = 0; i < len; i++) //считывание ключа с последовательного порта при запуске
        {
            while(Serial.available() == 0){} // ожидание начала передачи данных
            key[i] = Serial.read(); // считывание ключа шифрования посимвольно
        }

        i=0;
        while(Serial.available() > 0 && addr_len < 100) {
            server[i] = Serial.read(); addr_len=i; i++; // Чтение адреса сервера
        }

        for(i = 0; i < 16; i++)
            EEPROM.write(i, key[i]); // Запись ключа в EEPROM
        for(i = 0; i < addr_len; i++)
            EEPROM.write(i + 16, server[i]); // Запись адреса в EEPROM

        Serial.println();
    }
    else {
        for(i = 0; i < 16; i++)
            key[i] = EEPROM.read(i); // чтениею ключа с EEPROM

        for(i = 0; i < 100; i++)
            server[i]=EEPROM.read(i + 16); // Чтение имени сервера с EEPROM
    }

    // инициализация состояния шифратора
    beltCTRStart(&stateEncr, key, len, iv);

    // инициализация состояния дешифратора
    beltCTRStart(&stateDecr, key, len, iv);

    Serial.print("Server name: ");
    Serial.println(server);
    // Определение IP параметров с помощью DHCP
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        // initialize the ethernet device not using DHCP:
        Ethernet.begin(mac, ip, myDns, gateway, subnet);
    }
    // start the Ethernet connection using a fixed IP address and DNS server:
    // print the Ethernet board/shield's IP address:
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
    Serial.print("My DNS address: ");
    Serial.println(Ethernet.dnsServerIP());
    Serial.print("Gateway address: ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("SubnetMask: ");
    Serial.println(Ethernet.subnetMask());
}


void loop() {
    // Получены ли данные по сети
    if (client.available()) {

        char c = client.read(); // чтение данных
        beltCTRStepE(&c, 1, &stateDecr); //расшифровка байта данных
        Serial.print(c); // отладочный вывод

        buf[ii-1]=c; ij=ii;
        if(c=='\n')
            ii=0;
        ii++;
    }

    // обработка данных от сервера
    if (!client.connected() && lastConnected) {
        Serial.println();
        Serial.print("disconnecting");

        if(ij<=1) goto lab;
        for(ii=0;ii<ij;ii++)
            Serial.write(buf[ii]);
        Serial.println();
        if( buf[1]=='1') {digitalWrite(3,HIGH);}
        if( buf[1]=='0') {digitalWrite(3,LOW);}
        if( buf[2]=='1') {digitalWrite(5,HIGH);}
        if( buf[2]=='0') {digitalWrite(5,LOW);}
        if( buf[3]=='1') {digitalWrite(7,HIGH);}
        if( buf[3]=='0') {digitalWrite(7,LOW);}
        lab:
        client.stop();
    }

    // Если клиент не подключен и прошло 10 секунд с последнего подключения
    // Тогда подключаемся снова и отправляем данные
    if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
        sensors.requestTemperatures();
        int temp=sensors.getTempCByIndex(0);
        httpPost(&temp, 2); // шифрование и отправка данных от сенсора
    }
    if( !client.connected() && (millis() - lastConnectionTime > postingInterval/2)) {
        httpGet(); // опрашиваем сервер
    }
    // сохранить последнее состояние (подключен/не подключен)
    lastConnected = client.connected();
}


// Шифрование и отправка данных на сервер
void httpPost(char * data, size_t len) {
    if (client.connect(server, 80)) {
        Serial.println("connecting (POST)...");
        // send the HTTP PUT request:
        client.println("POST /command.php HTTP/1.1");
        client.println("User-Agent: arduino-ethernet");
        client.println("Connection: close");
        client.println();

        for(int i = 0; i < len; i++) {
            // шифрование
            beltCTRStepE(enc_data + i, 1, &stateEncr);

            // отправка данных
            client.print(data[i]);
        }

        // note the time that the connection was made:
        lastConnectionTime = millis();
    }
    else {
        // if you couldn't make a connection:
        Serial.println("connection failed");
        Serial.println("disconnecting.");
        client.stop();
    }
}

// опрос сервера
void httpGet() {
    if (client.connect(server, 80)) {
        Serial.println("connecting (GET)...");

        client.println("GET /command.php HTTP/1.1");
        client.println("Connection: close");
        client.println();
    }
}