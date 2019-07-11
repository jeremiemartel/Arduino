#include <LiquidCrystal.h>
// Initialize library with the numbers of interfaces pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int   incomingByte = 0;
char  incomingChar;

void  setup_serial();
void  setup_crystal();

void  ft_bzero(char *str, int len)
{
  int   i;

  i = 0;
  while (i < len)
  {
    str[i] = 0;
    i++;
  }
  return ;
}

void  ft_strmv(char *src, char *dest)
{
  int   i1 = 0;

  while (src[i1])
  {
    dest[i1] = src[i1];
    i1++;
  }
  dest[i1] = 0;
  ft_bzero(src, i1);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  setup_serial();
  setup_crystal();
}

char    c;
int     i = 0;
char    line[17];

void loop()
{

  if (Serial.available() > 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    c = Serial.read();
    Serial.print("I received: "); Serial.println(c, DEC);
    if (c <= 31)
    {
      lcd.clear();
      lcd.print(line);
      lcd.setCursor(0, 1);
      ft_bzero(line, 17);
      i = 0;
    }
    else
    {
      if (i < 16)
        line[i] = c;
//      lcd.setCursor(i, 1);/
      lcd.write(c);
      i++;
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void  setup_serial()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.pprintln("Serial connection established");
  digitalWrite(LED_BUILTIN, HIGH);
}

void  setup_crystal()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welcome");
  lcd.noBlink();
  delay(1500);
  lcd.clear();
  lcd.blink();
  // lcd.autoscroll();
  lcd.setCursor(0,0);
}
