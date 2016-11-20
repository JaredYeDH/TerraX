#pragma once
#include "ComDef.h"
#include "NetDefine.h"
#include "proto/server_packet.pb.h"
#include <queue>
#include <cassert>

using namespace ServerPacket;
namespace TerraX
{
	//you can load these info from config file;
	//index 0 means not registered,so we start with index 1;
	const uint16_t Max_ClientConnection_Count = 1025;

	class GateServer;
	class NetChannel;
	class CltConnectionManager
	{
		NOCOPY(CltConnectionManager);
	public:
		CltConnectionManager(GateServer& cs);

		void OnMessage_RegisterClient(NetChannel& channel, PktRegisterServer& pkt);

	private:
		GateServer& server;
		std::queue<uint16_t> m_freeindexes;

		// maybe we should use shared_ptr?
	};
}