# Makefile for Traffic Simulation application 

OBJS = Arena.o Entity.o TrafficLight.o Vehicle.o Car.o Motorcycle.o Truck.o Traffic_SimulationApp.o Traffic_SimulationMain.o

EXE = TrafficSim

CXX = g++

FILES = ../src ../assets

CFLAGS = -c

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) `wx-config --libs` -no-pie
	
Traffic_SimulationApp.o: Traffic_SimulationApp.cpp Traffic_SimulationApp.h
	$(CXX) $(CFLAGS) Traffic_SimulationApp.cpp `wx-config --cxxflags`
	
Traffic_SimulationMain.o: Traffic_SimulationMain.cpp Traffic_SimulationMain.h Arena.h Car.h Entity.h Motorcycle.h TrafficLight.h Truck.h Vehicle.h wx_pch.h
	$(CXX) $(CFLAGS) Traffic_SimulationMain.cpp `wx-config --cxxflags`
	
Arena.o: Arena.cpp Arena.h
	$(CXX) $(CFLAGS) Arena.cpp `wx-config --cxxflags`

Entity.o: Entity.cpp Entity.h
	$(CXX) $(CFLAGS) Entity.cpp `wx-config --cxxflags`
	
TrafficLight.o: TrafficLight.cpp TrafficLight.h Entity.h
	$(CXX) $(CFLAGS) TrafficLight.cpp `wx-config --cxxflags`
	
Vehicle.o: Vehicle.cpp Vehicle.h Entity.h
	$(CXX) $(CFLAGS) Vehicle.cpp `wx-config --cxxflags`
	
Car.o: Car.cpp Car.h Vehicle.h
	$(CXX) $(CFLAGS) Car.cpp `wx-config --cxxflags`
	
Motorcycle.o: Motorcycle.cpp Motorcycle.h Vehicle.h
	$(CXX) $(CFLAGS) Motorcycle.cpp `wx-config --cxxflags`
	
Truck.o: Truck.cpp Truck.h Vehicle.h
	$(CXX) $(CFLAGS) Truck.cpp `wx-config --cxxflags`

clean:
	\rm *.o  $(EXE)
tar:
	tar cfv $(EXE).tar $(FILES)

