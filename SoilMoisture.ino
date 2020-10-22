int WET= 16; // Indicador de agua D0
int DRY= 2;  // Ausencia de agua D4


int sense_Pin = 0; // Pin de entrada del sensor A0

int value = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(WET, OUTPUT);
  pinMode(DRY, OUTPUT);
  delay(2000);
}

void loop() 
{

   Serial.print("MOISTURE LEVEL : ");
   value= analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);

        if(value<50)
        {
            digitalWrite(WET, HIGH);
            Serial.print("Humedo");
        }
       else
       {
           digitalWrite(DRY,HIGH);
           Serial.print("Seco");
       }

       delay(1000);

       digitalWrite(WET,LOW);

       digitalWrite(DRY, LOW);
}
