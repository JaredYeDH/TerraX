#include "world_conn_service.h"
#include "comm/net/packet_dispatcher.h"


using namespace terra;
using namespace packet_ss;


WorldConnService::WorldConnService()
{
	REG_PACKET_HANDLER_ARG1(MsgWorldRegAtMasterAckMW, this, OnMessage_WorldRegAtMasterAckMW);
}

void WorldConnService::Connect2Master(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	conn_master_ = Connect(ip, port, sock_cb, msg_cb);
}

void WorldConnService::Login2Master(TcpConnection* conn, int server_uid)
{
	MsgWorldRegAtMasterWM msg;
	msg.set_server_uid(server_uid);
	net_->SendPacket(conn, msg);
}

void WorldConnService::SendPacket2Master(google::protobuf::Message& msg)
{
	packet_processor_.SendPacket(conn_master_, msg);
}

void WorldConnService::OnMasterConnected(TcpConnection* conn)
{
	Login2Master(conn, 1); //temp
};
void WorldConnService::OnMasterDisconnected(TcpConnection* conn)
{
	DestroyConnection(conn);
	conn_master_ = nullptr;
	// ReConnect();
}

void WorldConnService::OnMessage_WorldRegAtMasterAckMW(MsgWorldRegAtMasterAckMW* msg)
{
	int result = msg->result();
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "Register Result: %d", result);
}
