#include "client_conn_service.h"
#include "comm/net/packet_dispatcher.h"
#include <algorithm>
#include "comm/config/jsonstream.h"
#include "game_state_manager.h"

using namespace terra;

ClientConnService::ClientConnService()
	:
	packet_processor_(ClientPacketProcessor::GetInstance())
{
}
ClientConnService::~ClientConnService()
{
}

void ClientConnService::LoadLoginServerInfo(const std::string& path)
{
	JsonStream js;
	Document* doc = js.LoadFile("client.json");
	assert(doc);
	assert(doc->HasMember("login"));
	assert((*doc)["login"].IsArray());
	for (const auto& val : (*doc)["login"].GetArray()) {
		const char* ip = val["ip"].GetString();
		int port = val["port"].GetInt();
		login_info_.emplace_back(IPInfo(ip, port));
	}
}

void ClientConnService::Connect2Login()
{
	login_conn_ = Connect(
		login_info_[0].ip_.c_str(), login_info_[0].port_,
		[this](TcpConnection* conn, SocketEvent_t ev) { net_->OnLoginSocketEvent(conn, ev); },
		[this](TcpConnection* conn, evbuffer* evbuf) { net_->OnLoginMessageEvent(conn, evbuf); });
}

TcpConnection* ClientConnService::Connect(const char* ip, int port,
	SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	std::unique_ptr<TcpConnection>  conn(new TcpConnection(net_->get_event_loop(), ip, port, sock_cb, msg_cb));
	TcpConnection* ret_conn = conn.get();
	conns_.push_back(std::move(conn));
	return ret_conn;
}

void ClientConnService::DestroyConnection(TcpConnection* conn)
{
	auto iter = std::find_if(conns_.begin(), conns_.end(),
		[conn](const std::unique_ptr<TcpConnection>& val) {
		return val.get() == conn;
	});
	if (iter != conns_.end())
	{
		conns_.erase(iter);
	}
}

void ClientConnService::ProcessLoginMessage(TcpConnection* conn, evbuffer* evbuf)
{
	packet_processor_.ProcessServerPacket(conn, evbuf);
}

void ClientConnService::ProcessGateMessage(TcpConnection* conn, evbuffer* evbuf)
{
	packet_processor_.ProcessServerPacket(conn, evbuf);
}

void ClientConnService::SendPacket2LoginServer(google::protobuf::Message& msg)
{
	packet_processor_.SendPacket(login_conn_, msg);
}

void ClientConnService::SendPacket2GateServer(google::protobuf::Message& msg)
{
	packet_processor_.SendPacket(gate_conn_, msg);
}

void ClientConnService::OnLoginConnected(TcpConnection* conn)
{
	GameStateManager::GetInstance().NextState(GameState_t::ACCOUNT_LOGGINGIN);
}
void ClientConnService::OnLoginDisconnected(TcpConnection* conn)
{
	//
	DestroyConnection(conn);
	login_conn_ = nullptr;
	// ReConnect();
	CONSOLE_DEBUG_LOG(LEVEL_WARNING, "logout from login server!");
}

void ClientConnService::OnGateConnected(TcpConnection* conn)
{
}

void ClientConnService::OnGateDisconnected(TcpConnection* conn)
{
	DestroyConnection(conn);
	gate_conn_ = nullptr;
}
