#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_Helpme_Eleanor,
  Msg_Helpme_Chidi,
  Msg_Be_careful_Eleanor //�޼��� Ÿ�� �߰�.
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {


  case Msg_Helpme_Eleanor:

      return "Help me Eleanor";

  case Msg_Helpme_Chidi:

      return "Help me Chidi";
      
  case Msg_Be_careful_Eleanor:

      return "Be careful Eleanor";

  default:

    return "Not recognized!";
  }
}

#endif