#pragma once
#include "base/types.h"
#include <map>
#include <unordered_map>
#include "gate_load_info.h"
#include "node_load_info.h"

namespace terra
{
	class WorldLoadBalancingManager
	{
		MAKE_INSTANCE(WorldLoadBalancingManager);
		DISABLE_COPY(WorldLoadBalancingManager);
	private:
		std::map<int, std::unique_ptr<GateLoadInfo>> gates_;
		std::map<int, std::unique_ptr<NodeLoadInfo>> nodes_;
	public:
		WorldLoadBalancingManager() = default;
		~WorldLoadBalancingManager() = default;
		int GetLowestLoadGateServerId();
		void CreateGateServer(int server_id);

	};
}