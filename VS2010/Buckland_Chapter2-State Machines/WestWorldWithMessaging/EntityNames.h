#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Eleanor,

  ent_Chidi,

  ent_Michael //ĳ������ �̸��� �߰�. ������, ġ��, ����Ŭ
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Eleanor:

      return "Eleanor";

  case ent_Chidi:

      return "Chidi";
  
  case ent_Michael:

      return "Michael";

  default:

    return "UNKNOWN!";
  }
}

#endif