#define IN_PORT   A0
#define R_PORT    D0
#define V_PORT    D1
#define B_PORT    D2

int   r_state;
int   v_state;
int   b_state;
char  c;


void  show(void)
{
  Serial.print("r : ");
  Serial.print(r_state);
  Serial.print("b : ");
  Serial.print(b_state);
  Serial.print("v : ");
  Serial.println(v_state);
}

int   update_state(int state)
{
  if (state == LOW)
    return (HIGH);
  if (state == HIGH)
    return (LOW);
  return (HIGH);
}

void setup() {
    Serial.begin(9600);
    Serial.println("Serial started");
    pinMode(R_PORT, OUTPUT);
    pinMode(V_PORT, OUTPUT);
    pinMode(B_PORT, OUTPUT);
    digitalWrite(R_PORT, LOW);
    digitalWrite(V_PORT, LOW);
    digitalWrite(B_PORT, LOW);
    r_state = LOW;
    v_state = LOW;
    b_state = LOW;
}

void loop() {
  while (Serial.available() > 0)
  {
    c = Serial.read();
    if (c == 'r')
    {
      r_state = update_state(r_state);
      digitalWrite(R_PORT, r_state);
    }
    else if (c == 'b')
    {
      b_state = update_state(b_state);
      digitalWrite(B_PORT, b_state);
    }
    else if (c == 'v')
    {
      v_state = update_state(v_state);
      digitalWrite(V_PORT, v_state);
    }
    show();
  }
  delay(200);
 }
