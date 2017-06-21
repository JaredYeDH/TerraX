#pragma once
#include "base/types.h"
#include <map>
#include <unordered_map>
#include "world_account.h"

namespace terra
{
	class WorldAccount;
	class WorldServerManager
	{
		MAKE_INSTANCE(WorldServerManager);
		DISABLE_COPY(WorldServerManager);
		using WorldAccountMap = std::unordered_map<std::string, WorldAccount>;
	private:
		std::map<int, WorldAccountMap> accounts_sortby_gate_;
	public:
		WorldServerManager() = default;
		~WorldServerManager() = default;

		void CreateAccountMapByGateId(int gate_server_id);
		WorldAccount* FindAccountByAccountName(const std::string& account_name);
		int GetLowestLoadGateServerId();
	};
}