#pragma once
#include "../Node.h"

namespace ai
{
  namespace bt
  {

    class RepeatUntilFail : public Decorator
    {
    public:
      RepeatUntilFail()
      {
      }
      Status Update(const float delta_time);
    };
  } // namespace bt
} // namespace ai