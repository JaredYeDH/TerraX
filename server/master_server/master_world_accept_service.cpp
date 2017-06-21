#include "master_world_accept_service.h"
#include "comm/net/packet_dispatcher.h"
#include "server_manager/server_manager.h"

using namespace terra;
using namespace packet_ss;

MasterWorldAcceptService::MasterWorldAcceptService()
{
	REG_PACKET_HANDLER_ARG3(MsgWorldRegAtMasterWM, this, OnMessage_WorldRegAtMasterWM);
	REG_PACKET_HANDLER_ARG1(MsgReqEnterServerResultSL, this, OnMessage_ReqEnterServerResultSL);
}

void MasterWorldAcceptService::OnWorldConnected(TcpConnection* conn)
{

}

void MasterWorldAcceptService::OnWorldDisconnected(TcpConnection* conn)
{
	WorldServerObject* obj = ServerManager::GetInstance().FindWorldServerByConn(conn);
	if (obj)
	{
		obj->ClearConnection();
		obj->RefreshWorldServerInfo(MAINTAIN);
	}
}

void MasterWorldAcceptService::OnMessage_WorldRegAtMasterWM(TcpConnection* conn, int32_t avatar_id, MsgWorldRegAtMasterWM* msg)
{
	int server_uid = msg->server_uid();
	WorldServerObject* obj = ServerManager::GetInstance().FindWorldServerByUID(server_uid);
	if (!obj)
	{
		MsgWorldRegAtMasterAckMW ack;
		ack.set_result(1);
		net_->SendPacket(conn, ack);
		return;
	}
	obj->InitConnection(conn);
	obj->RefreshWorldServerInfo(FREE);

	MsgWorldRegAtMasterAckMW ack;
	ack.set_result(0);
	net_->SendPacket(conn, ack);
}

void MasterWorldAcceptService::OnMessage_ReqEnterServerResultSL(MsgReqEnterServerResultSL* msg)
{
	LoginServerObject* login_obj = ServerManager::GetInstance().FindLoginServerById(msg->login_serverid());
	if (login_obj)
	{
		SendPacket(login_obj->get_conn(), *msg);
	}
}
