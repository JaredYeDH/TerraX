#pragma once

#include "base/types.h"
#include <queue>
#include "srv/net/server_accept_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	//login server object
	//合并成一个server manager?
	class GateAcceptService : public ServerAcceptService
	{
		MAKE_INSTANCE(GateAcceptService);
		DISABLE_COPY(GateAcceptService);
	public:
		GateAcceptService();
		~GateAcceptService() = default;

		void SendPacketByAccountName(const std::string& account_name, google::protobuf::Message& msg); 
		
		void OnClientConnected(TcpConnection* conn);
		void OnClientDisconnected(TcpConnection* conn);
	};
}