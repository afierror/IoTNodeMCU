#include "DHT.h"
#include <ESP8266WiFi.h>

#define DHTTYPE DHT11 // DHT 11

const char* ssid = "xxxxxxxxx";           
const char* password = "yyyyyyyyy";        

WiFiServer server(80);
uint8_t DHTPin = 2; 

DHT dht(DHTPin, DHTTYPE);

float Temperature=0;
float Humidity=0;

void setup()
{    
  Serial.begin(115200);
  pinMode(DHTPin, INPUT);   
  dht.begin();             

  Serial.println("Conectando...");
  Serial.println(ssid);

  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED)
  {  
    delay(1000);
    Serial.print(".");      
  }  
  
  Serial.println("");
  Serial.println("WiFi conectada..!");
  Serial.print("IP del servidor: "); 
  Serial.println(WiFi.localIP());   

  server.begin();
  Serial.println("HTTP server started");
}


void loop()
{
  Temperature = dht.readTemperature();
  Humidity = dht.readHumidity();

////////////Pagina Web/////////////////////////////////

  WiFiClient client = server.available();  
  if (!client) {
    return;
  }


  Serial.println("nuevo cliente");
  while(!client.available()){
    delay(1);
  }

   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println("");
   client.println("<!DOCTYPE HTML>");
   client.println("<html>");
   client.print("Temperatura : ");   
   client.print(Temperature);    
   client.print(" C  ");

   client.print("Humedad : ");   
   client.print(Humidity);   
   client.print(" %  ");   
   client.println("</html>");
       
}
