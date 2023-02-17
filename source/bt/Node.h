#pragma once
#include <functional>
#include <vector>

namespace ai
{
  namespace bt
  {

    enum class Status
    {
      Success = 0,
      Failure,
      Running,
      Error
    };

    typedef std::function<Status(const float delta_time)> Function;

    class Node
    {
    public:
      Node()
      {
      }
      void Initialize(Function m_Func)
      {
        m_Logic = m_Func;
      }
      Status Update(const float delta_time)
      {
        return m_Logic(delta_time);
      }

    private:
      Function m_Logic;
    };

    class Decorator : public Node
    {
    public:
      Decorator()
      {
      }
      Status Update()
      {
      }

    protected:
      Node m_Child;
    };

    class CompositeNode : public Node
    {
    public:
      CompositeNode()
      {
      }
      void AddChild(Node child)
      {
        m_Children.push_back(child);
      }

    protected:
      std::vector<Node> m_Children;
    };
  } // namespace bt
} // namespace ai