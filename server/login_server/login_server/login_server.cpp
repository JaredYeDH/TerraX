#include "login_server.h"
#include <chrono>
#include <thread>
#include "login_net_module.h"
using namespace terra;

bool LoginServer::Init()
{
	GateNetModule::GetInstance().Init();
	return true;
}

bool LoginServer::AfterInit()
{
	GateNetModule::GetInstance().AfterInit();
	return true;
}

bool LoginServer::Tick()
{
	while (!exit_) {
		GateNetModule::GetInstance().Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return true;
}

bool LoginServer::BeforeShut()
{
	return true;
}

bool LoginServer::Shut()
{
	return true;
}

