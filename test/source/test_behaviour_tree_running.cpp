#include <ai/bt/Node.h>
#include <ai/bt/CompositeNode.h>
#include <ai/bt/BehaviourTree.h>
#include <ai/bt/NodeFactory.h>
#include <ai/bt/composite/Sequence.h>
#include <ai/bt/composite/Selector.h>
#include <iostream>
#include <random>

auto GetRandomProbability() {
	std::random_device rd;
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distr(0, 99); 
	return distr(gen);
}

class WalkToDoor : public Node {
public:
	WalkToDoor() = default;
	Status Update() override {
		std::cout << "Walking to door!\n";
		return Status::Success;
	};
};

class OpenDoor : public Node {
public:
	OpenDoor() = default;
	Status Update() override {
		if (action_time > 10) {
			if (GetRandomProbability() < 10) {
				std::cout << "Opening door!\n";
				return Status::Success;
			}
			else {
				std::cout << "Couldn't open door!\n";
				return Status::Failure;
			}
		}
		action_time++;
		std::cout << "Attempting to open door!\n";
		return Status::Running;
	};
private:
	int action_time = 0;
};

class CloseDoor : public Node {
public:
	CloseDoor() = default;
	Status Update() override {
		if (GetRandomProbability() < 50) {
			std::cout << "Closing door!\n\n";
			return Status::Success;
		}
		else {
			std::cout << "Couldn't close door!\n\n";
			return Status::Failure;
		}
	};
};

auto DoorSubtree(){
	auto door_sequence = NodeFactory::createCompositeNode<Sequence>();

	auto walk_to_door = NodeFactory::createNode<WalkToDoor>();
	auto open_door = NodeFactory::createNode<OpenDoor>();
	auto closing_door = NodeFactory::createNode<CloseDoor>();

	door_sequence->AddNode(std::move(walk_to_door));
	door_sequence->AddNode(std::move(open_door));
	door_sequence->AddNode(std::move(closing_door));

	return door_sequence;
}

int main() {
	
	BehaviourTree tree(std::move(DoorSubtree()));
	tree.Update();

	return 0;
}