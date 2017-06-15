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
	public:
		WorldNetModule();
		~WorldNetModule() = default;

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

		void OnAddNetObjectEvent(const std::vector<NetObject>& objs, const NetObject& net_obj);
	};
}