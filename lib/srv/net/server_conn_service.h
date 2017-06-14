#pragma once
#include <memory>
#include "comm/net/tcp_connection.h"
#include "comm/proto/server_server.pb.h"
#include "net_base_module.h"

namespace terra
{
	//用继承实现子类instance
    class ServerConnService
    {
        MAKE_INSTANCE(ServerConnService);
        DISABLE_COPY(ServerConnService);

    private:
        NetBaseModule* net_;
        ServerTable& server_table_;
        PacketProcessor& packet_processor_;
		std::vector<std::unique_ptr<TcpConnection>> conns_;
    public:
        ServerConnService();
        ~ServerConnService();

        void InitNetModule(NetBaseModule* net) { net_ = net; }

        void Login2World(TcpConnection* conn);
        void Login2Node(TcpConnection* conn);

        TcpConnection* NewConnect(const char* ip, int port, SocketEventCB sock_cb, MessageEventCB msg_cb);
		void DestroyConnection(TcpConnection* conn);
    private:
        void OnMessage_RegisterWS(packet_ss::MsgRegisterWS* msg);
    };
}