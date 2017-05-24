#include "server_accept_service.h"
#include "server_login_ack_service.h"
using namespace terra;

ServerAcceptService::ServerAcceptService(NetBaseModule& net)
	: net_(net)
{}
ServerAcceptService::~ServerAcceptService() {}

void ServerAcceptService::InitLoginAckService(PeerType_t peer, int max_conns)
{
	login_ack_.reset(new ServerLoginAckService(*this, peer, max_conns));
}

void ServerAcceptService::AcceptConnection(int port, uint32_t max_conns, SocketEventCB sock_cb, MessageEventCB msg_cb)
{
    server_.reset(new TcpServer(
        net_.get_event_loop(), port, max_conns, sock_cb, msg_cb));
}

void ServerAcceptService::OnDisconnected(TcpConnection* conn)
{
	if (login_ack_)
	{
		login_ack_->OnLogout(conn);
	}
}