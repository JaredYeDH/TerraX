#include "client_net_module.h"
#include "comm/net/packet_dispatcher.h"
#include "client_conn_service.h"
#include "game_state_manager.h"
using namespace terra;
using namespace packet_cs;

//TODO 数据包处理必须为Instance()
ClientNetModule::ClientNetModule()
	: kSelfPeer(PeerType_t::CLIENT),
	packet_processor_(ClientPacketProcessor::GetInstance()),
	conn_service_(ClientConnService::GetInstance())
{
	conn_service_.InitNetModule(this);
}

void ClientNetModule::InitLoginNetInfo()
{
	//ServerConfig::GetInstance().LoadConfigFromJson("loginserver.json");

	std::string conn_ip = "127.0.0.1";
	int conn_port = 10080;
	login_info_.emplace_back(IPInfo(std::move(conn_ip), conn_port));
}

void ClientNetModule::StartConnectLoginServer()
{
	assert(login_conn_ == nullptr);
	login_conn_ = conn_service_.NewConnect(
		login_info_[0].ip_.c_str(), login_info_[0].port_,
		[this](TcpConnection* conn, ConnState_t conn_state) { this->OnLoginSocketEvent(conn, conn_state); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnLoginMessageEvent(conn, evbuf); });
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
	get_event_loop()->loop();
	return true;
}
bool ClientNetModule::BeforeShut() { return true; }
bool ClientNetModule::Shut() { return true; }

void ClientNetModule::SendPacket2LoginServer(google::protobuf::Message& msg)
{
	packet_processor_.SendPacket(login_conn_, msg);
}

void ClientNetModule::SendPacket2GateServer(google::protobuf::Message& msg)
{
	packet_processor_.SendPacket(gate_conn_, msg);
}

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
	GameStateManager::GetInstance().NextState(GameState_t::ACCOUNT_LOGGINGIN);
};
void ClientNetModule::OnLoginDisconnected(TcpConnection* conn)
{
	//
	conn_service_.DestroyConnection(conn);
	login_conn_ = nullptr;
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
