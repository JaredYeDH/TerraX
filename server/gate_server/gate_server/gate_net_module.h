#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "gate_conn_service.h"

namespace terra
{
	class ServerConnService;
	class GateNetModule final : public NetBaseModule
	{
		DISABLE_COPY(GateNetModule);
		MAKE_INSTANCE(GateNetModule);
	private:
		GateConnService& conn_service_;
	public:
		GateNetModule();
		~GateNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();



		void OnServerSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnServerMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnClientSocketEvent(TcpConnection* conn, SocketEvent_t ev) {};
		void OnClientMessageEvent(TcpConnection* conn, evbuffer* evbuf) {};
	private:
		void InitGateNetInfo();
		void StartConnectWorldServer();
		//void AcceptClient() {};
	};
}