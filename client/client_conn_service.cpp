#include "server_conn_service.h"
#include "comm/net/packet_dispatcher.h"
#include <algorithm>

using namespace terra;
using namespace packet_ss;

ClientConnService::ClientConnService()
	:
	server_table_(ServerTable::GetInstance()),
	packet_processor_(PacketProcessor::GetInstance())
{
	REG_PACKET_HANDLER_ARG1(MsgRegisterWS, this, OnMessage_RegisterWS);
}
ClientConnService::~ClientConnService()
{
}

void ClientConnService::Login2World(TcpConnection* conn)
{
	MsgRegisterSW msg;
	msg.set_peer_type(static_cast<int>(net_->get_peer_type()));
	msg.set_listen_ip(net_->get_listen_ip());
	msg.set_listen_port(net_->get_listen_port());
	packet_processor_.SendPacket(conn, msg);
}

void ClientConnService::Login2Node(TcpConnection* conn)
{
	MsgLogin2NodeGN msg;
	msg.set_peer_type(static_cast<int>(net_->get_peer_type()));
	msg.set_server_id(server_table_.get_self_server_id());
	packet_processor_.SendPacket(conn, msg);
}


TcpConnection* ClientConnService::NewConnect(const char* ip, int port,
	SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	std::unique_ptr<TcpConnection>  conn(new TcpConnection(net_->get_event_loop(), ip, port, sock_cb, msg_cb));
	TcpConnection* ret_conn = conn.get();
	conns_.push_back(std::move(conn));
	return ret_conn;
}

void ClientConnService::OnMessage_RegisterWS(MsgRegisterWS* msg)
{
	int server_id = msg->server_id();
	server_table_.InitSelfServerInfo(net_->get_peer_type(), server_id);
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "register success! server id: %d", server_id);
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