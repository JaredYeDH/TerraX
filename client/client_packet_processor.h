#pragma once

#include <event2/bufferevent.h>
#include <google/protobuf/message.h>
#include "base/types.h"
#include "comm/net/net_define.h"
namespace terra
{
	class NetBaseModule;
	class ClientPacketProcessor
	{
		DISABLE_COPY(ClientPacketProcessor);
		MAKE_INSTANCE(ClientPacketProcessor);
	public:
		ClientPacketProcessor();
		~ClientPacketProcessor() {}

		void SendPacket(int server_id, google::protobuf::Message& msg);
		void SendPacket(TcpConnection* conn, google::protobuf::Message& msg);

		void ProcessServerPacket(TcpConnection* conn, struct evbuffer* evbuf);

	};
}