#pragma once
#include <memory>
#include "srv/net/server_conn_service.h"

namespace terra
{
	//用继承实现子类instance
	class WorldConnService : public ServerConnService
	{
		MAKE_INSTANCE(WorldConnService);
		DISABLE_COPY(WorldConnService);

	private:

	public:
		WorldConnService();
		~WorldConnService(){}

		void Login2Master(TcpConnection* conn, int server_uid);
	private:
		void OnMessage_WorldRegAtMasterAckMW(packet_ss::MsgWorldRegAtMasterAckMW* msg);
	};
}