#pragma once

#include <string>
#include "base/types.h"
#include "client_packet_processor.h"
#include "comm/net/eventloop.h"
#include "comm/net/tcp_connection.h"
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

        EventLoop* get_event_loop() { return &loop_; }

        void StartConnectLoginServer();
		void SetGateIpPort(const std::string& ip, int port); 
		void StartConnectGateServer();

        void SendPacket2LoginServer(google::protobuf::Message& msg);
        void SendPacket2GateServer(google::protobuf::Message& msg);

        void OnLoginSocketEvent(TcpConnection* conn, SocketEvent_t ev);
        void OnLoginMessageEvent(TcpConnection* conn, evbuffer* evbuf);

		void OnGateSocketEvent(TcpConnection* conn, SocketEvent_t ev);
		void OnGateMessageEvent(TcpConnection* conn, evbuffer* evbuf);
    private:
        void InitLoginNetInfo();
    };
}