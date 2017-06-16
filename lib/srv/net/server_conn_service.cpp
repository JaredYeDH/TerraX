#include "server_conn_service.h"
#include "comm/net/packet_dispatcher.h"
#include <algorithm>

using namespace terra;
using namespace packet_ss;

ServerConnService::ServerConnService()
	: 
	server_table_(ServerTable::GetInstance()),
	packet_processor_(PacketProcessor::GetInstance())
{
	REG_PACKET_HANDLER_ARG1(MsgRegisterWS, this, OnMessage_RegisterWS);
}
ServerConnService::~ServerConnService() 
{
}


TcpConnection* ServerConnService::Connect(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	std::unique_ptr<TcpConnection>  conn(new TcpConnection(net_->get_event_loop(), ip, port, sock_cb, msg_cb));
	TcpConnection* ret = conn.get();
	conns_.push_back(std::move(conn));
	return ret;
}

void ServerConnService::OnMessage_RegisterWS(MsgRegisterWS* msg)
{
	int server_id = msg->server_id();
	server_table_.InitSelfServerInfo(net_->get_peer_type(), server_id);
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "register success! server id: %d", server_id);
}

void ServerConnService::DestroyConnection(TcpConnection* conn)
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