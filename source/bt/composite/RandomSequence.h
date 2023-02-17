#pragma once
#include "../Node.h"

namespace ai
{
  namespace bt
  {

    class RandomSequence : public CompositeNode
    {
    public:
      RandomSequence()
      {
      }
      Status Update(const float delta_time);
    };
  } // namespace bt
} // namespace ai