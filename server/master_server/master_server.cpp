#include "master_server.h"
#include <chrono>
#include <thread>
#include "master_net_module.h"
using namespace terra;

bool MasterServer::Init()
{
	MasterNetModule::GetInstance().Init();
	return true;
}

bool MasterServer::AfterInit()
{
	MasterNetModule::GetInstance().AfterInit();
	return true;
}

bool MasterServer::Tick()
{
	while (!exit_) {
		MasterNetModule::GetInstance().Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return true;
}

bool MasterServer::BeforeShut()
{
	return true;
}

bool MasterServer::Shut()
{
	return true;
}
