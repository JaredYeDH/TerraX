#include "gate_net_module.h"

#include "srv/net/server_login_req_service.h"
#include "comm/config/server_config.h"

using namespace terra;
GateNetModule::GateNetModule() : NetBaseModule(PeerType_t::GATESERVER)
{

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
	world_conn_service_.reset(new ServerConnService(*this));
	world_conn_service_->CreateLoginReqService();
	
	TcpConnection* conn = world_conn_service_->Connect(conn_ip_.c_str(), conn_port_, 
		[this](TcpConnection* conn, ConnState_t conn_state) { this->OnSocketEvent(conn, conn_state); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnMessageEvent(conn, evbuf); });
	ServerTable::GetInstance().AddServerInfo(PeerType_t::WORLDSERVER, WORD_SERVER_ID, conn_ip_.c_str(), conn_port_, conn);
}

bool GateNetModule::Init()
{
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "Gate Server Start...");
	InitGateNetInfo();
	StartConnectWorldServer();
    return true;
}
bool GateNetModule::AfterInit()
{
    return true;
}
bool GateNetModule::Execute()
{
    get_event_loop()->loop();
    return true;
}
bool GateNetModule::BeforeShut() { return true; }
bool GateNetModule::Shut() { return true; }


void GateNetModule::OnSocketEvent(TcpConnection* conn, ConnState_t conn_state)
{
	NetObject no = servers
	switch (conn_state) {
	case ConnState_t::CONNECTED:

		if (login_req_)
		{
			login_req_->Login2World(conn);
		}
		break;
	case ConnState_t::DISCONNECTED:
		if (login_req_)
		{
			login_req_->OnLoginOut(conn);
		}
		ServerTable::GetInstance().RemoveByConn(conn);
		conn_.reset(nullptr);
		// ReConnect();
		break;
	default:
		break;
	}
}
void GateNetModule::OnMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
	net_.ProcessServerMessage(conn, evbuf);
}
