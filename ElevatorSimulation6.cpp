// Lab 16 , ElevatorSimulation6.cpp
// Programmer: Amir Babaei
// Editor(s) used: XCode
// Compiler(s) used: g++
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Building.h"

int getArrivalsForThisSecond(double averageRiderArrivalRate)
{
  int arrivals = 0;
  double probOfnArrivals = exp(-averageRiderArrivalRate); // for n=0 -- requires cmath
  for(double randomValue = (rand() % 1000) / 1000.0; // requires cstdlib AND srand in main
      (randomValue -= probOfnArrivals) > 0.0;
      probOfnArrivals *= averageRiderArrivalRate / ++arrivals);
  return arrivals;
}

int main()
{
  // print my name and this assignment's title
  cout << "Lab 16, ElevatorSimulation6.cpp\n";
  cout << "Programmer: Amir Babaei\n";
  cout << "Editor(s) used: XCode\n";
  cout << "Compiler(s) used: g++\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
  srand(time(0)); rand(); // requires cstdlib and ctime
  Building building;

  
  // continue the simulation for 600 more seconds (expect all riders to be gone by then)
  for (int i = 0;; i++)
  {
    cout << building.step(getArrivalsForThisSecond(2)) << endl; // time-step with no riders added
    if (!(i % 10)) // pause every 10 seconds
    {
      cout << "Press ENTER to continue, X-ENTER to quit...\n";
      if (cin.get() > 31) break;
    }
  }
  cout << "DONE: All riders should be gone, and all elevators idle\n";
}