// Emet une alarme en cas d'appui sur le bouton "USER"
// Affiche un message sur le LCD et change sa couleur de fond
// Attention : le shield Grove doit être positionné sur 5V pour le LCD

#include <Wire.h>
#include "rgb_lcd.h" // Gestion du LCD (branché sur un connecteur I2C)
rgb_lcd lcd;

const int BUZZER_PIN = 6; //Broche du buzzer
const int COLOR = 255; // Composante couleur

void setup() {
  pinMode(BUZZER_PIN, OUTPUT); // Initialisation broche du buzzer
  pinMode(USER_BTN, INPUT); // Initialisation broche bouton USER
  lcd.begin(16,2); // nombre de colonnes et de lignes du LCD
  lcd.setRGB(0, COLOR, 0); // couleur de fond du LCD (vert)
  lcd.display(); // démarre le LCD
}

void loop() {

  if(digitalRead(USER_BTN) == RESET) { // si le bouton USER est appuyé

    while(digitalRead(USER_BTN) == RESET); // attendre qu'il soit relâché

    lcd.setRGB(COLOR,0,0); // passe la couleur de fond du LCD à rouge
    lcd.print("Alarme !"); // écrit un message sur le LCD
 
    digitalWrite(BUZZER_PIN,HIGH); // alarme sur le buzzer
    delay(100);
    digitalWrite(BUZZER_PIN,LOW);
    delay(100);

    lcd.setRGB(0,COLOR,0); // passe la couleur de fond du LCD à vert
    lcd.clear(); // efface le texte du LCD
    
  }
 }


 
