#include "master_login_accept_service.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;
using namespace packet_ss;

MasterLoginAcceptService::MasterLoginAcceptService()
{
	REG_PACKET_HANDLER_ARG3(MsgRegisterSW, this, OnMessage_RegisterSW);
}

void MasterLoginAcceptService::OnMessage_RegisterSW(TcpConnection* conn, int32_t avatar_id, MsgRegisterSW* msg)
{
	assert(server_ids_.size() > 0);

	int server_id = server_ids_.front();
	server_ids_.pop();
	int peer_type = msg->peer_type();

	CONSOLE_DEBUG_LOG(LEVEL_INFO, "%s:\t %d", NetHelper::ServerName((PeerType_t)peer_type), server_id);

	server_table_.AddServerInfo(static_cast<PeerType_t>(peer_type), server_id, msg->listen_ip().c_str(), msg->listen_port(), conn);
}