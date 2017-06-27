#include "gate_accept_service.h"
#include "comm/net/packet_dispatcher.h"
#include "gate_account/gate_account_manager.h"

using namespace terra;

GateAcceptService::GateAcceptService()
{
}

void GateAcceptService::SendPacketByAccountName(const std::string& account_name, google::protobuf::Message& msg)
{
}

void GateAcceptService::OnClientConnected(TcpConnection* conn)
{
	GateAccountManager::GetInstance().CreateAccount(conn);
}

void GateAcceptService::OnClientDisconnected(TcpConnection* conn)
{
	GateAccountManager::GetInstance().RemoveAccount(conn);
}
