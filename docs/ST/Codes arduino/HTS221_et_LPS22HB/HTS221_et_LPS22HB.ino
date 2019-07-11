
// configuration des capteurs

#include <HTS221Sensor.h>
#include <LPS22HBSensor.h>

#define I2C2_SCL    PB10
#define I2C2_SDA    PB11

HTS221Sensor  *HTS221;
LPS22HBSensor *LPS22HB;
TwoWire *dev_i2c;

void setup() {
 
  pinMode(LED_BUILTIN, OUTPUT); // intialisation de la LED
  Serial.begin(9600); // initialisation du terminal série

  // initialisation du bus I2C
  dev_i2c = new TwoWire(I2C2_SDA, I2C2_SCL);
  dev_i2c->begin();

  // initialisation des capteurs
  HTS221 = new HTS221Sensor (dev_i2c);
  HTS221->Enable();
  LPS22HB = new LPS22HBSensor(dev_i2c);
  LPS22HB->Enable();
}

void loop() {
 
  float tempHTS221, tempLPS22HB;
 
  HTS221->GetTemperature(&tempHTS221);    // température selon HTS221
 
  LPS22HB->GetTemperature(&tempLPS22HB); // température selon LPS22HB
  
  // Ecriture des deux températures
  Serial.print("Temp HTS221[C]: ");
  Serial.print(tempHTS221, 2);
  Serial.print(" | Temp LPS22HB [C]: ");
  Serial.print(tempLPS22HB, 2);
  Serial.print(" | Abs Diff [C]: ");
  Serial.println(abs(tempHTS221 - tempLPS22HB), 2);  
}

