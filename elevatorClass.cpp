//
// Created by Alex on 2024-01-24.

#include <iostream>
//incorporate pointers and a linked list, can use a linked list to store the data of the floors visited.

//int whichOneComes ()
//input a linked list of elevators and with data of current floor and requested floors.

//assume and average of 1.9 people in an elevator per trip.

float averageElevatorPeople = 1.9;

typedef float DataType;

struct Node {
    DataType peoplePerFloor;
    Node* next;

    Node(): peoplePerFloor(0), next(nullptr) {};
    explicit Node(float x): peoplePerFloor(x*averageElevatorPeople), next(nullptr) {};
};

class LinkedList {
private:
    Node *head = nullptr;
public:
    void insert(DataType value, int position) {
        Node *newNode = new Node(value);
        if(position == 0) {
            if(head == nullptr) {
                head = newNode;
                delete newNode;
                newNode = nullptr;
                return;
            }
            else {
                newNode->next = head;
                head = newNode;
                return;
            }
        }
        else {
            Node *previous = head;
            Node* forward = head->next;
            while(!position--) {
                if (forward == nullptr)
                    break;
                previous = forward;
                forward = forward->next;
                position--;
            }
            previous = newNode;
            newNode->next = forward;
            return;
        }
    }
    void replace(int position, DataType value) {
        Node *newNode = new Node(value);
        newNode = head;
        while(!position--) {
            newNode = newNode->next;
            position--;
            if(newNode->next == nullptr)
                return;
        }
        newNode->peoplePerFloor = value;
        newNode = nullptr;
    }
    //void remove(int position);
    void print() {
        Node *newNode = new Node();
        newNode = head;
        while(newNode != nullptr) {
            std::cout<<newNode->peoplePerFloor<<std::endl;
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
        std::cout<<"Created an elevator in a building with 10 floors."<<std::endl;
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
        std::cout<<"Elevator for your trip to floor: "<<floorRequest<<" is coming shortly";
    }


};

int main () {

    LinkedList peoplePerFloor;

    std::cout<<"hello";

    peoplePerFloor.insert(0, 0);

    peoplePerFloor.print();


    Elevator elevator(10);

    try {
        elevator.request(1, 2);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }






    return 0;
}