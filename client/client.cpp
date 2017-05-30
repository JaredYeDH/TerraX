#include "client.h"
#include <chrono>
#include <thread>
#include "client_net_module.h"
#include "game_state_manager.h"
using namespace terra;

bool Client::Init()
{
	ClientNetModule::GetInstance().Init();
	return true;
}

bool Client::AfterInit()
{
	ClientNetModule::GetInstance().AfterInit();
	GameStateManager::GetInstance().EnterDefaultState();
	return true;
}

bool Client::Tick()
{
	while (!exit_) {
		ClientNetModule::GetInstance().Tick();
		GameStateManager::GetInstance().Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return true;
}

bool Client::BeforeShut()
{
	return true;
}

bool Client::Shut()
{
	return true;
}

