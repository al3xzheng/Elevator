//
// Created by Alex on 2024-01-24.

#include <iostream>
//incorporate pointers and a linked list, can use a linked list to store the data of the floors visited.

//int whichOneComes ()
//input a linked list of elevators and with data of current floor and requested floors.

//assume and average of 1.9 people in an elevator per trip.

float averageElevatorPeople = 1.9;

typedef float DataType;

//NOW CREATE A LIST with the number of times each floor was pressed.

struct Node {
    DataType people;
    Node* next;

    Node(): people(0), next(nullptr) {};
    explicit Node(float x): people(x*averageElevatorPeople), next(nullptr) {};
};

class LinkedList {
private:
    Node *head = nullptr;
public:
    void insert(DataType value, int position) { //INSERT NOT REPLACE!
        Node *newNode = new Node(value);
        if(position == 0) {
            newNode->next = head;
            head = newNode; //fix this when there are things after.
            return;
        }
        else {
            Node *previous = head;
            Node *current = head->next;
            while(position > 1) { //!position-- to reverse a linked list except the 2nd element will get shoved backwards due to if statement
                previous = current;
                current = current->next;
                if (current == nullptr)
                    break;
                position--;
            }
            previous->next = newNode;
            newNode->next = current;
            return;
        }
    }
    void replace(DataType value, int position) {
        Node *newNode;
        newNode = head;
        while(position > 0) {
            newNode = newNode->next;
            position--;
            if(newNode->next == nullptr)
                break;
        }
        newNode->people = value;
    }
    //void remove(int position);
    void print() {
        Node *newNode;
        newNode = head;
        while(newNode != nullptr) {
            std::cout<<newNode->people<<std::endl;
            newNode = newNode->next;
        }
    }
};


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
        int requestedFloor{};
        int currentFloor{};
        std::string direction;
        int numberFloors;
        std::string system = "STM32L4";
public:
    explicit Elevator(int constructFloors){
        numberFloors = constructFloors;
    }

    void enter (int people) {
        passengers +=people;
    }

    void leave (int people) {
        passengers -= people;
    }

    void request (int floorRequest, int currentFloors) {

        if(floorRequest < 1 || floorRequest > numberFloors) {
            throw std::invalid_argument("floor DNE");
        }
        requestedFloor = floorRequest;
        //std::cout<<"Elevator for your trip to floor: "<<floorRequest<<" is coming shortly";
    }
};

int main () {

    int floors;
    std::cout<<"How many floors does your building have?\n";
    std::cin>>floors;

    Elevator elevator(floors);

    LinkedList peoplePerFloor;

    for(int i =0; i < floors; i++) {
        peoplePerFloor.insert(0, i);
    }

    int floorRequest;

    std::cout<<"which floor do you want to go to?\n";
    std::cin>>floorRequest;

    peoplePerFloor.replace(averageElevatorPeople, floorRequest-1);

    peoplePerFloor.print();

//    try {
//        elevator.request(1, 2);
//    } catch (const std::exception& e) {
//        std::cerr << e.what() << std::endl;
//    }






    return 0;
}