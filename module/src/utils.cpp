#include "utils.hpp"

/**
 * @brief Convert from v8 to standard string.
 * @param v v8 string
 * @return standard string
 */
std::string toString(const v8::Local<v8::String> & v) {
  v8::String::Utf8Value value(v);
  return std::string(*value);
}

/**
 * @brief Get value from object with given key name.
 * @param {v8::Local<v8::Object>} o
 * @param {const std::string &} keyName
 * @throws std::runtime_error if key could not be recovered
 * @return v8::Local<v8::Value> value
 */
v8::Local<v8::Value> GetValue(const v8::Local<v8::Object> & o, const std::string & keyName) {

  Nan::MaybeLocal<v8::Value> uncheckedValue = Nan::Get(o, Nan::New(keyName).ToLocalChecked());

  if(uncheckedValue.IsEmpty())
    throw std::runtime_error(std::string("Could not get value for key ") + keyName);
  else
    return uncheckedValue.ToLocalChecked();
}


// We have to specialize for std::string, as To returns MaybeLocal, not Maybe as above.
template<>
std::string ToNative(const v8::Local<v8::Value> & val) {

  // V8 type conversion
  Nan::MaybeLocal<v8::String> uncheckedString = Nan::To<v8::String>(val);

  if(uncheckedString.IsEmpty())
    throw std::runtime_error(std::string("Value not valid string"));
  else
    return toString(uncheckedString.ToLocalChecked());
}
