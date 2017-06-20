#include "world_conn_service.h"
#include "comm/net/packet_dispatcher.h"
#include "world_net_module.h"
#include "world_server_manager/world_server_manager.h"

using namespace terra;
using namespace packet_ss;


WorldConnService::WorldConnService()
{
	REG_PACKET_HANDLER_ARG1(MsgWorldRegAtMasterAckMW, this, OnMessage_WorldRegAtMasterAckMW);
	REG_PACKET_HANDLER_ARG1(MsgReqEnterServerLS, this, OnMessage_ReqEnterServerLS);
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
	WorldNetModule* world_net = static_cast<WorldNetModule*>(net_);
	Login2Master(conn, world_net->get_server_uid()); //temp
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

void WorldConnService::OnMessage_ReqEnterServerLS(MsgReqEnterServerLS* msg)
{
	WorldAccount* account = WorldServerManager::GetInstance().FindAccountByAccountName(msg->account_name());
	if (account)
	{
		//kick out this account;
		return;
	}
	int server_id = WorldServerManager::GetInstance().GetLowestLoadGateServerId();
	NetObject* net_object = server_table_.GetNetObjectByServerID(server_id);
	if (!net_object)
	{
		//gate server not found
		MsgReqEnterServerResultSL ack;
		ack.set_result(1);
		ack.set_account_name(msg->account_name());
		ack.set_login_serverid(msg->login_serverid());
		SendPacket2Master(ack);
		return;
	}
	assert(net_object->peer_type_ == PeerType_t::GATESERVER);
	MsgReqEnterServerResultSL ack;
	ack.set_result(0);
	ack.set_account_name(msg->account_name());
	ack.set_login_serverid(msg->login_serverid());
	ack.set_gate_ip(net_object->listen_ip_);
	ack.set_gate_port(net_object->listen_port_);
	SendPacket2Master(ack);
}