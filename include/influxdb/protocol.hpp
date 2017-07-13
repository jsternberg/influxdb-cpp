#ifndef _INFLUXDB_PROTOCOL_HPP
#define _INFLUXDB_PROTOCOL_HPP

#include <ostream>
#include <sstream>

namespace influxdb {

class writer;
class point;

class protocol {
public:
  virtual ~protocol() {}

  virtual void encode(std::ostream& os, const point &pt) const = 0;

  virtual const char *content_type() const = 0;

  void encode(writer &writer, const point &pt) const;

  template <typename T>
    void encode(T &writer, const point &pt) const;

  virtual void encode_field(std::ostream& os, double value) const = 0;
  virtual void encode_field(std::ostream& os, int64_t value) const = 0;
  virtual void encode_field(std::ostream& os, const std::string& value) const = 0;
  virtual void encode_field(std::ostream& os, bool value) const = 0;

  class v1;
};

template <typename T>
void protocol::encode(T &writer, const point &pt) const {
  std::stringstream ss;
  this->encode(ss, pt);

  std::string s = ss.str();
  writer.write(s.c_str(), s.size());
}

class protocol::v1 : public protocol {
public:
  void encode(std::ostream &os, const point &pt) const;
  const char *content_type() const;

  void encode_field(std::ostream& os, double value) const;
  void encode_field(std::ostream& os, int64_t value) const;
  void encode_field(std::ostream& os, const std::string& value) const;
  void encode_field(std::ostream& os, bool value) const;
};

}

#endif
