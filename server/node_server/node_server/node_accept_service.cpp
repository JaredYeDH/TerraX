#include "node_accept_service.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;
using namespace packet_ss;

NodeAcceptService::NodeAcceptService(NetBaseModule& net, uint32_t aceept_max_conns)
	: ServerAcceptService(net, aceept_max_conns)
{
	REG_PACKET_HANDLER_ARG3(MsgLogin2NodeGN, this, OnMessage_Login2NodeGN);
}

void NodeAcceptService::OnLogout(TcpConnection* conn)
{
	NetObject* net_object = server_table_.GetNetObjectByConn(conn);
	assert(net_object);
}

void NodeAcceptService::OnMessage_Login2NodeGN(TcpConnection* conn, int32_t avatar_id, MsgLogin2NodeGN* msg)
{
	int peer_type = msg->peer_type();
	assert(peer_type == static_cast<int>(PeerType_t::GATESERVER));
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "%s:\t %d", NetHelper::ServerName((PeerType_t)peer_type), msg->server_id());

	server_table_.AddServerInfo(static_cast<PeerType_t>(peer_type), msg->server_id(), "", 0, conn);
}