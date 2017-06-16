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
	//ServerConfig::GetInstance().LoadConfigFromJson("loginserver.json");
	conn_service_.LoadLoginServerInfo("client.json");
}

void ClientNetModule::StartConnectLoginServer()
{
	conn_service_.Connect2Login();
}

bool ClientNetModule::Init()
{
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "Client Start...");
	InitLoginNetInfo();
	return true;
}
bool ClientNetModule::AfterInit() 
{ 
	
	return true;
}
bool ClientNetModule::Tick()
{
	get_event_loop()->loop();
	return true;
}
bool ClientNetModule::BeforeShut() { return true; }
bool ClientNetModule::Shut() { return true; }

void ClientNetModule::SendPacket2LoginServer(google::protobuf::Message& msg)
{
	conn_service_.SendPacket2LoginServer(msg);
}

void ClientNetModule::SendPacket2GateServer(google::protobuf::Message& msg)
{
	conn_service_.SendPacket2GateServer(msg);
}

void ClientNetModule::OnLoginSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
	switch (ev) {
	case SocketEvent_t::CONNECTED: {
		conn_service_.OnLoginConnected(conn);
	} break;
	case SocketEvent_t::CONNECT_ERROR:
	case SocketEvent_t::DISCONNECTED: {
		conn_service_.OnLoginDisconnected(conn);
	} break;
	default:
		break;
	}
}
void ClientNetModule::OnLoginMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
	conn_service_.ProcessLoginMessage(conn, evbuf);
}

void ClientNetModule::OnGateSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
	switch (ev) {
	case SocketEvent_t::CONNECTED: {
		conn_service_.OnGateConnected(conn);
	} break;
	case SocketEvent_t::CONNECT_ERROR:
	case SocketEvent_t::DISCONNECTED: {
		conn_service_.OnGateDisconnected(conn);
	} break;
	default:
		break;
	}
}
void ClientNetModule::OnGateMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
	conn_service_.ProcessGateMessage(conn, evbuf);
}

