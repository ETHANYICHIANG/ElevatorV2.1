//Programmer: Ethan Chiang
//Programmer ID: 1538719

#ifndef Panel_h
#define Panel_h

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Panel
{
  struct Button
  {
    string label;
    bool lit;
    int sequence;
    static int count;
  };
  vector<Button> buttons;
  
  public:
  friend ostream& operator<<(ostream&, const Panel&);
  void addButton(string);
  void press(string); 
  void clear(string);
  string getFirstLit() const;
  bool isLit(string) const;
  bool areAnyLit() const;
};

#endif