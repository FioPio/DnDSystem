#ifndef __ROLL_H__
#define __ROLL_H__

enum class Roll
{
    STRIGHT = 1,
    ADVANTAGE = 2,
    DISADVANTAGE = 3,
};


class Die
{
public:
  static int Roll(int nDice, int facesDie);
  static int RollAdvantage();
  static int RollDisadvantage();
  
};


#endif //__ROLL_H__
