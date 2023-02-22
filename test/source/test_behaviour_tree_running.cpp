#include <ai/Blackboard.h>
#include <ai/bt/BehaviourTree.h>
#include <ai/bt/composite/Selector.h>
#include <ai/bt/composite/Sequence.h>
#include <ai/bt/CompositeNode.h>
#include <ai/bt/Node.h>
#include <ai/bt/NodeFactory.h>
#include <engine/Globals.h>

#include <bitset>
#include <functional>
#include <iostream>
#include <random>

class Player
{
public:
  Player()
  {
    door_attempts = 0;
  }

  void CreateBt()
  {

    auto while_not_dead = [&]() -> Status {
      //	bitset index = 4
      if(tree_conditions[4]) return Status::Success; // Have this queried somehow
      tree_conditions.reset();
      door_attempts = 0;
      return Status::Running;
    };

    auto open_door_lam = [&]() -> Status {
      //	bitset index = 0
      if(tree_conditions[0]) return Status::Success; // Have this queried somehow
      if(door_attempts >= 10)
      {
        std::cout << "Opening door!\n";
        return Status::Success;
      }
      door_attempts++;
      std::cout << "Attempting to open door!\n";
      return Status::Running;
    };

    auto walk_door_lam = [&]() -> Status {
      //	bitset index = 1
      if(tree_conditions[1]) return Status::Success; // Have this queried somehow
      std::cout << "Walking to door!\n";
      tree_conditions.set(1);
      return Status::Success;
    };

    auto close_door_lam = [&]() -> Status {
      //	bitset index = 2
      if(tree_conditions[2]) return Status::Success; // Have this queried somehow
      std::cout << "Closing door!\n	\n";
      tree_conditions.set(2);
      return Status::Success;
    };

    auto blackboard    = ai::Blackboard(globals::GetAssetDirectory() + "blackboards/door_test.csv");
    auto door_sequence = NodeFactory::createCompositeNode<Sequence>(blackboard);

    auto alive_condition = NodeFactory::createNode<Node>(blackboard, while_not_dead);
    auto open_door       = NodeFactory::createNode<Node>(blackboard, open_door_lam);
    auto walk_to_door    = NodeFactory::createNode<Node>(blackboard, walk_door_lam);
    auto closing_door    = NodeFactory::createNode<Node>(blackboard, close_door_lam);

    door_sequence->AddNode(std::move(walk_to_door));
    door_sequence->AddNode(std::move(open_door));
    door_sequence->AddNode(std::move(closing_door));
    door_sequence->AddNode(std::move(alive_condition));

    tree = ai::BehaviourTree(std::move(door_sequence));
  }

  void UpdateTree()
  {
    tree.Update();
  }

private:
  ai::BehaviourTree tree;
  std::bitset<8>    tree_conditions;

  int door_attempts = 0;
};

int main()
{
  bool globals = globals::InitializeGlobals();
  if(!globals) return 1;

  Player carlo;
  carlo.CreateBt();

  // Fake game loop
  for(short i = 0; i <= 30; i++)
  {
    carlo.UpdateTree();
  }

  return 0;
}