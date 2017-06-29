#pragma once
#include "base/types.h"
#include <unordered_map>
#include "world_account.h"

namespace terra
{
	class WorldAccount;
	class WorldAccountManager
	{
		MAKE_INSTANCE(WorldAccountManager);
		DISABLE_COPY(WorldAccountManager);
		using WorldAccoutPtr = std::unique_ptr<WorldAccount>;
	private:
		std::unordered_map<std::string, WorldAccoutPtr> accounts_;
	public:
		WorldAccountManager() = default;
		~WorldAccountManager() = default;
		WorldAccount* FindAccountByAccountName(const std::string& account_name);
	};
}