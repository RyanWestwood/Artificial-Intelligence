#include <engine/Globals.h>
#include <ai/Blackboard.h>

int main() {
  
	bool globals = globals::InitializeGlobals();
    if(!globals) return 1;

	auto blackboard = ai::Blackboard(globals::GetAssetDirectory() + "blackboards/unit_test.csv");  
	
	if (*blackboard.GetFloat("name1", 10) != 10.10f) return 1;
	if (*blackboard.GetBool("name2", true) != true) return 1;
	if (*blackboard.GetInt("name3", 10) != 100) return 1;

	return 0;
}