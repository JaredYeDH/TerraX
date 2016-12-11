#pragma once
#include <map>
#include <functional>
#include <google/protobuf/message.h>
#include "NetDefine.h"
#include "ComDef.h"

namespace TerraX
{
	class NetChannel;
	namespace gpb = google::protobuf;
	class IPacketFunctor
	{
	public:
		IPacketFunctor() = default;
		virtual void operator()(NetChannelPtr& pChannel, int32_t nFromPeerInfo, gpb::Message& arg) {}
	};

	template<typename Packet>
	class PacketFunctor : public IPacketFunctor
	{
		using PacketCB = std::function<void(NetChannelPtr&, int32_t, Packet&)>;
	public:
		explicit PacketFunctor(PacketCB cb) {
			this->cb = cb;
		}
		void operator()(NetChannelPtr& pChannel, int32_t nFromPeerInfo, gpb::Message& msg) override final {
			cb(pChannel, nFromPeerInfo, static_cast<Packet&>(msg));
		}
	private:
		PacketCB cb;
	};


	class PacketDispatcher
	{
		MAKEINSTANCE(PacketDispatcher);
	public:
		PacketDispatcher() = default;

		template <class Packet>
		void RegPacketHandler(IPacketFunctor* pMsg) {
			assert(m_mapCallBacks.find(Packet::descriptor()) == m_mapCallBacks.end());
			m_mapCallBacks[Packet::descriptor()] = pMsg;
		}

		bool DeliverPacket(NetChannelPtr& pChannel, int32_t nFromPeerInfo, const std::string& strMsgType, const char* pBuffer, const int nBufferSize);
	private:
		std::map<const google::protobuf::Descriptor*, IPacketFunctor* > m_mapCallBacks;
	};
}