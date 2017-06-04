#include "Login_account.h"

using namespace terra;


void LoginAccount::EnterState(Account_State_t account_state)
{
	assert(account_state >= Account_State_t::ACCOUNT_INIT 
		&& account_state < Account_State_t::ACCOUNT_COUNT);

	//m_GameStates[int(eGameState)]->Leave();
	//m_CurGameState = eGameState;
	//m_GameStates[int(m_CurGameState)]->Enter();
}