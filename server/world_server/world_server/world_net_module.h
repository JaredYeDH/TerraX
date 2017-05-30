#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "world_accept_service.h"

namespace terra
{
	class WorldNetModule : public NetBaseModule
	{
		DISABLE_COPY(WorldNetModule);
		MAKE_INSTANCE(WorldNetModule);
	private:
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
		void StartAccept();

		void OnSocketEvent(TcpConnection* conn, ConnState_t conn_state);
		void OnMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnAddNetObjectEvent(const std::vector<NetObject>& objs, const NetObject& net_obj);
	};
}