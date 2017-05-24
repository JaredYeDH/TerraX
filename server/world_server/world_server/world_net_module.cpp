#include "world_net_module.h"

#include "comm/config/server_config.h"
#include "srv/net/server_login_ack_service.h"
using namespace terra;

WorldNetModule::WorldNetModule() : NetBaseModule(PeerType_t::WORLDSERVER) {}

void WorldNetModule::InitWorldNetInfo()
{
    ServerConfig::GetInstance().LoadConfigFromJson("world_server.json");
    std::string ip;
    int port;
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_ip", ip);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_port", port);
    InitListenInfo(ip, port);
}

void WorldNetModule::StartAccept()
{
    accept_service_.reset(new ServerAcceptService(*this));
    accept_service_->InitLoginAckService(PeerType_t::WORLDSERVER, 64);
    accept_service_->AcceptConnection(
        get_listen_port(), 64,
        [this](TcpConnection* conn, ConnState_t conn_state) { this->OnSocketEvent(conn, conn_state); },
        [this](TcpConnection* conn, evbuffer* evbuf) { this->OnMessageEvent(conn, evbuf); });
}

bool WorldNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "World Server Start...");
    InitWorldNetInfo();
    StartAccept();
    return true;
}
bool WorldNetModule::AfterInit() { return true; }
bool WorldNetModule::Execute()
{
    get_event_loop()->loop();
    ;
    return true;
}
bool WorldNetModule::BeforeShut() { return true; }
bool WorldNetModule::Shut() { return true; }

void WorldNetModule::OnSocketEvent(TcpConnection* conn, ConnState_t conn_state)
{
    NetObject* net_object = server_table_.GetNetObjectByConn(conn);
    assert(net_object);
    if (!net_object) {
        return;
    }
    switch (conn_state) {
        case ConnState_t::CONNECTED: {
            if (net_object->peer_type_ == PeerType_t::GATESERVER) {
                OnGateConnected(net_object);
            }
            if (net_object->peer_type_ == PeerType_t::NODESERVER) {
                OnNodeConnected(net_object);
            }
        } break;
        case ConnState_t::DISCONNECTED: {
            if (net_object->peer_type_ == PeerType_t::GATESERVER) {
                OnGateDisconnected(net_object);
            }
            if (net_object->peer_type_ == PeerType_t::NODESERVER) {
                OnNodeDisconnected(net_object);
            }
            // accept_service_->LoginOut()
            server_table_.RemoveByConn(conn);
        } break;
        default:
            break;
    }
}
void WorldNetModule::OnMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}

void WorldNetModule::OnGateConnected(NetObject* net_object) { assert(net_object); }

void WorldNetModule::OnGateDisconnected(NetObject* net_object)
{
    // ReConnect();
}

void WorldNetModule::OnNodeConnected(NetObject* net_object) {}
void WorldNetModule::OnNodeDisconnected(NetObject* net_object) {}
