#include "master_login_accept_service.h"
#include "comm/net/packet_dispatcher.h"
#include "server_manager/server_manager.h"

using namespace terra;
using namespace packet_ss;

MasterLoginAcceptService::MasterLoginAcceptService()
{
}


void MasterLoginAcceptService::OnLoginConnected(TcpConnection* conn)
{
	ServerManager::GetInstance().CreateLoginServerObj(conn);
}

void MasterLoginAcceptService::OnLoginDisconnected(TcpConnection* conn)
{
	ServerManager::GetInstance().RemoveLoginServerObj(conn);
}