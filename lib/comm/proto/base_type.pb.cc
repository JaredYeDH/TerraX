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

namespace base_proto {

namespace {


}  // namespace


void protobuf_AssignDesc_base_5ftype_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_base_5ftype_2eproto() {
  protobuf_AddDesc_base_5ftype_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "base_type.proto");
  GOOGLE_CHECK(file != NULL);
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
}

}  // namespace

void protobuf_ShutdownFile_base_5ftype_2eproto() {
}

void protobuf_AddDesc_base_5ftype_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_base_5ftype_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017base_type.proto\022\nbase_protob\006proto3", 37);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "base_type.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_base_5ftype_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_base_5ftype_2eproto {
  StaticDescriptorInitializer_base_5ftype_2eproto() {
    protobuf_AddDesc_base_5ftype_2eproto();
  }
} static_descriptor_initializer_base_5ftype_2eproto_;

// @@protoc_insertion_point(namespace_scope)

}  // namespace base_proto

// @@protoc_insertion_point(global_scope)
