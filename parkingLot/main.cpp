#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
// #include <pair>

using namespace std;

enum VehicleType { CarType, MotorcycleType, TruckType };


class Vehicle {
protected:
    string ID;
    VehicleType type;
    int size;
public:
    Vehicle(const string &plate, VehicleType vType) : ID(plate), type(vType){
        // switch (vType) {
        //     case Car: this->size = 3; break;
        //     case Motorcycle: this->size = 1; break;
        //     case Truck: this->size = 5; break;
        //     default: break;
        // }

    }
    // 获取车辆类型
    VehicleType getType() const {
        return this->type;
    }

    // 获取车牌号
    string getLicensePlate() const {
        return ID;
    }

    int getSize() const {
        return size;
    }

};

class Car: public Vehicle {
public:
    Car(const string &plate) :Vehicle(plate, CarType) {
        this->size = 3;
    }
};

class Truck: public Vehicle {
public:
    Truck(const string &plate) :Vehicle(plate, TruckType) {
        this->size = 5;
    }
};

class Motorcycle: public Vehicle {
public:
    Motorcycle(const string &plate) :Vehicle(plate, MotorcycleType) {
        this->size = 1;
    }
};


class ParkingLot {
private:
    unordered_map<string,pair<int,int>> ID_map;
    vector<bool> parkVector;
    const int size;
    int capacity;

public:
    ParkingLot(const int &s): size(s), capacity(s) {
        showInfo();
        parkVector.assign(size,false);
    }

    int parkVehicle(Vehicle &v){

        if(capacity > v.getSize()) {

            for(int i=0; i<size-v.getSize(); i++) {

                if(parkVector[i] == false) {
                    bool canPark = true;
                    for(int j=1; j<v.getSize(); j++) {
                        if(parkVector[i+j] != false) {
                            canPark = false;
                            break;
                        }
                    }
                    // Can park
                    if(canPark) {
                        ID_map[v.getLicensePlate()] = {i, v.getSize()};
                        for(int j=0; j<v.getSize(); j++) {
                            parkVector[i + j] = true;
                        }
                        cout <<v.getLicensePlate()<< "Parked from " << i << " to "<< i+v.getSize()-1  <<endl;
                        capacity -= v.getSize();
                        return i;
                    }
                }
            }
            cout<< "Parking lot is full. Parking failed. "<<endl;


        }
        else {
            cout<< "Parking lot is full. Parking failed. "<<endl;
        }

        return -1;


    }

    void outVehicle(string ID){

        auto it = ID_map.find(ID);
        if(it == ID_map.end()) {
            return;
        }


        int pos = it->second.first; // 起始位置
        int vSize = it->second.second; // 车辆大小

        for(int i = 0; i<vSize; i++) {
            parkVector[pos + i] = false;
        }

        capacity += vSize; // 恢复容量
        ID_map.erase(it); // 从 map 中移除车辆信息
        cout << "Vehicle with ID: " << ID << " has exited the parking lot." << endl;

    }


    int getVehiclePosition(string ID) {
        auto it = ID_map.find(ID);
        if(it != ID_map.end()) {
            return it->second.first;
        }
        else {
            cout<< "No such vehicle"<<endl;
            return -1;
        }
    }

    void showInfo() {
        cout<< "Parking lot max size : "<< size << endl;
        cout<< "Parking lot capacity now : "<< capacity << endl;
    }


};

int main() {
    std::cout << "Hello, World!" << std::endl;
    ParkingLot lot(10); // Parking lot with a capacity of 10 slots

    Car car1("CAR123");
    Motorcycle motor1("MOTO123");
    Truck truck1("TRUCK123");

    lot.parkVehicle(car1);
    // lot.parkVehicle(motor1);
    lot.parkVehicle(truck1);



    lot.showInfo();

    lot.outVehicle("CAR123");

    lot.showInfo();
    // lot.showInfo();
    return 0;
}
