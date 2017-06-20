#pragma once
#include <memory>
#include "srv/net/server_conn_service.h"

namespace terra
{
	class WorldConnService : public ServerConnService
	{
		MAKE_INSTANCE(WorldConnService);
		DISABLE_COPY(WorldConnService);

	private:
		TcpConnection* conn_master_{ nullptr };
	public:
		WorldConnService();
		~WorldConnService() {}
		void Connect2Master(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);
		void SendPacket2Master(google::protobuf::Message& msg);

		void OnMasterConnected(TcpConnection* conn);
		void OnMasterDisconnected(TcpConnection* conn);
	private:
		void Login2Master(TcpConnection* conn, int server_uid);

		void OnMessage_WorldRegAtMasterAckMW(packet_ss::MsgWorldRegAtMasterAckMW* msg);
		void OnMessage_ReqEnterServerLS(packet_ss::MsgReqEnterServerLS* msg);
	};
}