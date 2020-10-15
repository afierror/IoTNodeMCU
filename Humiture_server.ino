#include "DHT.h"
#include <ESP8266WiFi.h>

//#include <ESP8266WebServer.h>

#define DHTTYPE DHT11 // DHT 11

const char* ssid = "INFINITUMBC7209";            // Aqui va ti identificador
const char* password = "4DC9C863D1";        //Aqui va tu contraseña

WiFiServer server(80);
uint8_t DHTPin = 2; 

DHT dht(DHTPin, DHTTYPE);

float Temperature=0;
float Humidity=0;

void setup()
{    
  Serial.begin(115200);
  pinMode(DHTPin, INPUT);   
  dht.begin();             //Iniciamos el sensor

  Serial.println("Conectando...");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Intentamos la conexion a la WIFI
  while (WiFi.status() != WL_CONNECTED)
  {  
    delay(1000);
    Serial.print(".");      // Escribiendo puntitos hasta que conecte
  }  
  
  Serial.println("");
  Serial.println("WiFi conectada..!");
  Serial.print("IP del servidor: "); 
  Serial.println(WiFi.localIP());   // Imprimir nuestra IP al conectar

  server.begin();
  Serial.println("HTTP server started");
}


void loop()
{
  Temperature = dht.readTemperature();
  Humidity = dht.readHumidity();
  //Serial.print("Temperatura: ");
  //Serial.print(Temperature);
  //Serial.print(" Humedad: ");
  //Serial.print(Humidity);
  //Serial.println();
  
  //server.send(200, "text/html", SendHTML(Temperature,Humidity));

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
