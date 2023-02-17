#include "Succeeder.h"

namespace ai
{
  namespace bt
  {

    Status Succeeder::Update(const float delta_time)
    {
      m_Child.Update(delta_time);
      return Status::Success;
    }
  } // namespace bt
} // namespace ai
