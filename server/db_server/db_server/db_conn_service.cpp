#include "db_conn_service.h"
#include "comm/net/packet_dispatcher.h"
#include "db_net_module.h"

using namespace terra;
using namespace packet_ss;


DBConnService::DBConnService()
{
}

void DBConnService::Connect2World(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	TcpConnection* conn = Connect(ip, port, sock_cb, msg_cb);
	server_table_.AddServerInfo(PeerType_t::WORLDSERVER, 0, ip,
		port, conn);
}

void DBConnService::Login2World(TcpConnection* conn)
{
	DBNetModule* node_net = static_cast<DBNetModule*>(net_);
	MsgRegisterSW msg;
	msg.set_peer_type(static_cast<int>(net_->get_peer_type()));
	msg.set_listen_ip(node_net->get_gate_listen_ip());
	msg.set_listen_port(node_net->get_gate_listen_port());
	packet_processor_.SendPacket(conn, msg);
}



void DBConnService::OnWorldConnected(TcpConnection* conn)
{
	Login2World(conn);
};
void DBConnService::OnWorldDisconnected(TcpConnection* conn)
{
	server_table_.RemoveByConn(conn);
	DestroyConnection(conn);
	// ReConnect();
}
