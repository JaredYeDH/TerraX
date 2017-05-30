#include "world_server.h"
#include <chrono>
#include <thread>
#include "world_net_module.h"
using namespace terra;

bool WorldServer::Init()
{
	WorldNetModule::GetInstance().Init();
	return true;
}

bool WorldServer::AfterInit()
{
	WorldNetModule::GetInstance().AfterInit();
	return true;
}

bool WorldServer::Tick()
{
	while (!exit_) {
		WorldNetModule::GetInstance().Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return true;
}

bool WorldServer::BeforeShut()
{
	return true;
}

bool WorldServer::Shut()
{
	return true;
}
