#include <ai/bt/Node.h>
#include <ai/bt/CompositeNode.h>
#include <ai/bt/BehaviourTree.h>
#include <ai/bt/NodeFactory.h>
#include <ai/bt/composite/Sequence.h>
#include <ai/bt/composite/Selector.h>
#include <iostream>

class WalkToDoor : public Node {
public:
	WalkToDoor() = default;
	Status Update() override {
		std::cout << "Walking to door!\n";
		return Status::Success;
	};
};

class WalkThroughDoor : public Node {
public:
	WalkThroughDoor() = default;
	Status Update() override {
		std::cout << "Walking through door!\n";
		return Status::Success;
	};
};

class OpenDoor : public Node {
public:
	OpenDoor() = default;
	Status Update() override {
		std::cout << "Opening door!\n";
		return Status::Success;
	};
};

class SmashDoor : public Node {
public:
	SmashDoor() = default;
	Status Update() override {
		std::cout << "Smashing door!\n";
		return Status::Success;
	};
};

class UnlockDoor : public Node {
public:
	UnlockDoor() = default;
	Status Update() override {
		std::cout << "Unlocking door!\n";
		return Status::Success;
	};
};

class ForceDoorOpen : public Node {
public:
	ForceDoorOpen() = default;
	Status Update() override {
		std::cout << "Forcing door open!\n";
		return Status::Success;
	};
};

int main() {
	auto root = NodeFactory::createCompositeNode<Selector>();
	auto door_sequence = NodeFactory::createCompositeNode<Sequence>();
	auto window_sequence = NodeFactory::createCompositeNode<Sequence>();

	auto walk_to_door = NodeFactory::createNode<WalkToDoor>();
	auto door_open_selector = NodeFactory::createCompositeNode<Selector>();
	auto walk_through_door = NodeFactory::createNode<WalkThroughDoor>();

	auto open_door = NodeFactory::createNode<OpenDoor>();
	auto unlock_door_sequence = NodeFactory::createCompositeNode<Sequence>();
	auto smash_door = NodeFactory::createNode<SmashDoor>();;

	auto unlock_door = NodeFactory::createNode<UnlockDoor>();;
	auto force_door_open = NodeFactory::createNode<ForceDoorOpen>();;

	unlock_door_sequence->AddNode(std::move(unlock_door));
	unlock_door_sequence->AddNode(std::move(force_door_open));

	door_open_selector->AddNode(std::move(open_door));
	door_open_selector->AddNode(std::move(unlock_door_sequence));
	door_open_selector->AddNode(std::move(smash_door));

	door_sequence->AddNode(std::move(walk_to_door));
	door_sequence->AddNode(std::move(door_open_selector));
	door_sequence->AddNode(std::move(walk_through_door));

	root->AddNode(std::move(door_sequence));
	root->AddNode(std::move(window_sequence));
	
	BehaviourTree tree(std::move(root));
	tree.Update();

	return 0;
}