/*
  Blink
  Le même programme avec des constantes.
  Objectif : pemettre de remplacer une valeur partout dans le programme sans se tromper 
*/

const int WAIT_LED_HIGH = 100; /* variable de type int(eger) contentant la durée
                        pendant laquelle la LED sera allumée (en ms) */ 

const int WAIT_LED_LOW = 100; /* variable de type int (integer) contentant la durée
                      pendant laquelle la LED restera éteinte (en ms) */

const int BROCHE_LED = 13 ; /* constante de type int, remplace la constante 
                            prédéfinie LED_BULTIN */ 

const int ETAT_HAUT = 1 ; /* constante de type int, remplace la constante 
                            prédéfinie HIGH */ 

const int ETAT_BAS = 0 ; /* constante de type int, remplace la constante 
                            prédéfinie LOW */ 

/* La fonction SETUP est exécutée une fois lorsque vous mettez la carte sous tension ou 
   bien lorsque vous appuyez sur RESET */

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(BROCHE_LED, OUTPUT);
}

// La fontion Loop tourne éternellement (ver l'infini et au-delà, voire plus).

void loop() {
  digitalWrite(BROCHE_LED, ETAT_HAUT); // Allumer la LED en envoyant ETAT_HAUT sur la BROCHE_LED
  delay(WAIT_LED_HIGH);           // Attendre pendant waitLEDhigh millisecondes
  digitalWrite(BROCHE_LED, ETAT_BAS);  // Eteindre la LED en envoyant ETAT_BAS sur la BROCHE_LED
  delay(WAIT_LED_LOW);            // Attendre pendant waitLEDlow millisecondes
}
