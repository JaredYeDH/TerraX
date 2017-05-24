#pragma once
#include "comm/net/tcp_connection.h"
#include <memory>
#include "net_base_module.h"

namespace terra
{
	class ServerLoginReqService;
	class ServerConnService
	{
	private:
		NetBaseModule& net_;
		std::unique_ptr<TcpConnection> conn_;
		std::unique_ptr<ServerLoginReqService> login_req_;
	public:
		ServerConnService(NetBaseModule& net);
		~ServerConnService();

		NetBaseModule& get_net_base_module() { return net_; }
		const char* get_listen_ip() { return net_.get_listen_ip(); }
		int get_listen_port() { return net_.get_listen_port(); }

		void CreateLoginReqService();
		void Login2World(TcpConnection* conn);

		TcpConnection* Connect(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);

	private:
	};
}