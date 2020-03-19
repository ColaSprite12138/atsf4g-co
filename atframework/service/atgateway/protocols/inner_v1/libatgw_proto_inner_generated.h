// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_LIBATGWPROTOINNER_ATFRAME_GW_INNER_V1_H_
#define FLATBUFFERS_GENERATED_LIBATGWPROTOINNER_ATFRAME_GW_INNER_V1_H_

#include "flatbuffers/flatbuffers.h"

namespace atframe {
namespace gw {
namespace inner {
namespace v1 {

struct cs_msg_head;

struct cs_body_post;

struct cs_body_kickoff;

struct cs_body_handshake;

struct cs_body_ping;

struct cs_msg;

enum error_code_t {
  error_code_t_EN_ECT_REFUSE_RECONNECT = -1005,
  error_code_t_EN_ECT_SESSION_EXPIRED = -1004,
  error_code_t_EN_ECT_BUSY = -1003,
  error_code_t_EN_ECT_HANDSHAKE = -1002,
  error_code_t_EN_ECT_FIRST_IDEL = -1001,
  error_code_t_EN_ECT_SUCCESS = 0,
  error_code_t_MIN = error_code_t_EN_ECT_REFUSE_RECONNECT,
  error_code_t_MAX = error_code_t_EN_ECT_SUCCESS
};

inline const error_code_t (&EnumValueserror_code_t())[6] {
  static const error_code_t values[] = {
    error_code_t_EN_ECT_REFUSE_RECONNECT,
    error_code_t_EN_ECT_SESSION_EXPIRED,
    error_code_t_EN_ECT_BUSY,
    error_code_t_EN_ECT_HANDSHAKE,
    error_code_t_EN_ECT_FIRST_IDEL,
    error_code_t_EN_ECT_SUCCESS
  };
  return values;
}

inline const char *EnumNameerror_code_t(error_code_t e) {
  switch (e) {
    case error_code_t_EN_ECT_REFUSE_RECONNECT: return "EN_ECT_REFUSE_RECONNECT";
    case error_code_t_EN_ECT_SESSION_EXPIRED: return "EN_ECT_SESSION_EXPIRED";
    case error_code_t_EN_ECT_BUSY: return "EN_ECT_BUSY";
    case error_code_t_EN_ECT_HANDSHAKE: return "EN_ECT_HANDSHAKE";
    case error_code_t_EN_ECT_FIRST_IDEL: return "EN_ECT_FIRST_IDEL";
    case error_code_t_EN_ECT_SUCCESS: return "EN_ECT_SUCCESS";
    default: return "";
  }
}

enum handshake_step_t {
  handshake_step_t_EN_HST_START_REQ = 0,
  handshake_step_t_EN_HST_START_RSP = 1,
  handshake_step_t_EN_HST_RECONNECT_REQ = 11,
  handshake_step_t_EN_HST_RECONNECT_RSP = 12,
  handshake_step_t_EN_HST_DH_PUBKEY_REQ = 21,
  handshake_step_t_EN_HST_DH_PUBKEY_RSP = 22,
  handshake_step_t_EN_HST_ECDH_PUBKEY_REQ = 31,
  handshake_step_t_EN_HST_ECDH_PUBKEY_RSP = 32,
  handshake_step_t_EN_HST_VERIFY = 101,
  handshake_step_t_MIN = handshake_step_t_EN_HST_START_REQ,
  handshake_step_t_MAX = handshake_step_t_EN_HST_VERIFY
};

inline const handshake_step_t (&EnumValueshandshake_step_t())[9] {
  static const handshake_step_t values[] = {
    handshake_step_t_EN_HST_START_REQ,
    handshake_step_t_EN_HST_START_RSP,
    handshake_step_t_EN_HST_RECONNECT_REQ,
    handshake_step_t_EN_HST_RECONNECT_RSP,
    handshake_step_t_EN_HST_DH_PUBKEY_REQ,
    handshake_step_t_EN_HST_DH_PUBKEY_RSP,
    handshake_step_t_EN_HST_ECDH_PUBKEY_REQ,
    handshake_step_t_EN_HST_ECDH_PUBKEY_RSP,
    handshake_step_t_EN_HST_VERIFY
  };
  return values;
}

inline const char *EnumNamehandshake_step_t(handshake_step_t e) {
  switch (e) {
    case handshake_step_t_EN_HST_START_REQ: return "EN_HST_START_REQ";
    case handshake_step_t_EN_HST_START_RSP: return "EN_HST_START_RSP";
    case handshake_step_t_EN_HST_RECONNECT_REQ: return "EN_HST_RECONNECT_REQ";
    case handshake_step_t_EN_HST_RECONNECT_RSP: return "EN_HST_RECONNECT_RSP";
    case handshake_step_t_EN_HST_DH_PUBKEY_REQ: return "EN_HST_DH_PUBKEY_REQ";
    case handshake_step_t_EN_HST_DH_PUBKEY_RSP: return "EN_HST_DH_PUBKEY_RSP";
    case handshake_step_t_EN_HST_ECDH_PUBKEY_REQ: return "EN_HST_ECDH_PUBKEY_REQ";
    case handshake_step_t_EN_HST_ECDH_PUBKEY_RSP: return "EN_HST_ECDH_PUBKEY_RSP";
    case handshake_step_t_EN_HST_VERIFY: return "EN_HST_VERIFY";
    default: return "";
  }
}

enum switch_secret_t {
  switch_secret_t_EN_SST_DIRECT = 0,
  switch_secret_t_EN_SST_DH = 1,
  switch_secret_t_EN_SST_ECDH = 2,
  switch_secret_t_MIN = switch_secret_t_EN_SST_DIRECT,
  switch_secret_t_MAX = switch_secret_t_EN_SST_ECDH
};

inline const switch_secret_t (&EnumValuesswitch_secret_t())[3] {
  static const switch_secret_t values[] = {
    switch_secret_t_EN_SST_DIRECT,
    switch_secret_t_EN_SST_DH,
    switch_secret_t_EN_SST_ECDH
  };
  return values;
}

inline const char * const *EnumNamesswitch_secret_t() {
  static const char * const names[] = {
    "EN_SST_DIRECT",
    "EN_SST_DH",
    "EN_SST_ECDH",
    nullptr
  };
  return names;
}

inline const char *EnumNameswitch_secret_t(switch_secret_t e) {
  if (e < switch_secret_t_EN_SST_DIRECT || e > switch_secret_t_EN_SST_ECDH) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesswitch_secret_t()[index];
}

enum cs_msg_type_t {
  cs_msg_type_t_EN_MTT_UNKNOWN = 0,
  cs_msg_type_t_EN_MTT_POST = 1,
  cs_msg_type_t_EN_MTT_HANDSHAKE = 2,
  cs_msg_type_t_EN_MTT_PING = 3,
  cs_msg_type_t_EN_MTT_PONG = 4,
  cs_msg_type_t_EN_MTT_KICKOFF = 5,
  cs_msg_type_t_EN_MTT_POST_KEY_SYN = 6,
  cs_msg_type_t_EN_MTT_POST_KEY_ACK = 7,
  cs_msg_type_t_MIN = cs_msg_type_t_EN_MTT_UNKNOWN,
  cs_msg_type_t_MAX = cs_msg_type_t_EN_MTT_POST_KEY_ACK
};

inline const cs_msg_type_t (&EnumValuescs_msg_type_t())[8] {
  static const cs_msg_type_t values[] = {
    cs_msg_type_t_EN_MTT_UNKNOWN,
    cs_msg_type_t_EN_MTT_POST,
    cs_msg_type_t_EN_MTT_HANDSHAKE,
    cs_msg_type_t_EN_MTT_PING,
    cs_msg_type_t_EN_MTT_PONG,
    cs_msg_type_t_EN_MTT_KICKOFF,
    cs_msg_type_t_EN_MTT_POST_KEY_SYN,
    cs_msg_type_t_EN_MTT_POST_KEY_ACK
  };
  return values;
}

inline const char * const *EnumNamescs_msg_type_t() {
  static const char * const names[] = {
    "EN_MTT_UNKNOWN",
    "EN_MTT_POST",
    "EN_MTT_HANDSHAKE",
    "EN_MTT_PING",
    "EN_MTT_PONG",
    "EN_MTT_KICKOFF",
    "EN_MTT_POST_KEY_SYN",
    "EN_MTT_POST_KEY_ACK",
    nullptr
  };
  return names;
}

inline const char *EnumNamecs_msg_type_t(cs_msg_type_t e) {
  if (e < cs_msg_type_t_EN_MTT_UNKNOWN || e > cs_msg_type_t_EN_MTT_POST_KEY_ACK) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamescs_msg_type_t()[index];
}

enum cs_msg_body {
  cs_msg_body_NONE = 0,
  cs_msg_body_cs_body_post = 1,
  cs_msg_body_cs_body_kickoff = 2,
  cs_msg_body_cs_body_ping = 3,
  cs_msg_body_cs_body_handshake = 4,
  cs_msg_body_MIN = cs_msg_body_NONE,
  cs_msg_body_MAX = cs_msg_body_cs_body_handshake
};

inline const cs_msg_body (&EnumValuescs_msg_body())[5] {
  static const cs_msg_body values[] = {
    cs_msg_body_NONE,
    cs_msg_body_cs_body_post,
    cs_msg_body_cs_body_kickoff,
    cs_msg_body_cs_body_ping,
    cs_msg_body_cs_body_handshake
  };
  return values;
}

inline const char * const *EnumNamescs_msg_body() {
  static const char * const names[] = {
    "NONE",
    "cs_body_post",
    "cs_body_kickoff",
    "cs_body_ping",
    "cs_body_handshake",
    nullptr
  };
  return names;
}

inline const char *EnumNamecs_msg_body(cs_msg_body e) {
  if (e < cs_msg_body_NONE || e > cs_msg_body_cs_body_handshake) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamescs_msg_body()[index];
}

template<typename T> struct cs_msg_bodyTraits {
  static const cs_msg_body enum_value = cs_msg_body_NONE;
};

template<> struct cs_msg_bodyTraits<cs_body_post> {
  static const cs_msg_body enum_value = cs_msg_body_cs_body_post;
};

template<> struct cs_msg_bodyTraits<cs_body_kickoff> {
  static const cs_msg_body enum_value = cs_msg_body_cs_body_kickoff;
};

template<> struct cs_msg_bodyTraits<cs_body_ping> {
  static const cs_msg_body enum_value = cs_msg_body_cs_body_ping;
};

template<> struct cs_msg_bodyTraits<cs_body_handshake> {
  static const cs_msg_body enum_value = cs_msg_body_cs_body_handshake;
};

bool Verifycs_msg_body(flatbuffers::Verifier &verifier, const void *obj, cs_msg_body type);
bool Verifycs_msg_bodyVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

struct cs_msg_head FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_SEQUENCE = 6
  };
  cs_msg_type_t type() const {
    return static_cast<cs_msg_type_t>(GetField<uint8_t>(VT_TYPE, 0));
  }
  bool mutate_type(cs_msg_type_t _type) {
    return SetField<uint8_t>(VT_TYPE, static_cast<uint8_t>(_type), 0);
  }
  uint64_t sequence() const {
    return GetField<uint64_t>(VT_SEQUENCE, 0);
  }
  bool mutate_sequence(uint64_t _sequence) {
    return SetField<uint64_t>(VT_SEQUENCE, _sequence, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_TYPE) &&
           VerifyField<uint64_t>(verifier, VT_SEQUENCE) &&
           verifier.EndTable();
  }
};

struct cs_msg_headBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(cs_msg_type_t type) {
    fbb_.AddElement<uint8_t>(cs_msg_head::VT_TYPE, static_cast<uint8_t>(type), 0);
  }
  void add_sequence(uint64_t sequence) {
    fbb_.AddElement<uint64_t>(cs_msg_head::VT_SEQUENCE, sequence, 0);
  }
  explicit cs_msg_headBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  cs_msg_headBuilder &operator=(const cs_msg_headBuilder &);
  flatbuffers::Offset<cs_msg_head> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<cs_msg_head>(end);
    return o;
  }
};

inline flatbuffers::Offset<cs_msg_head> Createcs_msg_head(
    flatbuffers::FlatBufferBuilder &_fbb,
    cs_msg_type_t type = cs_msg_type_t_EN_MTT_UNKNOWN,
    uint64_t sequence = 0) {
  cs_msg_headBuilder builder_(_fbb);
  builder_.add_sequence(sequence);
  builder_.add_type(type);
  return builder_.Finish();
}

struct cs_body_post FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_LENGTH = 4,
    VT_DATA = 6
  };
  /// the length before encrypt, because encrypt data will pad data.
  uint64_t length() const {
    return GetField<uint64_t>(VT_LENGTH, 0);
  }
  bool mutate_length(uint64_t _length) {
    return SetField<uint64_t>(VT_LENGTH, _length, 0);
  }
  const flatbuffers::Vector<int8_t> *data() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  flatbuffers::Vector<int8_t> *mutable_data() {
    return GetPointer<flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_LENGTH) &&
           VerifyOffset(verifier, VT_DATA) &&
           verifier.VerifyVector(data()) &&
           verifier.EndTable();
  }
};

struct cs_body_postBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_length(uint64_t length) {
    fbb_.AddElement<uint64_t>(cs_body_post::VT_LENGTH, length, 0);
  }
  void add_data(flatbuffers::Offset<flatbuffers::Vector<int8_t>> data) {
    fbb_.AddOffset(cs_body_post::VT_DATA, data);
  }
  explicit cs_body_postBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  cs_body_postBuilder &operator=(const cs_body_postBuilder &);
  flatbuffers::Offset<cs_body_post> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<cs_body_post>(end);
    return o;
  }
};

inline flatbuffers::Offset<cs_body_post> Createcs_body_post(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t length = 0,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> data = 0) {
  cs_body_postBuilder builder_(_fbb);
  builder_.add_length(length);
  builder_.add_data(data);
  return builder_.Finish();
}

inline flatbuffers::Offset<cs_body_post> Createcs_body_postDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t length = 0,
    const std::vector<int8_t> *data = nullptr) {
  auto data__ = data ? _fbb.CreateVector<int8_t>(*data) : 0;
  return atframe::gw::inner::v1::Createcs_body_post(
      _fbb,
      length,
      data__);
}

struct cs_body_kickoff FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_REASON = 4
  };
  int32_t reason() const {
    return GetField<int32_t>(VT_REASON, 0);
  }
  bool mutate_reason(int32_t _reason) {
    return SetField<int32_t>(VT_REASON, _reason, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_REASON) &&
           verifier.EndTable();
  }
};

struct cs_body_kickoffBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_reason(int32_t reason) {
    fbb_.AddElement<int32_t>(cs_body_kickoff::VT_REASON, reason, 0);
  }
  explicit cs_body_kickoffBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  cs_body_kickoffBuilder &operator=(const cs_body_kickoffBuilder &);
  flatbuffers::Offset<cs_body_kickoff> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<cs_body_kickoff>(end);
    return o;
  }
};

inline flatbuffers::Offset<cs_body_kickoff> Createcs_body_kickoff(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t reason = 0) {
  cs_body_kickoffBuilder builder_(_fbb);
  builder_.add_reason(reason);
  return builder_.Finish();
}

///
/// crypt_param is used for different purpose depends on step and switch_type, that's
///     step=EN_HST_START_RSP, switch_type=EN_SST_DIRECT                        : nothing
///     step=EN_HST_START_RSP, switch_type=EN_SST_DH                            : DH Parameters: P,G,GX (GX means G^X and pub_key in openssl). KeyExchangeData as in SSL3
///     step=EN_HST_DH_PUBKEY_REQ|EN_HST_ECDH_PUBKEY_REQ, switch_type=EN_SST_DH : DH public key of client
///     step=EN_HST_DH_PUBKEY_RSP|EN_HST_ECDH_PUBKEY_RSP, switch_type=EN_SST_DH : verify data prefix
///     step=EN_HST_START_RSP, switch_type=EN_SST_DIRECT                        : secret
///     step=EN_HST_VERIFY, switch_type=ANY                                     : verify data prefix + suffix
struct cs_body_handshake FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SESSION_ID = 4,
    VT_STEP = 6,
    VT_SWITCH_TYPE = 8,
    VT_CRYPT_TYPE = 10,
    VT_CRYPT_PARAM = 12,
    VT_SWITCH_PARAM = 14
  };
  uint64_t session_id() const {
    return GetField<uint64_t>(VT_SESSION_ID, 0);
  }
  bool mutate_session_id(uint64_t _session_id) {
    return SetField<uint64_t>(VT_SESSION_ID, _session_id, 0);
  }
  handshake_step_t step() const {
    return static_cast<handshake_step_t>(GetField<uint8_t>(VT_STEP, 0));
  }
  bool mutate_step(handshake_step_t _step) {
    return SetField<uint8_t>(VT_STEP, static_cast<uint8_t>(_step), 0);
  }
  switch_secret_t switch_type() const {
    return static_cast<switch_secret_t>(GetField<uint8_t>(VT_SWITCH_TYPE, 0));
  }
  bool mutate_switch_type(switch_secret_t _switch_type) {
    return SetField<uint8_t>(VT_SWITCH_TYPE, static_cast<uint8_t>(_switch_type), 0);
  }
  const flatbuffers::String *crypt_type() const {
    return GetPointer<const flatbuffers::String *>(VT_CRYPT_TYPE);
  }
  flatbuffers::String *mutable_crypt_type() {
    return GetPointer<flatbuffers::String *>(VT_CRYPT_TYPE);
  }
  const flatbuffers::Vector<int8_t> *crypt_param() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_CRYPT_PARAM);
  }
  flatbuffers::Vector<int8_t> *mutable_crypt_param() {
    return GetPointer<flatbuffers::Vector<int8_t> *>(VT_CRYPT_PARAM);
  }
  const flatbuffers::Vector<int8_t> *switch_param() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_SWITCH_PARAM);
  }
  flatbuffers::Vector<int8_t> *mutable_switch_param() {
    return GetPointer<flatbuffers::Vector<int8_t> *>(VT_SWITCH_PARAM);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_SESSION_ID) &&
           VerifyField<uint8_t>(verifier, VT_STEP) &&
           VerifyField<uint8_t>(verifier, VT_SWITCH_TYPE) &&
           VerifyOffset(verifier, VT_CRYPT_TYPE) &&
           verifier.VerifyString(crypt_type()) &&
           VerifyOffset(verifier, VT_CRYPT_PARAM) &&
           verifier.VerifyVector(crypt_param()) &&
           VerifyOffset(verifier, VT_SWITCH_PARAM) &&
           verifier.VerifyVector(switch_param()) &&
           verifier.EndTable();
  }
};

struct cs_body_handshakeBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_session_id(uint64_t session_id) {
    fbb_.AddElement<uint64_t>(cs_body_handshake::VT_SESSION_ID, session_id, 0);
  }
  void add_step(handshake_step_t step) {
    fbb_.AddElement<uint8_t>(cs_body_handshake::VT_STEP, static_cast<uint8_t>(step), 0);
  }
  void add_switch_type(switch_secret_t switch_type) {
    fbb_.AddElement<uint8_t>(cs_body_handshake::VT_SWITCH_TYPE, static_cast<uint8_t>(switch_type), 0);
  }
  void add_crypt_type(flatbuffers::Offset<flatbuffers::String> crypt_type) {
    fbb_.AddOffset(cs_body_handshake::VT_CRYPT_TYPE, crypt_type);
  }
  void add_crypt_param(flatbuffers::Offset<flatbuffers::Vector<int8_t>> crypt_param) {
    fbb_.AddOffset(cs_body_handshake::VT_CRYPT_PARAM, crypt_param);
  }
  void add_switch_param(flatbuffers::Offset<flatbuffers::Vector<int8_t>> switch_param) {
    fbb_.AddOffset(cs_body_handshake::VT_SWITCH_PARAM, switch_param);
  }
  explicit cs_body_handshakeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  cs_body_handshakeBuilder &operator=(const cs_body_handshakeBuilder &);
  flatbuffers::Offset<cs_body_handshake> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<cs_body_handshake>(end);
    return o;
  }
};

inline flatbuffers::Offset<cs_body_handshake> Createcs_body_handshake(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t session_id = 0,
    handshake_step_t step = handshake_step_t_EN_HST_START_REQ,
    switch_secret_t switch_type = switch_secret_t_EN_SST_DIRECT,
    flatbuffers::Offset<flatbuffers::String> crypt_type = 0,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> crypt_param = 0,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> switch_param = 0) {
  cs_body_handshakeBuilder builder_(_fbb);
  builder_.add_session_id(session_id);
  builder_.add_switch_param(switch_param);
  builder_.add_crypt_param(crypt_param);
  builder_.add_crypt_type(crypt_type);
  builder_.add_switch_type(switch_type);
  builder_.add_step(step);
  return builder_.Finish();
}

inline flatbuffers::Offset<cs_body_handshake> Createcs_body_handshakeDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t session_id = 0,
    handshake_step_t step = handshake_step_t_EN_HST_START_REQ,
    switch_secret_t switch_type = switch_secret_t_EN_SST_DIRECT,
    const char *crypt_type = nullptr,
    const std::vector<int8_t> *crypt_param = nullptr,
    const std::vector<int8_t> *switch_param = nullptr) {
  auto crypt_type__ = crypt_type ? _fbb.CreateString(crypt_type) : 0;
  auto crypt_param__ = crypt_param ? _fbb.CreateVector<int8_t>(*crypt_param) : 0;
  auto switch_param__ = switch_param ? _fbb.CreateVector<int8_t>(*switch_param) : 0;
  return atframe::gw::inner::v1::Createcs_body_handshake(
      _fbb,
      session_id,
      step,
      switch_type,
      crypt_type__,
      crypt_param__,
      switch_param__);
}

struct cs_body_ping FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TIMEPOINT = 4
  };
  /// the time when start ping
  int64_t timepoint() const {
    return GetField<int64_t>(VT_TIMEPOINT, 0);
  }
  bool mutate_timepoint(int64_t _timepoint) {
    return SetField<int64_t>(VT_TIMEPOINT, _timepoint, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int64_t>(verifier, VT_TIMEPOINT) &&
           verifier.EndTable();
  }
};

struct cs_body_pingBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_timepoint(int64_t timepoint) {
    fbb_.AddElement<int64_t>(cs_body_ping::VT_TIMEPOINT, timepoint, 0);
  }
  explicit cs_body_pingBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  cs_body_pingBuilder &operator=(const cs_body_pingBuilder &);
  flatbuffers::Offset<cs_body_ping> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<cs_body_ping>(end);
    return o;
  }
};

inline flatbuffers::Offset<cs_body_ping> Createcs_body_ping(
    flatbuffers::FlatBufferBuilder &_fbb,
    int64_t timepoint = 0) {
  cs_body_pingBuilder builder_(_fbb);
  builder_.add_timepoint(timepoint);
  return builder_.Finish();
}

/// message
struct cs_msg FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_HEAD = 4,
    VT_BODY_TYPE = 6,
    VT_BODY = 8
  };
  const cs_msg_head *head() const {
    return GetPointer<const cs_msg_head *>(VT_HEAD);
  }
  cs_msg_head *mutable_head() {
    return GetPointer<cs_msg_head *>(VT_HEAD);
  }
  cs_msg_body body_type() const {
    return static_cast<cs_msg_body>(GetField<uint8_t>(VT_BODY_TYPE, 0));
  }
  bool mutate_body_type(cs_msg_body _body_type) {
    return SetField<uint8_t>(VT_BODY_TYPE, static_cast<uint8_t>(_body_type), 0);
  }
  const void *body() const {
    return GetPointer<const void *>(VT_BODY);
  }
  template<typename T> const T *body_as() const;
  const cs_body_post *body_as_cs_body_post() const {
    return body_type() == cs_msg_body_cs_body_post ? static_cast<const cs_body_post *>(body()) : nullptr;
  }
  const cs_body_kickoff *body_as_cs_body_kickoff() const {
    return body_type() == cs_msg_body_cs_body_kickoff ? static_cast<const cs_body_kickoff *>(body()) : nullptr;
  }
  const cs_body_ping *body_as_cs_body_ping() const {
    return body_type() == cs_msg_body_cs_body_ping ? static_cast<const cs_body_ping *>(body()) : nullptr;
  }
  const cs_body_handshake *body_as_cs_body_handshake() const {
    return body_type() == cs_msg_body_cs_body_handshake ? static_cast<const cs_body_handshake *>(body()) : nullptr;
  }
  void *mutable_body() {
    return GetPointer<void *>(VT_BODY);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_HEAD) &&
           verifier.VerifyTable(head()) &&
           VerifyField<uint8_t>(verifier, VT_BODY_TYPE) &&
           VerifyOffset(verifier, VT_BODY) &&
           Verifycs_msg_body(verifier, body(), body_type()) &&
           verifier.EndTable();
  }
};

template<> inline const cs_body_post *cs_msg::body_as<cs_body_post>() const {
  return body_as_cs_body_post();
}

template<> inline const cs_body_kickoff *cs_msg::body_as<cs_body_kickoff>() const {
  return body_as_cs_body_kickoff();
}

template<> inline const cs_body_ping *cs_msg::body_as<cs_body_ping>() const {
  return body_as_cs_body_ping();
}

template<> inline const cs_body_handshake *cs_msg::body_as<cs_body_handshake>() const {
  return body_as_cs_body_handshake();
}

struct cs_msgBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_head(flatbuffers::Offset<cs_msg_head> head) {
    fbb_.AddOffset(cs_msg::VT_HEAD, head);
  }
  void add_body_type(cs_msg_body body_type) {
    fbb_.AddElement<uint8_t>(cs_msg::VT_BODY_TYPE, static_cast<uint8_t>(body_type), 0);
  }
  void add_body(flatbuffers::Offset<void> body) {
    fbb_.AddOffset(cs_msg::VT_BODY, body);
  }
  explicit cs_msgBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  cs_msgBuilder &operator=(const cs_msgBuilder &);
  flatbuffers::Offset<cs_msg> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<cs_msg>(end);
    return o;
  }
};

inline flatbuffers::Offset<cs_msg> Createcs_msg(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<cs_msg_head> head = 0,
    cs_msg_body body_type = cs_msg_body_NONE,
    flatbuffers::Offset<void> body = 0) {
  cs_msgBuilder builder_(_fbb);
  builder_.add_body(body);
  builder_.add_head(head);
  builder_.add_body_type(body_type);
  return builder_.Finish();
}

inline bool Verifycs_msg_body(flatbuffers::Verifier &verifier, const void *obj, cs_msg_body type) {
  switch (type) {
    case cs_msg_body_NONE: {
      return true;
    }
    case cs_msg_body_cs_body_post: {
      auto ptr = reinterpret_cast<const cs_body_post *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case cs_msg_body_cs_body_kickoff: {
      auto ptr = reinterpret_cast<const cs_body_kickoff *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case cs_msg_body_cs_body_ping: {
      auto ptr = reinterpret_cast<const cs_body_ping *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case cs_msg_body_cs_body_handshake: {
      auto ptr = reinterpret_cast<const cs_body_handshake *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return false;
  }
}

inline bool Verifycs_msg_bodyVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!Verifycs_msg_body(
        verifier,  values->Get(i), types->GetEnum<cs_msg_body>(i))) {
      return false;
    }
  }
  return true;
}

inline const atframe::gw::inner::v1::cs_msg *Getcs_msg(const void *buf) {
  return flatbuffers::GetRoot<atframe::gw::inner::v1::cs_msg>(buf);
}

inline const atframe::gw::inner::v1::cs_msg *GetSizePrefixedcs_msg(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<atframe::gw::inner::v1::cs_msg>(buf);
}

inline cs_msg *GetMutablecs_msg(void *buf) {
  return flatbuffers::GetMutableRoot<cs_msg>(buf);
}

inline const char *cs_msgIdentifier() {
  return "ATGW";
}

inline bool cs_msgBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, cs_msgIdentifier());
}

inline bool Verifycs_msgBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<atframe::gw::inner::v1::cs_msg>(cs_msgIdentifier());
}

inline bool VerifySizePrefixedcs_msgBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<atframe::gw::inner::v1::cs_msg>(cs_msgIdentifier());
}

inline const char *cs_msgExtension() {
  return "atgw";
}

inline void Finishcs_msgBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<atframe::gw::inner::v1::cs_msg> root) {
  fbb.Finish(root, cs_msgIdentifier());
}

inline void FinishSizePrefixedcs_msgBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<atframe::gw::inner::v1::cs_msg> root) {
  fbb.FinishSizePrefixed(root, cs_msgIdentifier());
}

}  // namespace v1
}  // namespace inner
}  // namespace gw
}  // namespace atframe

#endif  // FLATBUFFERS_GENERATED_LIBATGWPROTOINNER_ATFRAME_GW_INNER_V1_H_
