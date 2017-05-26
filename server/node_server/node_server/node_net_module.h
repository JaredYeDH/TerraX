#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "srv/net/server_conn_service.h"
#include "srv/net/server_accept_service.h"

namespace terra
{
	//TODO: connservice 继承 根据不同server实现
	class ServerConnService;
	class NodeNetModule final : public NetBaseModule
	{
		DISABLE_COPY(NodeNetModule);
		MAKE_INSTANCE(NodeNetModule);
	private:
		std::unique_ptr<ServerConnService> world_conn_service_;
		std::unique_ptr<ServerAcceptService> gate_accept_service_;
	public:
		NodeNetModule();
		~NodeNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Execute();
		bool BeforeShut();
		bool Shut();
	private:
		void InitNodeNetInfo();
		void StartConnectWorldServer();
		void StartAcceptGateServer();
		//void AcceptClient() {};
		//void OnClientSocketEvent(TcpConnection* conn, ConnState_t conn_state) {};
		//void OnClientMessage(TcpConnection* conn, evbuffer* evbuf) {};

		void OnSocketEvent(TcpConnection* conn, ConnState_t conn_state);
		void OnMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnWorldConnected(TcpConnection* conn);
		void OnWorldDisconnected(TcpConnection* conn);

		void OnGateConnected(TcpConnection* conn);
		void OnGateDisconnected(TcpConnection* conn);


	};
}