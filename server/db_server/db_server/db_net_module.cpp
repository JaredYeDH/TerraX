#include "db_net_module.h"

#include "comm/config/server_config.h"

using namespace terra;

DBNetModule::DBNetModule()
    : NetBaseModule(PeerType_t::NODESERVER),
      conn_service_(DBConnService::GetInstance()),
      accept_service_(DBAcceptService::GetInstance())
{
	conn_service_.InitNetModule(this);
	accept_service_.InitNetModule(this);
}

void DBNetModule::InitNodeNetInfo()
{
    ServerConfig::GetInstance().LoadConfigFromJson("node_server.json");

    ServerConfig::GetInstance().GetJsonObjectValue("net", "world_server_ip", world_conn_ip_);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "world_server_port", world_conn_port_);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_ip", gate_listen_ip_);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_port", gate_listen_port_);
}

void DBNetModule::StartConnectWorldServer()
{
    conn_service_.Connect2World(
		world_conn_ip_.c_str(), world_conn_port_,
        [this](TcpConnection* conn, SocketEvent_t ev) { this->OnWorldSocketEvent(conn, ev); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnWorldMessageEvent(conn, evbuf); });
}

void DBNetModule::StartAccept()
{
    accept_service_.AcceptConnection(
		gate_listen_port_, 64,
        [this](TcpConnection* conn, SocketEvent_t ev) { this->OnGateSocketEvent(conn, ev); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnGateMessageEvent(conn, evbuf); });
}

bool DBNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "Node Server Start...");
    InitNodeNetInfo();
    StartConnectWorldServer();
    StartAccept();
    return true;
}
bool DBNetModule::AfterInit() { return true; }
bool DBNetModule::Tick()
{
    get_event_loop()->loop();
    return true;
}
bool DBNetModule::BeforeShut() { return true; }
bool DBNetModule::Shut() { return true; }

void DBNetModule::OnWorldSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
    switch (ev) {
        case SocketEvent_t::CONNECTED: {
            conn_service_.OnWorldConnected(conn);
        } break;
		case SocketEvent_t::CONNECT_ERROR:
        case SocketEvent_t::DISCONNECTED: {
			conn_service_.OnWorldDisconnected(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}
void DBNetModule::OnWorldMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}

void DBNetModule::OnGateSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
    switch (ev) {
        case SocketEvent_t::CONNECTED: {
			accept_service_.OnGateConnected(conn);
		} break;
		case SocketEvent_t::CONNECT_ERROR:
        case SocketEvent_t::DISCONNECTED: {
			accept_service_.OnGateDisconnected(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}

void DBNetModule::OnGateMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}
