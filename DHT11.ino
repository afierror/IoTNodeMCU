#include "DHT.h"
#define DHTTYPE DHT11 // DHT 11

uint8_t DHTPin = 2; 

DHT dht(DHTPin, DHTTYPE);

float Temperature=0;
float Humidity=0;

void setup()
{    Serial.begin(115200);
     pinMode(DHTPin, INPUT);   
     dht.begin();             //Iniciamos el sensor
}


void loop()
{
       Temperature = dht.readTemperature();
       Humidity = dht.readHumidity();
       Serial.print("Temperatura: ");
       Serial.print(Temperature);
       Serial.print(" Humedad: ");
       Serial.print(Humidity);
       Serial.println();
}
