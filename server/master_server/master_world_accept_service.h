#pragma once

#include "base/types.h"
#include <queue>
#include "srv/net/server_accept_service.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	class MasterWorldAcceptService : public ServerAcceptService
	{
		MAKE_INSTANCE(MasterWorldAcceptService);
		DISABLE_COPY(MasterWorldAcceptService);
	protected:
	public:
		MasterWorldAcceptService();
		~MasterWorldAcceptService() = default;

		void OnWorldConnected(TcpConnection* conn);
		void OnWorldDisconnected(TcpConnection* conn);
	private:
		void OnMessage_WorldRegAtMasterWM(TcpConnection* conn, int32_t avatar_id, packet_ss::MsgWorldRegAtMasterWM* msg);
	};
}