#include "world_conn_service.h"
#include "comm/net/packet_dispatcher.h"


using namespace terra;
using namespace packet_ss;


WorldConnService::WorldConnService()
{
	REG_PACKET_HANDLER_ARG1(MsgWorldRegAtMasterAckMW, this, OnMessage_WorldRegAtMasterAckMW);
}

void WorldConnService::Login2Master(TcpConnection* conn, int server_uid)
{
	MsgWorldRegAtMasterWM msg;
	msg.set_server_uid(server_uid);
	net_->SendPacket(conn, msg);
}

void WorldConnService::OnMessage_WorldRegAtMasterAckMW(MsgWorldRegAtMasterAckMW* msg)
{
	int result = msg->result();
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "Register Result: %d", result);
}
