#include "server_login_ack_service.h"

#include "comm/net/packet_dispatcher.h"

using namespace terra;
using namespace packet_ss;

ServerLoginAckService::ServerLoginAckService(ServerAcceptService& accept_service, PeerType_t peer, int max_conns)
	: accept_service_(accept_service),
	server_table_(accept_service.get_net_base_module().get_server_table()),
	packet_processor_(accept_service.get_net_base_module().get_packet_processor()),
	kSelfPeer(peer),
	max_conns_(max_conns)
{
    for (int i = 1; i < max_conns_; i++) {
        server_ids_.push(i);
    }
	server_table_.SetAddNetObjectEventCB(
        [this](const std::vector<NetObject>& objs, const NetObject& net_obj
               ) { this->OnAddNetObjectEvent(objs, net_obj); });

    REG_PACKET_HANDLER_ARG3(MsgRegisterSW, this, OnMessage_RegisterSW);
}
ServerLoginAckService::~ServerLoginAckService() {}

void ServerLoginAckService::OnLogout(TcpConnection* conn)
{
    NetObject* net_object = server_table_.GetNetObjectByConn(conn);
    assert(net_object);
    server_ids_.push(net_object->server_id_);
}

void ServerLoginAckService::OnAddNetObjectEvent(const std::vector<NetObject>& objs, const NetObject& net_obj)
{
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
    } else if (net_obj.peer_type_ == PeerType_t::NODESERVER) {
        for (const auto& obj : objs) {
            if (obj.peer_type_ == PeerType_t::GATESERVER) {
				MsgServerInfoWS msg;
                const auto& srv_info = msg.add_server_info();
                srv_info->set_peer_type(int(net_obj.peer_type_)); //该node的ip发送给其他gate
                srv_info->set_server_id(net_obj.server_id_);
                srv_info->set_listen_ip(net_obj.listen_ip_);
                srv_info->set_listen_port(net_obj.listen_port_);
				packet_processor_.SendPacket(obj.conn_, msg);
            }
        }
    } else {
    }
}

void ServerLoginAckService::OnMessage_RegisterSW(TcpConnection* conn, int32_t avatar_id, MsgRegisterSW* msg)
{
    assert(server_ids_.size() > 0);

    int server_id = server_ids_.front();
    server_ids_.pop();
    int peer_type = msg->peer_type();

    CONSOLE_DEBUG_LOG(LEVEL_INFO, "%s:\t %d", NetHelper::ServerName(PeerType_t(peer_type)), server_id);

	MsgRegisterWS msgWS;
	msgWS.set_server_id(server_id);
	packet_processor_.SendPacket(conn, msgWS);

	server_table_.AddServerInfo(static_cast<PeerType_t>(peer_type), server_id, msg->listen_ip().c_str(), msg->listen_port(), conn);
}