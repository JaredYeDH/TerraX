#include "node_net_module.h"

#include "comm/config/server_config.h"

using namespace terra;

NodeNetModule::NodeNetModule()
    : NetBaseModule(PeerType_t::NODESERVER),
      conn_service_(ServerConnService::GetInstance()),
      node_accept_service(NodeAcceptService::GetInstance())
{
	conn_service_.InitNetModule(this);
	node_accept_service.InitNetModule(this);
}

void NodeNetModule::InitNodeNetInfo()
{
    ServerConfig::GetInstance().LoadConfigFromJson("node_server.json");

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

void NodeNetModule::StartConnectWorldServer()
{
    TcpConnection* conn = conn_service_.NewConnect(
        conn_ip_.c_str(), conn_port_,
        [this](TcpConnection* conn, ConnState_t conn_state) { this->OnWorldSocketEvent(conn, conn_state); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnWorldMessageEvent(conn, evbuf); });
    server_table_.AddServerInfo(PeerType_t::WORLDSERVER, WORD_SERVER_ID, conn_ip_.c_str(), conn_port_, conn);
}

void NodeNetModule::StartAccept()
{
    node_accept_service.AcceptConnection(
        get_listen_port(), 64,
        [this](TcpConnection* conn, ConnState_t conn_state) { this->OnGateSocketEvent(conn, conn_state); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnGateMessageEvent(conn, evbuf); });
}

bool NodeNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "Node Server Start...");
    InitNodeNetInfo();
    StartConnectWorldServer();
    StartAccept();
    return true;
}
bool NodeNetModule::AfterInit() { return true; }
bool NodeNetModule::Tick()
{
    get_event_loop()->loop();
    return true;
}
bool NodeNetModule::BeforeShut() { return true; }
bool NodeNetModule::Shut() { return true; }

void NodeNetModule::OnWorldSocketEvent(TcpConnection* conn, ConnState_t conn_state)
{
    switch (conn_state) {
        case ConnState_t::CONNECTED: {
            OnWorldConnected(conn);
        } break;
        case ConnState_t::DISCONNECTED: {
			OnWorldDisconnected(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}
void NodeNetModule::OnWorldMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}

void NodeNetModule::OnGateSocketEvent(TcpConnection* conn, ConnState_t conn_state)
{
    switch (conn_state) {
        case ConnState_t::CONNECTED: {
            OnGateConnected(conn);
        } break;
        case ConnState_t::DISCONNECTED: {
			OnGateDisconnected(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}

void NodeNetModule::OnGateMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}

void NodeNetModule::OnWorldConnected(TcpConnection* conn)
{
    conn_service_.Login2World(conn);
};
void NodeNetModule::OnWorldDisconnected(TcpConnection* conn)
{
    // ReConnect();
    server_table_.RemoveByConn(conn);
	conn_service_.DestroyConnection(conn);
}

void NodeNetModule::OnGateConnected(TcpConnection* conn) {}
void NodeNetModule::OnGateDisconnected(TcpConnection* conn) 
{ 
	node_accept_service.OnLogout(conn);
}
