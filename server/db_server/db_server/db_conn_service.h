#pragma once
#include <memory>
#include "srv/net/server_conn_service.h"

namespace terra
{
	//用继承实现子类instance
	class DBConnService : public ServerConnService
	{
		MAKE_INSTANCE(DBConnService);
		DISABLE_COPY(DBConnService);

	private:
	public:
		DBConnService();
		~DBConnService() {}

		void Connect2World(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);


		void OnWorldConnected(TcpConnection* conn);
		void OnWorldDisconnected(TcpConnection* conn);

	private:
		void Login2World(TcpConnection* conn);
	};
}