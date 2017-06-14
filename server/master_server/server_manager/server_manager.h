#pragma once

#include "base/types.h"
#include <map>
#include "world_server_object.h"
#include "login_server_object.h"
#include "comm/proto/server_server.pb.h"
namespace terra
{
	class TcpConnection;
	class ServerManager
	{
		MAKE_INSTANCE(ServerManager);
		DISABLE_COPY(ServerManager);
	private:
		std::map<int, WorldServerObject> world_server_map_;
		std::map<int, LoginServerObject> login_server_map_;
	public:
		ServerManager();
		~ServerManager() = default;

		void LoadWorldConfig(const std::string& path);

		void CreateLoginServerObj(TcpConnection* conn);
		void RemoveLoginServerObj(TcpConnection* conn);
	private:
		void OnMessage_Login2MasterWM(TcpConnection* conn, int32_t avatar_id, packet_ss::MsgLogin2MasterWM* msg);
	};
}