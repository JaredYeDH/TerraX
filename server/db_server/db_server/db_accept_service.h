#pragma once

#include "base/types.h"
#include "srv/net/server_accept_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class DBAcceptService : public ServerAcceptService
	{
		MAKE_INSTANCE(DBAcceptService);
		DISABLE_COPY(DBAcceptService);
	protected:
	public:
		DBAcceptService();
		~DBAcceptService() = default;

		void OnGateConnected(TcpConnection* conn);
		void OnGateDisconnected(TcpConnection* conn);
	private:
		void OnLogout(TcpConnection* conn);
		void OnMessage_Login2NodeGN(TcpConnection* conn, int32_t avatar_id, packet_ss::MsgLogin2NodeGN* msg);
	};
}