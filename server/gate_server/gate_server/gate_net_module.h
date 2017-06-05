#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "srv/net/server_conn_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class ServerConnService;
	class GateNetModule final : public NetBaseModule
	{
		DISABLE_COPY(GateNetModule);
		MAKE_INSTANCE(GateNetModule);
	private:
		ServerConnService& conn_service_;
	public:
		GateNetModule();
		~GateNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();
	private:
		void InitGateNetInfo();
		void StartConnectWorldServer();
		//void AcceptClient() {};
		//void OnClientSocketEvent(TcpConnection* conn, SocketEvent_t ev) {};
		//void OnClientMessage(TcpConnection* conn, evbuffer* evbuf) {};

		void OnServerSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnServerMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnClientSocketEvent(TcpConnection* conn, SocketEvent_t ev) {};
		void OnClientMessageEvent(TcpConnection* conn, evbuffer* evbuf) {};

		void OnWorldConnected(TcpConnection* conn);
		void OnWorldDisconnected(TcpConnection* conn);

		void OnNodeConnected(TcpConnection* conn);
		void OnNodeDisconnected(TcpConnection* conn);

		void OnMessage_ServerInfoWS(packet_ss::MsgServerInfoWS* msg);
	};
}