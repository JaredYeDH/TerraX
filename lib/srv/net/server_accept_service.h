#pragma once

#include "comm/net/tcp_server.h"
#include "comm/proto/server_server.pb.h"
#include "net_base_module.h"

namespace terra
{
	class NetBaseModule;
    class ServerAcceptService
    {
	protected:
		NetBaseModule& net_;
		const PeerType_t kSelfPeer;
		ServerTable& server_table_;
		PacketProcessor& packet_processor_;

		std::unique_ptr<TcpServer> server_;

    public:
        ServerAcceptService(NetBaseModule& net);
        virtual ~ServerAcceptService();

		NetBaseModule& get_net_base_module() { return net_; }

        void AcceptConnection(int port, uint32_t max_conns, SocketEventCB sock_cb, MessageEventCB msg_cb);

    };
}