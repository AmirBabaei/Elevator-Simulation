// Lab 16 , Rider.h
// Programmer: Amir Babaei
// Editor(s) used: XCode
// Compiler(s) used: g++

#include "Building.h"
#include "Floor.h"
#include "Rider.h"
#include "Elevator.h"

#include <iostream>
using std::ostream;
using std::endl;
using std::cout;

#include <vector>
using std::vector;

void getDifferentInts(int , int& , int& );

Building::Building()
{
  time=0;
  
  floor.push_back(new Floor(0,"First floor"));
  floor.push_back(new Floor(100,"Second floor"));
  floor.push_back(new Floor(200,"Third floor"));
  floor.push_back(new Floor(300,"Fourth floor"));
  floor.push_back(new Floor(400,"Fifth floor"));
  elevator.push_back(new Elevator(12,20,*floor[0]));
  elevator.push_back(new Elevator(15,10,*floor[1]));
  elevator.push_back(new Elevator(12,20,*floor[2]));
  elevator.push_back(new Elevator(12,20,*floor[3]));
  elevator.push_back(new Elevator(12,20,*floor[1]));
  elevator.push_back(new Elevator(12,20,*floor[1]));
  
}
Building::~Building()
{
  for(int i=0; i<floor.size();i++)
    delete floor[i];
  for(int i=0; i<elevator.size();i++)
    delete elevator[i];
}
ostream& operator<<(ostream& out, const Building& b)
{
  out<< "Lab 15 , Programmer: Amir Babaei\nEditor(s) used: XCode\nCompiler(s) used: g++\n";
  out<<"\n\nTime= "<< b.time << endl;
  for(int i=0; i<(b.elevator).size();i++)
    out<<*(b.elevator[i])<<endl;
  for(int i=0; i<(b.floor).size();i++)
  {
    if((b.floor[i])->hasRidersWaiting())
    out<< *(b.floor[i])<<endl;
  }
  
  return out;
}
Building& Building::step(int r)
{
  for(int i=0; i< r;i++)
  {
    // create a rider with randomly selected from- and to-floors (where from- and to- are not the same!) [1]
    int a,b;
    getDifferentInts(getFloorCount(),a,b);
    // tell the from-floor to add this rider [1]
    floor[a]->addNewRider(Rider(*floor[b]));
  }
  
  for(int e=0;e<getElevatorCount();e++)
  {
    // if elevator door is closed (move up or down) [3]
    if(!(elevator[e]->isDoorOpen()))
    {
      // if not near enough to destination to reach it in this time step, continue moving [3]
      if(!(elevator[e]->isNearDestination()))
      {
        // if elevator direction is up, move up [3]
        if(elevator[e]->isDirectionUp()) elevator[e]->moveUp();
        // otherwise, move down [3]
        else elevator[e]->moveDown();
      }
      // otherwise it's near enough to destination to reach it in this time step... [4]
      else
      {
        // tell elevator to move to its destination floor [4]
        elevator[e]->moveToDestinationFloor();
        // tell elevator to open its door [4]
        elevator[e]->openDoor();
        // tell elevator to remove riders for its destination floor -- ignore returned vector of removed riders [4]
        elevator[e]->removeRidersForDestinationFloor();
        // get a non-const pointer to the elevator's destination floor (using const_cast) [5] HINT: lecture topic 9
        Floor* f;
        f=const_cast<Floor*>(&(elevator[e]->getDestination()));
        
        // if elevator is empty, choose a direction based on longest-waiting rider (the one with the smallest ID) on the floor: [5]
        if (elevator[e]->getRiderCount()==0)
        {
          // if the floor's chosen direction is up [5]
          if(f->isPreferredDirectionUp()) elevator[e]->setDirectionUp();
          // tell elevator to set its direction to up [5]
          // otherwise [5]
          else elevator[e]->setDirectionDown();
          // tell elevator to set its direction to down [5]
        }
        // if there is space in the elevator after letting off riders, board new ones [6]
        if(elevator[e]->getAvailableSpace()>0)
        {
          // if elevator direction is up, board up-riders (if any)... [6]
          if(elevator[e]->isDirectionUp())
            elevator[e]->addRiders(f->removeUpRiders(elevator[e]->getAvailableSpace()));
          // otherwise, board down-riders (if any) [6]
          else
            elevator[e]->addRiders(f->removeDownRiders(elevator[e]->getAvailableSpace()));
        }
        // reassess elevator destination based on its riders [8]
        elevator[e]->setDestinationBasedOnRiders();
      }
    }
    else
    {
      // if elevator has any riders (then they just boarded in the previous time step) [7]
      if(elevator[e]->getRiderCount()>0)
        elevator[e]->closeDoor(); // tell elevator to close its door [7]
      // otherwise [9]
      else
        elevator[e]->setIdle();// tell elevator to go idle [9]
    }
  }
  
  
  for(int i=0;i<getFloorCount();i++)
  {
    // if there are no riders waiting on this floor, continue with next floor [2]
    if(!(floor[i]->hasRidersWaiting()))continue;
    // look at each elevator to see if it needs to be sent here [2]
    for(int j=0;j<getElevatorCount();j++)
    {
      // get elevator's relative location (negative if elevator is below floor) [2]
      int loc =elevator[j]->getLocation()-floor[i]->getLocation();
      // if this elevator's idle... [2]
      if(elevator[j]->isIdle())
      {
        // if elevator is above the floor, set elevator direction to down [2]
        if(loc>0)elevator[j]->setDirectionDown();
        // otherwise if it's below, set elevator direction to up [2]
        else elevator[j]->setDirectionUp();
        // set elevator's destination to this floor [2]
        elevator[j]->setDestination(floor[i]);
        // tell elevator to close its door [2]
        elevator[j]->closeDoor();
      }
      else if(floor[i]->hasUpRiders() && elevator[j]->isDirectionUp())
      {
        // get distance from elevator's destination floor to this floor (positive if elevator destination is above this floor) [10]
        int g= (elevator[j])->getDestination().getLocation() - (floor[i])->getLocation();
        // if elevator is below floor and elevator destination is above this floor [10]
        if(g<0 && loc>0)
          elevator[j]->setDestination(floor[i]);// set elevator's destination to this floor [10]
      }
      // else if there are riders on this floor waiting to go down, and the elevator is going down... [10]
      else if(floor[i]->hasDownRiders() && elevator[j]->isDirectionDown())
      {
        // get distance from elevator's destination floor to this floor (negative if elevator destination is below this floor) [10]
        int g= (elevator[j]->getDestination()).getLocation() - (floor[i])->getLocation();
        // if elevator is above floor and elevator destination is below this floor [10]
        if(g>0 && loc>0)
          elevator[j]->setDestination(floor[i]);// set elevator's destination to this floor [10]
      }
    }
  }
  time++;
  return *this;
}
void getDifferentInts(int max, int& a, int& b)
{
  do
  {
    a = rand() % max; // range is 0 to (max-1)
    b = rand() % max; // range is 0 to (max-1)
  } while (a == b); // try again if they are the same
}
