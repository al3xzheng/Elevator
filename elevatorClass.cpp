//
// Created by Alex on 2024-01-24.

#include <iostream>
//incorporate pointers and a linked list, can use a linked list to store the data of the floors visited.

//int whichOneComes ()
//input a linked list of elevators and with data of current floor and requested floors.

class Person {
private:
    int currentFloor;
    int desiredFloor;
public:
    Person (int current, int want) {
        currentFloor = current;
        desiredFloor = want;
    }
};

class Elevator {
    private:
        bool doorsOpen = false;
        int passengers = 0;
        int requestedFloor;
        int currentFloor;
        std::string direction;
        int floors;
        std::string system = "STM32L4";
public:
    Elevator(int constructFloors){
        floors = constructFloors;
        std::cout<<"Created an elevator in a building with 10 floors."<<std::endl;
    }

    void enter (int people) {
        passengers +=people;
    }

    void leave (int people) {
        passengers -= people;
    }

    void request (int floorRequest, int currentFloor) {


        if(floorRequest < 1 || floorRequest > floors) {
            throw std::invalid_argument("floor DNE");
        }
        requestedFloor = floorRequest;
        std::cout<<"Elevator for your trip to floor: "<<floorRequest<<" is coming shortly";
    }


};

int main () {


    for(int)
    Elevator elevator(10);

    try {
        elevator.request(1, 2);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }






    return 0;
}
