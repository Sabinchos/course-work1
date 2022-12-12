#include <OneWire.h>// библиотека для работы с протоколом 1-Wire
#include <DallasTemperature.h>// библиотека для работы с датчиком DS18B20
#define MQ2pin (0)
DeviceAddress Term = { 0x28, 0x3F, 0x3A, 0x49, 0xF6, 0xA3, 0x3C, 0x67 };// адрес датчика DS18B20

OneWire oneWire(10);// создаём объект для работы с библиотекой OneWire
DallasTemperature sensors(&oneWire);// создадим объект для работы с библиотекой DallasTemperature
float sensorValue;// переменная для хранения значения датчика MQ-2

void setup(void)
{
  Serial.begin(9600); // настраиваем последовательный порт на скорость 9600
  Serial.println("Gas sensor warming up!");
  delay(20000); // даем MQ-2 время для прогрева
  sensors.begin();//инициализируем датчик
  pinMode (8, OUTPUT);// устанавливает режим работы - выход
  pinMode (7, OUTPUT);// устанавливает режим работы - выход

}


void loop(void)
{ 
  sensorValue = analogRead(MQ2pin); // прочитать аналоговый вход 0
  Serial.print("Gas: ");
  Serial.print(sensorValue); // выводим значения с MQ-2
  sensors.requestTemperatures();// отправляем запрос на измерение температуры
  Serial.print (" | Temperature: ");
  Serial.println(sensors.getTempC(Term));//выводим температуру в градусах Цельсия
 
  if(sensorValue > 350)
  {
    Serial.println("Gas detected!");
    if (sensors.getTempC(Term) > 30) {
      Serial.println("Fire!");
      digitalWrite (8, HIGH);// включаем светодиод (огнетушаащее вещество подано)
      digitalWrite (7, HIGH);// включаем светодиод (смс-сообщение в МЧС отправлено)
      delay (1500);//ждем 1,5 секунды
      digitalWrite (8, LOW);//выключаем светодиод
      digitalWrite (7, LOW);
      
    }
  }
  
  delay(2000); // подождать 2 сек до следующего чтения
}
