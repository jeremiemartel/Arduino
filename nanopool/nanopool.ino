#define IN_PORT		  A1
#define DANGER_PORT	A2
#define LED_PORT	  13

#define VALVE_PORT	A0

#define IN_LIMIT  	800

int			measure;
float		measure_V;
int			delay_ms = 1;

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial started");
    
    pinMode(IN_PORT, INPUT);
    pinMode(DANGER_PORT, INPUT);
    
    pinMode(VALVE_PORT, OUTPUT);
    
    pinMode(LED_PORT, OUTPUT);
    digitalWrite(LED_PORT, LOW);
}

void	open_valve()
{
	Serial.println("Opening");
	digitalWrite(VALVE_PORT, HIGH);
	digitalWrite(LED_PORT, HIGH);
}

void  close_valve()
{
  Serial.println("Closing");
  digitalWrite(VALVE_PORT, LOW);
  digitalWrite(LED_PORT, LOW);
}

void	serial_write_measure(int measure)
{
	measure_V = measure * (5.0 / 1023);
	Serial.print("measure : ");
	Serial.print(measure_V);
	Serial.print("  (");
	Serial.print(measure);
	Serial.println(")");
}

void	loop()
{
	measure = analogRead(IN_PORT);
	serial_write_measure(measure);
	if (measure > IN_LIMIT)
		open_valve();
  else
    close_valve();

	measure = analogRead(DANGER_PORT);
	serial_write_measure(measure);
	if (measure > IN_LIMIT)
	{
    	close_valve();
    	exit(1);
	}
	delay(600);
}
