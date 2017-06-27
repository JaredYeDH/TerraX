#include "gate_account_state.h"
#include "gate_account.h"
#include "gate_server/gate_net_module.h"


using namespace terra;

//////////////////////////////////////////////////////////////////////////

void AccountState_WaitingLogin::Enter(GateAccount& account) {}
void AccountState_WaitingLogin::Tick(GateAccount& account) {}
void AccountState_WaitingLogin::Leave(GateAccount& account) {}
void AccountState_WaitingLogin::HandleMessage(GateAccount& account, packet_cs::MsgReqLoginGameCS* msg)
{
	account.InitAccountName(msg->account_name());

	GateNetModule::GetInstance().SendPacket2World(*msg);
	account.EnterState(Account_State_t::ACCOUNT_CHECKING_PERMISSION);
}
//////////////////////////////////////////////////////////////////////////

void AccountState_CheckingPermission::Enter(GateAccount& account) {}
void AccountState_CheckingPermission::Tick(GateAccount& account) {}
void AccountState_CheckingPermission::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_QueryingRoleList::Enter(GateAccount& account) {}
void AccountState_QueryingRoleList::Tick(GateAccount& account) {}
void AccountState_QueryingRoleList::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_SelectingRole::Enter(GateAccount& account) {}
void AccountState_SelectingRole::Tick(GateAccount& account) {}
void AccountState_SelectingRole::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_CreatingRole::Enter(GateAccount& account) {}
void AccountState_CreatingRole::Tick(GateAccount& account) {}
void AccountState_CreatingRole::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_CreatingRoleFin::Enter(GateAccount& account) {}
void AccountState_CreatingRoleFin::Tick(GateAccount& account) {}
void AccountState_CreatingRoleFin::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_DeletingRole::Enter(GateAccount& account) {}
void AccountState_DeletingRole::Tick(GateAccount& account) {}
void AccountState_DeletingRole::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_EnteringGame::Enter(GateAccount& account) {}
void AccountState_EnteringGame::Tick(GateAccount& account) {}
void AccountState_EnteringGame::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_Gaming::Enter(GateAccount& account) {}
void AccountState_Gaming::Tick(GateAccount& account) {}
void AccountState_Gaming::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_Destory::Enter(GateAccount& account) {}
void AccountState_Destory::Tick(GateAccount& account) {}
void AccountState_Destory::Leave(GateAccount& account) {}

//////////////////////////////////////////////////////////////////////////