#pragma once

#include "comm/net/tcp_server.h"
#include "comm/proto/server_server.pb.h"
#include "net_base_module.h"

namespace terra
{
	class NetBaseModule;
    class ServerLoginAckService;
    class ServerAcceptService
    {
    private:
        NetBaseModule& net_;
        std::unique_ptr<TcpServer> server_;
        std::unique_ptr<ServerLoginAckService> login_ack_;

    public:
        ServerAcceptService(NetBaseModule& net);
        ~ServerAcceptService();

		NetBaseModule& get_net_base_module() { return net_; }

        void InitLoginAckService(PeerType_t peer, int max_conns);

        void AcceptConnection(int port, uint32_t max_conns, SocketEventCB sock_cb, MessageEventCB msg_cb);

		void OnDisconnected(TcpConnection* conn);
    };
}