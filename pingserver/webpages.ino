extern short			server_status;
extern EthernetClient	client;

void	send_css(EthernetClient client)
{
	client.println("<style>");
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
	client.println("</style>");
}

void	show_status()
{
	client.print("		<div class='status'");
	if (server_status == SERVER_ONLINE)
		client.println("	style='background-color: green'>Online");
	else if (server_status == SERVER_OFFLINE)
		client.println("	style='background-color: red'>Offline");
	client.println("</div>");
}

void	send_html(EthernetClient client)
{
	client.println("<!doctype html>");
	client.println("<html>");
	client.println("  <head>");
	client.println("    <title>Okalmhost</title>");
	show_status();
	client.println("  </head>");
	client.println("  <body>");
	client.println("    <a class='button_short' href='/?short'>Short</a>");
	client.println("    <a class='button_long' href='/?long'>Long</a>");
	client.println("    <a class='button_ping' href='/?ping'>PING</a>");
	client.println("  </body>");
	client.println("</html>");
}

void	send_page(EthernetClient client)
{
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html");
	client.println();
	send_css(client);
	send_html(client);
}
