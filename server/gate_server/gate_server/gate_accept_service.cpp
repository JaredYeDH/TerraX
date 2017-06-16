#include "gate_accept_service.h"
#include "comm/net/packet_dispatcher.h"

using namespace terra;

GateAcceptService::GateAcceptService()
{
}

void GateAcceptService::SendPacketByAccountName(const std::string& account_name, google::protobuf::Message& msg)
{
}

void GateAcceptService::OnClientConnected(TcpConnection* conn)
{
}

void GateAcceptService::OnClientDisconnected(TcpConnection* conn)
{
}