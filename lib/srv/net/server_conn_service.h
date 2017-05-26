#pragma once
#include "comm/net/tcp_connection.h"
#include <memory>
#include "net_base_module.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class ServerConnService
	{
	private:
		NetBaseModule& net_;
		const PeerType_t kSelfPeer;
		ServerTable& server_table_;
		PacketProcessor& packet_processor_;

		std::unique_ptr<TcpConnection> conn_;
	public:
		ServerConnService(NetBaseModule& net);
		~ServerConnService();

		void Login2World(TcpConnection* conn);
		void Login2Node(TcpConnection* conn);

		TcpConnection* Connect(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);

	private:
		void OnMessage_RegisterWS(packet_ss::MsgRegisterWS* msg);
	};
}