#pragma once

#include "base/types.h"
#include "srv/net/net_base_module.h"
#include "master_world_accept_service.h"

namespace terra
{
	class MasterNetModule : public NetBaseModule
	{
		DISABLE_COPY(MasterNetModule);
		MAKE_INSTANCE(MasterNetModule);
	private:
		MasterWorldAcceptService& master_world_accept_service_;
	public:
		MasterNetModule();
		~MasterNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();
	private:
		void InitmasterNetInfo();
		void StartAccept();

		void OnSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnAddNetObjectEvent(const std::vector<NetObject>& objs, const NetObject& net_obj);
	};
}