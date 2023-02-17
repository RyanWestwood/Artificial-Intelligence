#include "RepeatUntilFail.h"

namespace ai
{
  namespace bt
  {

    Status RepeatUntilFail::Update(const float delta_time)
    {
      while(true)
      {
        Status result = m_Child.Update(delta_time);

        if(result == Status::Failure)
        {
          return Status::Success;
        }
      }
    }
  } // namespace bt
} // namespace ai
