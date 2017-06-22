#include "gate_account_manager.h"
#include "comm/net/packet_dispatcher.h"
#include "gate_account.h"

using namespace terra;
using namespace packet_cs;
using namespace packet_ss;

GateAccountManager::GateAccountManager()
{
	InitAccountState();
}

void GateAccountManager::InitAccountState()
{
}

void GateAccountManager::CreateAccount(TcpConnection* conn)
{
	std::unique_ptr<GateAccount> account(new GateAccount(conn));
	account->EnterDefaultState();
	account_map_.insert(std::make_pair(conn->get_fd(), std::move(account)));
}


void GateAccountManager::RemoveAccount(TcpConnection* conn)
{
	auto iter = account_map_.find(conn->get_fd());
	if (iter == account_map_.end())
	{
		assert(0);
		return;
	}
	account2fd_map_.erase(iter->second->get_account_name());
	account_map_.erase(conn->get_fd()); //res = 1;
}

GateAccount* GateAccountManager::GetAccountByAccountName(const std::string& account_name)
{
	auto iter_fd = account2fd_map_.find(account_name);
	if (iter_fd == account2fd_map_.end())
	{
		return nullptr;
	}
	int fd = iter_fd->second;
	auto iter = account_map_.find(fd);
	if (iter == account_map_.end())
	{
		return nullptr;
	}
	return (iter->second).get();
}
