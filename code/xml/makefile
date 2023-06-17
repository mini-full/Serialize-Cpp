test_xml: test_xml.o tinyxml2.o
	g++ -o test_xml test_xml.o tinyxml2.o

test_xml.o : test_xml.cpp
	g++ -c test_xml.cpp

tinyxml2.o : tinyxml2.cpp
	g++ -c tinyxml2.cpp

clean:
	del test_xml.o test_xml.exe *.data *.xml -r