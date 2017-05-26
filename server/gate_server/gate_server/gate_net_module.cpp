#include "gate_net_module.h"

#include "comm/config/server_config.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;
using namespace packet_ss;

GateNetModule::GateNetModule() : NetBaseModule(PeerType_t::GATESERVER) 
{
	REG_PACKET_HANDLER_ARG1(MsgServerInfoWS, this, OnMessage_ServerInfoWS);
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

    TcpConnection* conn = world_conn_service_->Connect(
        conn_ip_.c_str(), conn_port_,
        [this](TcpConnection* conn, ConnState_t conn_state) { this->OnServerSocketEvent(conn, conn_state); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnServerMessageEvent(conn, evbuf); });
	server_table_.AddServerInfo(PeerType_t::WORLDSERVER, WORD_SERVER_ID, conn_ip_.c_str(),
                                             conn_port_, conn);
}

bool GateNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "Gate Server Start...");
    InitGateNetInfo();
    StartConnectWorldServer();
    return true;
}
bool GateNetModule::AfterInit() { return true; }
bool GateNetModule::Execute()
{
    get_event_loop()->loop();
    return true;
}
bool GateNetModule::BeforeShut() { return true; }
bool GateNetModule::Shut() { return true; }

void GateNetModule::OnServerSocketEvent(TcpConnection* conn, ConnState_t conn_state)
{
    NetObject* net_object = server_table_.GetNetObjectByConn(conn);
    assert(net_object);
    if (!net_object) {
        return;
    }
    switch (conn_state) {
        case ConnState_t::CONNECTED: {
            if (net_object->peer_type_ == PeerType_t::WORLDSERVER) {
                OnWorldConnected(conn);
            }
            if (net_object->peer_type_ == PeerType_t::NODESERVER) {
                OnNodeConnected(conn);
            }
        } break;
        case ConnState_t::DISCONNECTED: {
            if (net_object->peer_type_ == PeerType_t::WORLDSERVER) {
                OnWorldDisconnected(conn);
            }
            if (net_object->peer_type_ == PeerType_t::NODESERVER) {
                OnNodeDisconnected(conn);
            }
            server_table_.RemoveByConn(conn);
        } break;
        default:
            break;
    }
}
void GateNetModule::OnServerMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}

void GateNetModule::OnWorldConnected(TcpConnection* conn)
{
    assert(conn);
    if (world_conn_service_ && conn) {
        world_conn_service_->Login2World(conn);
    }
};
void GateNetModule::OnWorldDisconnected(TcpConnection* conn)
{
    world_conn_service_.reset(nullptr);
    // ReConnect();
}

void GateNetModule::OnNodeConnected(TcpConnection* conn) 
{

}
void GateNetModule::OnNodeDisconnected(TcpConnection* conn) {}


void GateNetModule::OnMessage_ServerInfoWS(MsgServerInfoWS* msg)
{
	for (int i = 0; i < msg->server_info_size(); ++i) {
		const auto& si = msg->server_info(i);
		if (si.peer_type() == static_cast<int>(PeerType_t::NODESERVER))
		{
			std::unique_ptr<ServerConnService> node_conn_service(new ServerConnService(*this));
			TcpConnection* conn = node_conn_service->Connect(si.listen_ip().c_str(), si.listen_port(),
				[this](TcpConnection* conn, ConnState_t conn_state) { this->OnServerSocketEvent(conn, conn_state); },
				[this](TcpConnection* conn, evbuffer* evbuf) { this->OnServerMessageEvent(conn, evbuf); });
			node_conn_services_[si.server_id()] = std::move(node_conn_service);
			server_table_.AddServerInfo(static_cast<PeerType_t>(si.peer_type()), si.server_id(),
				si.listen_ip().c_str(), si.listen_port(), conn);
		}

	}
}