#include <iostream>
#include <string>
using namespace std;

class Base {
public:
    static int people_on_base;
    static int vehicles_on_base;
    static double petrol_on_base;
    static double goods_on_base;

    static void showStatus() {
        cout << "People on base: " << people_on_base << endl;
        cout << "Vehicles on base: " << vehicles_on_base << endl;
        cout << "Petrol on base: " << petrol_on_base << " liters" << endl;
        cout << "Goods on base: " << goods_on_base << " tons" << endl;
    }
};

int Base::people_on_base = 0;
int Base::vehicles_on_base = 0;
double Base::petrol_on_base = 1000.0; 
double Base::goods_on_base = 50.0;   

class Vehicle {
protected:
    double petrol_amount; 
    double tank_volume;   
public:
    Vehicle(double petrol, double tank) : petrol_amount(petrol), tank_volume(tank) {}

    virtual double getTankVolume() const {
        return tank_volume;
    }

    virtual double getPetrolAmount() const {
        return petrol_amount;
    }

    virtual void arrive() = 0; 
    virtual bool leave() = 0;
};

class Bus : public Vehicle {
    int people;
    int max_people;
public:
    Bus(int people, int max_people, double petrol, double tank)
        : Vehicle(petrol, tank), people(people), max_people(max_people) {}

    int getPeopleCount() const {
        return people;
    }

    int getMaxPeople() const {
        return max_people;
    }

    void arrive() override {
        Base::people_on_base += people;
        Base::vehicles_on_base++;
        cout << "Bus arrived with " << people << " passengers." << endl;
    }

    bool leave() override {
        if (petrol_amount < tank_volume) {
            cout << "Filling the tank before leaving..." << endl;
            petrol_amount = tank_volume; 
        }
        if (people <= Base::people_on_base) {
            Base::people_on_base -= people;
            Base::vehicles_on_base--;
            cout << "Bus left with " << people << " passengers." << endl;
            return true;
        }
        return false;
    }
};

class Truck : public Vehicle {
    double load;
    double max_load;
public:
    Truck(double load, double max_load, double petrol, double tank)
        : Vehicle(petrol, tank), load(load), max_load(max_load) {}

    double getCurrentLoad() const {
        return load;
    }

    double getMaxLoad() const {
        return max_load;
    }

    void arrive() override {
        Base::goods_on_base += load;
        Base::vehicles_on_base++;
        cout << "Truck arrived with " << load << " tons of goods." << endl;
    }

    bool leave() override {
        if (petrol_amount < tank_volume) {
            cout << "Filling the tank before leaving..." << endl;
            petrol_amount = tank_volume; 
        }
        if (load <= Base::goods_on_base) {
            Base::goods_on_base -= load;
            Base::vehicles_on_base--;
            cout << "Truck left with " << load << " tons of goods." << endl;
            return true;
        }
        return false;
    }
};

int main() {
    Bus bus(30, 50, 50, 100);
    Truck truck(10, 20, 30, 100);

    bus.arrive();
    truck.arrive();
    Base::showStatus();

    bus.leave();
    truck.leave();
    Base::showStatus();

    return 0;
}
