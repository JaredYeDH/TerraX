#include "server_accept_service.h"
using namespace terra;

ServerAcceptService::ServerAcceptService()
	: server_table_(ServerTable::GetInstance()),
	packet_processor_(PacketProcessor::GetInstance())
{}
ServerAcceptService::~ServerAcceptService() {}


void ServerAcceptService::AcceptConnection(int port, uint32_t max_conns, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
    server_.reset(new TcpServer(
        net_->get_event_loop(), port, max_conns, sock_cb, msg_cb));
}

void ServerAcceptService::SendPacket(TcpConnection* conn, google::protobuf::Message& msg)
{
	//you can verify conn by finding conn in TcpServer
	packet_processor_.SendPacket(conn, msg);
}