#include "Login_account.h"
#include "login_account_manager.h"

using namespace terra;

LoginAccount::LoginAccount(TcpConnection* conn) : conn_(conn), fd_(conn->get_fd())
{

}

void LoginAccount::EnterDefaultState()
{
	EnterState(Account_State_t::ACCOUNT_WAITING_LOGIN);
}

void LoginAccount::EnterState(Account_State_t state)
{
	assert(state >= Account_State_t::ACCOUNT_WAITING_LOGIN
		&& state < Account_State_t::ACCOUNT_COUNT);
	if(account_state_) {
		account_state_->Leave(*this);
	}
	account_state_ = LoginAccountManager::GetInstance().GetAccountState(state);
	assert(account_state_);
	account_state_->Enter(*this);

}
