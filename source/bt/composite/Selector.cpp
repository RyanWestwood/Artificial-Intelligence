#include "Selector.h"

namespace ai
{
  namespace bt
  {

    Status Selector::Update(const float delta_time)
    {
      for(auto child : m_Children)
      {
        if(child.Update(delta_time) == Status::Success)
        {
          return Status::Success;
        }
      }
      return Status::Failure;
    }
  } // namespace bt
} // namespace ai