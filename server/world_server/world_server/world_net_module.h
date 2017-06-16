#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "world_accept_service.h"
#include "world_conn_service.h"

namespace terra
{
	class WorldNetModule : public NetBaseModule
	{
		DISABLE_COPY(WorldNetModule);
		MAKE_INSTANCE(WorldNetModule);
	private:
		WorldConnService& world_conn_service_;
		WorldAcceptService& world_accept_service_;

		int server_uid_{ 0 };
		std::string master_conn_ip_;
		int master_conn_port_{ 0 };
		std::string server_listen_ip_;
		int server_listen_port_{ 0 };
	public:
		WorldNetModule();
		~WorldNetModule() = default;

		int get_server_uid() const { return server_uid_; }
		const char* get_master_conn_ip() const { return master_conn_ip_.c_str(); }
		int get_master_conn_port()  const { return master_conn_port_; }
		const char* get_server_listen_ip() const { return server_listen_ip_.c_str(); }
		int get_server_listen_port()  const { return server_listen_port_; }

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();
	private:
		void InitWorldNetInfo();
		void StartConnectMaster();
		void StartAccept();

		void OnServerSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnServerMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnMasterSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnMasterMessageEvent(TcpConnection* conn, evbuffer* evbuf);

	};
}