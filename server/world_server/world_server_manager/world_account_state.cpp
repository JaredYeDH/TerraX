#include "world_account_state.h"
#include "world_account.h"
#include "world_server/world_net_module.h"


using namespace terra;

//////////////////////////////////////////////////////////////////////////

void AccountState_WaitingLogin::Enter(WorldAccount& account) {}
void AccountState_WaitingLogin::Tick(WorldAccount& account) {}
void AccountState_WaitingLogin::Leave(WorldAccount& account) {}
//////////////////////////////////////////////////////////////////////////

void AccountState_CheckingPermission::Enter(WorldAccount& account) {}
void AccountState_CheckingPermission::Tick(WorldAccount& account) {}
void AccountState_CheckingPermission::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_QueryingRoleList::Enter(WorldAccount& account) {}
void AccountState_QueryingRoleList::Tick(WorldAccount& account) {}
void AccountState_QueryingRoleList::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_SelectingRole::Enter(WorldAccount& account) {}
void AccountState_SelectingRole::Tick(WorldAccount& account) {}
void AccountState_SelectingRole::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_CreatingRole::Enter(WorldAccount& account) {}
void AccountState_CreatingRole::Tick(WorldAccount& account) {}
void AccountState_CreatingRole::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_CreatingRoleFin::Enter(WorldAccount& account) {}
void AccountState_CreatingRoleFin::Tick(WorldAccount& account) {}
void AccountState_CreatingRoleFin::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_DeletingRole::Enter(WorldAccount& account) {}
void AccountState_DeletingRole::Tick(WorldAccount& account) {}
void AccountState_DeletingRole::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_EnteringGame::Enter(WorldAccount& account) {}
void AccountState_EnteringGame::Tick(WorldAccount& account) {}
void AccountState_EnteringGame::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_Gaming::Enter(WorldAccount& account) {}
void AccountState_Gaming::Tick(WorldAccount& account) {}
void AccountState_Gaming::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////
void AccountState_Destory::Enter(WorldAccount& account) {}
void AccountState_Destory::Tick(WorldAccount& account) {}
void AccountState_Destory::Leave(WorldAccount& account) {}

//////////////////////////////////////////////////////////////////////////