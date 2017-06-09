#pragma once
#include "comm/proto/client_server.pb.h"
#include "comm/proto/server_server.pb.h"

namespace terra
{
	enum class Account_State_t
	{
		ACCOUNT_WAITING_LOGIN,
		ACCOUNT_WAITING_BILLINGAUTH,
		ACCOUNT_WAITING_SERVERLIST,
		ACCOUNT_WAITING_REQ_ENTERGAME,
		ACCOUNT_WAITING_WORLDCHECKTOKEN,
		ACCOUNT_WAITING_CLIENTSWITCH2GATE,
		ACCOUNT_DESTROY,

		ACCOUNT_COUNT,
	};
	class LoginAccount;
	class AccountState_Base
	{
	public:
		virtual void Enter(LoginAccount& account){}
		virtual void Tick(LoginAccount& account){}
		virtual void Leave(LoginAccount& account){}

		virtual void HandleMessage(LoginAccount& account, packet_cs::MsgReqLoginCL* msg) {}
		virtual void HandleMessage(LoginAccount& account, packet_ss::MsgServerListML* msg) {}
	};


	class AccountState_WaitingLogin : public AccountState_Base
	{
	public:
		void Enter(LoginAccount& account) override;
		void Tick(LoginAccount& account)  override;
		void Leave(LoginAccount& account)  override;

		void HandleMessage(LoginAccount& account, packet_cs::MsgReqLoginCL* msg) override;
	};

	class AccountState_WaitingBillingAuth : public AccountState_Base
	{
	public:
		void Enter(LoginAccount& account) override;
		void Tick(LoginAccount& account)  override;
		void Leave(LoginAccount& account)  override;
	};

	class AccountState_WaitingServerList : public AccountState_Base
	{
	public:
		void Enter(LoginAccount& account) override;
		void Tick(LoginAccount& account)  override;
		void Leave(LoginAccount& account)  override;
		void HandleMessage(LoginAccount& account, packet_ss::MsgServerListML* msg) override;
	};

	class AccountState_WaitingReqEnterGame : public AccountState_Base
	{
	public:
		void Enter(LoginAccount& account) override;
		void Tick(LoginAccount& account)  override;
		void Leave(LoginAccount& account)  override;
	};

	class AccountState_WaitingWorldCheckToken : public AccountState_Base
	{
	public:
		void Enter(LoginAccount& account) override;
		void Tick(LoginAccount& account)  override;
		void Leave(LoginAccount& account)  override;
	};

	class AccountState_WaitingClientSwitch2Gate : public AccountState_Base
	{
	public:
		void Enter(LoginAccount& account) override;
		void Tick(LoginAccount& account)  override;
		void Leave(LoginAccount& account)  override;
	};

	class AccountState_Destory : public AccountState_Base
	{
	public:
		void Enter(LoginAccount& account) override;
		void Tick(LoginAccount& account)  override;
		void Leave(LoginAccount& account)  override;
	};
}