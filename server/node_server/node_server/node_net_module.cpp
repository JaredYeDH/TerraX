#include "node_net_module.h"

#include "srv/net/server_login_req_service.h"
#include "comm/config/server_config.h"

using namespace terra;

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
	conn_service_.reset(new ServerConnService(*this));
	conn_service_->InitLoginReqService(PeerType_t::NODESERVER);
}

bool NodeNetModule::Init()
{
	CONSOLE_DEBUG_LOG(LEVEL_INFO, "Node Server Start...");
	InitNodeNetInfo();
	StartConnectWorldServer();
    return true;
}
bool NodeNetModule::AfterInit()
{
    conn_service_->Connect2World();
    return true;
}
bool NodeNetModule::Execute()
{
	get_event_loop()->loop();
    return true;
}
bool NodeNetModule::BeforeShut() { return true; }
bool NodeNetModule::Shut() { return true; }
