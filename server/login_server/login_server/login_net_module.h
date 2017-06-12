#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "srv/net/server_conn_service.h"
#include "srv/net/server_accept_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class ServerConnService;
	class LoginNetModule final : public NetBaseModule
	{
		DISABLE_COPY(LoginNetModule);
		MAKE_INSTANCE(LoginNetModule);
	private:
		ServerConnService& conn_service_;
		ServerAcceptService& accpet_service_;
	public:
		LoginNetModule();
		~LoginNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();
		//TODO: packet_processor不要有server_table，只能通过conn发送消息
		//		server_table通过外部包装
		//		通过继承实现acceptservice instance
		//		GateAccount, GateAvatar
		//		断线逻辑 world->gate->node
		void SendPacket2Master(google::protobuf::Message& msg);
		void SendPacket2Client(TcpConnection* conn, google::protobuf::Message& msg);
		void SendPacket2Client(const std::string& account_name, google::protobuf::Message& msg);
	private:
		void InitLoginNetInfo();
		void StartConnectMasterServer();
		void StartAcceptClient();
		//void OnClientSocketEvent(TcpConnection* conn, SocketEvent_t ev) {};
		//void OnClientMessage(TcpConnection* conn, evbuffer* evbuf) {};

		void OnServerSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnServerMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnClientSocketEvent(TcpConnection* conn, SocketEvent_t ev) {};
		void OnClientMessageEvent(TcpConnection* conn, evbuffer* evbuf) {};

		void OnMasterConnected(TcpConnection* conn);
		void OnMasterDisconnected(TcpConnection* conn);

		void OnClientConnected(TcpConnection* conn);
		void OnClientDisconnected(TcpConnection* conn);

	};
}