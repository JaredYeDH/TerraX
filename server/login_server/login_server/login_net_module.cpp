#include "login_net_module.h"

#include "comm/config/server_config.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;
using namespace packet_ss;

//TODO 数据包处理必须为Instance()
LoginNetModule::LoginNetModule() : NetBaseModule(PeerType_t::LOGINSERVER),
conn_service_(LoginConnService::GetInstance()),
accpet_service_(LoginAcceptService::GetInstance())
{
	conn_service_.InitNetModule(this);
	accpet_service_.InitNetModule(this);
}

void LoginNetModule::InitLoginNetInfo()
{
	ServerConfig::GetInstance().LoadConfigFromJson("login_server.json");

    ServerConfig::GetInstance().GetJsonObjectValue("master", "ip", master_conn_ip_);
    ServerConfig::GetInstance().GetJsonObjectValue("master", "port", master_conn_port_);

    ServerConfig::GetInstance().GetJsonObjectValue("client", "listen_ip", client_listen_ip_);
    ServerConfig::GetInstance().GetJsonObjectValue("client", "listen_port", client_listen_port_);
}

void LoginNetModule::StartConnectMasterServer()
{
	conn_service_.Connect2Master(master_conn_ip_.c_str(), master_conn_port_,
		[this](TcpConnection* conn, SocketEvent_t ev) { this->OnMasterSocketEvent(conn, ev); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnMasterMessageEvent(conn, evbuf); });
}

void LoginNetModule::StartAcceptClient()
{
	accpet_service_.AcceptConnection(client_listen_port_, 1024,
		[this](TcpConnection* conn, SocketEvent_t ev) { this->OnClientSocketEvent(conn, ev); },
		[this](TcpConnection* conn, evbuffer* evbuf) { this->OnClientMessageEvent(conn, evbuf); });
}

bool LoginNetModule::Init()
{
    CONSOLE_DEBUG_LOG(LEVEL_INFO, "Login Server Start...");
    InitLoginNetInfo();
    StartConnectMasterServer();
	StartAcceptClient();
    return true;
}
bool LoginNetModule::AfterInit() { return true; }
bool LoginNetModule::Tick()
{
    get_event_loop()->loop();
    return true;
}
bool LoginNetModule::BeforeShut() { return true; }
bool LoginNetModule::Shut() { return true; }

void LoginNetModule::SendPacket2Master(google::protobuf::Message& msg)
{
	conn_service_.SendPacket2Master(msg);
}

void LoginNetModule::SendPacket2Client(TcpConnection* conn, google::protobuf::Message& msg)
{
	accpet_service_.SendPacket(conn, msg);
}

void LoginNetModule::SendPacket2Client(const std::string& account_name, google::protobuf::Message& msg)
{
	accpet_service_.SendPacketByAccountName(account_name, msg);
}


void LoginNetModule::OnMasterSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
    switch (ev) {
	case SocketEvent_t::CONNECTED: {
			conn_service_.OnMasterConnected(conn);
        } break;
		case SocketEvent_t::CONNECT_ERROR:
		case SocketEvent_t::DISCONNECTED: {
			conn_service_.OnMasterDisconnected(conn);
			//server_table_.PrintServerTable();
        } break;
        default:
            break;
    }
}
void LoginNetModule::OnMasterMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    ProcessServerMessage(conn, evbuf);
}

void LoginNetModule::OnClientSocketEvent(TcpConnection* conn, SocketEvent_t ev)
{
	switch (ev) {
	case SocketEvent_t::CONNECTED: {
		accpet_service_.OnClientConnected(conn);
	} break;
	case SocketEvent_t::CONNECT_ERROR:
	case SocketEvent_t::DISCONNECTED: {
		accpet_service_.OnClientDisconnected(conn);
		//server_table_.PrintServerTable();
	} break;
	default:
		break;
	}
}

void LoginNetModule::OnClientMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
	ProcessServerMessage(conn, evbuf);
}

