#include <SPI.h>
#include <Ethernet.h>
#include <ICMPPing.h>

#include "webpages.h"

#define RELAY_PORT		PD6		
#define LED_PORT		13

#define LINE_MAX		200

#define SERVER_ONLINE	0
#define SERVER_OFFLINE	1

byte		mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress	card_ip(169,254,108,150);
IPAddress	server_ip(169,254,108,125);

EthernetServer	server(80);
EthernetClient	client;

SOCKET		pingSocket = 0;
ICMPPing	ping(pingSocket, (uint16_t)random(0, 255));

short		server_status = SERVER_OFFLINE;
char 		buffer [256];

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
	ping_server();
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
	else if (line.indexOf("?ping") > 0)
	{
		ping_server();
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

void	ping_server()
{
	ICMPEchoReply echoReply = ping(server_ip, 4);
	if (echoReply.status == SUCCESS)
	{
		sprintf(buffer,
			"Reply[%d] from: %d.%d.%d.%d: bytes=%d time=%ldms TTL=%d",
			echoReply.data.seq,
			echoReply.addr[0],
			echoReply.addr[1],
			echoReply.addr[2],
			echoReply.addr[3],
			REQ_DATASIZE,
			millis() - echoReply.data.time,
			echoReply.ttl);
		server_status = SERVER_ONLINE;
	}
	else
	{
		sprintf(buffer, "Echo request failed : %d", echoReply.status);
		server_status = SERVER_OFFLINE;
	}
	Serial.println(buffer);
	return ;
}

void	loop()
{
	int		i;

	if ((client = server.available()))
	{
		Serial.println("New client is here");
		read_request(client);
		delay(100);
		client.stop();
		Serial.println("Client disconnected");
		i = 0;
	}
	else if (i == 600)
	{
		ping_server();
		i = 0;
	}
	else
	{
		delay(100);
	}
	i++;
}
