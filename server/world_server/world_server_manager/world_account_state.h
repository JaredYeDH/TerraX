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
	class WorldAccount;

	class AccountState_Base
	{
	public:
		virtual void Enter(WorldAccount& account) {}
		virtual void Tick(WorldAccount& account) {}
		virtual void Leave(WorldAccount& account) {}

		virtual void HandleMessage(WorldAccount& account, packet_cs::MsgReqLoginGameCS* msg) {}
	};

	class AccountState_WaitingLogin : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_CheckingPermission : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_QueryingRoleList : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_SelectingRole : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_CreatingRole : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_CreatingRoleFin : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_DeletingRole : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_EnteringGame : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_Gaming : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

	class AccountState_Destory : public AccountState_Base
	{
	public:
		void Enter(WorldAccount& account) override;
		void Tick(WorldAccount& account) override;
		void Leave(WorldAccount& account) override;
	};

}