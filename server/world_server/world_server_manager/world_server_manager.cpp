#include "world_server_manager.h"
#include "world_loadbalancing_manager.h"

using namespace terra;


void WorldServerManager::OnGateServerConnected(int server_id)
{
	WorldLoadBalancingManager::GetInstance().CreateGateServer(server_id);
}