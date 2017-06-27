#pragma once

#include "base/types.h"
#include <queue>
#include "srv/net/server_accept_service.h"

namespace terra
{
	//login server object
	//合并成一个server manager?
	class LoginAcceptService : public ServerAcceptService
	{
		MAKE_INSTANCE(LoginAcceptService);
		DISABLE_COPY(LoginAcceptService);
	public:
		LoginAcceptService();
		~LoginAcceptService() = default;

		void SendPacketByAccountName(const std::string& account_name, google::protobuf::Message& msg); 
		
		void OnClientConnected(TcpConnection* conn);
		void OnClientDisconnected(TcpConnection* conn);

	};
}