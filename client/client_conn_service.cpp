#include "client_conn_service.h"
#include "comm/net/packet_dispatcher.h"
#include <algorithm>

using namespace terra;

ClientConnService::ClientConnService()
	:
	packet_processor_(ClientPacketProcessor::GetInstance())
{
}
ClientConnService::~ClientConnService()
{
}


TcpConnection* ClientConnService::NewConnect(const char* ip, int port,
	SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	std::unique_ptr<TcpConnection>  conn(new TcpConnection(net_->get_event_loop(), ip, port, sock_cb, msg_cb));
	TcpConnection* ret_conn = conn.get();
	conns_.push_back(std::move(conn));
	return ret_conn;
}

void ClientConnService::DestroyConnection(TcpConnection* conn)
{
	auto iter = std::find_if(conns_.begin(), conns_.end(),
		[conn](const std::unique_ptr<TcpConnection>& val) {
		return val.get() == conn;
	});
	if (iter != conns_.end())
	{
		conns_.erase(iter);
	}
}