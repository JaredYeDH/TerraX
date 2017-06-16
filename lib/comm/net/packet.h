#pragma once

#include <arpa/inet.h>
#include <google/protobuf/message.h>
#include "base/types.h"

namespace terra
{
    class NullTag_t
    {
    public:
        static const int TAG_SIZE = 0;

    public:
        NullTag_t() = default;
        ~NullTag_t() = default;

        bool InitialWithMsg(char* buffer) { return true; }
        bool InitialFromBuffer(char* buffer) { return true; }

        int get_tag_size()  const { return TAG_SIZE; }
    };

    class NullData_t
    {
    public:
        static const int MIN_MSG_DATA_SIZE = 0;

        bool InitialWithMsg(char* buffer) { return true; }
        bool InitialFromBuffer(char* buffer) { return true; }

        void set_avatar_id(int avatar_id) {}
        int get_avatar_id()  const { return 0; }

        const char* get_msg_data() const { return ""; }
        int get_msg_data_size()  const { return 0; }

        const char* get_msg_name() const { return ""; }
        const char* get_msg() const { return ""; }
        int get_msg_size()  const { return 0; }
    };

    class SrvInfoTag
    {
    public:
        static const int TAG_SIZE = sizeof(int);

    private:
        char* msg_tag_{nullptr};
        int server_id_{-1};

    public:
        SrvInfoTag() = default;
        ~SrvInfoTag() = default;

        bool InitialWithMsg(char* buffer);
        bool InitialFromBuffer(char* buffer);
        void set_server_id(int server_id)
        {
            assert(msg_tag_);
            server_id_ = server_id;
            int be32 = htonl(server_id);
            memcpy(msg_tag_, &be32, sizeof be32);
        }
        int get_server_id()  const { return server_id_; };
        int get_tag_size()  const { return TAG_SIZE; }
    };

    class MsgData
    {
    public:
        static const int MIN_MSG_DATA_SIZE = sizeof(uint16_t) + sizeof(int);

    private:
        // msg_data_size_ + avatar_id_ + 1('\0') + 1
        char* msg_data_{nullptr};
        uint16_t msg_data_size_{0};
        int avatar_id_{0};
        char* msg_name_{nullptr};
        uint8_t msg_name_size_{0};
        char* msg_{nullptr};
        int msg_size_{0};

    public:
        MsgData() = default;
        ~MsgData() = default;

        bool InitialWithMsg(char* buffer, int size, google::protobuf::Message& msg);
        bool InitialFromBuffer(char* buffer);

        void set_avatar_id(int avatar_id)
        {
            assert(msg_data_);
            avatar_id_ = avatar_id;
            int be32 = htonl(avatar_id);
            memcpy(msg_data_ + sizeof(uint16_t), &be32, sizeof be32);
        }
        int get_avatar_id() const { return avatar_id_; }

        const char* get_msg_data() const { return msg_data_; }
        int get_msg_data_size() const { return msg_data_size_; }

        const char* get_msg_name() const { return msg_name_; }
        const char* get_msg() { return msg_; }
        int get_msg_size() const { return msg_size_; }
    };
}