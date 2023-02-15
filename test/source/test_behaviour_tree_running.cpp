#include <ai/Blackboard.h>
#include <ai/bt/Node.h>
#include <ai/bt/CompositeNode.h>
#include <ai/bt/BehaviourTree.h>
#include <ai/bt/NodeFactory.h>
#include <ai/bt/composite/Sequence.h>
#include <ai/bt/composite/Selector.h>
#include <engine/Globals.h>

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
		if (m_Status == Status::Success) return Status::Success;
		std::cout << "Walking to door!\n";
		m_Status = Status::Success;
		return Status::Success;
	};
};

class OpenDoor : public Node {
public:
	OpenDoor() = default;
	Status Update() override {
		if (action_time >= 10) {
				std::cout << "Opening door!\n";
				return Status::Success;
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
		std::cout << "Closing door!\n	\n";
		return Status::Success;
	};
};

int main() {

	bool globals = globals::InitializeGlobals();
	if (!globals) return 1;
	auto blackboard = ai::CreateBlackboard(globals::GetAssetDirectory() + "blackboards/door_test.csv");

	auto door_sequence = NodeFactory::createCompositeNode<Sequence>(blackboard);

	auto walk_to_door = NodeFactory::createNode<WalkToDoor>();
	auto open_door = NodeFactory::createNode<OpenDoor>();
	auto closing_door = NodeFactory::createNode<CloseDoor>();

	door_sequence->AddNode(std::move(walk_to_door));
	door_sequence->AddNode(std::move(open_door));
	door_sequence->AddNode(std::move(closing_door));

	BehaviourTree tree(std::move(door_sequence));

	Status result = Status::Error;
	do
	{
		result = tree.Update();
	} while (result != Status::Success);

	return 0;
}