#include <iostream>
#include <memory>
#include "component.h"

using namespace fsm;

int main()
{
	std::unique_ptr<Avatar> avatar(new Avatar());
	avatar->InitFSMComponnet();
	avatar->InitAIComponet();
	avatar->GetAIComponent()->InitAIController

}