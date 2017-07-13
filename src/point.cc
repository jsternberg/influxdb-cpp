#include "influxdb.hpp"

namespace influxdb {

class value {
public:
  virtual ~value() {}
  virtual void encode(std::ostream& os, const protocol &protocol) = 0;
  virtual value *clone() = 0;
};

template <typename T>
class value_impl : public value {
public:
  value_impl(const T &value) : value_(value) {}

  virtual void encode(std::ostream& os, const protocol &protocol) {
    protocol.encode_field(os, value_);
  }

  virtual value *clone() {
    return new value_impl<T>(value_);
  }

private:
  T value_;
};

field::field(const std::string& key, double value) :
  key_(key),
  value_(new value_impl<double>(value)) {}

field::field(const std::string& key, int64_t value) :
  key_(key),
  value_(new value_impl<int64_t>(value)) {}

field::field(const std::string& key, const std::string& value) :
  key_(key),
  value_(new value_impl<std::string>(value)) {}

field::field(const std::string& key, bool value) :
  key_(key),
  value_(new value_impl<bool>(value)) {}

field::field(const field& other) :
  key_(other.key_),
  value_(reinterpret_cast<value*>(other.value_)->clone()) {}

field::field(field&& other) noexcept :
  key_(std::move(other.key_)),
  value_(other.value_) {
  other.value_ = NULL;
}

field::~field() {
  value *v = reinterpret_cast<value*>(value_);
  delete v;
}

const std::string& field::key() const {
  return this->key_;
}

void field::encode(std::ostream& os, const protocol &protocol) const {
  value *v = reinterpret_cast<value*>(value_);
  v->encode(os, protocol);
}

}
