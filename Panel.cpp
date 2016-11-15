//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <iostream>
#include <string>
using namespace std;

#include "Panel.h"

int Panel::Button::count = 0;

void Panel::addButton(string label)
{
  Button temp;
  temp.label = label;
  temp.lit = false;
  buttons.push_back(temp);
}

void Panel::press(string label)
{
  for(int i = 0; i < buttons.size(); i++)
  {
    if(this->buttons[i].label == label)
    {
      this->buttons[i].lit = true;
      Button::count++;
      this->buttons[i].sequence = Button::count;
    }
  }
}

void Panel::clear(string label)
{
  for(int i = 0; i < this->buttons.size(); i++)
  {
    if(this->buttons[i].label == label)
      this->buttons[i].lit = false;
  }
}

string Panel::getFirstLit() const
{
  string firstLit = "";
  int sequence = 0;

  for(int i = 0; i < this->buttons.size(); i++)
  {
    if(this->buttons[i].lit)
    {
      if(sequence == 0 ) 
      {
        sequence = buttons[i].sequence;
        firstLit = buttons[i].label;
      }
      else if(sequence != 0 && sequence > this->buttons[i].sequence)
      {
        sequence = this->buttons[i].sequence;
        firstLit = this->buttons[i].label;
      }
    }
  }
  return firstLit;
}

bool Panel::isLit(string label) const
{
  for(int i = 0; i < buttons.size(); i++)
  {
    if(label == buttons[i].label)
      return buttons[i].lit ? true : false;
  }
  return false;
}

bool Panel::areAnyLit() const
{
  for(int i = 0; i < this->buttons.size(); i++)
  {
    if(this->buttons[i].lit) return true;
  }
  return false;
}

ostream& operator<<(ostream& out, const Panel& p)
{
  for(int i = 0; i < p.buttons.size(); i++)
  {
    if(p.buttons[i].lit)
    {
      out << "[" << p.buttons[i].label << "]";
    }
  }
  return out;
}