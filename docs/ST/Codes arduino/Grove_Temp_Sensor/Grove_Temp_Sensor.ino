// Mesure de température avec capteur Grove 

#include <math.h>

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Capteur de température Grove connecté sur A0
const float CORRECTION = 0;    // correction à apporter à la lecture de température 

// On calcule la température en faisant la moyenne de AVGCOUNT lectures du capteur
int counter = 0;
float sumTemp =0;
float avgTemp = 0;
const int AVGCOUNT = 5; 

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int a = analogRead(pinTempSensor); // valeur fonnée par le capteur (0-1023)
   
    // convertit en température le signal numérique du capteur
    float R = 1023.0/a-1.0;
    R = R0*R;
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-(273.15 + CORRECTION); 
   
    // prépare la moyenne
    counter = counter+1;
    sumTemp = sumTemp + temperature;

    // toutes les AVGCOUNT mesures, affiche la moyenne de température
    if (counter == AVGCOUNT) {
      avgTemp =sumTemp / AVGCOUNT;
      Serial.print("température (°C) = ");
      Serial.println(avgTemp);
      counter = 0;
      sumTemp = 0;
    }
    
    delay(1000);
}
