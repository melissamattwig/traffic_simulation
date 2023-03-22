all: traffic_simulation.exe

CarClass.o: CarClass.cpp CarClass.h
	g++ -std=c++98 -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h
	g++ -std=c++98 -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h random.h EventClass.h CarClass.h SortedListClass.h FIFOQueueClass.h 
	g++ -std=c++98 -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

random.o: random.cpp random.h
	g++ -std=c++98 -Wall -c random.cpp -o random.o

traffic.o: traffic.cpp LinkedNodeClass.h SortedListClass.h
	g++ -std=c++98 -Wall -c traffic.cpp -o traffic.o

traffic_simulation.exe: traffic.o CarClass.o IntersectionSimulationClass.o EventClass.o random.o
	g++ -std=c++98 -Wall traffic.o IntersectionSimulationClass.o EventClass.o random.o CarClass.o -o traffic_simulation.exe

clean:
	rm -rf *.o *.exe
