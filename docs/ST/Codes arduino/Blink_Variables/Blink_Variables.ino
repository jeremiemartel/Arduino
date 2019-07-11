/*  Blink avec un calcul de durée et un affichage sur le moniteur série
  Objectifs : utiliser le port série mais aussi apporter des rudiments de langage C tels que
             - variables et type de variables
             - optimisation de l'usage mémoire en choissant les variables du type adéquat
             - calculs sur des variables
             - instruction "if" */

 const int PERIODE_AFFICHAGE = 5000; // écrit sur le moniteur série toutes les 5 s
 const int DELAI_LED = 100; // durée en ms pendant laquelle la LED est allumée ou éteinte.
 int tempsEcoule = 0; // variable de type int comptant le temps écoulé (ms)
 long nbPeriode = 0; // variable de type long comptant le nombre de PERIODE_AFFICHAGE realisées
 float affichTemps = 0; // variable de type float (nombre à virgule) pour l'affichage en secondes
 
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600); /* Ouvre une connexion entre le PC et la carte, par le port série
                        avec un débit de 9600 bits par seconde */

  Serial.println("Initialisation de Blink terminee"); // écriture d'un message avec saut à la ligne

}

void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(DELAI_LED);
  digitalWrite(LED_BUILTIN, LOW);
  delay(DELAI_LED);
  
  tempsEcoule = tempsEcoule + 2 * DELAI_LED;  // calcule le temps écoulé

  if ( tempsEcoule >= PERIODE_AFFICHAGE ) // si PERIODE_AFFICHAGE ms ou plus se sont écoulées
     { // début "if", pensez à indenter votre code !
      
       tempsEcoule = 0; // re-intitailise le compteur de temps écoulé
       
       nbPeriode = nbPeriode + 1; // on vient de finir une période, on incrémente le compteur

       affichTemps = ( nbPeriode * PERIODE_AFFICHAGE ) / 1000; // calcule de la valeur à afficher
       
       Serial.print("Temps ecoule (secondes) "); // écriture d'un message sans saut à la ligne
       Serial.println(affichTemps); // fin du message avec saut à la ligne
     } // fin "if"
}
