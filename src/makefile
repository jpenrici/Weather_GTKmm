# Makefile

main : main.o weatherApp.o weatherWindow.o connect.o
	g++ -g -Wall -o WeatherApp main.o weatherApp.o weatherWindow.o connect.o `pkg-config gtkmm-3.0 jsoncpp --cflags --libs` -l curl 

main.o : main.cpp weatherApp.hpp
	g++ -g -Wall -c main.cpp `pkg-config gtkmm-3.0 jsoncpp --cflags --libs`

weatherApp.o : weatherApp.cpp weatherApp.hpp weatherWindow.hpp connect.h
	g++ -g -Wall -c weatherApp.cpp `pkg-config gtkmm-3.0 jsoncpp --cflags --libs`

weatherWindow.o : weatherWindow.cpp weatherWindow.hpp
	g++ -g -Wall -c weatherWindow.cpp `pkg-config gtkmm-3.0 --cflags --libs`

connect.o : connect.c connect.h
	gcc -g -Wall -c connect.c -l curl

test_connect :
	gcc -g -Wall -o test_connect test_connect.c connect.c -l curl

clean :
	rm -f WeatherApp main.o weatherApp.o weatherWindow.o connect.o
	rm -f test_connect