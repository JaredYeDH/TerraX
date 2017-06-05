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