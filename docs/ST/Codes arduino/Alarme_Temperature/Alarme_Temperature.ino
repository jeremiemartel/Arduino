// Alarme de température avec seuil

// Déclaration pour le capteur intégré à la carte
#include <HTS221Sensor.h>  
#define I2C2_SCL    PB10
#define I2C2_SDA    PB11
HTS221Sensor  *HumTemp;
TwoWire *dev_i2c;

const int BUZZER_PIN = 6;  // broche du buzzer
const float TEMP_THRESHOLD = 27.5; // seuil de température
const int delayValue = 10; // délà entre deux notes du buzzer, en ms
 
void setup() {
  // initalisations capteur et moniteur série
  Serial.begin(9600);
  dev_i2c = new TwoWire(I2C2_SDA, I2C2_SCL);
  dev_i2c->begin();
  HumTemp = new HTS221Sensor (dev_i2c);
  HumTemp->Enable();
   
  pinMode(BUZZER_PIN, OUTPUT); // initialisation broche Buzzer
}

void loop() {
  
  // Lecture de la température et affichage dans le moniteur série
  float temperature;
  HumTemp->GetTemperature(&temperature);
  Serial.println("Temp[C]: " + String(temperature)); // cast + concaténation
  
  if( temperature > TEMP_THRESHOLD) { // si le seuil de temp. est dépassé
    buzzer_alarm(delayValue); // alarme !
  }
  delay(1000); // pause d'une seconde
}

void buzzer_alarm(int delayValue) // fonction chargée de l'alarme
{
  digitalWrite(BUZZER_PIN, HIGH);
  delay(delayValue);
  digitalWrite(BUZZER_PIN, LOW);
  delay(delayValue);
}

