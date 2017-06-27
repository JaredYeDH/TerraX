#include "gate_net_module.h"

#include "comm/config/server_config.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;

GateNetModule::GateNetModule() : NetBaseModule(PeerType_t::GATESERVER),
conn_service_(GateConnService::GetInstance())
{
	conn_service_.InitNetModule(this);
}

void GateNetModule::InitGateNetInfo()
{
	ServerConfig::GetInstance().LoadConfigFromJson("gate_server.json");

    ServerConfig::GetInstance().GetJsonObjectValue("net", "world_server_ip", world_conn_ip_);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "world_server_port", world_conn_port_);

    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_ip", client_listen_ip_);
    ServerConfig::GetInstance().GetJsonObjectValue("net", "listen_port", client_listen_port_);
}

void GateNetModule::StartConnectWorldServer()
{
	conn_service_.Connect2World(world_conn_ip_.c_str(), world_conn_port_,
		[this](TcpConnection* conn, SocketEvent_t ev) { this->OnServerSocketEvent(conn, ev); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnServerMessageEvent(conn, evbuf); });

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
    
    switch (ev) {
        case SocketEvent_t::CONNECTED: {
			conn_service_.OnServerConnected(conn);
        } break;
		case SocketEvent_t::CONNECT_ERROR:
        case SocketEvent_t::DISCONNECTED: {
			conn_service_.OnServerDisconnected(conn);
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

void GateNetModule::SendPacket2World(google::protobuf::Message& msg)
{
	conn_service_.SendPacketByServerId(0, msg);
}

void GateNetModule::SendPacket2Node(int node_id, google::protobuf::Message& msg)
{
	conn_service_.SendPacketByServerId(node_id, msg);
}

void GateNetModule::SendPacket2Client(TcpConnection* conn, google::protobuf::Message& msg)
{

}

void GateNetModule::SendPacket2Client(const std::string& account_name, google::protobuf::Message& msg)
{

}
