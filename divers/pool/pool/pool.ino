#define IN_PORT		A0
#define LED_PORT	LED_BUILTIN

#define OPEN_PORT	D0
#define CLOSE_PORT	D1

#define HOUR		3600 * 1000
#define MINUTE		60 * 1000
#define IN_LIMIT	800
#define DELAY_SHORT	500
#define DELAY_OPEN	20 * MINUTE
#define DELAY_CLOSE	4 * HOUR

int			measure;
float		measure_V;
int			delay_ms = 1;

void setup() {
    Serial.begin(9600);
    Serial.println("Serial started");
    Serial.print(HIGH);
    pinMode(IN_PORT, INPUT);
    pinMode(OPEN_PORT, OUTPUT);
    pinMode(CLOSE_PORT, OUTPUT);
    pinMode(LED_PORT, OUTPUT);

    digitalWrite(LED_PORT, LOW);
}

void	open()
{
	Serial.println("Opening");
	digitalWrite(OPEN_PORT, HIGH);
	delay(DELAY_SHORT);
	digitalWrite(OPEN_PORT, LOW);
}

void	close()
{
	Serial.println("Closing");
	digitalWrite(CLOSE_PORT, HIGH);
	delay(DELAY_SHORT);
	digitalWrite(CLOSE_PORT, LOW);
}

void loop()
{
	measure = analogRead(IN_PORT);
	measure_V = measure * (5.0 / 1023);
	Serial.print("measure : ");
	Serial.print(measure_V);
	Serial.print("  (");
	Serial.print(measure);
	Serial.println(")");

	if (measure > IN_LIMIT)
	{
		open();
		delay_ms = DELAY_OPEN;
	}
	else
	{
		close();
		delay_ms = DELAY_CLOSE;
	}
	delay(delay_ms);
}
