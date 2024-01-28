
// Created by Alex on 2024-01-24.

#include <iostream>

float averageElevatorPeople = 1.9;

typedef float DataType;
typedef int DataType2;
//TODO add a list that tracks the number of times each floor was pressed from the inside and out of the elevator
//NOW CREATE A LIST with the number of times each floor was pressed.

struct Node1 {
    DataType2 outside;
    DataType2 inside;
    Node1 *back;
    Node1 *next;

    Node1(): inside(0), outside(0), back(nullptr), next(nullptr) {};
    Node1(int x, int y): outside(x), inside(y), back(nullptr), next(nullptr) {};
};

class FloorsList {
private:
    Node1 *head = nullptr;
public:
    void insert(int value1, int value2, int position) {
        Node1 *newNode;
        newNode = new Node1(value1, value2);
        if(position == 0) {
            newNode->next = head;
            head = newNode;
            return;
        }
        else {
            Node1 *previous = head;
            Node1 *forward = head->next;
            while(position > 1) {
                if(forward == nullptr)
                    break;
                previous = forward; //can do previous->next
                forward = forward->next;
                position--;
            }
            newNode->back = previous;
            newNode->next = forward;
            previous->next = newNode;
            if(forward != nullptr)
                forward->back = newNode;
        }
    }
    void add(int value1, int value2, int position) {
        Node1 *newNode = head;
        while(position > 0) {
            newNode = newNode->next;
            position--;
        }
        newNode->outside += value1;
        newNode->inside += value2;
    }
    void print() {
        int floor = 1;
        Node1 *newNode;
        newNode = head;
        while(newNode != nullptr) {
            std::cout<<"The number of requests to leave floor "<<floor<<" was: "<< newNode->outside<<std::endl;
            std::cout<<"The number of requests to go to floor "<<floor<<" from inside the elevator is: "<< newNode->inside<<std::endl;
            newNode = newNode->next;
            floor++;
        }
    }
};

struct Node {
    DataType data;
    Node* next;

    Node(): data(0), next(nullptr) {};
    explicit Node(float x): data(x*averageElevatorPeople), next(nullptr) {};
};

class PeopleList {
private:
    Node *head = nullptr;
public:
    void insert(DataType value, int position) { //INSERT NOT REPLACE!
        Node *newNode = new Node(value);
        if(position == 0) {
            newNode->next = head;
            head = newNode;
            return; //realistically the original head just gets shoved back.
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
    void add(float value, int position) {
        Node *newNode;
        newNode = head;
        while(position > 0) {
            newNode = newNode->next;
            position--;
        }
        newNode->data += value;
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
    FloorsList buttonsPressed;

    for(int i =0; i < floors; i++) {
        peoplePerFloor.insert(0, i);
        buttonsPressed.insert(0,0, i);
    }

    int floorRequest;

    std::cout<<"which floor do you want to go to?\n";
    std::cin>>floorRequest;

    buttonsPressed.add(1,0,0);
    peoplePerFloor.add(averageElevatorPeople, floorRequest-1);

    //peoplePerFloor.remove(6);

    peoplePerFloor.print();
    buttonsPressed.print();

    return 0;
}