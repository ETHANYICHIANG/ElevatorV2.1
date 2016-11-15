//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include "Building.h"
#include "Floor.h"
#include "Rider.h"
#include "Panel.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#include <climits>

const char* const Floor::UP = "Up";
const char* const Floor::DOWN = "Down";
int Floor::TOP = INT_MIN; // defined in climits
int Floor::BOTTOM = INT_MAX; // also in climits


Floor::Floor(const int elevation, const char* const name, const char* const label)
:name(name), label(label), elevation(elevation)
{
  panel.addButton(UP);
  panel.addButton(DOWN);
  if (TOP < elevation) TOP = elevation;
  if (elevation < BOTTOM) BOTTOM = elevation;
}

ostream& operator<<(ostream& out, const Floor& floor)
{
  out.width(3);
  out << floor.label;
  out.width(15);
  out << floor.name << " at";
  out.width(6);
  out << floor.elevation;
  out << "\" Up/Down:";
  out.width(4);
  out << floor.upRiders.size() << "/" << floor.downRiders.size()
      << "   Button:  " << floor.panel;
  return out;
}

void Floor::addRider(const Rider& r)
{
  if(r.goingUp)
    {
      this->upRiders.push(r);
      panel.press(UP);
    }
  else if(r.goingDown)
    {
      this->downRiders.push(r);
      panel.press(DOWN);
    }
  else throw "ADD_RIDER ERROR!";
}

Rider Floor::removeUpRider()
{
  if(this->upRiders.empty()) throw "UP_RIDER EMPTY!";

  Rider r = this->upRiders.front();
  this->upRiders.pop();

  return r;
}

Rider Floor::removeDownRider()
{
  if(this->downRiders.empty()) throw "DOWN_RIDER EMPTY!";

  Rider r = this->downRiders.front();
  this->downRiders.pop();

  return r;
}
