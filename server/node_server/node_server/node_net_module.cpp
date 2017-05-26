#include "node_net_module.h"

#include "comm/config/server_config.h"

using namespace terra;

NodeNetModule::NodeNetModule() : NetBaseModule(PeerType_t::NODESERVER) {}

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
	world_conn_service_.reset(new ServerConnService(*this));
	TcpConnection* conn = world_conn_service_->Connect(
		conn_ip_.c_str(), conn_port_,
		[this](TcpConnection* conn, ConnState_t conn_state) { this->OnWorldSocketEvent(conn, conn_state); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnWorldMessageEvent(conn, evbuf); });
	server_table_.AddServerInfo(PeerType_t::WORLDSERVER, WORD_SERVER_ID, conn_ip_.c_str(),
		conn_port_, conn);
}

void NodeNetModule::StartAcceptGateServer()
{
	gate_accept_service_.reset(new ServerAcceptService(*this, 64));
	gate_accept_service_->AcceptConnection(
		get_listen_port(),
		[this](TcpConnection* conn, ConnState_t conn_state) { this->OnGateSocketEvent(conn, conn_state); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnGateMessageEvent(conn, evbuf); });
}

bool NodeNetModule::Init()
{
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "Node Server Start...");
	InitNodeNetInfo();
	StartConnectWorldServer();
	StartAcceptGateServer();
    return true;
}
bool NodeNetModule::AfterInit()
{
    return true;
}
bool NodeNetModule::Execute()
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
	assert(conn);
	if (world_conn_service_ && conn) {
		world_conn_service_->Login2World(conn);
	}
};
void NodeNetModule::OnWorldDisconnected(TcpConnection* conn)
{
	world_conn_service_.reset(nullptr);
	// ReConnect();
	server_table_.RemoveByConn(conn);
}

void NodeNetModule::OnGateConnected(TcpConnection* conn) {}
void NodeNetModule::OnGateDisconnected(TcpConnection* conn) 
{
	server_table_.RemoveByConn(conn);
}
