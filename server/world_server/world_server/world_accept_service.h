#pragma once

#include "base/types.h"
#include <queue>
#include "srv/net/server_accept_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class WorldAcceptService : public ServerAcceptService
	{
		MAKE_INSTANCE(WorldAcceptService);
		DISABLE_COPY(WorldAcceptService);
	protected:
		std::queue<int> server_ids_;
	public:
		WorldAcceptService();
		~WorldAcceptService() = default;
		void InitAvaliableIDCount(uint32_t server_ids);
		void OnLogout(TcpConnection* conn);
	private:
		void OnMessage_RegisterSW(TcpConnection* conn, int32_t avatar_id, packet_ss::MsgRegisterSW* msg);
	};
}