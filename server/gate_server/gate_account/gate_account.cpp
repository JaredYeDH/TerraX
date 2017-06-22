#include "gate_account.h"
#include "gate_account_manager.h"

using namespace terra;

GateAccount::GateAccount(TcpConnection* conn) : conn_(conn), fd_(conn->get_fd())
{

}
void GateAccount::InitAccountName(const std::string& account_name)
{
	//if (account_name_.size() != 0)
	//{
	//	GateAccountManager::GetInstance().RemoveAccount2FdInfo(account_name_);
	//}
	//account_name_ = account_name;
	//GateAccountManager::GetInstance().AddAccount2FdInfo(account_name_, fd_);
}

void GateAccount::EnterDefaultState()
{
	EnterState(Account_State_t::ACCOUNT_WAITING_LOGIN);
}

void GateAccount::EnterState(Account_State_t state)
{
	//assert(state >= Account_State_t::ACCOUNT_WAITING_LOGIN
	//	&& state < Account_State_t::ACCOUNT_COUNT);
	//if (account_state_) {
	//	account_state_->Leave(*this);
	//}
	//account_state_ = GateAccountManager::GetInstance().GetAccountState(state);
	//assert(account_state_);
	//account_state_->Enter(*this);

}