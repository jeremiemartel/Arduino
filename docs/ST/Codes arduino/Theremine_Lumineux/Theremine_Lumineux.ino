// Thérémine lumineux, d'après le "Livre des projets Arduino" 

int sensorValue; // valeur de la photorésistance, entre 0 et 1023
int sensorLow = 1023; // plus petite valeur de la photorésistance, initialement à 1023
int sensorHigh = 0; // plus grande valeur de la photorésistance, initialement à 0
const int ledPin = 13; // broche de la LED
const int buzzerPin = 8; // broche du buzzer
const int photoResistorPin = A0; // broche de la photorésistance
const int soundDuration = 15; // durée du son à jouer, en millisecondes

void setup() {
 
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, HIGH); // allume la LED au début de l'étalonnage

  while(millis() < 5000) { // Boucle d'étalonnage, pendant 5s
    
    sensorValue = analogRead(photoResistorPin); // lis la photorésistance (entre 0 et 1023)
    
    if (sensorValue > sensorHigh) { // met à jour sa valeur maximum
       sensorHigh = sensorValue;
      }

    if (sensorValue < sensorLow) { // met à journe sa valeur minimum
       sensorLow = sensorValue;     
      }

    digitalWrite(ledPin, LOW);  // éteint la LED à la fin de l'étalonnage

  }
  
}

void loop() {

  sensorValue = analogRead(A0); // lis la photorésistance
  
  // re-mappe cette valeur dans l'intervalle de fréquence 50 - 4000 Hz ("produit en croix")
  int soundFrequency = map(sensorValue, sensorLow, sensorHigh, 50, 4000); // fréquence du son à jouer
  tone(buzzerPin, soundFrequency, soundDuration); // joue sur le buzzer une note
                                                  //  - de fréquence soundFrequency (Hz)
                                                  //  - de durée soudDuration (ms)
  delay(10); //attends 10 milliscondes
  
}
