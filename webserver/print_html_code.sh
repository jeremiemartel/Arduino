#!/bin/bash

css="lib/style.css"
html="index.html"

IFS="
"

function show_css()
{
	echo "void	send_css()"
	echo "{"
	for line in `cat $css` ; do 
		echo -n "	client.println(\""
		echo -n $line
		echo "\");"
	done
	echo "}"
}

function show_html()
{
	echo "void	send_html()"
	echo "{"
	for line in `cat $html` ; do 
		echo -n "	client.println(\""
		echo -n "$line"
		echo "\");"
	done
	echo "}"
}

function show_page()
{
	echo "void	send_page()"
	echo "{"
	echo '	client.println("HTTP/1.1 200 OK");'
	echo '	client.println("Content-Type: text/html");'
	echo "	send_css();"
	echo "	send_html();"
	echo "}"
}
show_css
echo ""
show_html
echo ""
show_page
