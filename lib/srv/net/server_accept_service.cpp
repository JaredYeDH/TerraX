#include "server_accept_service.h"
using namespace terra;

ServerAcceptService::ServerAcceptService(NetBaseModule& net, uint32_t aceept_max_conns)
	: net_(net),
	max_conns_(aceept_max_conns),
	kSelfPeer(net.get_peer_type()),
	server_table_(net.get_server_table()),
	packet_processor_(net.get_packet_processor())
{}
ServerAcceptService::~ServerAcceptService() {}


void ServerAcceptService::AcceptConnection(int port, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
    server_.reset(new TcpServer(
        net_.get_event_loop(), port, max_conns_, sock_cb, msg_cb));
}
