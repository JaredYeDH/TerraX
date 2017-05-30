#include "packet.h"

using namespace terra;

bool SrvInfoTag::InitialWithMsg(char* buffer)
{
    msg_tag_ = buffer;
    set_server_id(-1);
    return true;
}

bool SrvInfoTag::InitialFromBuffer(char* buffer)
{
    msg_tag_ = buffer;
    memcpy(&server_id_, msg_tag_, sizeof(server_id_));
    server_id_ = ntohl(server_id_);
    return true;
}

//////////////////////////////////////////////////////////////////////////
bool MsgData::InitialWithMsg(char* buffer, int size, google::protobuf::Message& msg)
{
    const std::string& msgName = msg.GetDescriptor()->name();
    assert(msgName.size() + 1 <= 0xFF);
    msg_data_ = buffer;
    msg_name_size_ = static_cast<uint8_t>(msgName.size() + 1);  //'\0'
    msg_size_ = msg.ByteSize();
    // msg_data_size(2)-avatar_id(4)-msg_name_size(1)-msg_name-msg)
    msg_data_size_ = sizeof(uint16_t) + sizeof(int) + sizeof(msg_name_size_) + msg_name_size_ + msg_size_;
    assert(msg_data_size_ <= size);
    int start_index = 0;

    uint16_t packet_be16 = htons(static_cast<uint16_t>(msg_data_size_));
    memcpy(msg_data_, &packet_be16, sizeof packet_be16);
    start_index += sizeof packet_be16;

    start_index += sizeof(int32_t);

    memcpy(msg_data_ + start_index, &msg_name_size_, sizeof msg_name_size_);
    start_index += sizeof msg_name_size_;

    memcpy(msg_data_ + start_index, msgName.c_str(), msg_name_size_);
    start_index += msg_name_size_;

    msg_ = msg_data_ + start_index;
    msg.SerializeToArray(msg_, msg.ByteSize());
    start_index += msg.ByteSize();

    return true;
}
bool MsgData::InitialFromBuffer(char* buffer)
{
    msg_data_ = buffer;

    int offset = 0;
    memcpy(&msg_data_size_, msg_data_, sizeof msg_data_size_);
    msg_data_size_ = ntohs(msg_data_size_);
    offset += sizeof(msg_data_size_);

    memcpy(&avatar_id_, msg_data_ + offset, sizeof avatar_id_);
    avatar_id_ = ntohl(avatar_id_);
    offset += sizeof(avatar_id_);

    memcpy(&msg_name_size_, msg_data_ + offset, sizeof msg_name_size_);
    offset += sizeof(msg_name_size_);

    msg_name_ = msg_data_ + offset;
    offset += msg_name_size_;

    msg_ = msg_data_ + offset;
    msg_size_ = msg_data_size_ - offset;
	return true;
}