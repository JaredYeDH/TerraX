#pragma once

#include "base/types.h"
#include "comm/net/eventloop.h"
#include "comm/net/tcp_connection.h"
#include "client_packet_processor.h"
#include "comm/proto/client_server.pb.h"
#include <string>
namespace terra
{
	class IPInfo
	{
	public:
		std::string ip_;
		int port_{ 0 };

		IPInfo() = default;
		~IPInfo() = default;
		IPInfo(std::string&& ip, int port) :
			ip_(ip), port_(port)
		{
		}
	};

	class ClientConnService;
	class ClientNetModule final
	{
		DISABLE_COPY(ClientNetModule);
		MAKE_INSTANCE(ClientNetModule);
	private:
		const PeerType_t kSelfPeer;
		ClientPacketProcessor& packet_processor_;
		EventLoop loop_;
		ClientConnService& conn_service_;
		std::vector<IPInfo> login_info_;
		TcpConnection* login_conn_{ nullptr };
		TcpConnection* gate_conn_{ nullptr };
	public:
		ClientNetModule();
		~ClientNetModule() = default;

		bool Init();
		bool AfterInit();
		bool Tick();
		bool BeforeShut();
		bool Shut();

		EventLoop* get_event_loop() { return &loop_; }

		void StartConnectLoginServer();

		void SendPacket2LoginServer(google::protobuf::Message& msg);
		void SendPacket2GateServer(google::protobuf::Message& msg);
	private:
		void InitLoginNetInfo();


		void OnLoginSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnLoginMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnGateSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnGateMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnLoginConnected(TcpConnection* conn);
		void OnLoginDisconnected(TcpConnection* conn);

		void OnGateConnected(TcpConnection* conn);
		void OnGateDisconnected(TcpConnection* conn);

	};
}