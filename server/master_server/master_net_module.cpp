#include "master_net_module.h"

#include "comm/config/server_config.h"

using namespace terra;
using namespace packet_ss;

MasterNetModule::MasterNetModule()
    : NetBaseModule(PeerType_t::MASTERSERVER), master_accept_service_(MasterAcceptService::GetInstance())
{
    master_accept_service_.InitNetModule(this);
    server_table_.SetAddNetObjectEventCB(
        [this](const std::vector<NetObject>& objs, const NetObject& net_obj) {
            this->OnAddNetObjectEvent(objs, net_obj);
        });
}

void MasterNetModule::InitmasterNetInfo()
{
    ServerConfig::GetInstance().LoadConfigFromJson("master_server.json");
    std::string ip;
    int port;
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_ip", ip);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_port", port);
    InitListenInfo(ip, port);
}

void MasterNetModule::StartAccept()
{
    master_accept_service_.InitAvaliableIDCount(64);
    master_accept_service_.AcceptConnection(
        get_listen_port(), 64,
        [this](TcpConnection* conn, SocketEvent_t ev) { this->OnSocketEvent(conn, ev); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnMessageEvent(conn, evbuf); });
}

bool MasterNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "master Server Start...");
    InitmasterNetInfo();
    StartAccept();
    return true;
}
bool MasterNetModule::AfterInit() { return true; }
bool MasterNetModule::Tick()
{
    get_event_loop()->loop();
    return true;
}
bool MasterNetModule::BeforeShut() { return true; }
bool MasterNetModule::Shut() { return true; }

void MasterNetModule::OnSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
    switch (ev) {
        case SocketEvent_t::CONNECTED: {
        } break;
		case SocketEvent_t::CONNECT_ERROR:
        case SocketEvent_t::DISCONNECTED: {
            master_accept_service_.OnLogout(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}
void MasterNetModule::OnMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}

void MasterNetModule::OnAddNetObjectEvent(const std::vector<NetObject>& objs, const NetObject& net_obj)
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
    } else if (net_obj.peer_type_ == PeerType_t::NODESERVER) {
        for (const auto& obj : objs) {
			if (obj.peer_type_ == PeerType_t::GATESERVER) {
				MsgServerInfoWS msg;
                const auto& srv_info = msg.add_server_info();
                srv_info->set_peer_type(int(net_obj.peer_type_));
                srv_info->set_server_id(net_obj.server_id_);
                srv_info->set_listen_ip(net_obj.listen_ip_);
                srv_info->set_listen_port(net_obj.listen_port_);
                packet_processor_.SendPacket(obj.conn_, msg);
                std::cout << __FUNCTION__ << std::endl;
            }
        }
    } else {
    }
}