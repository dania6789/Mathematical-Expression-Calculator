mycalc: maincalc.o myfunctions.o
	g++ maincalc.o myfunctions.o -o mycalc
maincalc.o: maincalc.cpp
	g++ -c maincalc.cpp
myfunctions.o: myfunctions.cpp myfunctions.h
	g++ -c myfunctions.cpp
clean:
	rm *.o mycalc

