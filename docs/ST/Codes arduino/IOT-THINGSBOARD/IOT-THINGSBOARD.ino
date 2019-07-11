/*
Prototype Hackathon LAB Aix 2018
Carte utilisée STM B-L475E-IOT01A
Plateforme Thingsboard.io
Transfert des datas et connexion à la plateforme via Wifi avec protocole JSON
Température/Humidité/Pression atmosphérique/Magnetomètre
BERNIER FRANCOIS - 04/2018
 */


// Includes.
#include <HTS221Sensor.h> // Capteur Humidité et Température
#include <WiFiST.h> // WiFi de la carte IOT Node
#include <PubSubClient.h> //cette librairie permet d’envoyer et de recevoir des messages MQTT et de gérer le QoS
#include <SPI.h> // cette librairie vous permet de communiquer avec des périphériques SPI
#include <LPS22HBSensor.h> // Capteur Barométrique
#include <LIS3MDLSensor.h> // Magnétomètre ( boussolle digitale )
#include <LSM6DSLSensor.h> // 3D Gyroscope et Accelerométre)

#define I2C2_SCL    PB10 // Port IC2 SCL utilisé sur la carte IOT Node
#define I2C2_SDA    PB11 // Port IC2 SDA utilisé sur la carte IOT Node

#define TOKEN "xxxxxxxxxxxxxxxxxxx" // Clé / Token généré dans le Device de Thingsboard

// Update these with values suitable for your network.

char ssid[] = "xxxxxx"; // SSID  du reseau Wifi sur lequel se connectera la carte
const char* password = "xxxxxx"; // Mot de passe du SSID


// WiFi module setup
SPIClass SPI_3(PC12, PC11, PC10);
WiFiClass WiFi(&SPI_3, PE0, PE1, PE8, PB13);
WiFiClient STClient;

int status = WL_IDLE_STATUS; // the Wifi  status
unsigned long lastSend;

PubSubClient client(STClient); // Declaration du Cleint PubSub
long lastMsg = 0; // Format de variable
char msg[8];   // Format de variable


char thingsboardServer[] = "demo.thingsboard.io"; // adresse du site serveur thingsboard

// Variables des differents capteurs

HTS221Sensor  *HumTemp;
LPS22HBSensor *PressTemp;
LIS3MDLSensor *Magneto;
LSM6DSLSensor *AccGyr;
TwoWire *dev_i2c;



void setup() {

  // Led.
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Initialize serial for output.
  Serial.begin(115200); // démarage de la connection serie à la vitesse de 115200 bauds
  
  setup_wifi(); // Initialisation du module WiFi
 
  client.setServer( thingsboardServer, 1883 ); // port utilisé pour transférer les dats sur le serveur Thingsboard
  lastSend = 0;
  
  // Initialisation du Bus I2C
  dev_i2c = new TwoWire(I2C2_SDA, I2C2_SCL);
  dev_i2c->begin();

  // Initialisation des capteurs
  HumTemp = new HTS221Sensor (dev_i2c);
  HumTemp->Enable();
  
  PressTemp = new LPS22HBSensor(dev_i2c);
  PressTemp->Enable();

  Magneto = new LIS3MDLSensor(dev_i2c);
  Magneto->Enable();

  AccGyr = new LSM6DSLSensor(dev_i2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW);
  AccGyr->Enable_X();
  AccGyr->Enable_G();
}



void setup_wifi() {

  delay(100);

  // Initialize the WiFi module:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi module not detected");
    // don't continue:
    while (true);
  }
 
  // Attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WIFI network: ");
  Serial.print(ssid);
  Serial.println( ". . ." );
  while (status != WL_CONNECTED) {
  Serial.print("");
  
    // Connect to network:
    status = WiFi.begin(ssid, password);
    // Wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println( "" );
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("STMicro Discovery IOT Node", TOKEN, NULL) ) {
    Serial.println( "[DONE]" );
    Serial.println( "" );
    } else {
    Serial.print( "[FAILED] [ rc = " );
    Serial.print( client.state() );
    Serial.println( " : retrying in 5 seconds]" );
    // Wait 5 seconds before retrying
    delay( 5000 );
    }
  }
}



void loop() {
  
  // Clignotement de la Led à chaque boucle ( emission des datas vers le serveur)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
   digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);

  
 if (!client.connected()) {
    reconnect();
  }
    client.loop();
    
  if ( millis() - lastSend > 1000 ) { // Update and send only after x seconds
    getAndSendData();
    lastSend = millis();
  }


  delay(55000); // delais entre chaque boucle ( ici 55 sec)
  
}

// Génération et envoi des données

void getAndSendData(){
  
  Serial.println("Collecting datas...");
  Serial.println( "" );
  
  float humidity, temperature; // formatage des données
  HumTemp->GetHumidity(&humidity); // récupération des données
  HumTemp->GetTemperature(&temperature);
  
  float pressure;
  PressTemp->GetPressure(&pressure);
  
  int32_t magnetometer[3];
  Magneto->GetAxes(magnetometer);
  
  int32_t accelerometer[3];
  int32_t gyroscope[3];
  
  AccGyr->Get_X_Axes(accelerometer);
  AccGyr->Get_G_Axes(gyroscope);


  
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = (humidity); // déclaration de la variable "humidity" vers la variable "h"
  // Read temperature as Celsius (the default)
  float t = (temperature-4.1);
  // Read pressure.
  float p = (pressure);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from sensors!");
  return;
  }

// Affichage des données vers le port serie
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" % " );
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Pressure: ");
  Serial.print(p);
  Serial.print(" MilliBars ");
  Serial.println("");  
  Serial.print("Mag[mGauss]: |");
  Serial.print(magnetometer[0]);
  Serial.print("| ");
  Serial.print(magnetometer[1]);
  Serial.print("| ");
  Serial.print(magnetometer[2]); 
  Serial.println("| ");
  Serial.print("Acc[mg]: | ");
  Serial.print(accelerometer[0]);
  Serial.print(" | ");
  Serial.print(accelerometer[1]);
  Serial.print(" | ");
  Serial.print(accelerometer[2]);
  Serial.print(" | Gyr[mdps]: |");
  Serial.print(gyroscope[0]);
  Serial.print(" | ");
  Serial.print(gyroscope[1]);
  Serial.print("| ");
  Serial.print(gyroscope[2]);
  Serial.println(" |");



  Serial.println(" ");
  Serial.print( "==> Sent Payload Listing  -> " );
  Serial.println(" ");
  Serial.println(" ");


  
  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"Temp\":"; payload += temperature; payload += ",";
  payload += "\"Hum\":"; payload += humidity; payload += ",";
  payload += "\"Press\":"; payload += pressure; payload += ",";
  payload += "\"Magneto1\":"; payload += magnetometer[0]; payload += ",";
  payload += "\"Magneto2\":"; payload += magnetometer[1]; payload += ",";
  payload += "\"Magneto3\":"; payload += magnetometer[2]; 
  payload += "}";


  // Send payload
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  client.publish( "v1/devices/me/telemetry", attributes );
  Serial.print(  "Payload " ); 
  Serial.println(  attributes );
  Serial.println("");


 // Prepare a JSON payload1 string
  String payload1 = "{";
  payload1 += "\"Accel1\":"; payload1 += accelerometer[0]; payload1 += ",";
  payload1 += "\"Accel2\":"; payload1 += accelerometer[1]; payload1 += ",";
  payload1 += "\"Accel3\":"; payload1 += accelerometer[2]; payload1 += ",";
  payload1 += "\"Gyro1\":"; payload1 += gyroscope[0]; payload1 += ",";
  payload1 += "\"Gyro2\":"; payload1 += gyroscope[1]; payload1 += ",";
  payload1 += "\"Gyro3\":"; payload1 += gyroscope[2]; 
  payload1 += "}";


  // Send payload1
  char attributes1[100];
  payload1.toCharArray( attributes1, 100 );
  client.publish( "v1/devices/me/telemetry", attributes1 );
  Serial.print(  "Payload1 " ); 
  Serial.println(  attributes1 );
  Serial.println("");


}
