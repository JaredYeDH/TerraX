// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: base_type.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "base_type.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace pb_base {

namespace {

const ::google::protobuf::Descriptor* ServerProfile_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ServerProfile_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* ServerStatus_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_base_5ftype_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_base_5ftype_2eproto() {
  protobuf_AddDesc_base_5ftype_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "base_type.proto");
  GOOGLE_CHECK(file != NULL);
  ServerProfile_descriptor_ = file->message_type(0);
  static const int ServerProfile_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, server_uid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, region_showindex_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, region_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, server_showindex_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, server_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, server_status_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, recommond_new_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, recommond_hot_),
  };
  ServerProfile_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      ServerProfile_descriptor_,
      ServerProfile::default_instance_,
      ServerProfile_offsets_,
      -1,
      -1,
      -1,
      sizeof(ServerProfile),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ServerProfile, _is_default_instance_));
  ServerStatus_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_base_5ftype_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      ServerProfile_descriptor_, &ServerProfile::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_base_5ftype_2eproto() {
  delete ServerProfile::default_instance_;
  delete ServerProfile_reflection_;
}

void protobuf_AddDesc_base_5ftype_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_base_5ftype_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017base_type.proto\022\007pb_base\"\335\001\n\rServerPro"
    "file\022\022\n\nserver_uid\030\001 \001(\005\022\030\n\020region_showi"
    "ndex\030\002 \001(\005\022\023\n\013region_name\030\003 \001(\t\022\030\n\020serve"
    "r_showindex\030\004 \001(\005\022\023\n\013server_name\030\005 \001(\t\022,"
    "\n\rserver_status\030\006 \001(\0162\025.pb_base.ServerSt"
    "atus\022\025\n\rrecommond_new\030\007 \001(\010\022\025\n\rrecommond"
    "_hot\030\010 \001(\010*E\n\014ServerStatus\022\014\n\010MAINTAIN\020\000"
    "\022\010\n\004FREE\020\001\022\010\n\004BUSY\020\002\022\t\n\005CROWD\020\003\022\010\n\004FULL\020"
    "\004b\006proto3", 329);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "base_type.proto", &protobuf_RegisterTypes);
  ServerProfile::default_instance_ = new ServerProfile();
  ServerProfile::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_base_5ftype_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_base_5ftype_2eproto {
  StaticDescriptorInitializer_base_5ftype_2eproto() {
    protobuf_AddDesc_base_5ftype_2eproto();
  }
} static_descriptor_initializer_base_5ftype_2eproto_;
const ::google::protobuf::EnumDescriptor* ServerStatus_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ServerStatus_descriptor_;
}
bool ServerStatus_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ServerProfile::kServerUidFieldNumber;
const int ServerProfile::kRegionShowindexFieldNumber;
const int ServerProfile::kRegionNameFieldNumber;
const int ServerProfile::kServerShowindexFieldNumber;
const int ServerProfile::kServerNameFieldNumber;
const int ServerProfile::kServerStatusFieldNumber;
const int ServerProfile::kRecommondNewFieldNumber;
const int ServerProfile::kRecommondHotFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ServerProfile::ServerProfile()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb_base.ServerProfile)
}

void ServerProfile::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

ServerProfile::ServerProfile(const ServerProfile& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb_base.ServerProfile)
}

void ServerProfile::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  server_uid_ = 0;
  region_showindex_ = 0;
  region_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  server_showindex_ = 0;
  server_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  server_status_ = 0;
  recommond_new_ = false;
  recommond_hot_ = false;
}

ServerProfile::~ServerProfile() {
  // @@protoc_insertion_point(destructor:pb_base.ServerProfile)
  SharedDtor();
}

void ServerProfile::SharedDtor() {
  region_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  server_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void ServerProfile::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ServerProfile::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ServerProfile_descriptor_;
}

const ServerProfile& ServerProfile::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_base_5ftype_2eproto();
  return *default_instance_;
}

ServerProfile* ServerProfile::default_instance_ = NULL;

ServerProfile* ServerProfile::New(::google::protobuf::Arena* arena) const {
  ServerProfile* n = new ServerProfile;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ServerProfile::Clear() {
// @@protoc_insertion_point(message_clear_start:pb_base.ServerProfile)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(ServerProfile, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<ServerProfile*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(server_uid_, region_showindex_);
  ZR_(server_showindex_, recommond_hot_);
  region_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  server_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());

#undef ZR_HELPER_
#undef ZR_

}

bool ServerProfile::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb_base.ServerProfile)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 server_uid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &server_uid_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_region_showindex;
        break;
      }

      // optional int32 region_showindex = 2;
      case 2: {
        if (tag == 16) {
         parse_region_showindex:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &region_showindex_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_region_name;
        break;
      }

      // optional string region_name = 3;
      case 3: {
        if (tag == 26) {
         parse_region_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_region_name()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->region_name().data(), this->region_name().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "pb_base.ServerProfile.region_name"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_server_showindex;
        break;
      }

      // optional int32 server_showindex = 4;
      case 4: {
        if (tag == 32) {
         parse_server_showindex:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &server_showindex_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_server_name;
        break;
      }

      // optional string server_name = 5;
      case 5: {
        if (tag == 42) {
         parse_server_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_server_name()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->server_name().data(), this->server_name().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "pb_base.ServerProfile.server_name"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_server_status;
        break;
      }

      // optional .pb_base.ServerStatus server_status = 6;
      case 6: {
        if (tag == 48) {
         parse_server_status:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_server_status(static_cast< ::pb_base::ServerStatus >(value));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_recommond_new;
        break;
      }

      // optional bool recommond_new = 7;
      case 7: {
        if (tag == 56) {
         parse_recommond_new:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &recommond_new_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_recommond_hot;
        break;
      }

      // optional bool recommond_hot = 8;
      case 8: {
        if (tag == 64) {
         parse_recommond_hot:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &recommond_hot_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:pb_base.ServerProfile)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb_base.ServerProfile)
  return false;
#undef DO_
}

void ServerProfile::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb_base.ServerProfile)
  // optional int32 server_uid = 1;
  if (this->server_uid() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->server_uid(), output);
  }

  // optional int32 region_showindex = 2;
  if (this->region_showindex() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->region_showindex(), output);
  }

  // optional string region_name = 3;
  if (this->region_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->region_name().data(), this->region_name().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "pb_base.ServerProfile.region_name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->region_name(), output);
  }

  // optional int32 server_showindex = 4;
  if (this->server_showindex() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->server_showindex(), output);
  }

  // optional string server_name = 5;
  if (this->server_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->server_name().data(), this->server_name().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "pb_base.ServerProfile.server_name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->server_name(), output);
  }

  // optional .pb_base.ServerStatus server_status = 6;
  if (this->server_status() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      6, this->server_status(), output);
  }

  // optional bool recommond_new = 7;
  if (this->recommond_new() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(7, this->recommond_new(), output);
  }

  // optional bool recommond_hot = 8;
  if (this->recommond_hot() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(8, this->recommond_hot(), output);
  }

  // @@protoc_insertion_point(serialize_end:pb_base.ServerProfile)
}

::google::protobuf::uint8* ServerProfile::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb_base.ServerProfile)
  // optional int32 server_uid = 1;
  if (this->server_uid() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->server_uid(), target);
  }

  // optional int32 region_showindex = 2;
  if (this->region_showindex() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->region_showindex(), target);
  }

  // optional string region_name = 3;
  if (this->region_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->region_name().data(), this->region_name().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "pb_base.ServerProfile.region_name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->region_name(), target);
  }

  // optional int32 server_showindex = 4;
  if (this->server_showindex() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->server_showindex(), target);
  }

  // optional string server_name = 5;
  if (this->server_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->server_name().data(), this->server_name().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "pb_base.ServerProfile.server_name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->server_name(), target);
  }

  // optional .pb_base.ServerStatus server_status = 6;
  if (this->server_status() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      6, this->server_status(), target);
  }

  // optional bool recommond_new = 7;
  if (this->recommond_new() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(7, this->recommond_new(), target);
  }

  // optional bool recommond_hot = 8;
  if (this->recommond_hot() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(8, this->recommond_hot(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:pb_base.ServerProfile)
  return target;
}

int ServerProfile::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:pb_base.ServerProfile)
  int total_size = 0;

  // optional int32 server_uid = 1;
  if (this->server_uid() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->server_uid());
  }

  // optional int32 region_showindex = 2;
  if (this->region_showindex() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->region_showindex());
  }

  // optional string region_name = 3;
  if (this->region_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->region_name());
  }

  // optional int32 server_showindex = 4;
  if (this->server_showindex() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->server_showindex());
  }

  // optional string server_name = 5;
  if (this->server_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->server_name());
  }

  // optional .pb_base.ServerStatus server_status = 6;
  if (this->server_status() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->server_status());
  }

  // optional bool recommond_new = 7;
  if (this->recommond_new() != 0) {
    total_size += 1 + 1;
  }

  // optional bool recommond_hot = 8;
  if (this->recommond_hot() != 0) {
    total_size += 1 + 1;
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ServerProfile::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:pb_base.ServerProfile)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const ServerProfile* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const ServerProfile>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:pb_base.ServerProfile)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:pb_base.ServerProfile)
    MergeFrom(*source);
  }
}

void ServerProfile::MergeFrom(const ServerProfile& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pb_base.ServerProfile)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.server_uid() != 0) {
    set_server_uid(from.server_uid());
  }
  if (from.region_showindex() != 0) {
    set_region_showindex(from.region_showindex());
  }
  if (from.region_name().size() > 0) {

    region_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.region_name_);
  }
  if (from.server_showindex() != 0) {
    set_server_showindex(from.server_showindex());
  }
  if (from.server_name().size() > 0) {

    server_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.server_name_);
  }
  if (from.server_status() != 0) {
    set_server_status(from.server_status());
  }
  if (from.recommond_new() != 0) {
    set_recommond_new(from.recommond_new());
  }
  if (from.recommond_hot() != 0) {
    set_recommond_hot(from.recommond_hot());
  }
}

void ServerProfile::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:pb_base.ServerProfile)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ServerProfile::CopyFrom(const ServerProfile& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pb_base.ServerProfile)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ServerProfile::IsInitialized() const {

  return true;
}

void ServerProfile::Swap(ServerProfile* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ServerProfile::InternalSwap(ServerProfile* other) {
  std::swap(server_uid_, other->server_uid_);
  std::swap(region_showindex_, other->region_showindex_);
  region_name_.Swap(&other->region_name_);
  std::swap(server_showindex_, other->server_showindex_);
  server_name_.Swap(&other->server_name_);
  std::swap(server_status_, other->server_status_);
  std::swap(recommond_new_, other->recommond_new_);
  std::swap(recommond_hot_, other->recommond_hot_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ServerProfile::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ServerProfile_descriptor_;
  metadata.reflection = ServerProfile_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ServerProfile

// optional int32 server_uid = 1;
void ServerProfile::clear_server_uid() {
  server_uid_ = 0;
}
 ::google::protobuf::int32 ServerProfile::server_uid() const {
  // @@protoc_insertion_point(field_get:pb_base.ServerProfile.server_uid)
  return server_uid_;
}
 void ServerProfile::set_server_uid(::google::protobuf::int32 value) {
  
  server_uid_ = value;
  // @@protoc_insertion_point(field_set:pb_base.ServerProfile.server_uid)
}

// optional int32 region_showindex = 2;
void ServerProfile::clear_region_showindex() {
  region_showindex_ = 0;
}
 ::google::protobuf::int32 ServerProfile::region_showindex() const {
  // @@protoc_insertion_point(field_get:pb_base.ServerProfile.region_showindex)
  return region_showindex_;
}
 void ServerProfile::set_region_showindex(::google::protobuf::int32 value) {
  
  region_showindex_ = value;
  // @@protoc_insertion_point(field_set:pb_base.ServerProfile.region_showindex)
}

// optional string region_name = 3;
void ServerProfile::clear_region_name() {
  region_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& ServerProfile::region_name() const {
  // @@protoc_insertion_point(field_get:pb_base.ServerProfile.region_name)
  return region_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void ServerProfile::set_region_name(const ::std::string& value) {
  
  region_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:pb_base.ServerProfile.region_name)
}
 void ServerProfile::set_region_name(const char* value) {
  
  region_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:pb_base.ServerProfile.region_name)
}
 void ServerProfile::set_region_name(const char* value, size_t size) {
  
  region_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:pb_base.ServerProfile.region_name)
}
 ::std::string* ServerProfile::mutable_region_name() {
  
  // @@protoc_insertion_point(field_mutable:pb_base.ServerProfile.region_name)
  return region_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* ServerProfile::release_region_name() {
  // @@protoc_insertion_point(field_release:pb_base.ServerProfile.region_name)
  
  return region_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void ServerProfile::set_allocated_region_name(::std::string* region_name) {
  if (region_name != NULL) {
    
  } else {
    
  }
  region_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), region_name);
  // @@protoc_insertion_point(field_set_allocated:pb_base.ServerProfile.region_name)
}

// optional int32 server_showindex = 4;
void ServerProfile::clear_server_showindex() {
  server_showindex_ = 0;
}
 ::google::protobuf::int32 ServerProfile::server_showindex() const {
  // @@protoc_insertion_point(field_get:pb_base.ServerProfile.server_showindex)
  return server_showindex_;
}
 void ServerProfile::set_server_showindex(::google::protobuf::int32 value) {
  
  server_showindex_ = value;
  // @@protoc_insertion_point(field_set:pb_base.ServerProfile.server_showindex)
}

// optional string server_name = 5;
void ServerProfile::clear_server_name() {
  server_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& ServerProfile::server_name() const {
  // @@protoc_insertion_point(field_get:pb_base.ServerProfile.server_name)
  return server_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void ServerProfile::set_server_name(const ::std::string& value) {
  
  server_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:pb_base.ServerProfile.server_name)
}
 void ServerProfile::set_server_name(const char* value) {
  
  server_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:pb_base.ServerProfile.server_name)
}
 void ServerProfile::set_server_name(const char* value, size_t size) {
  
  server_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:pb_base.ServerProfile.server_name)
}
 ::std::string* ServerProfile::mutable_server_name() {
  
  // @@protoc_insertion_point(field_mutable:pb_base.ServerProfile.server_name)
  return server_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* ServerProfile::release_server_name() {
  // @@protoc_insertion_point(field_release:pb_base.ServerProfile.server_name)
  
  return server_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void ServerProfile::set_allocated_server_name(::std::string* server_name) {
  if (server_name != NULL) {
    
  } else {
    
  }
  server_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), server_name);
  // @@protoc_insertion_point(field_set_allocated:pb_base.ServerProfile.server_name)
}

// optional .pb_base.ServerStatus server_status = 6;
void ServerProfile::clear_server_status() {
  server_status_ = 0;
}
 ::pb_base::ServerStatus ServerProfile::server_status() const {
  // @@protoc_insertion_point(field_get:pb_base.ServerProfile.server_status)
  return static_cast< ::pb_base::ServerStatus >(server_status_);
}
 void ServerProfile::set_server_status(::pb_base::ServerStatus value) {
  
  server_status_ = value;
  // @@protoc_insertion_point(field_set:pb_base.ServerProfile.server_status)
}

// optional bool recommond_new = 7;
void ServerProfile::clear_recommond_new() {
  recommond_new_ = false;
}
 bool ServerProfile::recommond_new() const {
  // @@protoc_insertion_point(field_get:pb_base.ServerProfile.recommond_new)
  return recommond_new_;
}
 void ServerProfile::set_recommond_new(bool value) {
  
  recommond_new_ = value;
  // @@protoc_insertion_point(field_set:pb_base.ServerProfile.recommond_new)
}

// optional bool recommond_hot = 8;
void ServerProfile::clear_recommond_hot() {
  recommond_hot_ = false;
}
 bool ServerProfile::recommond_hot() const {
  // @@protoc_insertion_point(field_get:pb_base.ServerProfile.recommond_hot)
  return recommond_hot_;
}
 void ServerProfile::set_recommond_hot(bool value) {
  
  recommond_hot_ = value;
  // @@protoc_insertion_point(field_set:pb_base.ServerProfile.recommond_hot)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace pb_base

// @@protoc_insertion_point(global_scope)