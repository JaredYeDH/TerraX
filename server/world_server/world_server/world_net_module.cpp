#include "world_net_module.h"

#include "comm/config/server_config.h"

using namespace terra;
using namespace packet_ss;

WorldNetModule::WorldNetModule()
    : NetBaseModule(PeerType_t::WORLDSERVER), 
	world_conn_service_(WorldConnService::GetInstance()),
	world_accept_service_(WorldAcceptService::GetInstance())
{
	world_conn_service_.InitNetModule(this);
    world_accept_service_.InitNetModule(this);
    server_table_.SetAddNetObjectEventCB(
        [this](const std::vector<NetObject>& objs, const NetObject& net_obj) {
            this->OnAddNetObjectEvent(objs, net_obj);
        });
}

void WorldNetModule::InitWorldNetInfo()
{
	ServerConfig::GetInstance().LoadConfigFromJson("world_server.json");

	int server_uid;
	std::string conn_ip;
	int conn_port;
	ServerConfig::GetInstance().GetJsonObjectValue("master", "server_uid", server_uid);
	ServerConfig::GetInstance().GetJsonObjectValue("master", "ip", conn_ip);
	ServerConfig::GetInstance().GetJsonObjectValue("master", "port", conn_port);
	InitConnectInfo(conn_ip, conn_port);

    std::string ip;
    int port;
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_ip", ip);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_port", port);
    InitListenInfo(ip, port);
}

void WorldNetModule::StartConnectMaster()
{
	TcpConnection* conn = world_conn_service_.NewConnect(
		conn_ip_.c_str(), conn_port_,
		[this](TcpConnection* conn, SocketEvent_t ev) { this->OnMasterSocketEvent(conn, ev); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnMasterMessageEvent(conn, evbuf); });
	//server_table_.AddServerInfo(PeerType_t::WORLDSERVER, WORD_SERVER_ID, conn_ip_.c_str(), conn_port_, conn);
}

void WorldNetModule::StartAccept()
{
    world_accept_service_.InitAvaliableIDCount(64);
    world_accept_service_.AcceptConnection(
        get_listen_port(), 64,
        [this](TcpConnection* conn, SocketEvent_t ev) { this->OnServerSocketEvent(conn, ev); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnServerMessageEvent(conn, evbuf); });
}

bool WorldNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "World Server Start...");
    InitWorldNetInfo();
	StartConnectMaster();
    StartAccept();
    return true;
}
bool WorldNetModule::AfterInit() { return true; }
bool WorldNetModule::Tick()
{
    get_event_loop()->loop();
    return true;
}
bool WorldNetModule::BeforeShut() { return true; }
bool WorldNetModule::Shut() { return true; }

void WorldNetModule::OnServerSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
    switch (ev) {
        case SocketEvent_t::CONNECTED: {
        } break;
		case SocketEvent_t::CONNECT_ERROR:
        case SocketEvent_t::DISCONNECTED: {
            world_accept_service_.OnLogout(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}
void WorldNetModule::OnServerMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}

void WorldNetModule::OnMasterSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
	switch (ev) {
	case SocketEvent_t::CONNECTED: {
		world_conn_service_.Login2Master(conn, 1); //temp
	} break;
	case SocketEvent_t::CONNECT_ERROR:
	case SocketEvent_t::DISCONNECTED: {
		world_conn_service_.DestroyConnection(conn);
		//server_table_.PrintServerTable();
	} break;
	default:
		break;
	}
}

void WorldNetModule::OnMasterMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
	ProcessServerMessage(conn, evbuf);
}

void WorldNetModule::OnAddNetObjectEvent(const std::vector<NetObject>& objs, const NetObject& net_obj)
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