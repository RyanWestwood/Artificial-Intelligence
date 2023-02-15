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

class WalkThroughDoor : public Node {
public:
	WalkThroughDoor() = default;
	Status Update() override {
		std::cout << "Walking through door!\n";
		return Status::Success;
	};
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

class OpenDoor : public Node {
public:
	OpenDoor() = default;
	Status Update() override {
		if(GetRandomProbability() < 10){
			std::cout << "Opening door!\n";
			return Status::Success;
		}else{
			std::cout << "Couldn't open door!\n";
			return Status::Failure;
		}
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
		if (GetRandomProbability() < 50) {
			std::cout << "Unlocking door!\n";
			return Status::Success;
		}
		else {
			std::cout << "Couldn't unlock door!\n";
			return Status::Failure;
		}
	};
};

class ForceDoorOpen : public Node {
public:
	ForceDoorOpen() = default;
	Status Update() override {
		if (GetRandomProbability() < 50) {
			std::cout << "Forcing door open!\n";
			return Status::Success;
		}
		else {
			std::cout << "Couldn't force door open!\n";
			return Status::Failure;
		}
	};
};

auto DoorSubtree(){
	auto door_sequence = NodeFactory::createCompositeNode<Sequence>();

	auto walk_to_door = NodeFactory::createNode<WalkToDoor>();
	auto door_open_selector = NodeFactory::createCompositeNode<Selector>();
	auto walk_through_door = NodeFactory::createNode<WalkThroughDoor>();
	auto closing_door = NodeFactory::createNode<CloseDoor>();

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
	door_sequence->AddNode(std::move(closing_door));

	return door_sequence;
}

class WalkToWindow : public Node {
public:
	WalkToWindow() = default;
	Status Update() override {
		std::cout << "Walking to Window!\n";
		return Status::Success;
	};
};

class WalkThroughWindow : public Node {
public:
	WalkThroughWindow() = default;
	Status Update() override {
		std::cout << "Walking through Window!\n";
		return Status::Success;
	};
};

class CloseWindow : public Node {
public:
	CloseWindow() = default;
	Status Update() override {
		std::cout << "Closing Window!\n\n";
		return Status::Success;
	};
};

class OpenWindow : public Node {
public:
	OpenWindow() = default;
	Status Update() override {
		std::cout << "Opening Window!\n";
		return Status::Success;
	};
};

class SmashWindow : public Node {
public:
	SmashWindow() = default;
	Status Update() override {
		std::cout << "Smashing Window!\n";
		return Status::Success;
	};
};

class UnlockWindow : public Node {
public:
	UnlockWindow() = default;
	Status Update() override {
		std::cout << "Unlocking Window!\n";
		return Status::Success;
	};
};

class ForceWindowOpen : public Node {
public:
	ForceWindowOpen() = default;
	Status Update() override {
		std::cout << "Forcing Window open!\n";
		return Status::Success;
	};
};

auto WindowSubtree() {
	auto window_sequence = NodeFactory::createCompositeNode<Sequence>();

	auto walk_to_window = NodeFactory::createNode<WalkToWindow>();
	auto window_open_selector = NodeFactory::createCompositeNode<Selector>();
	auto walk_through_window = NodeFactory::createNode<WalkThroughWindow>();
	auto closing_window = NodeFactory::createNode<CloseWindow>();

	auto open_window = NodeFactory::createNode<OpenWindow>();
	auto unlock_window_sequence = NodeFactory::createCompositeNode<Sequence>();
	auto smash_window = NodeFactory::createNode<SmashWindow>();;

	auto unlock_window = NodeFactory::createNode<UnlockWindow>();;
	auto force_window_open = NodeFactory::createNode<ForceWindowOpen>();;

	unlock_window_sequence->AddNode(std::move(unlock_window));
	unlock_window_sequence->AddNode(std::move(force_window_open));

	window_open_selector->AddNode(std::move(open_window));
	window_open_selector->AddNode(std::move(unlock_window_sequence));
	window_open_selector->AddNode(std::move(smash_window));

	window_sequence->AddNode(std::move(walk_to_window));
	window_sequence->AddNode(std::move(window_open_selector));
	window_sequence->AddNode(std::move(walk_through_window));
	window_sequence->AddNode(std::move(closing_window));

	return window_sequence;
}

int main() {
	auto root = NodeFactory::createCompositeNode<Selector>();
	root->AddNode(std::move(DoorSubtree()));
	root->AddNode(std::move(WindowSubtree()));
	
	BehaviourTree tree(std::move(root));
	tree.Update();

	return 0;
}