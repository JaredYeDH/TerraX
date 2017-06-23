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
		std::map<int, std::unique_ptr<WorldServerObject>> world_server_map_;
		std::map<int, std::unique_ptr<LoginServerObject>> login_server_map_;
	public:
		ServerManager();
		~ServerManager() = default;

		void LoadWorldConfig(const std::string& path);

		void CreateLoginServerObj(TcpConnection* conn);
		void RemoveLoginServerObj(TcpConnection* conn);

		LoginServerObject* FindLoginServerById(int login_server_id);
		WorldServerObject* FindWorldServerByUID(int server_uid);
		WorldServerObject* FindWorldServerByConn(TcpConnection* conn);


		const std::map<int, std::unique_ptr<WorldServerObject>>& GetWorldServers() { return world_server_map_; }
	};
}
