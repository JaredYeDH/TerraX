#pragma once

#include "comm/net/tcp_server.h"
#include "comm/proto/server_server.pb.h"
#include "net_base_module.h"

namespace terra
{
	class NetBaseModule;
    class ServerAcceptService
	{
		MAKE_INSTANCE(ServerAcceptService);
		DISABLE_COPY(ServerAcceptService);
	protected:
		NetBaseModule* net_;
		ServerTable& server_table_;
		PacketProcessor& packet_processor_;

		std::unique_ptr<TcpServer> server_;

    public:
        ServerAcceptService();
        virtual ~ServerAcceptService();

		void InitNetModule(NetBaseModule* net) { net_ = net; }

        void AcceptConnection(int port, uint32_t max_conns, SocketEventCB sock_cb, MessageEventCB msg_cb);

    };
}