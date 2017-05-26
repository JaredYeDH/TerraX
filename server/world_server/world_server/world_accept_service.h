#pragma once

#include "base/types.h"
#include <queue>
#include "srv/net/server_accept_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class WorldAcceptService : public ServerAcceptService
	{
	protected:
		const int max_conns_;
		std::queue<int> server_ids_;
	public:
		WorldAcceptService(NetBaseModule& net, int aceept_max_conns);
		void OnLogout(TcpConnection* conn);
	private:
		void OnMessage_RegisterSW(TcpConnection* conn, int32_t avatar_id, packet_ss::MsgRegisterSW* msg);
	};
}