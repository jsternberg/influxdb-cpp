#include "influxdb.hpp"
#include <sstream>

namespace influxdb {

void protocol::v1::encode(std::ostream &os, const point &pt) const {
  std::stringstream ss;
  ss << pt.name;
  for (auto &tag : pt.tags) {
    ss << "," << tag.key << "=" << tag.value;
  }

  bool first = true;
  for (auto &f : pt.fields) {
    if (first) {
      ss << " ";
    } else {
      ss << ",";
    }
    ss << f.key() << "=";
    f.encode(ss, *this);
    first = false;
  }
  os << ss.str();
}

const char *protocol::v1::content_type() const {
  return "application/x-influxdb-line-protocol-v1";
}

void protocol::v1::encode_field(std::ostream& os, double value) const {
  auto flags = os.flags();
  auto precision = os.precision();
  os.setf(std::ios_base::fixed | std::ios_base::showpoint);
  os.precision(3);
  os << value;
  os.precision(precision);
  os.setf(flags);
}

void protocol::v1::encode_field(std::ostream& os, int64_t value) const {
}

void protocol::v1::encode_field(std::ostream& os, const std::string& value) const {
}

void protocol::v1::encode_field(std::ostream& os, bool value) const {
}

}
