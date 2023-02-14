#include <ai/bt/Node.h>
#include <ai/bt/CompositeNode.h>
#include <ai/bt/BehaviourTree.h>
#include <ai/bt/NodeFactory.h>
#include <ai/bt/composite/Sequence.h>
#include <iostream>

class OpenDoor : public Node {
public:
	OpenDoor() = default;
	Status Update() override {
		std::cout << "Updating Open door!\n";
		return Status::Success;
	};
};

class CloseDoor : public Node {
public:
	CloseDoor() = default;
	Status Update() override {
		std::cout << "Updating Close door!\n";
		return Status::Success;
	};
};

int main() {
	auto open_door = NodeFactory::createNode<OpenDoor>();
	auto close_door = NodeFactory::createNode<CloseDoor>();

	auto sequence = NodeFactory::createCompositeNode<Sequence>();
	sequence->AddNode(std::move(open_door));
	sequence->AddNode(std::move(close_door));

	BehaviourTree tree(std::move(sequence));
	 tree.Update();

	return 0;
}