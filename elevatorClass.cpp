
// Created by Alex on 2024-01-24.

#include <iostream>

float averageElevatorPeople = 1.9;

typedef float DataType;
//TODO add a list that tracks the number of times each floor was pressed from the inside and out of the elevator
//NOW CREATE A LIST with the number of times each floor was pressed.

struct Node {
    DataType data;
    Node* next;

    Node(): data(0), next(nullptr) {};
    explicit Node(float x): data(x*averageElevatorPeople), next(nullptr) {};
};

class FloorsList {
private:
    Node *head = nullptr;
public:
    void insert (DataType value, int position) {

    }
};

class PeopleList {
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
            if(newNode->next == nullptr)
                return;
            newNode = newNode->next;
            position--;
        }
        newNode->data = value;
    }
    void remove(int position) {
        Node *newNode;
        if(position == 0) {
            newNode = head->next;
            delete head;
            head = newNode;
            return;
        }
        Node *previous;
        Node *forward;
        previous = head;
        forward = head->next->next;
        while(position > 1) {
            previous = previous->next;
            forward = forward->next;
            position--;
        }
        delete previous->next;
        previous->next = forward;
    }
    void print() {
        Node *newNode;
        newNode = head;
        while(newNode != nullptr) {
            std::cout<<newNode->data<<std::endl;
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

    PeopleList peoplePerFloor;

    for(int i =0; i < floors; i++) {
        peoplePerFloor.insert(0, i);
    }

    int floorRequest;

    std::cout<<"which floor do you want to go to?\n";
    std::cin>>floorRequest;

    peoplePerFloor.replace(averageElevatorPeople, floorRequest-1);

    peoplePerFloor.remove(6);

    peoplePerFloor.print();

    return 0;
}