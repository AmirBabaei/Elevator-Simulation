// Lab 16 , Elevator.cpp
// Programmer: Amir Babaei
// Editor(s) used: XCode
// Compiler(s) used: g++

#include "Elevator.h"
#include <cstdlib>

using std::abs;
class Floor;
int Elevator::elevatorID=0;
Elevator::Elevator(const int c, const int s, const Floor& f):ID(elevatorID),capacity(c),speed(s),toFloor(0)
{
  setIdle();
  location = f.getLocation();
  openDoor();
}
bool Elevator::isNearDestination()const
{
  if(hasADestination())
  {
    if(abs(toFloor->getLocation()-location)<=speed||abs(toFloor->getLocation()-abs(location))<=speed)
      return true;
    else
      return false;
  }
  else
    return false;
}
void Elevator::moveToDestinationFloor()
{
  location=toFloor->getLocation();
}
ostream& operator<<(ostream& out, const Elevator& El)
{
  out<< El.rider.size() << " riders in elevator. ";
  if(El.location>0)
    out<<"Elevator is: "<<abs(El.location)<<" inches above ground, ";
  else if(El.location<0)
    out<<"Elevator is: "<<abs(El.location)<<" inches below ground, ";
  else
    out<<"Ground Floor, ";
  if(El.isDirectionDown())
    out<<"Going Down, ";
  else if(El.isDirectionUp())
    out<<"Going Up, ";
  else
    out<<"Idle, ";
  out<<((El.isDoorOpen())? "Door: open":"Door: closed");
  return out;
}
vector<Rider> Elevator::removeRidersForDestinationFloor()
{
  // create empty vector of removed riders to be used as return value
  vector<Rider> removedRiders;
  // if elevator has any riders
  if(rider.size()!=0)
  {
    // create an empty vector for riders who remain on elevator
    vector<Rider> remainingRiders;
    // traverse vector of current riders
    for(int i=0;i<rider.size();i++)
    {
      if(rider[i].getDestination().getLocation() == toFloor->getLocation())// if a rider's destination floor is same as elevator's destination...
        removedRiders.push_back(rider[i]);// add rider to vector of removed riders
      else
        remainingRiders.push_back(rider[i]);  // add rider to vector of remaining riders
    }
    rider=remainingRiders;  // reassign elevator rider vector to vector of remaining riders
  }
  return removedRiders;  // return vector of removed riders
}

void Elevator::addRiders(const vector<Rider>& riders)
{
  // traverse the parameter vector
  for(int i=0;i<riders.size();i++)
  {
    if(rider.size()< capacity)  // if there is still room on the elevator
      rider.push_back(riders[i]);  // add the rider to the elevator's rider vector
  }
}

void Elevator::setDestinationBasedOnRiders()
{
  // if there are no riders on the elevator
  if(rider.size()==0)
    return;// exit the function
    
  // set elevator's destination to the zeroth Rider's destination
  const_cast<const Floor*&>(toFloor) = &rider[0].getDestination();
  // traverse the vector of elevator riders
  for(int i=0;i<rider.size();i++)
  {
    // get the absolute value of the distance from the elevator to the rider's destination floor
    int ridDest = abs(rider[i].getDestination().getLocation()-location);
    // get the absolute value of the distance from the elevator to the elevator's destination floor
    int elDest = abs(toFloor->getLocation()-location);
    // if closer to the rider's destination than to the elevator's destination
    if(ridDest<elDest)
      const_cast<const Floor*&>(toFloor) = &rider[i].getDestination();// set elevator's destination to the rider's destination
  }
}
