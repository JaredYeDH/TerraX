#include "master_net_module.h"
#include "comm/config/server_config.h"

using namespace terra;
using namespace packet_ss;

MasterNetModule::MasterNetModule()
    : NetBaseModule(PeerType_t::MASTERSERVER), 
	master_world_accept_service_(MasterWorldAcceptService::GetInstance()),
	master_login_accept_service_(MasterLoginAcceptService::GetInstance())
{
	master_login_accept_service_.InitNetModule(this);
    master_world_accept_service_.InitNetModule(this);
}

void MasterNetModule::InitMasterNetInfo()
{
    ServerConfig::GetInstance().LoadConfigFromJson("master_server.json");
    std::string ip;
    int port;
    ServerConfig::GetInstance().GetJsonObjectValue("world", "listen_ip", ip);
    ServerConfig::GetInstance().GetJsonObjectValue("world", "listen_port", port);
    InitListenInfo(ip, port);

	std::string login_listen_ip;
	int login_listen_port;
	ServerConfig::GetInstance().GetJsonObjectValue("login", "listen_ip", login_listen_ip);
	ServerConfig::GetInstance().GetJsonObjectValue("login", "listen_port", login_listen_port);
	InitLoginListenIpAndPort(login_listen_ip, login_listen_port);
}

void MasterNetModule::InitLoginListenIpAndPort(const std::string& ip, int port)
{
	login_listen_ip_ = ip;
	login_listen_port_ = port;
}

void MasterNetModule::StartAcceptWorldServer()
{
    master_world_accept_service_.AcceptConnection(
        get_listen_port(), 64,
        [this](TcpConnection* conn, SocketEvent_t ev) { this->OnWorldSocketEvent(conn, ev); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnWorldMessageEvent(conn, evbuf); });
}

void MasterNetModule::StartAcceptLoginServer()
{
	master_login_accept_service_.AcceptConnection(
		login_listen_port_, 64,
		[this](TcpConnection* conn, SocketEvent_t ev) { this->OnLoginSocketEvent(conn, ev); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnLoginMessageEvent(conn, evbuf); });
}

bool MasterNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "Master Server Start...");
    InitMasterNetInfo();
    StartAcceptWorldServer();
	StartAcceptLoginServer();
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

void MasterNetModule::OnWorldSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
    switch (ev) {
        case SocketEvent_t::CONNECTED: {
			master_world_accept_service_.OnWorldConnected(conn);
        } break;
		case SocketEvent_t::CONNECT_ERROR:
		case SocketEvent_t::DISCONNECTED: {
			master_world_accept_service_.OnWorldDisconnected(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}
void MasterNetModule::OnWorldMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}


void MasterNetModule::OnLoginSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
	switch (ev) {
	case SocketEvent_t::CONNECTED: {
		master_login_accept_service_.OnLoginConnected(conn);
	} break;
	case SocketEvent_t::CONNECT_ERROR:
	case SocketEvent_t::DISCONNECTED: {
		master_login_accept_service_.OnLoginDisconnected(conn);
		//master_login_accept_service_.OnLogout(conn);
		//server_table_.PrintServerTable();
	} break;
	default:
		break;
	}
}

void MasterNetModule::OnLoginMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
	ProcessServerMessage(conn, evbuf);
}