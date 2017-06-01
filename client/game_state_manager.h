#pragma once
#include "base/types.h"
#include "game_state.h"
#include <array>
#include <memory>
#include "comm/proto/client_server.pb.h"

namespace terra
{
	using GameStateArray = std::array<std::unique_ptr<IGameState>, int32_t(GameState_t::GAMESTATE_COUNT)>;
	class GameStateManager final
	{
		DISABLE_COPY(GameStateManager);
		MAKE_INSTANCE(GameStateManager);
	private:
		GameState_t m_CurGameState{ GameState_t::UNKNOWN_STATE };
		GameStateArray m_GameStates;
	public:
		GameStateManager();
		~GameStateManager() = default;
		void Tick();
		void EnterDefaultState();
		void NextState(GameState_t eGameState);

		void OnMessage_LoginResultLC(packet_cs::MsgLoginResultLC* msg);
		//void OnMessage_PktRoleListAck(C2SPacket::PktRoleListAck* msg);
	};
}
