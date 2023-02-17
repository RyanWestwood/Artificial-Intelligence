#include "Inverter.h"

namespace ai
{
  namespace bt
  {

    Status Inverter::Update(const float delta_time)
    {
      Status result = m_Child.Update(delta_time);
      if(result == Status::Success)
      {
        return Status::Failure;
      }
      else if(result == Status::Failure)
      {
        return Status::Success;
      }
      return result;
    }
  } // namespace bt
} // namespace ai
