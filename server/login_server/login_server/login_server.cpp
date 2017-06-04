#include "login_server.h"
#include <chrono>
#include <thread>
#include "login_net_module.h"
using namespace terra;

bool LoginServer::Init()
{
	LoginNetModule::GetInstance().Init();
	return true;
}

bool LoginServer::AfterInit()
{
	LoginNetModule::GetInstance().AfterInit();
	return true;
}

bool LoginServer::Tick()
{
	while (!exit_) {
		LoginNetModule::GetInstance().Tick();
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

