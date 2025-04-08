#ifndef __STATBLOCK_H__
#define __STATBLOCK_H__

#include <vector>

class Action;

class Statblock
{
public:
  float GetCR();
  



private:
  float _cr;
  std::vector<Action> _actions{};
  std::vector<Action> _bouns_actions{};
  std::vector<Action> _reactions{};
  std::vector<Action> _legendary_actions{};
  std::vector<Action> _legendary_reactions{};
  int _stats[6] { /*STR*/10, /*DEX*/10, /*CON*/10, /*WIS*/10, /*INT*/10, /*CHA*/10};
  
};


#endif // __STATBLOCK_H__
