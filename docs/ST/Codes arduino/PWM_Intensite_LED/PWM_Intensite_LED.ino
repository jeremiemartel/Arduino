/*
  Ce programme allume puis éteint progressivement une LED branchée sur la broche 6
  lorsque le bouton poussoir est appuyé
  Illustre l'usage de analogWrite et de la boucle for.
  http://wiki.labaixbidouille.com/index.php/Modifier_l%27intensit%C3%A9_lumineuse_d%27une_LED
*/

const int LED_PWM_PIN = 6; // broche PWM (~) de la LED
const int MAX_PWM_WIDTH = 255; // largeur d'impulation max
int i = 0; // variable de la boucle for

void setup() // setup est exécuté une seule fois après la remise à zéro
{                
  pinMode(LED_PWM_PIN, OUTPUT); // la broche LED_PWM_PIN est configuée en sortie 
     
  pinMode(USER_BTN, INPUT_PULLUP); // la broche USER_BTN est configurée en entrée 
                                   // avec résistance de tirage au +
}

void loop() // loop est exécuté indéfiniment
{
  while (!digitalRead(USER_BTN)) // exécute la boucle tant que USER_BTN est appuyé
    {
  
    for (i=0;i<MAX_PWM_WIDTH;i++) // i augmente de 1 à MAX_PWM_WIDTH par incréments de 1
      {
      if(digitalRead(USER_BTN)) {break;} // quitte la boucle si le bouton est relâché
      analogWrite(LED_PWM_PIN,i); // génère une impulsion de "largeur" 255*i/100 sur la broche 
      // la luminosité augmente car la largeur des impulsions augmente 
      delay(10); // pause de 10 ms entre chaque pas
      }
  
    for (i=MAX_PWM_WIDTH;i>0;i--) // i diminue de MAX_PWM_WIDTH à 1, par décréments de 1
      {
      if(digitalRead(USER_BTN)) {break;} // quitte la boucle si le bouton est relâché
      analogWrite(LED_PWM_PIN,i); // génère une impulsion de "largeur" 255*i/100 sur la broche 
      // la luminosité diminue car la largeur des impulsions diminue 
      delay(10); // pause de 10 ms entre chaque pas
      }  
    }
}


