#include "rules/Roll.h"

#include <random>

int Die::Roll(int nDice, int facesDie)
{
  int sum = 0;
  static std::random_device seed;

  static std::mt19937 gen(seed());

  static std::uniform_int_distribution<int>distrib(1, facesDie);

  for (int num_die = 0;  num_die < nDice; num_die++)
  {
    sum += distrib(gen);
  }

  return sum;
  
}

int Die::RollAdvantage()
{
  int roll_1 = Roll(1, 20);
  int roll_2 = Roll(1, 20);

  return std::max(roll_1, roll_2);
}

int Die::RollDisadvantage()
{
  int roll_1 = Roll(1, 20);
  int roll_2 = Roll(1, 20);

  return std::min(roll_1, roll_2);
}
