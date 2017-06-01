#pragma once
#include <memory>
#include "comm/net/tcp_connection.h"
#include "client_net_module.h"


namespace terra
{
	class ClientConnService
	{
		MAKE_INSTANCE(ClientConnService);
		DISABLE_COPY(ClientConnService);

	private:
		ClientNetModule* net_;
		ClientPacketProcessor& packet_processor_;
		std::vector<std::unique_ptr<TcpConnection>> conns_;
	public:
		ClientConnService();
		~ClientConnService();

		void InitNetModule(ClientNetModule* net) { net_ = net; }

		TcpConnection* NewConnect(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);
		void DestroyConnection(TcpConnection* conn);
	private:
	};
}