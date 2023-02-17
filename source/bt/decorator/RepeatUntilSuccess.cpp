#include "RepeatUntilSuccess.h"

namespace ai
{
  namespace bt
  {

    Status RepeatUntilSuccess::Update(const float delta_time)
    {
      while(true)
      {
        Status result = m_Child.Update(delta_time);
        if(result == Status::Success)
        {
          return Status::Success;
        }
      }
    }
  } // namespace bt
} // namespace ai