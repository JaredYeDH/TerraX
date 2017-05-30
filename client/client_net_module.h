#pragma once

#include "base/types.h"
#include "comm/net/eventloop.h"
#include "comm/net/tcp_connection.h"
#include "packet_processor.h"
#include "comm/proto/client_server.pb.h"

namespace terra
{
	class ClientConnService;
	class ClientNetModule final
	{
		DISABLE_COPY(ClientNetModule);
		MAKE_INSTANCE(ClientNetModule);
	private:
		const PeerType_t kSelfPeer;

		EventLoop loop_;
		ClientConnService& conn_service_;
	public:
		ClientNetModule();
		~ClientNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();

	private:
		void InitLoginNetInfo();

		void StartConnectLoginServer();

		void OnLoginSocketEvent(TcpConnection* conn, ConnState_t conn_state);
		void OnLoginMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnGateSocketEvent(TcpConnection* conn, ConnState_t conn_state);
		void OnGateMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnLoginConnected(TcpConnection* conn);
		void OnLoginDisconnected(TcpConnection* conn);

		void OnGateConnected(TcpConnection* conn);
		void OnGateDisconnected(TcpConnection* conn);

	};
}