#pragma once

#include "comm/proto/client_server.pb.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	enum class Account_State_t
	{
		ACCOUNT_WAITING_LOGIN,
		ACCOUNT_CHECKING_PERMISSION,
		ACCOUNT_QUERYING_ROLELIST,
		ACCOUNT_SELECTING_ROLE,
		ACCOUNT_CREATING_ROLE,
		ACCOUNT_CREATING_ROLE_FIN,
		ACCOUNT_DELETING_ROLE,
		ACCOUNT_ENTERING_GAME,
		ACCOUNT_GAMING,
		ACCOUNT_DESTROY,
		ACCOUNT_COUNT
	};
	class GateAccount;

	class AccountState_Base
	{
	public:
		virtual void Enter(GateAccount& account) {}
		virtual void Tick(GateAccount& account) {}
		virtual void Leave(GateAccount& account) {}

		virtual void HandleMessage(GateAccount& account, packet_cs::MsgReqLoginGameCS* msg) {}
	};

	class AccountState_WaitingLogin : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
		void HandleMessage(GateAccount& account, packet_cs::MsgReqLoginGameCS* msg) override;
	};

	class AccountState_CheckingPermission : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

	class AccountState_QueryingRoleList : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

	class AccountState_SelectingRole : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

	class AccountState_CreatingRole : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

	class AccountState_CreatingRoleFin : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

	class AccountState_DeletingRole : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

	class AccountState_EnteringGame : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

	class AccountState_Gaming : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

	class AccountState_Destory : public AccountState_Base
	{
	public:
		void Enter(GateAccount& account) override;
		void Tick(GateAccount& account) override;
		void Leave(GateAccount& account) override;
	};

}