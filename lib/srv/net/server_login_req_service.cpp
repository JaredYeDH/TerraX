#include "server_login_req_service.h"

#include "comm/net/packet_dispatcher.h"
#include "net_base_module.h"
#include "packet_processor.h"
#include "server_table.h"

using namespace terra;
using namespace packet_ss;

ServerLoginReqService::ServerLoginReqService(ServerConnService& conn_service, PeerType_t peer)
    : conn_service_(conn_service), kSelfPeer(peer)
{
    REG_PACKET_HANDLER_ARG1(MsgRegisterWS, this, OnMessage_RegisterWS);
    REG_PACKET_HANDLER_ARG1(MsgServerInfoWS, this, OnMessage_ServerInfoWS);
}

void ServerLoginReqService::Login2World(TcpConnection* conn)
{
    MsgRegisterSW msg;
    msg.set_peer_type(static_cast<int>(kSelfPeer));
    msg.set_listen_ip(conn_service_.get_listen_ip());
    msg.set_listen_port(conn_service_.get_listen_port());
    PacketProcessor::GetInstance().SendPacket2World(msg);
}

void ServerLoginReqService::OnLoginOut(TcpConnection* conn) {}

void ServerLoginReqService::OnMessage_RegisterWS(MsgRegisterWS* msg)
{
    int server_id = msg->server_id();
    ServerTable::GetInstance().InitSelfServerInfo(kSelfPeer, server_id);
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "register success! server id: %d", server_id);
}

void ServerLoginReqService::OnMessage_ServerInfoWS(MsgServerInfoWS* msg) 
{
	for (int i = 0; i < msg->server_info_size(); ++i)
	{
		const auto& si = msg->server_info(i);
		TcpConnection* conn = conn_service_.Connect(si.listen_ip().c_str(), si.listen_port(), nullptr, nullptr);
		ServerTable::GetInstance().AddServerInfo(static_cast<PeerType_t>(si.peer_type()), si.server_id(), si.listen_ip().c_str(), si.listen_port(), conn);
	}
}