#pragma once


namespace terra
{
	enum class Account_State_t
	{
		ACCOUNT_INIT,
		ACCOUNT_WAITING_LOGININFO,
		ACCOUNT_BILLINGAUTH,
		ACCOUNT_WAITING_BILLINGRESULT,
		ACCOUNT_WAITING_SYNCSERVERLIST,
		ACCOUNT_WAITING_REQ_ENTERGAME,
		ACCOUNT_WAITING_WORLDCHECKTOKEN,
		ACCOUNT_WAITING_CLIENTSWITCH2GATE,
		ACCOUNT_DESTROY,

		ACCOUNT_COUNT,
	};

	class AccountState_Base
	{

	};

	class AccountState_Init : public AccountState_Base
	{

	};

	class AccountState_WaitingLoginInfo : public AccountState_Base
	{

	};

	class AccountState_BillingAuth : public AccountState_Base
	{

	};

	class AccountState_WaitingClientSwitch2Gate : public AccountState_Base
	{

	};

	class AccountState_SyncServerList : public AccountState_Base
	{

	};

	class AccountState_WaitingReqEnterGame : public AccountState_Base
	{

	};

	class AccountState_WaitingWorldCheckToken : public AccountState_Base
	{

	};

	class AccountState_WaitingWorldCheckToken : public AccountState_Base
	{

	};

	class AccountState_Destory : public AccountState_Base
	{

	};
}