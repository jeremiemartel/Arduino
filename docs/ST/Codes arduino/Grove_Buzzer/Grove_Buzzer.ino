// Objectif : 
//   - Emettre une alarme en appuyant sur le bouton "USER"
//   - Afficher un message sur le LCD 
// Attention : le shield Grove doit être positionné sur 5V (pou le LCD)

// Pour gérer le LCD
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

const int BUZZER_PIN = 6; // broche du buzzer D6
const int color = 255; // compposante couleur

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT); // Initialisation broche Buzzer
  pinMode(USER_BTN,INPUT); // Initialisation broche du bouton utilisateur

  lcd.begin(16, 2); // nombre de colonnes et lignes du LCD
  lcd.setRGB(0, color, 0); // couleur de fond du LCD : vert
 }

void loop()
{
  if(digitalRead(USER_BTN) == RESET) // Si le bouton est appuyé
  { 
    // attends jusqu'à ce qu'il soit relâché
    while (digitalRead(USER_BTN) == RESET); 
    
    lcd.setRGB( color, 0, 0); // couleur de fond du LCD : rouge
    lcd.print("Alarm!"); // écrit un message sur le LCD
    lcd.display(); // affiche le message

    // alarme sur le buzzer  
    digitalWrite(BUZZER_PIN, HIGH);
    delay(analogRead(0));
    digitalWrite(BUZZER_PIN, LOW);
    delay(analogRead(0));
    
    lcd.setRGB(0, color, 0); // couleur de fond du LCD : vert
    lcd.noDisplay(); // cesse d'afficher
    }
}
