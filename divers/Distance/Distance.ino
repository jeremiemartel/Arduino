/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.ino                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 21:03:25 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/17 21:15:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define OUT_PIN     A0
#define TRIG_PIN    A1
#define ECHO_PIN    A2

const unsigned int		MAX_RANGE = 2;
const float				SOUND_SPEED = 340.0;
const unsigned int		PULSE_NBR = 10;
const unsigned int		PULSE_DURATION = 2;
const float				TIMEOUT = 2 * MAX_RANGE / SOUND_SPEED;
const unsigned int		TWO_MEASURE_DELAY = 2 * TIMEOUT;

void	setup_lcd();
void	setup_serial();
void	setup_pin();

void	setup()
{
	setup_serial();
	setup_lcd();
	setup_pin();
}

int		measure();
void	update_limit();

long	time_measured;
int		dist_cm;

void	loop()
{
	//update_limit();
	time_measured = measure();
	dist_cm = (time_measured / 2) * SOUND_SPEED * 10;
}

void	setup_lcd()
{
    lcd.begin(16, 2);
    lcd.print("Welcome");
    delay(1000);
    lcd.clear();
}

void	setup_serial()
{
    Serial.begin(9600);
    Serial.println("Serial link started");
}

void	setup_pin()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void	update_limit()
{
	if (Serial.available())
    {
        c = Serial.read();
		if (c >= '0' && c <= '9')
		{
			lim = (c - '0') * 10;
			Serial.print("Limit changed to : ");Serial.println(lim);
		}
    }
}

int		measure()
{
	int		i = 0;
	int		average = 0;
	int		val;

	digitalWrite(LED_BUILTIN, HIGH);
	while (i < PULSE_NBR)
	{
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(PULSE_DURATION);
        digitalWrite(TRIG_PIN, LOW);
		val = pulseIn(ECHO_PIN, HIGH, TIMEOUT);
		delay(TWO_MEASURE_DELAY);
		average += val;
		i++;
	}
	digitalWrite(LED_BUILTIN, LOW);
	return (average / i);
}
