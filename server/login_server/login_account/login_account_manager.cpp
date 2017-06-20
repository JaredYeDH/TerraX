#include "login_account_manager.h"
#include "comm/net/packet_dispatcher.h"
#include "Login_account.h"

using namespace terra;
using namespace packet_cs;
using namespace packet_ss;

LoginAccountManager::LoginAccountManager()
{
	InitAccountState();
	REG_PACKET_HANDLER_ARG3(MsgReqLoginCL, this, OnMessage_ReqLoginCL); 
	REG_PACKET_HANDLER_ARG1(MsgServerListML, this, OnMessage_ServerListML);
	REG_PACKET_HANDLER_ARG3(MsgSelectServerCL, this, OnMessage_SelectServerCL);
	REG_PACKET_HANDLER_ARG1(MsgReqEnterServerResultSL, this, OnMessage_ReqEnterServerResultSL);
	REG_PACKET_HANDLER_ARG3(MsgQuitLoginCL, this, OnMessage_QuitLoginCL);
}

void LoginAccountManager::InitAccountState()
{
	states_[(int)Account_State_t::ACCOUNT_WAITING_LOGIN].reset(new AccountState_WaitingLogin());
	states_[(int)Account_State_t::ACCOUNT_WAITING_BILLINGAUTH].reset(new AccountState_WaitingBillingAuth());
	states_[(int)Account_State_t::ACCOUNT_WAITING_SERVERLIST].reset(new AccountState_WaitingServerList());
	states_[(int)Account_State_t::ACCOUNT_WAITING_REQ_ENTERSERVER].reset(new AccountState_WaitingReqEnterServer());
	states_[(int)Account_State_t::ACCOUNT_WAITING_GETGATEINFO].reset(new AccountState_WaitingGetGateInfo());
	states_[(int)Account_State_t::ACCOUNT_WAITING_CLIENTSWITCH2GATE].reset(new AccountState_WaitingClientSwitch2Gate());
	states_[(int)Account_State_t::ACCOUNT_DESTROY].reset(new AccountState_Destory());
}

void LoginAccountManager::CreateAccount(TcpConnection* conn)
{
	std::unique_ptr<LoginAccount> account(new LoginAccount(conn));
	account->EnterDefaultState();
	account_map_.insert(std::make_pair(conn->get_fd(), std::move(account)));
}


void LoginAccountManager::RemoveAccount(TcpConnection* conn)
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

LoginAccount* LoginAccountManager::GetAccountByAccountName(const std::string& account_name)
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

void LoginAccountManager::OnMessage_ReqLoginCL(TcpConnection* conn, int32_t avatar_id, MsgReqLoginCL* msg)
{
	auto iter = account_map_.find(conn->get_fd());
	if (iter == account_map_.end())
	{
		assert(0);
		return;
	}
	AccountState_Base* state = iter->second->get_current_state();
	state->HandleMessage(*(iter->second), msg);
}

void LoginAccountManager::OnMessage_ServerListML(MsgServerListML* msg)
{
	LoginAccount* account = GetAccountByAccountName(msg->post_back().account_name());
	if (!account)
	{
		assert(0);
		return;
	}
	AccountState_Base* state = account->get_current_state();
	state->HandleMessage(*account, msg);
}

void LoginAccountManager::OnMessage_SelectServerCL(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgSelectServerCL* msg)
{
	auto iter = account_map_.find(conn->get_fd());
	if (iter == account_map_.end())
	{
		assert(0);
		return;
	}
	AccountState_Base* state = iter->second->get_current_state();
	state->HandleMessage(*(iter->second), msg);
}


void LoginAccountManager::OnMessage_ReqEnterServerResultSL(MsgReqEnterServerResultSL* msg)
{
	LoginAccount* account = GetAccountByAccountName(msg->account_name());
	if (!account)
	{
		assert(0);
		return;
	}
	AccountState_Base* state = account->get_current_state();
	state->HandleMessage(*account, msg);
}

void LoginAccountManager::OnMessage_QuitLoginCL(TcpConnection* conn, int32_t avatar_id, packet_cs::MsgQuitLoginCL* msg)
{
	auto iter = account_map_.find(conn->get_fd());
	if (iter == account_map_.end())
	{
		assert(0);
		return;
	}
	AccountState_Base* state = iter->second->get_current_state();
	state->HandleMessage(*(iter->second), msg);
}