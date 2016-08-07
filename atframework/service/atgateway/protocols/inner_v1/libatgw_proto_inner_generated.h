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
struct cs_body_rsa_cert;
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

enum crypt_type_t {
  crypt_type_t_EN_ET_NONE = 0,
  crypt_type_t_EN_ET_XTEA = 1,
  crypt_type_t_EN_ET_AES = 2,
  crypt_type_t_MIN = crypt_type_t_EN_ET_NONE,
  crypt_type_t_MAX = crypt_type_t_EN_ET_AES
};

inline const char **EnumNamescrypt_type_t() {
  static const char *names[] = { "EN_ET_NONE", "EN_ET_XTEA", "EN_ET_AES", nullptr };
  return names;
}

inline const char *EnumNamecrypt_type_t(crypt_type_t e) { return EnumNamescrypt_type_t()[static_cast<int>(e)]; }

enum rsa_sign_t {
  rsa_sign_t_EN_RST_PKCS1 = 0,
  rsa_sign_t_EN_RST_PKCS1_V15 = 1,
  rsa_sign_t_EN_RST_PSS = 2,
  rsa_sign_t_MIN = rsa_sign_t_EN_RST_PKCS1,
  rsa_sign_t_MAX = rsa_sign_t_EN_RST_PSS
};

inline const char **EnumNamesrsa_sign_t() {
  static const char *names[] = { "EN_RST_PKCS1", "EN_RST_PKCS1_V15", "EN_RST_PSS", nullptr };
  return names;
}

inline const char *EnumNamersa_sign_t(rsa_sign_t e) { return EnumNamesrsa_sign_t()[static_cast<int>(e)]; }

enum hash_id_t {
  hash_id_t_EN_HIT_MD5 = 0,
  hash_id_t_EN_HIT_SHA1 = 1,
  hash_id_t_EN_HIT_SHA256 = 2,
  hash_id_t_EN_HIT_SHA512 = 3,
  hash_id_t_MIN = hash_id_t_EN_HIT_MD5,
  hash_id_t_MAX = hash_id_t_EN_HIT_SHA512
};

inline const char **EnumNameshash_id_t() {
  static const char *names[] = { "EN_HIT_MD5", "EN_HIT_SHA1", "EN_HIT_SHA256", "EN_HIT_SHA512", nullptr };
  return names;
}

inline const char *EnumNamehash_id_t(hash_id_t e) { return EnumNameshash_id_t()[static_cast<int>(e)]; }

enum handshake_step_t {
  handshake_step_t_EN_HST_START_REQ = 0,
  handshake_step_t_EN_HST_START_RSP = 1,
  handshake_step_t_EN_HST_RECONNECT_REQ = 2,
  handshake_step_t_EN_HST_RECONNECT_RSP = 3,
  handshake_step_t_EN_HST_DH_PUBKEY_REQ = 4,
  handshake_step_t_EN_HST_DH_PUBKEY_RSP = 5,
  handshake_step_t_EN_HST_RSA_SECRET_REQ = 6,
  handshake_step_t_EN_HST_RSA_SECRET_RSP = 7,
  handshake_step_t_EN_HST_VERIFY = 8,
  handshake_step_t_MIN = handshake_step_t_EN_HST_START_REQ,
  handshake_step_t_MAX = handshake_step_t_EN_HST_VERIFY
};

inline const char **EnumNameshandshake_step_t() {
  static const char *names[] = { "EN_HST_START_REQ", "EN_HST_START_RSP", "EN_HST_RECONNECT_REQ", "EN_HST_RECONNECT_RSP", "EN_HST_DH_PUBKEY_REQ", "EN_HST_DH_PUBKEY_RSP", "EN_HST_RSA_SECRET_REQ", "EN_HST_RSA_SECRET_RSP", "EN_HST_VERIFY", nullptr };
  return names;
}

inline const char *EnumNamehandshake_step_t(handshake_step_t e) { return EnumNameshandshake_step_t()[static_cast<int>(e)]; }

enum switch_secret_t {
  switch_secret_t_EN_SST_DIRECT = 0,
  switch_secret_t_EN_SST_DH = 1,
  switch_secret_t_EN_SST_RSA = 2,
  switch_secret_t_MIN = switch_secret_t_EN_SST_DIRECT,
  switch_secret_t_MAX = switch_secret_t_EN_SST_RSA
};

inline const char **EnumNamesswitch_secret_t() {
  static const char *names[] = { "EN_SST_DIRECT", "EN_SST_DH", "EN_SST_RSA", nullptr };
  return names;
}

inline const char *EnumNameswitch_secret_t(switch_secret_t e) { return EnumNamesswitch_secret_t()[static_cast<int>(e)]; }

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

inline const char **EnumNamescs_msg_type_t() {
  static const char *names[] = { "EN_MTT_UNKNOWN", "EN_MTT_POST", "EN_MTT_HANDSHAKE", "EN_MTT_PING", "EN_MTT_PONG", "EN_MTT_KICKOFF", "EN_MTT_POST_KEY_SYN", "EN_MTT_POST_KEY_ACK", nullptr };
  return names;
}

inline const char *EnumNamecs_msg_type_t(cs_msg_type_t e) { return EnumNamescs_msg_type_t()[static_cast<int>(e)]; }

enum cs_msg_body {
  cs_msg_body_NONE = 0,
  cs_msg_body_cs_body_post = 1,
  cs_msg_body_cs_body_kickoff = 2,
  cs_msg_body_cs_body_ping = 3,
  cs_msg_body_cs_body_handshake = 4,
  cs_msg_body_MIN = cs_msg_body_NONE,
  cs_msg_body_MAX = cs_msg_body_cs_body_handshake
};

inline const char **EnumNamescs_msg_body() {
  static const char *names[] = { "NONE", "cs_body_post", "cs_body_kickoff", "cs_body_ping", "cs_body_handshake", nullptr };
  return names;
}

inline const char *EnumNamecs_msg_body(cs_msg_body e) { return EnumNamescs_msg_body()[static_cast<int>(e)]; }

inline bool Verifycs_msg_body(flatbuffers::Verifier &verifier, const void *union_obj, cs_msg_body type);

struct cs_msg_head FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TYPE = 4,
    VT_SEQUENCE = 6
  };
  cs_msg_type_t type() const { return static_cast<cs_msg_type_t>(GetField<int8_t>(VT_TYPE, 0)); }
  uint64_t sequence() const { return GetField<uint64_t>(VT_SEQUENCE, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           VerifyField<uint64_t>(verifier, VT_SEQUENCE) &&
           verifier.EndTable();
  }
};

struct cs_msg_headBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(cs_msg_type_t type) { fbb_.AddElement<int8_t>(cs_msg_head::VT_TYPE, static_cast<int8_t>(type), 0); }
  void add_sequence(uint64_t sequence) { fbb_.AddElement<uint64_t>(cs_msg_head::VT_SEQUENCE, sequence, 0); }
  cs_msg_headBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  cs_msg_headBuilder &operator=(const cs_msg_headBuilder &);
  flatbuffers::Offset<cs_msg_head> Finish() {
    auto o = flatbuffers::Offset<cs_msg_head>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<cs_msg_head> Createcs_msg_head(flatbuffers::FlatBufferBuilder &_fbb,
   cs_msg_type_t type = cs_msg_type_t_EN_MTT_UNKNOWN,
   uint64_t sequence = 0) {
  cs_msg_headBuilder builder_(_fbb);
  builder_.add_sequence(sequence);
  builder_.add_type(type);
  return builder_.Finish();
}

struct cs_body_post FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_LENGTH = 4,
    VT_DATA = 6
  };
  /// the length before encrypt, because encrypt data will pad data.
  uint64_t length() const { return GetField<uint64_t>(VT_LENGTH, 0); }
  const flatbuffers::Vector<int8_t> *data() const { return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_DATA); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_LENGTH) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
           verifier.Verify(data()) &&
           verifier.EndTable();
  }
};

struct cs_body_postBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_length(uint64_t length) { fbb_.AddElement<uint64_t>(cs_body_post::VT_LENGTH, length, 0); }
  void add_data(flatbuffers::Offset<flatbuffers::Vector<int8_t>> data) { fbb_.AddOffset(cs_body_post::VT_DATA, data); }
  cs_body_postBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  cs_body_postBuilder &operator=(const cs_body_postBuilder &);
  flatbuffers::Offset<cs_body_post> Finish() {
    auto o = flatbuffers::Offset<cs_body_post>(fbb_.EndTable(start_, 2));
    return o;
  }
};

inline flatbuffers::Offset<cs_body_post> Createcs_body_post(flatbuffers::FlatBufferBuilder &_fbb,
   uint64_t length = 0,
   flatbuffers::Offset<flatbuffers::Vector<int8_t>> data = 0) {
  cs_body_postBuilder builder_(_fbb);
  builder_.add_length(length);
  builder_.add_data(data);
  return builder_.Finish();
}

struct cs_body_kickoff FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_REASON = 4
  };
  int32_t reason() const { return GetField<int32_t>(VT_REASON, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_REASON) &&
           verifier.EndTable();
  }
};

struct cs_body_kickoffBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_reason(int32_t reason) { fbb_.AddElement<int32_t>(cs_body_kickoff::VT_REASON, reason, 0); }
  cs_body_kickoffBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  cs_body_kickoffBuilder &operator=(const cs_body_kickoffBuilder &);
  flatbuffers::Offset<cs_body_kickoff> Finish() {
    auto o = flatbuffers::Offset<cs_body_kickoff>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<cs_body_kickoff> Createcs_body_kickoff(flatbuffers::FlatBufferBuilder &_fbb,
   int32_t reason = 0) {
  cs_body_kickoffBuilder builder_(_fbb);
  builder_.add_reason(reason);
  return builder_.Finish();
}

struct cs_body_rsa_cert FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_RSA_SIGN = 4,
    VT_HASH_TYPE = 6,
    VT_PUBKEY = 8
  };
  rsa_sign_t rsa_sign() const { return static_cast<rsa_sign_t>(GetField<int8_t>(VT_RSA_SIGN, 0)); }
  hash_id_t hash_type() const { return static_cast<hash_id_t>(GetField<int8_t>(VT_HASH_TYPE, 0)); }
  const flatbuffers::Vector<int8_t> *pubkey() const { return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_PUBKEY); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_RSA_SIGN) &&
           VerifyField<int8_t>(verifier, VT_HASH_TYPE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_PUBKEY) &&
           verifier.Verify(pubkey()) &&
           verifier.EndTable();
  }
};

struct cs_body_rsa_certBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_rsa_sign(rsa_sign_t rsa_sign) { fbb_.AddElement<int8_t>(cs_body_rsa_cert::VT_RSA_SIGN, static_cast<int8_t>(rsa_sign), 0); }
  void add_hash_type(hash_id_t hash_type) { fbb_.AddElement<int8_t>(cs_body_rsa_cert::VT_HASH_TYPE, static_cast<int8_t>(hash_type), 0); }
  void add_pubkey(flatbuffers::Offset<flatbuffers::Vector<int8_t>> pubkey) { fbb_.AddOffset(cs_body_rsa_cert::VT_PUBKEY, pubkey); }
  cs_body_rsa_certBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  cs_body_rsa_certBuilder &operator=(const cs_body_rsa_certBuilder &);
  flatbuffers::Offset<cs_body_rsa_cert> Finish() {
    auto o = flatbuffers::Offset<cs_body_rsa_cert>(fbb_.EndTable(start_, 3));
    return o;
  }
};

inline flatbuffers::Offset<cs_body_rsa_cert> Createcs_body_rsa_cert(flatbuffers::FlatBufferBuilder &_fbb,
   rsa_sign_t rsa_sign = rsa_sign_t_EN_RST_PKCS1,
   hash_id_t hash_type = hash_id_t_EN_HIT_MD5,
   flatbuffers::Offset<flatbuffers::Vector<int8_t>> pubkey = 0) {
  cs_body_rsa_certBuilder builder_(_fbb);
  builder_.add_pubkey(pubkey);
  builder_.add_hash_type(hash_type);
  builder_.add_rsa_sign(rsa_sign);
  return builder_.Finish();
}

///
/// crypt_param is used for different purpose depends on step and switch_type, that's
///     step=EN_HST_START_RSP, switch_type=EN_SST_DH : DH parameter
///     step=EN_HST_START_RSP, switch_type=EN_SST_DH : DH parameter
///     step=EN_HST_DH_PUBKEY_REQ, switch_type=EN_SST_DH : DH public key
///     step=EN_HST_DH_PUBKEY_RSP, switch_type=EN_SST_DH : nothing
///     step=EN_HST_START_RSP, switch_type=EN_SST_DIRECT: secret
///     step=EN_HST_START_RSP, switch_type=EN_SST_RSA: salt
///     step=EN_HST_RSA_SECRET_REQ, switch_type=EN_SST_RSA: encrypted secret
///     step=EN_HST_RSA_SECRET_RSP, switch_type=EN_SST_RSA: nothing
///     step=EN_HST_VERIFY, switch_type=ANY : any message just for test
struct cs_body_handshake FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_SESSION_ID = 4,
    VT_STEP = 6,
    VT_SWITCH_TYPE = 8,
    VT_CRYPT_TYPE = 10,
    VT_CRYPT_BITS = 12,
    VT_CRYPT_PARAM = 14,
    VT_RSA_CERT = 16
  };
  uint64_t session_id() const { return GetField<uint64_t>(VT_SESSION_ID, 0); }
  handshake_step_t step() const { return static_cast<handshake_step_t>(GetField<int8_t>(VT_STEP, 0)); }
  switch_secret_t switch_type() const { return static_cast<switch_secret_t>(GetField<int8_t>(VT_SWITCH_TYPE, 0)); }
  crypt_type_t crypt_type() const { return static_cast<crypt_type_t>(GetField<int8_t>(VT_CRYPT_TYPE, 0)); }
  uint32_t crypt_bits() const { return GetField<uint32_t>(VT_CRYPT_BITS, 0); }
  const flatbuffers::Vector<int8_t> *crypt_param() const { return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_CRYPT_PARAM); }
  const cs_body_rsa_cert *rsa_cert() const { return GetPointer<const cs_body_rsa_cert *>(VT_RSA_CERT); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_SESSION_ID) &&
           VerifyField<int8_t>(verifier, VT_STEP) &&
           VerifyField<int8_t>(verifier, VT_SWITCH_TYPE) &&
           VerifyField<int8_t>(verifier, VT_CRYPT_TYPE) &&
           VerifyField<uint32_t>(verifier, VT_CRYPT_BITS) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_CRYPT_PARAM) &&
           verifier.Verify(crypt_param()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_RSA_CERT) &&
           verifier.VerifyTable(rsa_cert()) &&
           verifier.EndTable();
  }
};

struct cs_body_handshakeBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_session_id(uint64_t session_id) { fbb_.AddElement<uint64_t>(cs_body_handshake::VT_SESSION_ID, session_id, 0); }
  void add_step(handshake_step_t step) { fbb_.AddElement<int8_t>(cs_body_handshake::VT_STEP, static_cast<int8_t>(step), 0); }
  void add_switch_type(switch_secret_t switch_type) { fbb_.AddElement<int8_t>(cs_body_handshake::VT_SWITCH_TYPE, static_cast<int8_t>(switch_type), 0); }
  void add_crypt_type(crypt_type_t crypt_type) { fbb_.AddElement<int8_t>(cs_body_handshake::VT_CRYPT_TYPE, static_cast<int8_t>(crypt_type), 0); }
  void add_crypt_bits(uint32_t crypt_bits) { fbb_.AddElement<uint32_t>(cs_body_handshake::VT_CRYPT_BITS, crypt_bits, 0); }
  void add_crypt_param(flatbuffers::Offset<flatbuffers::Vector<int8_t>> crypt_param) { fbb_.AddOffset(cs_body_handshake::VT_CRYPT_PARAM, crypt_param); }
  void add_rsa_cert(flatbuffers::Offset<cs_body_rsa_cert> rsa_cert) { fbb_.AddOffset(cs_body_handshake::VT_RSA_CERT, rsa_cert); }
  cs_body_handshakeBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  cs_body_handshakeBuilder &operator=(const cs_body_handshakeBuilder &);
  flatbuffers::Offset<cs_body_handshake> Finish() {
    auto o = flatbuffers::Offset<cs_body_handshake>(fbb_.EndTable(start_, 7));
    return o;
  }
};

inline flatbuffers::Offset<cs_body_handshake> Createcs_body_handshake(flatbuffers::FlatBufferBuilder &_fbb,
   uint64_t session_id = 0,
   handshake_step_t step = handshake_step_t_EN_HST_START_REQ,
   switch_secret_t switch_type = switch_secret_t_EN_SST_DIRECT,
   crypt_type_t crypt_type = crypt_type_t_EN_ET_NONE,
   uint32_t crypt_bits = 0,
   flatbuffers::Offset<flatbuffers::Vector<int8_t>> crypt_param = 0,
   flatbuffers::Offset<cs_body_rsa_cert> rsa_cert = 0) {
  cs_body_handshakeBuilder builder_(_fbb);
  builder_.add_session_id(session_id);
  builder_.add_rsa_cert(rsa_cert);
  builder_.add_crypt_param(crypt_param);
  builder_.add_crypt_bits(crypt_bits);
  builder_.add_crypt_type(crypt_type);
  builder_.add_switch_type(switch_type);
  builder_.add_step(step);
  return builder_.Finish();
}

struct cs_body_ping FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TIMEPOINT = 4
  };
  /// the time when start ping
  int64_t timepoint() const { return GetField<int64_t>(VT_TIMEPOINT, 0); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int64_t>(verifier, VT_TIMEPOINT) &&
           verifier.EndTable();
  }
};

struct cs_body_pingBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_timepoint(int64_t timepoint) { fbb_.AddElement<int64_t>(cs_body_ping::VT_TIMEPOINT, timepoint, 0); }
  cs_body_pingBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  cs_body_pingBuilder &operator=(const cs_body_pingBuilder &);
  flatbuffers::Offset<cs_body_ping> Finish() {
    auto o = flatbuffers::Offset<cs_body_ping>(fbb_.EndTable(start_, 1));
    return o;
  }
};

inline flatbuffers::Offset<cs_body_ping> Createcs_body_ping(flatbuffers::FlatBufferBuilder &_fbb,
   int64_t timepoint = 0) {
  cs_body_pingBuilder builder_(_fbb);
  builder_.add_timepoint(timepoint);
  return builder_.Finish();
}

/// message
struct cs_msg FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_HEAD = 4,
    VT_BODY_TYPE = 6,
    VT_BODY = 8
  };
  const cs_msg_head *head() const { return GetPointer<const cs_msg_head *>(VT_HEAD); }
  cs_msg_body body_type() const { return static_cast<cs_msg_body>(GetField<uint8_t>(VT_BODY_TYPE, 0)); }
  const void *body() const { return GetPointer<const void *>(VT_BODY); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_HEAD) &&
           verifier.VerifyTable(head()) &&
           VerifyField<uint8_t>(verifier, VT_BODY_TYPE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_BODY) &&
           Verifycs_msg_body(verifier, body(), body_type()) &&
           verifier.EndTable();
  }
};

struct cs_msgBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_head(flatbuffers::Offset<cs_msg_head> head) { fbb_.AddOffset(cs_msg::VT_HEAD, head); }
  void add_body_type(cs_msg_body body_type) { fbb_.AddElement<uint8_t>(cs_msg::VT_BODY_TYPE, static_cast<uint8_t>(body_type), 0); }
  void add_body(flatbuffers::Offset<void> body) { fbb_.AddOffset(cs_msg::VT_BODY, body); }
  cs_msgBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  cs_msgBuilder &operator=(const cs_msgBuilder &);
  flatbuffers::Offset<cs_msg> Finish() {
    auto o = flatbuffers::Offset<cs_msg>(fbb_.EndTable(start_, 3));
    return o;
  }
};

inline flatbuffers::Offset<cs_msg> Createcs_msg(flatbuffers::FlatBufferBuilder &_fbb,
   flatbuffers::Offset<cs_msg_head> head = 0,
   cs_msg_body body_type = cs_msg_body_NONE,
   flatbuffers::Offset<void> body = 0) {
  cs_msgBuilder builder_(_fbb);
  builder_.add_body(body);
  builder_.add_head(head);
  builder_.add_body_type(body_type);
  return builder_.Finish();
}

inline bool Verifycs_msg_body(flatbuffers::Verifier &verifier, const void *union_obj, cs_msg_body type) {
  switch (type) {
    case cs_msg_body_NONE: return true;
    case cs_msg_body_cs_body_post: return verifier.VerifyTable(reinterpret_cast<const cs_body_post *>(union_obj));
    case cs_msg_body_cs_body_kickoff: return verifier.VerifyTable(reinterpret_cast<const cs_body_kickoff *>(union_obj));
    case cs_msg_body_cs_body_ping: return verifier.VerifyTable(reinterpret_cast<const cs_body_ping *>(union_obj));
    case cs_msg_body_cs_body_handshake: return verifier.VerifyTable(reinterpret_cast<const cs_body_handshake *>(union_obj));
    default: return false;
  }
}

inline const atframe::gw::inner::v1::cs_msg *Getcs_msg(const void *buf) { return flatbuffers::GetRoot<atframe::gw::inner::v1::cs_msg>(buf); }

inline bool Verifycs_msgBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<atframe::gw::inner::v1::cs_msg>(); }

inline const char *cs_msgIdentifier() { return "ATGW"; }

inline bool cs_msgBufferHasIdentifier(const void *buf) { return flatbuffers::BufferHasIdentifier(buf, cs_msgIdentifier()); }

inline const char *cs_msgExtension() { return "atgw"; }

inline void Finishcs_msgBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<atframe::gw::inner::v1::cs_msg> root) { fbb.Finish(root, cs_msgIdentifier()); }

}  // namespace v1
}  // namespace inner
}  // namespace gw
}  // namespace atframe

#endif  // FLATBUFFERS_GENERATED_LIBATGWPROTOINNER_ATFRAME_GW_INNER_V1_H_
