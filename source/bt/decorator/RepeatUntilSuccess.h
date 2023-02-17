#pragma once
#include "../Node.h"

namespace ai
{
  namespace bt
  {

    class RepeatUntilSuccess : public Decorator
    {
    public:
      RepeatUntilSuccess()
      {
      }
      Status Update(const float delta_time);
    };
  } // namespace bt
} // namespace ai