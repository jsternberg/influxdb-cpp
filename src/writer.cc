#include "influxdb.hpp"

namespace influxdb {

static protocol::v1 default_protocol;

const protocol& writer::protocol() {
  if (protocol_) {
    return *protocol_;
  }
  return default_protocol;
}

}
