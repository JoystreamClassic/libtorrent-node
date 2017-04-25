/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, February 12 2016
 */

#ifndef LIBTORRENT_NODE_UTILS_HPP
#define LIBTORRENT_NODE_UTILS_HPP

#include <nan.h>

#include <unordered_map>
#include <map>
#include <vector>

/**
* Guard, used in the context of a function call callback to a constructor function,
* in order to detect absence of javascript `new` operator. Absence leads to reinvocation
* of provided constructor. A macro is used in order to be able to return from callback.
*
* It is meant to mimic the effect of the following snippet in a javascript constructor function named `T`
*
* if(!(this instanceof T))
*   return new T(args);
*/

#define NEW_OPERATOR_GUARD(info, ctr) \
if(!info.IsConstructCall()) { \
  std::vector<v8::Local<v8::Value>> argv; \
  for(int i = 0;i < info.Length();i++) \
    argv.push_back(info[i]); \
  v8::Local<v8::Function> cons = Nan::New(ctr); \
  info.GetReturnValue().Set(cons->NewInstance(Nan::GetCurrentContext(), info.Length(), &argv[0]).ToLocalChecked()); \
  return; \
} \

#define NEW_OBJECT(cons, var) v8::Local<v8::Object> var = (((Nan::New(cons))->NewInstance(Nan::GetCurrentContext())).ToLocalChecked());

#define RETURN(var) info.GetReturnValue().Set(var);

#define RETURN_VOID RETURN(Nan::Undefined())

/**
 * Object setters.
 * @param {v8::Local<v8::Object>} o
 * @param {const char *| const std::string &} key name
 */

// @param {v8::Local<v8::Value>} val
#define SET_VAL(o, key, val)    (Nan::Set(o, Nan::New(key).ToLocalChecked(), val))

#define SET_UNDEFINED(o, key)   (SET_VAL(o, key, Nan::Undefined()))

#define SET_NULL(o, key) (SET_VAL(o, key, Nan::Null()))

// @param {int} val
// Based on v8::Local<v8::Int32> Nan::New<T>(int32_t value)
#define SET_INT32(o, key, val)    (SET_VAL(o, key, Nan::New(val)))

// @param {int} val
// Based on v8::Local<v8::Uint32> Nan::New<T>(uint32_t value)
#define SET_UINT32(o, key, val)   (SET_VAL(o, key, Nan::New(val)))

// @param {double} val
// Based on v8::Local<v8::Number> Nan::New<T>(double value)
#define SET_NUMBER(o, key, val) (SET_VAL(o, key, Nan::New(static_cast<double>(val))))

// @param {bool} val
// Based on v8::Local<v8::Boolean> Nan::New<T>(bool value);
#define SET_BOOL(o, key, val)   (SET_VAL(o, key, Nan::New(val)))

// @param {const char * | const std::string &} val
// Based on Nan::MaybeLocal<v8::String> Nan::New<T>(const char * value)
#define SET_CONST_CHAR(o, key, val)    (Nan::Set(o, Nan::New(key).ToLocalChecked(), Nan::New(val).ToLocalChecked()))
// @param {const char * | const std::string &} val
// Based on Nan::MaybeLocal<v8::String> Nan::New<T>(std::string const& value);
#define SET_STD_STRING(o, key, val)    (Nan::Set(o, Nan::New(key).ToLocalChecked(), Nan::New(val).ToLocalChecked()))

/**
 * @brief Convert from v8 to standard string.
 * @param v v8 string
 * @return standard string
 */
std::string toString(const v8::Local<v8::String> & v);

/**
 * @brief Get value from object with given key name.
 * @param {v8::Local<v8::Object>} o
 * @param {const std::string &} keyName
 * @throws std::runtime_error if key could not be recovered
 * @return v8::Local<v8::Value> value
 */
v8::Local<v8::Value> GetValue(const v8::Local<v8::Object> & o, const std::string & keyName);

/**
 * @brief Convert value to given native type instance
 */
template<class T>
T ToNative(const v8::Local<v8::Value> & val) {

  // // Native types conversions
  // https://github.com/nodejs/nan/blob/master/doc/converters.md#api_nan_to
  // Nan::Maybe<bool> Nan::To<bool>(v8::Local<v8::Value> val);
  // Nan::Maybe<double> Nan::To<double>(v8::Local<v8::Value> val);
  // Nan::Maybe<int32_t> Nan::To<int32_t>(v8::Local<v8::Value> val);
  // Nan::Maybe<int64_t> Nan::To<int64_t>(v8::Local<v8::Value> val);
  // Nan::Maybe<uint32_t> Nan::To<uint32_t>(v8::Local<v8::Value> val);

  Nan::Maybe<T> maybeT = Nan::To<T>(val);

  if(!maybeT.IsJust())
    throw std::runtime_error("conversion to desired type failed");
  else
    return maybeT.FromJust();
}

// We have to specialize for std::string, as To returns MaybeLocal, not Maybe as above.
template<>
std::string ToNative(const v8::Local<v8::Value> & val);

/**
 * @briaf Convert value to given v8 type instance, or throw.
 */
template<class T>
v8::Local<T> ToV8(const v8::Local<v8::Value> val) {

  // // V8 types
  // Nan::MaybeLocal<v8::Boolean> Nan::To<v8::Boolean>(v8::Local<v8::Value> val);
  // Nan::MaybeLocal<v8::Int32> Nan::To<v8::Int32>(v8::Local<v8::Value> val);
  // Nan::MaybeLocal<v8::Integer> Nan::To<v8::Integer>(v8::Local<v8::Value> val);
  // Nan::MaybeLocal<v8::Object> Nan::To<v8::Object>(v8::Local<v8::Value> val);
  // Nan::MaybeLocal<v8::Number> Nan::To<v8::Number>(v8::Local<v8::Value> val);
  // Nan::MaybeLocal<v8::String> Nan::To<v8::String>(v8::Local<v8::Value> val);
  // Nan::MaybeLocal<v8::Uint32> Nan::To<v8::Uint32>(v8::Local<v8::Value> val);

  Nan::MaybeLocal<T> maybeLocal = Nan::To<T>(val);

  if(maybeLocal.IsEmpty())
    throw std::runtime_error("conversion to desired type failed");
  else
    return maybeLocal.ToLocalChecked();
}

namespace std_lib_utils {

  /// Implementations are in bottom of file for readability

  /// Decoders

  template<class T>
  using DecoderFunction = T(*)(const v8::Local<v8::Value> & v);

  template<class K, class V>
  std::unordered_map<K, V> decode(const v8::Local<v8::Value> & v,
                                  const DecoderFunction<K> & keyDecoder,
                                  const DecoderFunction<V> & valueDecoder);

  /// Encoders

  template<class T>
  using EncoderFunction = v8::Local<v8::Value>(*)(const T &);

  // Switch to v8::Map in return type when Nan is updated, and node 7.4.0 is more common
  template <class K, class V>
  v8::Local<v8::Object> encode(const std::map<K,V> & map,
                               const EncoderFunction<K> & keyEncoder,
                               const EncoderFunction<V> & valueEncoder);

  // Switch to v8::Map in return type when Nan is updated, and node 7.4.0 is more common
  template <class K, class V>
  v8::Local<v8::Object> encode(const std::unordered_map<K,V> & map,
                               const EncoderFunction<K> & keyEncoder,
                               const EncoderFunction<V> & valueEncoder);

  template <class V>
  v8::Local<v8::Array> encode(const std::vector<V> & v,
                              const EncoderFunction<V> & elementEncoder);

}

/**
 * Verify if key is not undefined
 * @param {v8::Local<v8::Object>} o
 * @param {const std::string &} key name
 */
#define HAS_KEY(o, key)                                                      \
  (Nan::Has(o, Nan::New(key).ToLocalChecked()) == Nan::Just(true))


/**
 * Object getters.
 * @param {v8::Local<v8::Object>} o
 * @param {const std::string &} key name
 */

// @return {v8::Local<v8::Value>}
#define GET_VAL(o, key)           (GetValue(o, key))

// @return {int32_t}
#define GET_INT32(o, key)         (ToNative<int32_t>(GET_VAL(o, key)))

// @return {uint32_t}
#define GET_UINT32(o, key)        (ToNative<uint32_t>(GET_VAL(o, key)))

// @return {int64_t}
#define GET_INT64(o, key)         (ToNative<int64_t>(GET_VAL(o, key)))

// @return {double}
#define GET_DOUBLE(o, key)        (ToNative<double>(GET_VAL(o, key)))

// @return {bool}
#define GET_BOOL(o, key)          (ToNative<bool>(GET_VAL(o, key)))

// @return {std::string}
#define GET_STD_STRING(o, key)    (ToNative<std::string>(GET_VAL(o, key)))

// @return {char*}
#define GET_BUFFER_BEGIN(o, key)  (::node::Buffer::Data(GET_VAL(o, key)))

// @return {char*}
#define GET_BUFFER_END(o, key)    (GET_BUFFER_BEGIN(o, key) + ::node::Buffer::Length(GET_VAL(o, key)))

///////////////////////////////////////////////////////////////////////////////
/// Utility macros from @fanatid in macro.hpp@a4901b
///////////////////////////////////////////////////////////////////////////////

#define REQUIRE_ARGUMENTS(n)                                                  \
  if (info.Length() < (n)) {                                                  \
    return Nan::ThrowTypeError("Expected " #n "arguments");                   \
  }

#define ARGUMENTS_OPTIONAL_OBJECT(i, var, defaultValue)                       \
  v8::Local<v8::Object> var;                                                  \
  if (info.Length() > i && !info[i]->IsUndefined()) {                         \
    if (!info[i]->IsObject()) {                                               \
      return Nan::ThrowTypeError("Argument " #i " must be a Object");         \
    }                                                                         \
    var = info[i]->ToObject();                                                \
  } else {                                                                    \
    var = (defaultValue);                                                     \
  }

#define ARGUMENTS_IS_NUMBER(i)                                                \
  (info.Length() > (i) && info[i]->IsNumber())

#define ARGUMENTS_REQUIRE_NUMBER(i, var)                                      \
  if (!ARGUMENTS_IS_NUMBER(i)) {                                              \
    return Nan::ThrowTypeError("Argument " #i " must be a Number");           \
  }                                                                           \
  int64_t var = info[i]->IntegerValue();

#define ARGUMENTS_IS_BOOLEAN(i)                                               \
  (info.Length() > (i) && info[i]->IsBoolean())

#define ARGUMENTS_REQUIRE_BOOLEAN(i, var)                                     \
  if (!ARGUMENTS_IS_BOOLEAN(i)) {                                             \
    return Nan::ThrowTypeError("Argument " #i " must be a Boolean");          \
  }                                                                           \
  bool var = info[i]->BooleanValue();

#define ARGUMENTS_IS_STRING(i)                                                \
  (info.Length() > (i) && info[i]->IsString())

#define ARGUMENTS_REQUIRE_STRING(i, var)                                      \
  if (!ARGUMENTS_IS_STRING(i)) {                                              \
    return Nan::ThrowTypeError("Argument " #i " must be a String");           \
  }                                                                           \
  Nan::Utf8String var(info[i]);

#define ARGUMENTS_IS_FUNCTION(i)                                              \
  (info.Length() > (i) && info[i]->IsFunction())

#define ARGUMENTS_REQUIRE_FUNCTION(i, var)                                    \
  if (!ARGUMENTS_IS_FUNCTION(i)) {                                            \
    return Nan::ThrowTypeError("Argument " #i " must be a Function");         \
  }                                                                           \
  v8::Local<v8::Function> var = v8::Local<v8::Function>::Cast(info[i]);

#define ARGUMENTS_IS_OBJECT(i)                                                \
  (info.Length() >= (i) && info[i]->IsObject())

#define ARGUMENTS_IS_BUFFER(i)                                                \
  (info.Length() >= (i) && node::Buffer::HasInstance(info[i]))

///////////////////////////////////

#define ARGUMENTS_IS(i) (info.Length() > (i))

// Requires that class has public:
// static Nan::Persistent<v8::Function> constructor
#define ARGUMENTS_IS_DIRECT_INSTANCE(i, cls)                                  \
  (ARGUMENTS_IS_OBJECT(i) && (cls::constructor == (info[i]->ToObject()).GetPrototype()))

#define ARGUMENTS_REQUIRE_DIRECT_INSTANCE(i, cls, var)                        \
  if (!ARGUMENTS_IS_DIRECT_INSTANCE(i, cls)) {                                \
    return Nan::ThrowTypeError("Argument " #i " must be a " #cls);            \
  }                                                                           \
  cls* var = Nan::ObjectWrap::Unwrap<cls>(info[i]->ToObject());

#define EXPLOSIVE_ARGUMENT_REQUIRE_WRAPS(i, type, var)                        \
if (!ARGUMENTS_IS_OBJECT(i)) {                                                \
  return Nan::ThrowTypeError("Argument " #i " must be an Object");            \
}                                                                             \
type * var = Nan::ObjectWrap::Unwrap<type>(info[i]->ToObject());

// Tries to decode the ith argument (info[i]) using decoder (decoder) of given
// type (type). Requires that type also has default constructor
// Throws javascript exception if it fails
#define ARGUMENTS_REQUIRE_DECODED(i, var, type, decoder)                        \
  if (!ARGUMENTS_IS(i)) {                                                       \
    return Nan::ThrowTypeError("Argument " #i " of type " #type " is missing"); \
  }                                                                             \
  type var;                                                                     \
  try {                                                                         \
    var = decoder(info[i]);                                                     \
  } catch(const std::runtime_error & e) {                                       \
    v8::Local<v8::String> v8ErrorMessage = (Nan::New(std::string("Argument " #i " could not be decoded with " #decoder " into " #type " : ") + e.what())).ToLocalChecked(); \
    return Nan::ThrowTypeError(v8ErrorMessage); \
  }


///////////////// templated function implementations

namespace std_lib_utils {

  /// Implementations are in bottom of file for clarity

  /// Decoders

  template<class Key, class Value>
  std::unordered_map<Key, Value> decode(const v8::Local<v8::Value> & v,
                                        const DecoderFunction<Key> & keyDecoder,
                                        const DecoderFunction<Value> & valueDecoder) {
    /// Recover map
    if(!v->IsMap())
      throw std::runtime_error("argument must be a map");

    const v8::Map * const raw_map = v8::Map::Cast(*v);

    /// Recover array, so that we can iterate pairs

    // ::AsArray returns an array of length Size() * 2, where index N is the Nth key and index N + 1 is the Nth value.
    v8::Local<v8::Array> array_encoded_map = raw_map->AsArray();

    std::unordered_map<Key, Value> result;
    for(uint32_t i = 0;i < array_encoded_map->Length(); i += 2) {

      // Decode key
      Key key = keyDecoder(Nan::Get(array_encoded_map, i).ToLocalChecked());

      // Check that key is not already present in map
      if(result.count(key))
        throw std::runtime_error("duplicate keys in map");

      // Decode value
      Value value = valueDecoder(Nan::Get(array_encoded_map, i + 1).ToLocalChecked());

      // Insert pair in mapping
      result.insert(std::make_pair(key, value));
    }

    return result;
  }

  /// Encoders

  template <class K, class V>
  v8::Local<v8::Object> encode(const std::map<K, V> & map,
                               const EncoderFunction<K> & keyEncoder,
                               const EncoderFunction<V> & valueEncoder) {
    return Nan::New<v8::Object>();
  }

  template <class K, class V>
  v8::Local<v8::Object> encode(const std::unordered_map<K, V> & map,
                               const EncoderFunction<K> & keyEncoder,
                               const EncoderFunction<V> & valueEncoder) {
    return Nan::New<v8::Object>();
  }

  template <class V>
  v8::Local<v8::Array> encode(const std::vector<V> & v,
                              const EncoderFunction<V> & elementEncoder) {

    v8::Local<v8::Array> array = Nan::New<v8::Array>();

    for(auto item : v)
      Nan::Set(array, array->Length(), elementEncoder(v));

    return array;
  }

}


#endif // LIBTORRENT_NODE_UTILS_HPP
