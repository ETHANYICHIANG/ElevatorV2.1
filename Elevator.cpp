#include "Building.h"
#include "Elevator.h"
#include "Panel.h"
#include "Rider.h"
#include <iostream>
#include <vector>
using namespace std;

#include <cstdlib>

Elevator::Elevator(unsigned int capacity, int speed, int start)
:speed(speed), CAPACITY(capacity), location(Building::floors[start])
{
  start = Building::floors[start];
  direction = IDLE;
  timer = 0;
  atFloorIndex = -1;

  for(int i = 0; i < Building::FLOORS; i++)
  {
    panel.addButton(Building::floors[i].label);
  }
}


ostream& operator<<(ostream& out, const Elevator& e)
{
  cout << "Elevator at ";
  cout.width(5);
  cout << e.location;

  cout.width(11);
  switch(e.direction)
  {
  	case 1:
  	  cout << "going UP";
  	  break;
  	case -1:
  	  cout << "going DOWN";
  	  break;
  	case 0:
  	  cout << "IDLE";
  	  break;
  }

  cout.width(3);
  cout << e.riders.size() << " riders";

  cout.width(16);
  if(e.atFloorIndex != -1)
    cout << " door is OPEN|" << e.timer;
  else
  {
    cout.width(15);
    cout << " ";
  }

  cout << " " << e.panel;

  return out;
}

void Elevator::openDoorTo(int floorindex)
{
  this->panel.clear(Building::floors[floorindex].label);
  this->atFloorIndex = floorindex;
  this->resetTimer();
}

void Elevator::board(const Rider& r)
{
  this->riders.push_back(r); // add rider

  //string to = Building::floors[r.to].label;
  this->panel.press(Building::floors[r.to].label); // press button

  if(r.goingUp) // set direction of elevator
    this->direction = this->UP;
  else if(r.goingDown)
    this->direction = this->DOWN;
  else throw "BOARD ERROR!";

  this->resetTimer(); // reset close door timer
}

bool Elevator::hasRiderForFloor() const
{
  if(atFloorIndex == -1)
    return false;

  for(int i = 0; i < riders.size(); i++)
    if(riders[i].to == atFloorIndex)
      return true; // find rider for floor

  return false; // end of function
}

void Elevator::removeRider()
{
  vector<Rider>:: iterator it;
  for(it = riders.begin(); it != riders.end(); it++)
  {
    if(it->to == atFloorIndex)
    {
      this->panel.clear(Building::floors[it->to].label);
      it = this->riders.erase(it);
      this->resetTimer();
      break;
    }
  }
}

bool Elevator::closeDoor()
{
  if(atFloorIndex == -1) return false;
  
  if (this->direction == 1 && !Building::floors[atFloorIndex].hasUpRider())
    this->panel.clear("UP");
  else if (this->direction == -1 && !Building::floors[atFloorIndex].hasDownRider())
    this->panel.clear("DOWN");
  
  this->direction = -1;
  return true;
}

bool Elevator::move()
{
  if(this->direction == 1)
  {
    this->location += speed;
    return true;
  }
  else if(this->direction == -1)
  {
    this->location -= speed;
    return true;
  }
  else return false;

}
