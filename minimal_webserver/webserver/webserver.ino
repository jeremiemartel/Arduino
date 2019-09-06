#include <SPI.h>
#include <Ethernet.h>


#define RELAY_PORT		PD6		
#define LED_PORT		13

#define LINE_MAX		200

#define SERVER_ONLINE	0
#define SERVER_OFFLINE	1

byte		mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress	card_ip(169,254,108,150);
IPAddress	server_ip(169,254,108,125);

EthernetServer	server(80);

short			server_status = SERVER_OFFLINE;

void	setup()
{
	Serial.begin(9600);
	Serial.println("Serial communication started");

	Ethernet.begin(mac, card_ip);
	server.begin();
	delay(100);
	Serial.print("Server is online at : ");
	Serial.println(Ethernet.localIP());
	pinMode(RELAY_PORT, OUTPUT);
	pinMode(LED_PORT, OUTPUT);
}

void	parse_line(String line)
{
	Serial.println("request : ");
	Serial.println(line);
	if (line.indexOf("?short") > 0)
	{
		digitalWrite(RELAY_PORT, HIGH);
		digitalWrite(LED_PORT, HIGH);
		delay(1000);
		digitalWrite(RELAY_PORT, LOW);
		digitalWrite(LED_PORT, LOW);
	}
	else if (line.indexOf("?long") > 0)
	{
		digitalWrite(LED_PORT, HIGH);
		digitalWrite(RELAY_PORT, HIGH);
		delay(5000);
		digitalWrite(RELAY_PORT, LOW);
		digitalWrite(LED_PORT, LOW);
	}
}

int		read_request(EthernetClient client)
{
	String	line;
	char	c;

	while (client.connected())
	{
		if (client.available())
		{
			c = client.read();
			if (line.length() < LINE_MAX)
				line += c;
			if (c == '\n')
			{
				parse_line(line);
				send_page(client);
				return (0);
			}
		}
	}
	return (0);
}

void	loop()
{
	EthernetClient	client;

	if ((client = server.available()))
	{
		Serial.println("New client is here");
		read_request(client);
		delay(100);
		client.stop();
		Serial.println("Client disconnected");
	}
}
