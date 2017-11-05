// Lab 16 , Floor.cpp
// Programmer: Amir Babaei
// Editor(s) used: XCode
// Compiler(s) used: g++

#include "Floor.h"
#include "Rider.h"
#include <cstdlib>
using std::abs;

Floor::Floor(const int a, const char* const s ):NAME(s),location(a){};
void Floor::addNewRider(const Rider& rider)
{
  // if added rider's destination is greater than the floor's location
  if(rider.getDestination().getLocation()>location)
    upRiders.push_back(rider);// add rider to the upRiders vector
  // else
  else
    downRiders.push_back(rider);// add rider to the downRiders vector
}

vector<Rider> Floor::removeUpRiders(int max) // max = #of unused spaces on elevator
{
  // create an empty vector for riders to be removed
  vector<Rider> mveRiders;
  // if there are any up riders...
  if(upRiders.size()!=0)
  {
    // create an empty vector for riders to remain on the floor
    vector<Rider> remRiders;
    // traverse the upRiders vector
    for(int i=0;i<upRiders.size();i++)
    {
      // if there are still spaces left on the elevator...
      if(i<max)
        mveRiders.push_back(upRiders[i]);// add an upRider to the vector of riders to be removed
      // else
      else
        remRiders.push_back(upRiders[i]); // add an upRider to the vector of riders to remain on the floor
    }
    // replace the upRiders vector with the vector of remaining riders
    upRiders=remRiders;
  }
  // return the vector of removed riders
  return mveRiders;
}

vector<Rider> Floor::removeDownRiders(int max)
{
  // create an empty vector for riders to be removed
  vector<Rider> mveRiders;
  // if there are any up riders...
  if(downRiders.size()!=0)
  {
    // create an empty vector for riders to remain on the floor
    vector<Rider> remRiders;
    // traverse the upRiders vector
    for(int i=0;i<downRiders.size();i++)
    {
      // if there are still spaces left on the elevator...
      if(i<max)
        mveRiders.push_back(downRiders[i]);// add an upRider to the vector of riders to be removed
      // else
      else
        remRiders.push_back(downRiders[i]); // add an upRider to the vector of riders to remain on the floor
    }
    // replace the upRiders vector with the vector of remaining riders
    downRiders=remRiders;
  }
  // return the vector of removed riders
  return mveRiders;
}

bool Floor::isPreferredDirectionUp() const
{
  // if there are no downRiders, return true
  if(downRiders.size()==0)
    return true;
  // if there are no upRiders, return false
  if(upRiders.size()==0)
    return false;
  // if the ID of the first upRider (upRider[0]) is less than that of the first downRider...
  if(upRiders[0]<downRiders[0])
    return true;// return true
  return false;
  // return false
}
ostream& operator<<(ostream& out, const Floor& f)
{
  out<< f.NAME << "\n";
  out<<abs(f.location)<<" is the location\n";
  out<< f.upRiders.size()<< " Up Riders waiting\n";
  out<< f.downRiders.size()<< " down Riders\n";
  
  return out;
}