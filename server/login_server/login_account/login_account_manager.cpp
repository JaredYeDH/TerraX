#include "login_account_manager.h"
#include "comm/net/packet_dispatcher.h"
#include "Login_account.h"

using namespace terra;
using namespace packet_cs;

LoginAccountManager::LoginAccountManager()
{
	InitAccountState();
	REG_PACKET_HANDLER_ARG3(MsgReqLoginCL, this, OnMessage_ReqLoginCL);
}

void LoginAccountManager::InitAccountState()
{
	states_[(int)Account_State_t::ACCOUNT_WAITING_LOGIN].reset(new AccountState_WaitingLogin());
	states_[(int)Account_State_t::ACCOUNT_WAITING_BILLINGAUTH].reset(new AccountState_WaitingBillingAuth());
	states_[(int)Account_State_t::ACCOUNT_WAITING_SERVERLIST].reset(new AccountState_WaitingServerList());
	states_[(int)Account_State_t::ACCOUNT_WAITING_REQ_ENTERGAME].reset(new AccountState_WaitingReqEnterGame());
	states_[(int)Account_State_t::ACCOUNT_WAITING_WORLDCHECKTOKEN].reset(new AccountState_WaitingWorldCheckToken());
	states_[(int)Account_State_t::ACCOUNT_WAITING_CLIENTSWITCH2GATE].reset(new AccountState_WaitingClientSwitch2Gate());
	states_[(int)Account_State_t::ACCOUNT_DESTROY].reset(new AccountState_Destory());
}

void LoginAccountManager::CreateAccount(TcpConnection* conn)
{
	std::unique_ptr<LoginAccount> account(new LoginAccount(conn));
	account->EnterDefaultState();
	account_map_.insert(std::make_pair(conn->get_fd(), std::move(account)));
}

void LoginAccountManager::OnMessage_ReqLoginCL(TcpConnection* conn, int32_t avatar_id, MsgReqLoginCL* msg)
{
	auto iter = account_map_.find(conn->get_fd());
	if (iter != account_map_.end())
	{
		assert(iter->second != nullptr);
		AccountState_Base* state = iter->second->get_current_state();
		state->HandleMessage(*(iter->second), msg);
	}
}

void LoginAccountManager::OnMessage_MsgLoginResultLC(MsgLoginResultLC* msg)
{

}