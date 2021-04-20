# Makefile for Traffic Simulation application 

OBJS = Arena.o Entity.o TrafficLight.o Vehicle.o Car.o Motorcycle.o Truck.o Traffic_SimulationApp.o Traffic_SimulationMain.o

EXE = TrafficSim

CXX = g++

FILES = Arena.cpp Entity.h simend.png Truck.cpp Arena.h grass_img.jpg Truck.h bike.png grassmedian_img.jpg truck.png car2_img.png green.png TrafficLight.cpp Vehicle.cpp Car.cpp grey.png TrafficLight.h Vehicle.h Car.h Motorcycle.cpp Traffic_SimulationApp.cpp wx_pch.h crash.png Motorcycle.h Traffic_SimulationApp.h yellow.png endscreen_img.jpg NEWSTART.jpg Traffic_SimulationMain.cpp Entity.cpp red.png Traffic_SimulationMain.h Makefile

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXE) `wx-config --libs` -no-pie
	
Traffic_SimulationApp.o: Traffic_SimulationApp.cpp Traffic_SimulationApp.h
	$(CXX) -c Traffic_SimulationApp.cpp `wx-config --cxxflags`
	
Traffic_SimulationMain.o: Traffic_SimulationMain.cpp Traffic_SimulationMain.h Arena.h Car.h Entity.h Motorcycle.h TrafficLight.h Truck.h Vehicle.h wx_pch.h
	$(CXX) -c Traffic_SimulationMain.cpp `wx-config --cxxflags`
	
Arena.o: Arena.cpp Arena.h
	$(CXX) -c Arena.cpp `wx-config --cxxflags`

Entity.o: Entity.cpp Entity.h
	$(CXX) -c Entity.cpp `wx-config --cxxflags`
	
TrafficLight.o: TrafficLight.cpp TrafficLight.h Entity.h
	$(CXX) -c TrafficLight.cpp `wx-config --cxxflags`
	
Vehicle.o: Vehicle.cpp Vehicle.h Entity.h
	$(CXX) -c Vehicle.cpp `wx-config --cxxflags`
	
Car.o: Car.cpp Car.h Vehicle.h
	$(CXX) -c Car.cpp `wx-config --cxxflags`
	
Motorcycle.o: Motorcycle.cpp Motorcycle.h Vehicle.h
	$(CXX) -c Motorcycle.cpp `wx-config --cxxflags`
	
Truck.o: Truck.cpp Truck.h Vehicle.h
	$(CXX) -c Truck.cpp `wx-config --cxxflags`

clean:
	\rm *.o $(EXE)
tar:
	tar cfv $(EXE).tar $(FILES)

