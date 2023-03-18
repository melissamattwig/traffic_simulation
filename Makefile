all: proj5.exe

CarClass.o: CarClass.cpp CarClass.h
	g++ -std=c++98 -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h
	g++ -std=c++98 -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h random.h EventClass.h CarClass.h SortedListClass.h FIFOQueueClass.h 
	g++ -std=c++98 -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

random.o: random.cpp random.h
	g++ -std=c++98 -Wall -c random.cpp -o random.o

project5.o: project5.cpp LinkedNodeClass.h SortedListClass.h
	g++ -std=c++98 -Wall -c project5.cpp -o project5.o

proj5.exe: project5.o CarClass.o IntersectionSimulationClass.o EventClass.o random.o
	g++ -std=c++98 -Wall project5.o IntersectionSimulationClass.o EventClass.o random.o CarClass.o -o proj5.exe

clean:
	rm -rf *.o *.exe