// Copyright atframework
// Created by owent on 2016/10/5.
//

#pragma once

#include <google/protobuf/message.h>

#include <libcopp/future/poller.h>

#include <inttypes.h>
#include <stdint.h>
#include <cstddef>
#include <vector>

extern "C" struct redisReply;

namespace rpc {
namespace db {

/**
 * @brief 数据库接口统一返回结构
 * @note 这里不使用原始int类型是为了位以后扩展更高级的设计模式做预留。（比武无栈协程）
 */
struct result_t {
  result_t();
  explicit result_t(int code);
  operator int() const noexcept;

  bool is_success() const noexcept;
  bool is_error() const noexcept;

  copp::future::poller<int> result;
};

/**
 * allocate a buffer in specify buffer block and align address to type Ty
 * @note it's useful in allocate args when using redis to store data and using reflect to pack message.
 *       because object's address must be align to type size on x86 or ARM architecture, such as size_t, uint32_t,
 * uint64_t and etc.
 * @param buf_addr input available buffer block, output left available address
 * @param buf_len input available buffer length, output left available length
 * @return allocated buffer address, nullptr if failed
 */
template <typename Ty>
void* align_alloc(void*& buf_addr, size_t& buf_len) {
  if (nullptr == buf_addr) {
    return nullptr;
  }

  uintptr_t align_sz = sizeof(Ty);
  uintptr_t in_addr = (uintptr_t)buf_addr;
  uintptr_t padding_offset = in_addr % align_sz;
  if (0 != padding_offset) {
    padding_offset = align_sz - padding_offset;
    in_addr += padding_offset;
  }

  // buffer not enough
  if (buf_len < padding_offset) {
    return nullptr;
  }

  buf_len -= padding_offset;
  buf_addr = (void*)(in_addr);
  return buf_addr;
}

class redis_args {
 public:
  redis_args(size_t argc);
  ~redis_args();

  char* alloc(size_t sz);
  void dealloc();
  bool empty() const;
  size_t size() const;

  /**
   * get start pointer of all arguments
   * @note although const char* const * is better,
   *       but hiredis use const char** as input argumeng type, so we also use it
   * @return
   */
  const char** get_args_values();
  const size_t* get_args_lengths() const;

  bool push(const char* str, size_t len = 0);
  bool push(const std::string& str);
  bool push(uint8_t);
  bool push(int8_t);
  bool push(uint16_t);
  bool push(int16_t);
  bool push(uint32_t);
  bool push(int32_t);
  bool push(uint64_t);
  bool push(int64_t);

 private:
  std::vector<const char*> segment_value_;
  std::vector<size_t> segment_length_;
  size_t used_;
  char* free_buffer_;
};

int unpack_message(::google::protobuf::Message& msg, const redisReply* reply, std::string* version);

/**
 * package message into redis args, each message field will take two segment in args
 * @param msg message
 * @param args where to store arguments
 * @param fds which fields will be packed
 * @param version version if need
 * @param debug_message debug message if need
 * @return 0 or error code
 */
int pack_message(const ::google::protobuf::Message& msg, redis_args& args,
                 std::vector<const ::google::protobuf::FieldDescriptor*> fds, std::string* version,
                 std::ostream* debug_message);
}  // namespace db
}  // namespace rpc
