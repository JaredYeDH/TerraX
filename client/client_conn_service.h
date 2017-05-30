#pragma once
#include <memory>
#include "comm/net/tcp_connection.h"
#include "comm/proto/server_server.pb.h"
#include "client_net_module.h"


namespace terra
{
	class ClientConnService
	{
		MAKE_INSTANCE(ClientConnService);
		DISABLE_COPY(ClientConnService);

	private:
		ClientNetModule* net_;
		PacketProcessor& packet_processor_;
		std::vector<std::unique_ptr<TcpConnection>> conns_;
	public:
		ClientConnService();
		~ClientConnService();

		void InitNetModule(ClientNetModule* net) { net_ = net; }

		void Login2World(TcpConnection* conn);
		void Login2Node(TcpConnection* conn);

		TcpConnection* NewConnect(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);
		void DestroyConnection(TcpConnection* conn);
	private:
		void OnMessage_RegisterWS(packet_ss::MsgRegisterWS* msg);
	};
}