#include "client_net_module.h"
#include "comm/net/packet_dispatcher.h"
#include "client_conn_service.h"

using namespace terra;
using namespace packet_cs;

//TODO 数据包处理必须为Instance()
ClientNetModule::ClientNetModule()
	: kSelfPeer(PeerType_t::CLIENT),
	conn_service_(ClientConnService::GetInstance())
{
	conn_service_.InitNetModule(this);
}

void ClientNetModule::InitLoginNetInfo()
{
	/*ServerConfig::GetInstance().LoadConfigFromJson("gate_server.json");

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
	*/
}

void ClientNetModule::StartConnectLoginServer()
{
	/*TcpConnection* conn = conn_service_.NewConnect(
		conn_ip_.c_str(), conn_port_,
		[this](TcpConnection* conn, ConnState_t conn_state) { this->OnServerSocketEvent(conn, conn_state); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnServerMessageEvent(conn, evbuf); });
	server_table_.AddServerInfo(PeerType_t::WORLDSERVER, WORD_SERVER_ID, conn_ip_.c_str(),
		conn_port_, conn);*/
}

bool ClientNetModule::Init()
{
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "Gate Server Start...");
	InitLoginNetInfo();
	return true;
}
bool ClientNetModule::AfterInit() 
{ 
	
	return true;
}
bool ClientNetModule::Tick()
{
	loop_.loop();
	return true;
}
bool ClientNetModule::BeforeShut() { return true; }
bool ClientNetModule::Shut() { return true; }

void ClientNetModule::OnLoginSocketEvent(TcpConnection* conn, ConnState_t conn_state)
{
	switch (conn_state) {
	case ConnState_t::CONNECTED: {
		OnLoginConnected(conn);
	} break;
	case ConnState_t::DISCONNECTED: {
		OnLoginDisconnected(conn);
	} break;
	default:
		break;
	}
}
void ClientNetModule::OnLoginMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
	//ProcessLoginMessage(conn, evbuf);
}

void ClientNetModule::OnLoginConnected(TcpConnection* conn)
{
};
void ClientNetModule::OnLoginDisconnected(TcpConnection* conn)
{
	conn_service_.DestroyConnection(conn);
	// ReConnect();
}

void ClientNetModule::OnGateSocketEvent(TcpConnection* conn, ConnState_t conn_state)
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
void ClientNetModule::OnGateMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
	//ProcessGateMessage(conn, evbuf);
}

void ClientNetModule::OnGateConnected(TcpConnection* conn)
{
}
void ClientNetModule::OnGateDisconnected(TcpConnection* conn)
{
	conn_service_.DestroyConnection(conn);
}
