#include "master_world_accept_service.h"
#include "comm/net/packet_dispatcher.h"
#include "server_manager/server_manager.h"

using namespace terra;
using namespace packet_ss;

MasterWorldAcceptService::MasterWorldAcceptService()
{
	REG_PACKET_HANDLER_ARG3(MsgWorldRegAtMasterWM, this, OnMessage_WorldRegAtMasterWM);
}

void MasterWorldAcceptService::OnWorldConnected(TcpConnection* conn)
{

}

void MasterWorldAcceptService::OnWorldDisconnected(TcpConnection* conn)
{

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
	obj->InitTcpConnection(conn);
	obj->RefreshWorldServerInfo(FREE);

	MsgWorldRegAtMasterAckMW ack;
	ack.set_result(0);
	net_->SendPacket(conn, ack);
}