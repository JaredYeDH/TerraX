#include "server_conn_service.h"
#include "server_login_req_service.h"
#include "net_base_module.h"
#include "server_table.h"

using namespace terra;

ServerConnService::ServerConnService(NetBaseModule& net)
	: net_(net)
{

}
ServerConnService::~ServerConnService() {}

void ServerConnService::CreateLoginReqService()
{
	login_req_.reset(new ServerLoginReqService(*this, net_.get_peer_type()));
}

void ServerConnService::Login2World(TcpConnection* conn)
{
	if (login_req_)
	{
		login_req_->Login2World(conn);
	}
}


TcpConnection* ServerConnService::Connect(const char* ip, int port,
                                SocketEventCB sock_cb, MessageEventCB msg_cb)
{
	conn_.reset(new TcpConnection(net_.get_event_loop(), ip, port, sock_cb, msg_cb));
	return conn_.get();
}

void ServerConnService::OnSocketEvent(TcpConnection* conn, ConnState_t conn_state)
{
    switch (conn_state) {
        case ConnState_t::CONNECTED:
			if (login_req_)
			{
				login_req_->Login2World(conn);
			}
            break;
        case ConnState_t::DISCONNECTED:
			if (login_req_)
			{
				login_req_->OnLoginOut(conn);
			}
			ServerTable::GetInstance().RemoveByConn(conn);
			conn_.reset(nullptr);
            // ReConnect();
            break;
        default:
            break;
    }
}
void ServerConnService::OnMessageEvent(TcpConnection* conn, evbuffer* evbuf)
{
    net_.ProcessServerMessage(conn, evbuf);
}
