#pragma once
#include <memory>
#include "srv/net/server_conn_service.h"

namespace terra
{
	//用继承实现子类instance
	class LoginConnService : public ServerConnService
	{
		MAKE_INSTANCE(LoginConnService);
		DISABLE_COPY(LoginConnService);

	private:
		TcpConnection* conn_master_{ nullptr };
	public:
		LoginConnService();
		~LoginConnService() {}

		void Connect2Master(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);
		void SendPacket2Master(google::protobuf::Message& msg);

		void OnMasterConnected(TcpConnection* conn);
		void OnMasterDisconnected(TcpConnection* conn);
	};
}