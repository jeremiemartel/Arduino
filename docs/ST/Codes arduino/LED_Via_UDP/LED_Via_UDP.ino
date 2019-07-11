/*
Exemple de commande à distance de la carte utilisant le protocole UDP
 */

// références requises pour configurer le mdoule WiF intégré
#include <SPI.h>
#include <WiFiST.h>
#include <WiFiUdpST.h>
 
// intialisation des bus et du module WiFi
SPIClass SPI_3(PC12, PC11, PC10);
WiFiClass WiFi(&SPI_3, PE0, PE1, PE8, PB13);

// initialisation du jingle
int speakerOut = 5;
int ledPin = 13;
byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p"; 
int count = 0;
int count2 = 0;
int count3 = 0;
int MAX_COUNT = 24;
int statePin = LOW;

int status = WL_IDLE_STATUS; // état du module WiFi
char ssid[] = "CooLab_Creaspace";     // le nom de votre réseau WiFi
char pass[] = "CooLab_Creaspace";     // le mot de passe de votre réseau WiFi
int keyIndex = 0;  // l'index de votre clef réseau (utile seulement pour WEP)

WiFiUDP Udp; /* initialisation de User Datagram Protocol (UDP).
             UDP est le protocole (langage) de communication que nous allons utiliser 
             à travers la connexion WiFi.*/
               
unsigned int localPort = 3000;  // Le numéro du port UDP ouvert sur la carte
char packetBuffer[255];         // table tampon quyi recevra les messages envoyés depuis le PC

int ledstate = 0; // état de la LED intégrée à la carte
int trycnt = 0;   // décompte des tentatives de connexion au réseau WiFi

void setup() {
  
  //Initialize le port série et la LED intégrée à la carte
  Serial.begin(9600);
  while (!Serial) {;}
  pinMode(13, OUTPUT);
  
  Serial.println("Port UDP local attribué à la carte : " + String(localPort));

  // Essaye de se connecter au réseau WiFi
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    trycnt = trycnt + 1;      // compte le nombre de tentatives de connexions
    if (trycnt > 1) {Serial.println("Nouvelle tentative de connexion à " + String(ssid));}
    delay(1000);   // attends une seconde
  }
 
  printWifiStatus(); // cette fonction, détaillée par la suite, affiche l'état de la connexion WiFi
  
  Serial.println("\nCarte à l'écoute de messages UDP ...");
  Udp.begin(localPort); // le module WiFi est à l'écoute des messages UDP entrants sur le port 3000
  
  }

void loop() {
  
  // Lis les messages entrants (envoyés par le PC) et les charge dans packetBuffer
  int len = Udp.read(packetBuffer, 255);
 
  if (strcmp(packetBuffer,"LED")==0) { // si le texte du message est "LED"

      // informations sur le message reçu
      IPAddress remoteIp = Udp.remoteIP();
      Serial.print("\nPaquet reçu de ");
      Serial.print(remoteIp);
      Serial.print(" sur le port ");
      Serial.println(Udp.remotePort());
    
      if (ledstate == 0) { // si la LED est éteinte
        
        ledstate = 1; // signale qu'elle doit être allumée
        Udp.write("LED ON\n"); // renvoie ce message au client UDP
        Serial.println("- LED allumée");
        
      }
      
      else { // si la LED est allumée
      
        ledstate = 0; // signale qu'elle doit être éteinte
        Udp.write("LED OFF\n"); // renvoie ce message au client UDP
        Serial.println("- LED éteinte");
      }
    
      digitalWrite(ledPin, ledstate); // chage l'état de la LED
      
  }

  else if (strcmp(packetBuffer,"JINGLE")==0) { // si le texte du message est "JINGLE"
   
    Udp.write("JINGLE\n"); // renvoie ce message au client UDP
    Serial.println("- Aïe mes oreilles !");
    play_jingle();
    
  }
}

void printWifiStatus() {
  
  // Affiche le SSID du réseau WiFi auquel on est connecté

  Serial.print("Connexion WiFi établie sur ");
  Serial.println(WiFi.SSID());

  // Affiche l'adresse IP attribuée à la carte
  IPAddress ip = WiFi.localIP();
  Serial.print("Adresse IP atribuée à la carte : ");
  Serial.println(ip);

  // Affiche l'atténuation du signal WiFi vu par la carte
  long rssi = WiFi.RSSI();
  Serial.print("Atténuation du signal : ");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void play_jingle() {
  analogWrite(speakerOut, 0);     
  for (count = 0; count < MAX_COUNT; count++) {
     for (count3 = 0; count3 <= (melody[count*2] - 48) * 30; count3++) {
      for (count2=0;count2<8;count2++) {
        if (names[count2] == melody[count*2 + 1]) {       
          analogWrite(speakerOut,500);
          delayMicroseconds(tones[count2]);
          analogWrite(speakerOut, 0);
          delayMicroseconds(tones[count2]);
        } 
        if (melody[count*2 + 1] == 'p') {
          // make a pause of a certain size
          analogWrite(speakerOut, 0);
          delayMicroseconds(500);
        }
      }
    }
  }
}
