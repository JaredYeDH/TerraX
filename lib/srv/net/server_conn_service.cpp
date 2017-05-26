#include "server_conn_service.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;
using namespace packet_ss;

ServerConnService::ServerConnService(NetBaseModule& net)
	: net_(net),
	kSelfPeer(net.get_peer_type()),
	server_table_(net.get_server_table()),
	packet_processor_(net.get_packet_processor())
{
	REG_PACKET_HANDLER_ARG1(MsgRegisterWS, this, OnMessage_RegisterWS);
}
ServerConnService::~ServerConnService() {}

void ServerConnService::Login2World(TcpConnection* conn)
{
	MsgRegisterSW msg;
	msg.set_peer_type(static_cast<int>(kSelfPeer));
	msg.set_listen_ip(net_.get_listen_ip());
	msg.set_listen_port(net_.get_listen_port());
	packet_processor_.SendPacket(conn, msg);
}

void ServerConnService::Login2Node(TcpConnection* conn)
{
	MsgLogin2NodeGN msg;
	msg.set_peer_type(static_cast<int>(kSelfPeer));
	msg.set_server_id(server_table_.get_self_server_id());
	packet_processor_.SendPacket(conn, msg);
}


TcpConnection* ServerConnService::Connect(const char* ip, int port,
                                SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	conn_.reset(new TcpConnection(net_.get_event_loop(), ip, port, sock_cb, msg_cb));
	return conn_.get();
}

void ServerConnService::OnMessage_RegisterWS(MsgRegisterWS* msg)
{
	int server_id = msg->server_id();
	server_table_.InitSelfServerInfo(kSelfPeer, server_id);
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "register success! server id: %d", server_id);
}
