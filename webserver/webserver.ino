#include <SPI.h>
#include <Ethernet.h>
// #include <ICMPPing.h>

#define RELAY_PORT		PD6		
#define LINE_MAX		200

#define MAC_ADDRESS		0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
#define SELF_ADDRESS	169,254,25,141
#define SERVER_ADDRESS	169,254,25,140
// #define SELF_ADDRESS	192, 168, 0, 150
// #define SERVER_ADDRESS	192, 168, 0, 50

#define SERVER_ONLINE	0
#define SERVER_OFFLINE	1

EthernetServer	server(80);
EthernetClient	client;

// SOCKET pingSocket = 0;
// ICMPPing ping(pingSocket, (uint16_t)random(0, 255));

// short			server_status = 0;

// void		ping_server()
// {
// 	ICMPEchoReply echoReply = ping(IPAddress(SERVER_ADDRESS), 4);
// 	if (echoReply.status == SUCCESS)
// 	{
// 		Serial.println("Server is Online");
// 		server_status = SERVER_ONLINE;
// 	}
//  	else
//  	{
// 		Serial.println("Server is Offline");
// 		server_status = SERVER_OFFLINE;
// 	}
// }

void	setup()
{
	byte mac[] = {MAC_ADDRESS};

	Serial.begin(9600);
	Serial.println("Serial communication started");
	Ethernet.begin(mac, IPAddress(SELF_ADDRESS));
	server.begin();
	Serial.print("Server is online at : ");
	Serial.println(Ethernet.localIP());
}

void	parse_line(String line)
{
	if (line.indexOf("?short") > 0)
	{
		digitalWrite(RELAY_PORT, HIGH);
		delay(1000);
		digitalWrite(RELAY_PORT, LOW);
	}
	else if (line.indexOf("?long") > 0)
	{
		digitalWrite(RELAY_PORT, HIGH);
		delay(5000);
		digitalWrite(RELAY_PORT, LOW);
	}
	else if (line.indexOf("?ping") > 0)
	{
		// ping_server();
	}
}

// void	show_status()
// {
// 	if (server_status == SERVER_ONLINE)
// 	{
// 		client.println();
// 	}
// 	else
// 	{
// 		client.println();
// 	}
// }

void	send_css()
{
	client.println("/* Add your styles here */");
	client.println("body{");
	client.println("  background-color:#f0ffff;");
	client.println("}");
	client.println("a {");
	client.println("	border-radius:12px 0 12px 0;");
	client.println("	background: #f5f5f5;");
	client.println("	border:none;");
	client.println("	color:#555;");
	client.println("	font:bold 12px Verdana;");
	client.println("	padding:6px 0 6px 0;");
	client.println("	box-shadow:1px 1px 3px #999;");
	client.println("  text-align: center;");
	client.println("  display: block;");
	client.println("  margin: auto;");
	client.println("  margin-bottom: 3%;");
	client.println("  margin-top: 3%;");
	client.println("}");
	client.println(".status{");
	client.println("  text-align: center;");
	client.println("  background: green;");
	client.println("  border-radius: 50px 50px;");
	client.println("  margin-right: 20%;");
	client.println("  margin-left: 20%;");
	client.println("  font-size: 10vh;");
	client.println("  font-family:monospace;");
	client.println("}");
	client.println(".button_ping{");
	client.println("  background: chocolate;");
	client.println("  margin-left: 40%;");
	client.println("  margin-right: 40%;");
	client.println("  border-radius: 0px;");
	client.println("}");
	client.println(".button_short{");
	client.println("  background: lightblue;");
	client.println("}");
	client.println(".button_long{");
	client.println("  background: mediumslateblue;");
	client.println("}");
	client.println("h1{");
	client.println("  text-align: center;");
	client.println("  font-size: 5vw;");
	client.println("}");
}

void	send_html()
{
	client.println("<!doctype html>");
	client.println("<html>");
	client.println("  <head>");
	client.println("    <title>Okalmhost</title>");
	client.println("  </head>");
	client.println("  <body>");
	client.println("    <br>");
	client.println("    <div class='status'>Online</div>");
	client.println("    <br>");
	client.println("    <a class='button_ping' href='ping'>PING</a>");
	client.println("    <a class='button_short' href='short'>Short</a>");
	client.println("    <a class='button_long' href='long'>Long</a>");
	client.println("  </body>");
	client.println("</html>");
}

void	send_page()
{
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html");
	client.println();
	send_css();
	send_html();
}

int		read_request()
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
				send_page();
				return (0);
			}
		}
	}
	return (0);
}

void	loop()
{
	if ((client = server.available()))
	{
		Serial.println("New client is here");
		read_request();
		delay(100);
		client.stop();
		Serial.println("Client disconnected");
	}
}
