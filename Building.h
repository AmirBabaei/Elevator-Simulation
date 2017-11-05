// Lab 16 , Rider.h
// Programmer: Amir Babaei
// Editor(s) used: XCode
// Compiler(s) used: g++
#ifndef Lab_15_Building_h
#define Lab_15_Building_h

#include "Elevator.h"
#include "Floor.h"

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

class Building
{
  int time;
  vector<Floor*> floor;
  vector<Elevator*> elevator;
public:
  Building();
  ~Building();
  Building& step(int);
  int getFloorCount() const{return floor.size();} // return #of floors in the vector of Floor*'s
  int getElevatorCount() const{return elevator.size();}// return #of elevators in the vector of Elevator*'s
  const Floor& getFloor(int index) const{return *floor[index];} // return a reference to the "indexth" floor
  const Elevator& getElevator(int index) const{return *elevator[index];} // return a reference to the "indexth" elevator
  
  friend ostream& operator<<(ostream&, const Building&);
};
#endif


