// Lab 16 , Rider.cpp
// Programmer: Amir Babaei
// Editor(s) used: XCode
// Compiler(s) used: g++
#include "Floor.h"
#include "Rider.h"

int Rider::copyID = 1;

Rider::Rider(const Floor& x):f(&x), RiderID(copyID)
{
  copyID++;
}
bool Rider:: operator==(const Rider& b) const
{
  bool result = false;
  if (RiderID== b.RiderID)result= true;
  
  return result;
}
bool Rider:: operator<(const Rider& b) const
{
  bool result = false;
  if (RiderID< b.RiderID)result= true;
  
  return result;
}
Rider& Rider::operator=(const Rider& a)
{
  const_cast<int&>(RiderID) = a.RiderID;
  const_cast<const Floor*&>(f)=a.f;
  return *this;
}