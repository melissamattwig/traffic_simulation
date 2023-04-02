# Traffic Simulation
Event-driven simulation of traffic flow through a 4-way intersection that is managed by a traffic light

## Table of contents
* [General info](#general-info)
* [Skills gained](#skills-gained)
* [Technologies](#technologies)
* [Setup](#setup)
* [Citations](#citations)

## General info
This project will involve implementation of an event-driven simulation of traffic flow through a 4-way intersection that is managed by a traffic light. The simulation includes cars arriving at the intersection traveling in all four directions, as well as the light changing state throughout the simulation. After the simulation is complete, there is an output with very minimal statistics about the traffic flow.

## Skills gained
* Use of Friend Functions / Classes
* Use of C++ "string" Type, pointers, and overloaded operators
* Use of makefile and multiple source code files
* Implementation of first-in-first-out queue and last-in-first-out stack classes

## Technologies
Project is created with:
* Visual Studio Code version 1.76.2
* C++98
	
## Setup
To run this project:

```
$ cd ../traffic_simulation
$ make
$ g++ -std=c++98 -Wall traffic.o IntersectionSimulationClass.o EventClass.o random.o CarClass.o -o traffic_simulation.exe
$ valgrind --leak-check=full ./traffic_simulation.exe
```

## Citations
Traffic simulation gif retrieved from: https://github.com/scmilburn/traffic_simulator/blob/master/traffic.gif
