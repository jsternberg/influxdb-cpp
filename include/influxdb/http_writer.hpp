#ifndef _INFLUXDB_HTTP_WRITER_HPP
#define _INFLUXDB_HTTP_WRITER_HPP

namespace influxdb {

class client;

class http_writer : public writer {
public:
  http_writer(const client& client) : client_(client) {}
  http_writer(const client& client, const influxdb::protocol &protocol) : writer(protocol), client_(client) {}
  virtual ~http_writer() {}

  http_writer& write(const char *s, size_t len);

private:
  const client& client_;
};

}

#endif
