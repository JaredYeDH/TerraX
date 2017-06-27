#pragma once
#include <memory>
#include "srv/net/server_conn_service.h"

namespace terra
{
	//用继承实现子类instance
	class GateConnService : public ServerConnService
	{
		MAKE_INSTANCE(GateConnService);
		DISABLE_COPY(GateConnService);

	private:
	public:
		GateConnService();
		~GateConnService() {}

		void Connect2World(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);

		void OnServerConnected(TcpConnection* conn);
		void OnServerDisconnected(TcpConnection* conn);

		void OnWorldConnected(TcpConnection* conn);
		void OnWorldDisconnected(TcpConnection* conn);

		void OnNodeConnected(TcpConnection* conn);
		void OnNodeDisconnected(TcpConnection* conn);


		void SendPacketByServerId(int server_id, google::protobuf::Message& msg);
	private:
		void Login2World(TcpConnection* conn);
		void Login2Node(TcpConnection* conn);

		void OnMessage_ServerInfoWS(packet_ss::MsgServerInfoWS* msg);
	};
}