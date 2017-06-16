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
		std::string world_conn_ip_;
		int world_conn_port_{ 0 };
		std::string client_listen_ip_;
		int client_listen_port_{ 0 };
	public:
		GateNetModule();
		~GateNetModule() = default;

		const char* get_world_conn_ip() const { return world_conn_ip_.c_str(); }
		int get_world_conn_port()  const { return world_conn_port_; }
		const char* get_client_listen_ip() const { return client_listen_ip_.c_str(); }
		int get_client_listen_port()  const { return client_listen_port_; }

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