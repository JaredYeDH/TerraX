#pragma once

namespace TerraX
{
	enum class GameState_t
	{
		eUnKnownState = -1,
		ePress2Start = 0,				// ��������
		eLoginForm,						// ��¼����	
		eConnecting2Login,				// �������ӵ�¼������...��������
		eAccountLoggingin,				// ���ڵ�¼��...����,�յ��ɹ�������������ѡ�����������������Ϸ����,ʧ���򷵻ص�¼�׶�
		/*eAccountChosingServer,*/		// ѡ�����������
		eAcc,
		eAccountEnteringWorld,			// ������Ϸ������...�ɹ�������ɫѡ����棬ʧ�ܷ��ص�¼����
		eAccountSelectingAvatar,		// ѡ����� //��ѡ�񣬴�����ɾ���ȵ��Ƿ���Ҫ����״̬����
		ePlayerEnteringScene,			// ���볡��
		eGaming,						// ��Ϸ��

		eGameState_Count,
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
		void Enter() override final {}
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_AccountLoggingin : public IGameState
	{
	public:
		void Enter() override final {}
		void Tick() override final {}
		void Leave() override final {}
	};

	class GameState_Connecting2Gate : public IGameState
	{
	public:
		void Enter() override final;
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

	class GameState_AccountSelectingAvatar : public IGameState
	{
	public:
		void Enter() override final {}
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
