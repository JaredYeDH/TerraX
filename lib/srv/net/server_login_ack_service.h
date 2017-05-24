#pragma once
#include "base/types.h"
#include <queue>
#include <vector>
#include "comm/proto/server_server.pb.h"
#include "server_accept_service.h"

namespace terra
{
	class TcpConnection;
	class ServerTable;
	class PacketProcessor;
	class ServerLoginAckService
	{
	private:
		ServerAcceptService& accept_service_;
		ServerTable& server_table_;
		PacketProcessor& packet_processor_;

		const PeerType_t kSelfPeer;
		const int max_conns_;
		std::queue<int> server_ids_;
	public:
		ServerLoginAckService(ServerAcceptService& accept_service, PeerType_t peer, int max_conns);
		~ServerLoginAckService();
		void OnLogout(TcpConnection* conn);
	private:
		void OnAddNetObjectEvent(const std::vector<NetObject>& objs, const NetObject& net_obj);

		void OnMessage_RegisterSW(TcpConnection* conn, int32_t avatar_id, packet_ss::MsgRegisterSW* msg);
	};
}