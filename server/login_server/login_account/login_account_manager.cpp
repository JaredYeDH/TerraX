#include "login_account_manager.h"
#include "comm/net/packet_dispatcher.h"
#include "Login_account.h"

using namespace terra;
using namespace packet_cs;

LoginAccountManager::LoginAccountManager()
{
	REG_PACKET_HANDLER_ARG3(MsgReqLoginCL, this, OnMessage_ReqLoginCL);
}


void LoginAccountManager::OnMessage_ReqLoginCL(TcpConnection* conn, int32_t avatar_id, MsgReqLoginCL* msg)
{
	if (account_map_.find(msg->account_name()) != account_map_.end())
	{
		assert(0);
		return;
	}
	LoginAccount* account = CreateAccount();
	account->EnterState();
}