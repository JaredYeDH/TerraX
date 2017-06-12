#pragma once

#include "base/types.h"
#include <map>
#include "world_server_object.h"
#include "comm/proto/server_server.pb.h"
namespace terra
{
	class TcpConnection;
	class WorldServerManager
	{
		MAKE_INSTANCE(WorldServerManager);
		DISABLE_COPY(WorldServerManager);
	private:
		std::map<int, WorldServerObject> world_server_map_;

	public:
		WorldServerManager();
		~WorldServerManager() = default;

		void LoadWorldConfig(const std::string& path);

	private:
		void OnMessage_Login2MasterWM(TcpConnection* conn, int32_t avatar_id, packet_ss::MsgLogin2MasterWM* msg);
	};
}
