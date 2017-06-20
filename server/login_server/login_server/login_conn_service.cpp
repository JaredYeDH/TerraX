#include "login_conn_service.h"
#include "comm/net/packet_dispatcher.h"
using namespace packet_ss;

using namespace terra;


LoginConnService::LoginConnService()
{
	REG_PACKET_HANDLER_ARG1(MsgSyncLoginServerIdML, this, OnMessage_SyncLoginServerIdML);
}


void LoginConnService::Connect2Master(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	conn_master_ = Connect(ip, port, sock_cb, msg_cb);
}


void LoginConnService::SendPacket2Master(google::protobuf::Message& msg)
{
	packet_processor_.SendPacket(conn_master_, msg);
}

void LoginConnService::OnMasterConnected(TcpConnection* conn)
{

};
void LoginConnService::OnMasterDisconnected(TcpConnection* conn)
{
	DestroyConnection(conn);
	conn_master_ = nullptr;
	// ReConnect();
}

void LoginConnService::OnMessage_SyncLoginServerIdML(packet_ss::MsgSyncLoginServerIdML* msg)
{
	login_server_id_ = msg->server_id();
}