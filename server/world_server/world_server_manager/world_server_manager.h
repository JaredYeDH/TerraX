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
	private:
	public:
		WorldServerManager() = default;
		~WorldServerManager() = default;

		void OnGateServerConnected(int server_id);
	};
}