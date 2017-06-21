#include "world_accept_service.h"
#include "comm/net/packet_dispatcher.h"
#include "world_server_manager/world_server_manager.h"

using namespace terra;
using namespace packet_ss;

WorldAcceptService::WorldAcceptService()
{
	REG_PACKET_HANDLER_ARG3(MsgRegisterSW, this, OnMessage_RegisterSW);


	server_table_.SetAddNetObjectEventCB(
		[this](const std::vector<NetObject>& objs, const NetObject& net_obj) {
		this->OnAddNetObjectEvent(objs, net_obj);
	});
}

void WorldAcceptService::InitAvaliableIDCount(uint32_t server_ids)
{
	for (std::size_t i = 1; i < server_ids; i++) {
		server_ids_.push(i);
	}
}

void WorldAcceptService::OnServerConnected(TcpConnection* conn)
{
}

void WorldAcceptService::OnServerDisconnected(TcpConnection* conn)
{
	NetObject* net_object = server_table_.GetNetObjectByConn(conn);
	assert(net_object);
	server_ids_.push(net_object->server_id_);
	server_table_.RemoveByConn(conn);
}


void WorldAcceptService::OnMessage_RegisterSW(TcpConnection* conn, int32_t avatar_id, MsgRegisterSW* msg)
{
	assert(server_ids_.size() > 0);

	int server_id = server_ids_.front();
	server_ids_.pop();
	int peer_type = msg->peer_type();

	CONSOLE_DEBUG_LOG(LEVEL_INFO, "%s:\t %d", NetHelper::ServerName((PeerType_t)peer_type), server_id);

	server_table_.AddServerInfo(static_cast<PeerType_t>(peer_type), server_id, msg->listen_ip().c_str(), msg->listen_port(), conn);
	if (peer_type == static_cast<int>(PeerType_t::GATESERVER))
	{
		WorldServerManager::GetInstance().CreateAccountMapByGateId(server_id);
	}
}

void WorldAcceptService::OnAddNetObjectEvent(const std::vector<NetObject>& objs, const NetObject& net_obj)
{
	MsgRegisterWS msg2Me;
	msg2Me.set_server_id(net_obj.server_id_);
	packet_processor_.SendPacket(net_obj.conn_, msg2Me);

	if (net_obj.peer_type_ == PeerType_t::GATESERVER) {
		MsgServerInfoWS msg;
		for (const auto& obj : objs) {
			if (obj.peer_type_ == PeerType_t::NODESERVER) {
				const auto& srv_info = msg.add_server_info();
				srv_info->set_peer_type(int(obj.peer_type_));
				srv_info->set_server_id(obj.server_id_);
				srv_info->set_listen_ip(obj.listen_ip_);
				srv_info->set_listen_port(obj.listen_port_);
			}
		}
		packet_processor_.SendPacket(net_obj.conn_, msg);
	}
	else if (net_obj.peer_type_ == PeerType_t::NODESERVER) {
		for (const auto& obj : objs) {
			if (obj.peer_type_ == PeerType_t::GATESERVER) {
				MsgServerInfoWS msg;
				const auto& srv_info = msg.add_server_info();
				srv_info->set_peer_type(int(net_obj.peer_type_));
				srv_info->set_server_id(net_obj.server_id_);
				srv_info->set_listen_ip(net_obj.listen_ip_);
				srv_info->set_listen_port(net_obj.listen_port_);
				packet_processor_.SendPacket(obj.conn_, msg);
			}
		}
	}
	else {
	}
}