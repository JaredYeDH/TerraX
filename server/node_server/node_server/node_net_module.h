#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "srv/net/server_conn_service.h"
#include "node_accept_service.h"

namespace terra
{
	class ServerConnService;
	class NodeNetModule final : public NetBaseModule
	{
		DISABLE_COPY(NodeNetModule);
		MAKE_INSTANCE(NodeNetModule);
	private:
		ServerConnService& conn_service_;
		NodeAcceptService& node_accept_service;
	public:
		NodeNetModule();
		~NodeNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();
	private:
		void InitNodeNetInfo();
		void StartConnectWorldServer();
		void StartAccept();
		//void AcceptClient() {};
		//void OnClientSocketEvent(TcpConnection* conn, ConnState_t conn_state) {};
		//void OnClientMessage(TcpConnection* conn, evbuffer* evbuf) {};

		void OnWorldSocketEvent(TcpConnection* conn, ConnState_t conn_state);
		void OnWorldMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnWorldConnected(TcpConnection* conn);
		void OnWorldDisconnected(TcpConnection* conn);

		void OnGateSocketEvent(TcpConnection* conn, ConnState_t conn_state);
		void OnGateMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnGateConnected(TcpConnection* conn);
		void OnGateDisconnected(TcpConnection* conn);


	};
}