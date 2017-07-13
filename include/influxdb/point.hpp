#ifndef _INFLUXDB_POINT_HPP
#define _INFLUXDB_POINT_HPP

#include <string>
#include <vector>

namespace influxdb {

class protocol;

struct tag {
  tag(const std::string& key, const std::string value) : key(key), value(value) {}

  std::string key;
  std::string value;
};

class field {
public:
  field(const std::string& key, double value);
  field(const std::string& key, int64_t value);
  field(const std::string& key, const std::string& value);
  field(const std::string& key, bool value);

  field(const field& other);
  field(field&& other) noexcept;

  ~field();

  const std::string& key() const;
  void encode(std::ostream& os, const protocol &protocol) const;

private:
  std::string key_;
  void *value_;
};

class point {
public:
  point(const std::string& name) : name(name) {}

  std::string name;
  std::vector<tag> tags;
  std::vector<field> fields;
};

}

#endif
