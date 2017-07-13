#ifndef _INFLUXDB_WRITER_HPP
#define _INFLUXDB_WRITER_HPP

namespace influxdb {

class protocol;

class writer {
public:
  writer() : protocol_(nullptr) {}
  writer(const protocol &protocol) : protocol_(&protocol) {}
  virtual ~writer() {}

  const protocol& protocol();

  virtual writer& write(const char *s, size_t len) = 0;

private:
  const influxdb::protocol *protocol_;
};

}

#endif
