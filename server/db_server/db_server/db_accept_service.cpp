#include "db_accept_service.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;
using namespace packet_ss;

DBAcceptService::DBAcceptService()
{
}

void DBAcceptService::OnGateConnected(TcpConnection* conn)
{
}

void DBAcceptService::OnGateDisconnected(TcpConnection* conn)
{
	OnLogout(conn);
}


void DBAcceptService::OnLogout(TcpConnection* conn)
{
	NetObject* net_object = server_table_.GetNetObjectByConn(conn);
	assert(net_object);
	server_table_.RemoveByConn(conn);
}
