#pragma once
#include "ComDef.h"
#include "NetDefine.h"
#include "proto/server_server.pb.h"
#include <array>
#include <queue>
#include <map>
#include <cassert>
#include "ServerAddrManager.h"

using namespace S2SPacket;
namespace TerraX
{
	class CenterServer;
	class NetChannel;

	const int MAX_GATE_CONNECTION_COUNT = 4;
	const int MAX_GAME_CONNECTION_COUNT = 4;
	const int MAX_WORLD_CONNECTION_COUNT = 1;

	class ConnectionManager
	{
		NOCOPY(ConnectionManager);
		MAKEINSTANCE(ConnectionManager);
	public:
		ConnectionManager(); 

		void OnMessage_Register(NetChannelPtr& channel, int32_t nFromPeerInfo, PktRegisterServer& pkt);

		void OnChannel_DisConnect(NetChannelPtr& channel);
	private:
		uint8_t GetAvailableConnIdx(PeerType_t peer_type);

	private:
		std::queue<uint8_t> m_queue_gateconnIds;
		std::queue<uint8_t> m_queue_gameconnIds;
		std::queue<uint8_t> m_queue_worldconnIds;
		ServerAddrManager m_SrvAddrManager;
	};
}