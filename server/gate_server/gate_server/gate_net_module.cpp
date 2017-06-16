#include "gate_net_module.h"

#include "comm/config/server_config.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;

//TODO 数据包处理必须为Instance()
GateNetModule::GateNetModule() : NetBaseModule(PeerType_t::GATESERVER),
conn_service_(GateConnService::GetInstance())
{
	conn_service_.InitNetModule(this);
}

void GateNetModule::InitGateNetInfo()
{
	ServerConfig::GetInstance().LoadConfigFromJson("gate_server.json");

    std::string conn_ip;
    int conn_port;
    ServerConfig::GetInstance().GetJsonObjectValue("net", "world_server_ip", conn_ip);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "world_server_port", conn_port);
    InitConnectInfo(conn_ip, conn_port);

    std::string listen_ip;
    int listen_port;
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_ip", listen_ip);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_port", listen_port);
    InitListenInfo(listen_ip, listen_port);
}

void GateNetModule::StartConnectWorldServer()
{
	conn_service_.Connect2World(conn_ip_.c_str(), conn_port_,
		[this](TcpConnection* conn, SocketEvent_t ev) { this->OnServerSocketEvent(conn, ev); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnServerMessageEvent(conn, evbuf); });

}

bool GateNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "Gate Server Start...");
    InitGateNetInfo();
    StartConnectWorldServer();
    return true;
}
bool GateNetModule::AfterInit() { return true; }
bool GateNetModule::Tick()
{
    get_event_loop()->loop();
    return true;
}
bool GateNetModule::BeforeShut() { return true; }
bool GateNetModule::Shut() { return true; }

void GateNetModule::OnServerSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
    
    switch (ev) {
        case SocketEvent_t::CONNECTED: {
			conn_service_.OnServerConnected(conn);
        } break;
		case SocketEvent_t::CONNECT_ERROR:
        case SocketEvent_t::DISCONNECTED: {
			conn_service_.OnServerDisconnected(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}
void GateNetModule::OnServerMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}
