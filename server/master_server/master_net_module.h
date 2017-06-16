#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "master_world_accept_service.h"
#include "master_login_accept_service.h"

namespace terra
{
	class MasterNetModule : public NetBaseModule
	{
		DISABLE_COPY(MasterNetModule);
		MAKE_INSTANCE(MasterNetModule);
	private:
		MasterWorldAcceptService& master_world_accept_service_;
		MasterLoginAcceptService& master_login_accept_service_;

		std::string world_listen_ip_;
		int world_listen_port_{ 0 };
		std::string login_listen_ip_;
		int login_listen_port_{ 0 };
	public:
		MasterNetModule();
		~MasterNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();
	private:
		void InitMasterNetInfo();
		void StartAcceptWorldServer();
		void StartAcceptLoginServer();

		void OnWorldSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnWorldMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnLoginSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnLoginMessageEvent(TcpConnection* conn, evbuffer* evbuf);

	};
}