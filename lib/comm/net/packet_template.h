#pragma once

#include <google/protobuf/message.h>
#include "base/types.h"
#include <arpa/inet.h>
#include "packet_define.h"
#include "packet.h"

namespace terra
{

	template<typename Tag, typename Data, int BUFFER_SIZE = 4096>
	class PacketT
	{
	public:
		static const int MIN_PACKET_SIZE = sizeof(uint16_t) + Tag::TAG_SIZE + Data::MIN_MSG_DATA_SIZE;
	private:
		char buffer_[BUFFER_SIZE];
		uint16_t total_len_{ 0 };
		Tag msg_tag_;
		Data msg_data_;
		uint16_t avatar_count_{ 0 };
		uint16_t max_avatar_count_{ 0 };
		int* avatars_{ nullptr };

	public:
		PacketT() = default;
		~PacketT() = default;

		void InitialWithMsg(google::protobuf::Message& msg, int max_avatar_count = 0);
		void InitialFromBuffer(uint16_t total_len);

		char* get_buffer() { return buffer_; }
		uint16_t get_total_len() { return total_len_; }

		void set_avatar_id(int avatar_id) { msg_data_.set_avatar_id(avatar_id); }

		Tag& get_msg_tag() { return msg_tag_; }
		Data& get_msg_data() { return msg_data_; }

		void append_avatar(int avatar_id){}

	private:
		void set_total_len(uint16_t len)
		{
			assert(len);
			total_len_ = len;
			uint16_t be16 = htons(len);
			memcpy(buffer_, &be16, sizeof be16);
		}
	};

	template<typename Tag, typename Data, int BUFFER_SIZE>
	void PacketT<Tag, Data, BUFFER_SIZE>::InitialWithMsg(google::protobuf::Message& msg, int max_avatar_count/* = 0*/)
	{
		max_avatar_count_ = max_avatar_count;

		int offset = sizeof(total_len_);
		char* msg_tag_buffer = buffer_ + offset;
		msg_tag_.InitialWithMsg(msg_tag_buffer);
		offset += msg_tag_.get_tag_size();

		char* msg_data_buffer = buffer_ + offset;
		int rest_size = BUFFER_SIZE - sizeof(total_len_) - msg_tag_.get_tag_size() -
			sizeof(max_avatar_count_) - max_avatar_count_ * sizeof(int);
		msg_data_.InitialWithMsg(msg_data_buffer, rest_size, msg);

		set_total_len(sizeof(total_len_) + msg_tag_.get_tag_size() + msg_data_.get_msg_data_size());
	}

	//TODO: avatar
	template<typename Tag, typename Data, int BUFFER_SIZE>
	void PacketT<Tag, Data, BUFFER_SIZE>::InitialFromBuffer(uint16_t total_len)
	{
		total_len_ = total_len;

		int offset = sizeof(total_len_);
		char* msg_tag_buffer = buffer_ + offset;
		msg_tag_.InitialFromBuffer(msg_tag_buffer);
		offset += msg_tag_.get_tag_size();

		char* msg_data_buffer = buffer_ + offset;
		msg_data_.InitialFromBuffer(msg_data_buffer);
		offset += msg_data_.get_msg_data_size();

		int rest_size = total_len_ - offset;
		if (rest_size > 0)
		{
			assert((rest_size % sizeof(int) == sizeof(avatar_count_)) && (rest_size >= static_cast<int>(sizeof(int) + sizeof(avatar_count_))));
			uint16_t avatar_count = 0;
			memcpy(&avatar_count, buffer_ + offset, sizeof(uint16_t));
			max_avatar_count_ = avatar_count_ = ntohs(avatar_count);
			//copy avatars
			memcpy(&avatars_, buffer_ + offset + sizeof(uint16_t), sizeof(int) * avatar_count);
		}
	}
}