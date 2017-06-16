#include "world_net_module.h"

#include "comm/config/server_config.h"

using namespace terra;

WorldNetModule::WorldNetModule()
    : NetBaseModule(PeerType_t::WORLDSERVER), 
	world_conn_service_(WorldConnService::GetInstance()),
	world_accept_service_(WorldAcceptService::GetInstance())
{
	world_conn_service_.InitNetModule(this);
    world_accept_service_.InitNetModule(this);
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
	world_conn_service_.Connect2Master(
		conn_ip_.c_str(), conn_port_,
		[this](TcpConnection* conn, SocketEvent_t ev) { this->OnMasterSocketEvent(conn, ev); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnMasterMessageEvent(conn, evbuf); });
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
			world_accept_service_.OnServerConnected(conn);
        } break;
		case SocketEvent_t::CONNECT_ERROR:
        case SocketEvent_t::DISCONNECTED: {
            world_accept_service_.OnServerDisconnected(conn);
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
		world_conn_service_.OnMasterConnected(conn);
	} break;
	case SocketEvent_t::CONNECT_ERROR:
	case SocketEvent_t::DISCONNECTED: {
		world_conn_service_.OnMasterDisconnected(conn);
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

