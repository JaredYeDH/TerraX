#pragma once

#include "base/types.h"

namespace terra
{
	enum class GameState_t
	{
		UNKNOWN_STATE = -1,
		PRESS2START = 0,				// 启动界面
		LOGIN_FORM,						// 登录界面	
		CONNECTING2LOGIN,				// 正在连接登录服务器...弹出窗口
		ACCOUNT_LOGGINGIN,				// 正在登录中...弹窗,收到成功包则进入服务器选择界面或者申请进入游戏世界,失败则返回登录阶段
		ACCOUNT_CHOSINGSERVER,			// 选择服务器界面
		CONNECTING_GATE,
		ACCOUNT_CHECKINGTOKEN,
		SELECTING_AVATAR,				// 角色选择界面 //（选择，创建，删除等等是否需要新增状态？）
		ENTERING_GAME,					// 进入游戏世界中...
		ENTERING_SCENE,					// 进入场景
		GAMING,							// 游戏中

		GAMESTATE_COUNT,
	};

	class IGameState
	{
	public:
		virtual void Enter() = 0;
		virtual void Tick() = 0;
		virtual void Leave() = 0;
	};

	class GameState_Press2Start : public IGameState
	{
	public:
		void Enter() override final;
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_eLoginForm : public IGameState
	{
	public:
		void Enter() override final;
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_Connecting2Login : public IGameState
	{
	public:
		void Enter() override final;
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_AccountLoggingin : public IGameState
	{
	public:
		void Enter() override final;
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_ChosingServer : public IGameState
	{
	public:
		void Enter() override final;
		void Tick() override final {}
		void Leave() override final;
	};

	class GameState_Connecting2Gate : public IGameState
	{
	public:
		void Enter() override final;
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_CheckingPermission : public IGameState
	{
	public:
		void Enter() override final;
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_AccountSelectingAvatar : public IGameState
	{
	public:
		void Enter() override final {}
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_AccountEnteringWorld : public IGameState
	{
	public:
		void Enter() override final;
		void Tick() override final {}
		void Leave() override final {}
	};


	class GameState_PlayerEnteringScene : public IGameState
	{
	public:
		void Enter() override final {}
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_Gaming : public IGameState
	{
	public:
		void Enter() override final {}
		void Tick() override final {}
		void Leave() override final {}
	};

}
