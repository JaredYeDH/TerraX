#include "login_accept_service.h"
#include "comm/net/packet_dispatcher.h"
#include "login_account/login_account_manager.h"
#include "login_account/Login_account.h"
using namespace terra;

LoginAcceptService::LoginAcceptService()
{
}

void LoginAcceptService::SendPacketByAccountName(const std::string& account_name, google::protobuf::Message& msg)
{
	LoginAccount* account = LoginAccountManager::GetInstance().GetAccountByAccountName(account_name);
	if (!account)
	{
		return;
	}
	SendPacket(account->get_conn(), msg);
}

void LoginAcceptService::OnClientConnected(TcpConnection* conn)
{
	LoginAccountManager::GetInstance().CreateAccount(conn);
}

void LoginAcceptService::OnClientDisconnected(TcpConnection* conn)
{
	LoginAccountManager::GetInstance().RemoveAccount(conn);
}

void LoginAcceptService::CloseConnection(int fd)
{
	server_->Close(fd);
}

