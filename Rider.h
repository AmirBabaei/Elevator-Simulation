// Lab 16 , Rider.h
// Programmer: Amir Babaei
// Editor(s) used: XCode
// Compiler(s) used: g++
#ifndef Rider_H
#define Rider_H

class Floor;


class Rider
{
  const int RiderID;
  static int copyID;
  const Floor* const f;
public:
  Rider& operator=(const Rider&);
  Rider(const Floor& x);
  const Floor& getDestination() const{return *f;}
  bool operator==(const Rider&) const;
  bool operator<(const Rider&) const;
};
#endif