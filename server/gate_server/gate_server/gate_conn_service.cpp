#include "gate_conn_service.h"
#include "comm/net/packet_dispatcher.h"
#include "gate_net_module.h"

using namespace terra;
using namespace packet_ss;


GateConnService::GateConnService()
{
	REG_PACKET_HANDLER_ARG1(MsgServerInfoWS, this, OnMessage_ServerInfoWS);
}

void GateConnService::Connect2World(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	TcpConnection* conn = Connect(ip, port, sock_cb, msg_cb);
	server_table_.AddServerInfo(PeerType_t::WORLDSERVER, 0, ip,
		port, conn);
}

void GateConnService::Login2World(TcpConnection* conn)
{
	GateNetModule* gate_net = static_cast<GateNetModule*>(net_);
	MsgRegisterSW msg;
	msg.set_peer_type(static_cast<int>(net_->get_peer_type()));
	msg.set_listen_ip(gate_net->get_client_listen_ip());
	msg.set_listen_port(gate_net->get_client_listen_port());
	packet_processor_.SendPacket(conn, msg);
}

void GateConnService::Login2Node(TcpConnection* conn)
{
	MsgLogin2NodeGN msg;
	msg.set_peer_type(static_cast<int>(net_->get_peer_type()));
	msg.set_server_id(server_table_.get_self_server_id());
	packet_processor_.SendPacket(conn, msg);
}

void GateConnService::OnServerConnected(TcpConnection* conn)
{
	NetObject* net_object = server_table_.GetNetObjectByConn(conn);
	assert(net_object);
	if (!net_object) {
		return;
	}
	if (net_object->peer_type_ == PeerType_t::WORLDSERVER) {
		OnWorldConnected(conn);
	}
	if (net_object->peer_type_ == PeerType_t::NODESERVER) {
		OnNodeConnected(conn);
	}
};
void GateConnService::OnServerDisconnected(TcpConnection* conn)
{
	NetObject* net_object = server_table_.GetNetObjectByConn(conn);
	assert(net_object);
	if (!net_object) {
		return;
	}
	if (net_object->peer_type_ == PeerType_t::WORLDSERVER) {
		OnWorldDisconnected(conn);
	}
	if (net_object->peer_type_ == PeerType_t::NODESERVER) {
		OnNodeDisconnected(conn);
	}
	// ReConnect();
}

void GateConnService::OnWorldConnected(TcpConnection* conn)
{
	Login2World(conn);
};
void GateConnService::OnWorldDisconnected(TcpConnection* conn)
{
	server_table_.RemoveByConn(conn);
	DestroyConnection(conn);
	// ReConnect();
}

void GateConnService::OnNodeConnected(TcpConnection* conn)
{
	NetObject* net_object = server_table_.GetNetObjectByConn(conn);
	assert(net_object);
	if (net_object)
	{
		Login2Node(conn);
	}
}
void GateConnService::OnNodeDisconnected(TcpConnection* conn)
{
	server_table_.RemoveByConn(conn);
	DestroyConnection(conn);
}

void GateConnService::SendPacketByServerId(int server_id, google::protobuf::Message& msg)
{
	NetObject* obj = server_table_.GetNetObjectByServerID(server_id);
	if (!obj)
	{
		return;
	}
	packet_processor_.SendPacket(obj->conn_, msg);
}

void GateConnService::OnMessage_ServerInfoWS(MsgServerInfoWS* msg)
{
	for (int i = 0; i < msg->server_info_size(); ++i) {
		const auto& si = msg->server_info(i);
		if (si.peer_type() == static_cast<int>(PeerType_t::NODESERVER))
		{
			TcpConnection* conn = Connect(si.listen_ip().c_str(), si.listen_port(),
				[this](TcpConnection* conn, SocketEvent_t ev) { static_cast<GateNetModule*>(net_)->OnServerSocketEvent(conn, ev); },
				[this](TcpConnection* conn, evbuffer* evbuf) { static_cast<GateNetModule*>(net_)->OnServerMessageEvent(conn, evbuf); });
			server_table_.AddServerInfo(static_cast<PeerType_t>(si.peer_type()), si.server_id(),
				si.listen_ip().c_str(), si.listen_port(), conn);
		}

	}
}
