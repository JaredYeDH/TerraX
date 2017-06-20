#pragma once
#include <memory>
#include "srv/net/server_conn_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	//用继承实现子类instance
	class LoginConnService : public ServerConnService
	{
		MAKE_INSTANCE(LoginConnService);
		DISABLE_COPY(LoginConnService);

	private:
		TcpConnection* conn_master_{ nullptr };
		int login_server_id_{ 0 };
	public:
		LoginConnService();
		~LoginConnService() {}

		int get_login_server_id() const { return login_server_id_; }

		void Connect2Master(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);
		void SendPacket2Master(google::protobuf::Message& msg);

		void OnMasterConnected(TcpConnection* conn);
		void OnMasterDisconnected(TcpConnection* conn);

		void OnMessage_SyncLoginServerIdML(packet_ss::MsgSyncLoginServerIdML* msg);
	};
}