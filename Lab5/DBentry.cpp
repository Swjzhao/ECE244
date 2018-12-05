#include "DBentry.h"
#include <iostream>
//string name;
//	unsigned int IPaddress;
//        bool active;
DBentry::DBentry() {
    this->name = "";
    this->IPaddress = 0;
    this->active = false;
}

DBentry::DBentry (string _name, unsigned int _IPaddress, bool _active) {
    this->name = _name;
    this->IPaddress = _IPaddress;
    this->active = _active;
}

// the destructor
DBentry::~DBentry() {

}

// sets the domain name, which we will use as a key.
void DBentry::setName(string _name) {
    this->name = _name;
}

// sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress) {
    this->IPaddress = _IPaddress;
}

// sets whether or not this entry is active.
void DBentry::setActive (bool _active) {
    this->active = _active;
}

// returns the name.
string DBentry::getName() const {
    return this->name;
}

// returns the IPaddress data.
unsigned int DBentry::getIPaddress() const {
    return this->IPaddress;
}

// returns whether or not this entry is active.
bool DBentry::getActive() const {
    return this->active;
}

// prints the entry in the format
// name : IPaddress : active  followed by newline
// active is printed as a string (active or inactive)
ostream& operator<< (ostream& out, const DBentry& rhs) {
    out << rhs.name << " : " << rhs.IPaddress << " : ";
    if(rhs.active)
        out<<"active"<<endl;
    else
        out << "inactive"<<endl;
    return out;
}

//comparison operators

bool operator <(const DBentry& db1, const DBentry& db2) {
    return db1.getName() < db2.getName();
}
bool operator > (const DBentry& db1, const DBentry& db2)
{
    return db1.getName() > db2.getName();
}