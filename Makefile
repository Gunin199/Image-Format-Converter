app: main.o Converter.o gdfConverter.o ppmConverter.o ErrorHandler.o Application.o txtConverter.o csvConverter.o tools.o
	g++ main.o Converter.o gdfConverter.o ppmConverter.o ErrorHandler.o Application.o tools.o txtConverter.o csvConverter.o -o app

main.o: main.cpp
	g++ -c main.cpp

Converter.o: Converter.cpp
	g++ -c Converter.cpp

gdfConverter.o: gdfConverter.cpp
	g++ -c gdfConverter.cpp

ppmConverter.o: ppmConverter.cpp
	g++ -c ppmConverter.cpp

ErrorHandler.o: ErrorHandler.cpp
	g++ -c ErrorHandler.cpp

Application.o: Application.cpp
	g++ -c Application.cpp

txtConverter.o: txtConverter.cpp
	g++ -c txtConverter.cpp

csvConverter.o: csvConverter.cpp
	g++ -c csvConverter.cpp
	
tools.o: tools.cpp
	g++ -c tools.cpp