#include "node_conn_service.h"
#include "comm/net/packet_dispatcher.h"
#include "node_net_module.h"

using namespace terra;
using namespace packet_ss;


NodeConnService::NodeConnService()
{
}

void NodeConnService::Connect2World(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	TcpConnection* conn = Connect(ip, port, sock_cb, msg_cb);
	server_table_.AddServerInfo(PeerType_t::WORLDSERVER, 0, ip,
		port, conn);
}

void NodeConnService::Login2World(TcpConnection* conn)
{
	MsgRegisterSW msg;
	msg.set_peer_type(static_cast<int>(net_->get_peer_type()));
	msg.set_listen_ip(net_->get_listen_ip());
	msg.set_listen_port(net_->get_listen_port());
	packet_processor_.SendPacket(conn, msg);
}



void NodeConnService::OnWorldConnected(TcpConnection* conn)
{
	Login2World(conn);
};
void NodeConnService::OnWorldDisconnected(TcpConnection* conn)
{
	server_table_.RemoveByConn(conn);
	DestroyConnection(conn);
	// ReConnect();
}
