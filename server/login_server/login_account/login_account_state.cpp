#include "login_account_state.h"
#include "Login_account.h"
#include "comm/proto/server_server.pb.h"
#include "login_server/login_net_module.h"

using namespace terra;
using namespace packet_cs;
using namespace packet_ss;

//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingLogin::Enter(LoginAccount& account) {}
void AccountState_WaitingLogin::Tick(LoginAccount& account) {}
void AccountState_WaitingLogin::Leave(LoginAccount& account) {}
void AccountState_WaitingLogin::HandleMessage(LoginAccount& account, MsgReqLoginCL* msg)
{
	account.InitAccountName(msg->account_name());

#ifdef NEED_BILLING_AUTH
	//account, password
	//send packet 2 billing
	account.EnterState(Account_State_t::ACCOUNT_WAITING_BILLINGAUTH);
#else
	account.set_token("token_key");
	MsgReqServerListLM req;
	req.set_account_name(msg->account_name());
	LoginNetModule::GetInstance().SendPacket2Master(req);
	account.EnterState(Account_State_t::ACCOUNT_WAITING_SERVERLIST);
#endif
}
//////////////////////////////////////////////////////////////////////////

void AccountState_WaitingBillingAuth::Enter(LoginAccount& account) {}
void AccountState_WaitingBillingAuth::Tick(LoginAccount& account) {}
void AccountState_WaitingBillingAuth::Leave(LoginAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingServerList::Enter(LoginAccount& account) {}
void AccountState_WaitingServerList::Tick(LoginAccount& account) {}
void AccountState_WaitingServerList::Leave(LoginAccount& account) {}

void AccountState_WaitingServerList::HandleMessage(LoginAccount& account, MsgServerListML* msg)
{
	MsgLoginResultLC res;
	res.set_result(0);
	res.set_token(account.get_token());
	res.mutable_servers()->Swap(msg->mutable_servers());
	LoginNetModule::GetInstance().SendPacket2Client(account.get_conn(), res);
}
//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingReqEnterGame::Enter(LoginAccount& account) {}
void AccountState_WaitingReqEnterGame::Tick(LoginAccount& account) {}
void AccountState_WaitingReqEnterGame::Leave(LoginAccount& account) {}
//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingWorldCheckToken::Enter(LoginAccount& account) {}
void AccountState_WaitingWorldCheckToken::Tick(LoginAccount& account) {}
void AccountState_WaitingWorldCheckToken::Leave(LoginAccount& account) {}
//////////////////////////////////////////////////////////////////////////
void AccountState_WaitingClientSwitch2Gate::Enter(LoginAccount& account) {}
void AccountState_WaitingClientSwitch2Gate::Tick(LoginAccount& account) {}
void AccountState_WaitingClientSwitch2Gate::Leave(LoginAccount& account) {}
//////////////////////////////////////////////////////////////////////////
void AccountState_Destory::Enter(LoginAccount& account) {}
void AccountState_Destory::Tick(LoginAccount& account) {}
void AccountState_Destory::Leave(LoginAccount& account) {}