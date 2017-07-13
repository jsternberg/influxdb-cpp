#ifndef _INFLUXDB_WRITER_HPP
#define _INFLUXDB_WRITER_HPP

namespace influxdb {

class protocol;

class writer {
public:
  virtual writer& write(const char *s, size_t len) = 0;
  virtual const protocol& protocol() = 0;
};

}

#endif
