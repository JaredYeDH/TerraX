#include "world_server_manager.h"

using namespace terra;

WorldAccount* WorldServerManager::FindAccountByAccountName(const std::string& account_name)
{
	for (auto& val : accounts_sortby_gate_)
	{
		auto iter = val.second.find(account_name);
		if (iter != val.second.end())
		{
			return (iter->second).get();
		}
	}
	return nullptr;
}

int WorldServerManager::GetLowestLoadGateServerId()
{
	int least_count = 9999;
	bool find = false;
	int server_id = -1;
	for (const auto& val : accounts_sortby_gate_)
	{
		int account_count = val.second.size();
		if (account_count < least_count)
		{
			least_count = account_count;
			find = true;
			server_id = val.first;
		}
	}
	return server_id;
}

void WorldServerManager::CreateAccountMapByGateId(int gate_server_id)
{
	accounts_sortby_gate_.emplace(gate_server_id, WorldAccountMap());
}