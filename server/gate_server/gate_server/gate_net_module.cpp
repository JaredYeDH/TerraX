#include "gate_net_module.h"

#include "comm/config/server_config.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;
using namespace packet_ss;

//TODO 数据包处理必须为Instance()
GateNetModule::GateNetModule() : NetBaseModule(PeerType_t::GATESERVER),
conn_service_(ServerConnService::GetInstance())
{
	conn_service_.InitNetModule(this);
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
    TcpConnection* conn = conn_service_.NewConnect(
        conn_ip_.c_str(), conn_port_,
        [this](TcpConnection* conn, SocketEvent_t ev) { this->OnServerSocketEvent(conn, ev); },
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
bool GateNetModule::Tick()
{
    get_event_loop()->loop();
    return true;
}
bool GateNetModule::BeforeShut() { return true; }
bool GateNetModule::Shut() { return true; }

void GateNetModule::OnServerSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
    NetObject* net_object = server_table_.GetNetObjectByConn(conn);
    assert(net_object);
    if (!net_object) {
        return;
    }
    switch (ev) {
        case SocketEvent_t::CONNECTED: {
            if (net_object->peer_type_ == PeerType_t::WORLDSERVER) {
                OnWorldConnected(conn);
            }
            if (net_object->peer_type_ == PeerType_t::NODESERVER) {
                OnNodeConnected(conn);
            }
        } break;
		case SocketEvent_t::CONNECT_ERROR:
        case SocketEvent_t::DISCONNECTED: {
            if (net_object->peer_type_ == PeerType_t::WORLDSERVER) {
                OnWorldDisconnected(conn);
            }
            if (net_object->peer_type_ == PeerType_t::NODESERVER) {
                OnNodeDisconnected(conn);
			}
			//server_table_.PrintServerTable();
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
    conn_service_.Login2World(conn);
};
void GateNetModule::OnWorldDisconnected(TcpConnection* conn)
{
	server_table_.RemoveByConn(conn);
	conn_service_.DestroyConnection(conn);
    // ReConnect();
}

void GateNetModule::OnNodeConnected(TcpConnection* conn) 
{
	NetObject* net_object = server_table_.GetNetObjectByConn(conn);
	assert(net_object);
	if (net_object)
	{
		conn_service_.Login2Node(conn);
	}
}
void GateNetModule::OnNodeDisconnected(TcpConnection* conn) 
{
	server_table_.RemoveByConn(conn);
	conn_service_.DestroyConnection(conn);
}


void GateNetModule::OnMessage_ServerInfoWS(MsgServerInfoWS* msg)
{
	for (int i = 0; i < msg->server_info_size(); ++i) {
		const auto& si = msg->server_info(i);
		if (si.peer_type() == static_cast<int>(PeerType_t::NODESERVER))
		{
			TcpConnection* conn = conn_service_.NewConnect(si.listen_ip().c_str(), si.listen_port(),
				[this](TcpConnection* conn, SocketEvent_t ev) { this->OnServerSocketEvent(conn, ev); },
				[this](TcpConnection* conn, evbuffer* evbuf) { this->OnServerMessageEvent(conn, evbuf); });
			server_table_.AddServerInfo(static_cast<PeerType_t>(si.peer_type()), si.server_id(),
				si.listen_ip().c_str(), si.listen_port(), conn);
		}

	}
}