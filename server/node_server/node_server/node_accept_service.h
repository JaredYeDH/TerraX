#pragma once

#include "base/types.h"
#include "srv/net/server_accept_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class NodeAcceptService : public ServerAcceptService
	{
		MAKE_INSTANCE(NodeAcceptService);
		DISABLE_COPY(NodeAcceptService);
	protected:
	public:
		NodeAcceptService();
		~NodeAcceptService() = default;
		void OnLogout(TcpConnection* conn);
	private:
		void OnMessage_Login2NodeGN(TcpConnection* conn, int32_t avatar_id, packet_ss::MsgLogin2NodeGN* msg);
	};
}