#pragma once

#include <event2/bufferevent.h>
#include <google/protobuf/message.h>
#include "base/types.h"
#include "comm/net/net_define.h"
namespace terra
{
	class NetBaseModule;
	class ServerTable;
	class PacketProcessor
	{
		DISABLE_COPY(PacketProcessor);
		MAKE_INSTANCE(PacketProcessor);
	public:
		PacketProcessor();
		~PacketProcessor(){}

		void SendPacket(TcpConnection* conn, google::protobuf::Message& msg);

		void ProcessServerPacket(TcpConnection* conn, struct evbuffer* evbuf);
		
	};
}