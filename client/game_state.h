#pragma once

#include "base/types.h"

namespace terra
{
	enum class GameState_t
	{
		UNKNOWN_STATE = -1,
		PRESS2START = 0,				// ��������
		LOGIN_FORM,						// ��¼����	
		CONNECTING2LOGIN,				// �������ӵ�¼������...��������
		ACCOUNT_LOGGINGIN,				// ���ڵ�¼��...����,�յ��ɹ�������������ѡ�����������������Ϸ����,ʧ���򷵻ص�¼�׶�
		ACCOUNT_CHOSINGSERVER,			// ѡ�����������
		CONNECTING_GATE,
		ACCOUNT_CHECKINGTOKEN,
		SELECTING_AVATAR,				// ��ɫѡ����� //��ѡ�񣬴�����ɾ���ȵ��Ƿ���Ҫ����״̬����
		ENTERING_GAME,					// ������Ϸ������...
		ENTERING_SCENE,					// ���볡��
		GAMING,							// ��Ϸ��

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
