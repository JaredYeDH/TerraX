#include "db_server.h"
#include <chrono>
#include <thread>
#include "db_net_module.h"
using namespace terra;

bool DBServer::Init()
{
	DBNetModule::GetInstance().Init();
	return true;
}

bool DBServer::AfterInit()
{
	DBNetModule::GetInstance().AfterInit();
	return true;
}

bool DBServer::Tick()
{
	while (!exit_) {
		DBNetModule::GetInstance().Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return true;
}

bool DBServer::BeforeShut()
{
	return true;
}

bool DBServer::Shut()
{
	return true;
}

