#include "gate_account_manager.h"
#include "comm/net/packet_dispatcher.h"
#include "gate_account.h"

using namespace terra;
using namespace packet_cs;
using namespace packet_ss;

GateAccountManager::GateAccountManager()
{
	InitAccountState();
	REG_PACKET_HANDLER_ARG3(MsgReqLoginGameCS, this, OnMessage_ReqLoginGameCS);
}

void GateAccountManager::InitAccountState()
{
}

void GateAccountManager::CreateAccount(TcpConnection* conn)
{
	std::unique_ptr<GateAccount> account(new GateAccount(conn));
	account->EnterDefaultState();
	accounts_.InsertPKeyValue(conn->get_fd(), std::move(account));
}


void GateAccountManager::RemoveAccount(TcpConnection* conn)
{
	accounts_.EraseValueByPrimaryKey(conn->get_fd());
}

void GateAccountManager::AddAccount2FdInfo(const std::string& account_name, int fd)
{
	accounts_.SetFKey2PKey(account_name, fd);
}
void GateAccountManager::RemoveAccount2FdInfo(const std::string& account_name)
{
	accounts_.EraseForeignKeyOnly(account_name);
}

GateAccount* GateAccountManager::GetAccountByAccountName(const std::string& account_name)
{
	auto ptr = accounts_.GetValueByForeignkey(account_name);
	if (!ptr)
	{
		return nullptr;
	}
	return (*ptr).get();
}

void GateAccountManager::OnMessage_ReqLoginGameCS(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgReqLoginGameCS* msg)
{
	ProcessMessageByfd(conn->get_fd(), msg);
}