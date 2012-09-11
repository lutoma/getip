all: getip-fcgi

getip-fcgi: getip.c
	gcc -O3 -Wall -o getip-fcgi getip.c -lfcgi

install: getip-fcgi
	cp getip-fcgi /usr/bin/

clean:
	rm -rf getip-fcgi