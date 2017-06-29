#include "world_loadbalancing_manager.h"

using namespace terra;

int WorldLoadBalancingManager::GetLowestLoadGateServerId()
{
	int serverid = -1;
	int least_count = 999999;
	for (auto& kv : gates_)
	{
		int cur_count = (kv.second)->get_account_count();
		if (cur_count < least_count)
		{
			least_count = cur_count;
			serverid = kv.first;
		}
	}
	return serverid;
}

void WorldLoadBalancingManager::CreateGateServer(int server_id)
{
	gates_[server_id] = std::move(std::unique_ptr<GateLoadInfo>(new GateLoadInfo()));
}