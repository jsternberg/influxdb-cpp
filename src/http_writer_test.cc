#include "catch.hpp"
#include "influxdb.hpp"

TEST_CASE( "write a point to the http service", "[http-writer]" ) {
  influxdb::client client;
  influxdb::http_writer writer(client);

  influxdb::point pt("cpu");
  pt.fields.push_back(influxdb::field("value", 2.0));
  pt.write_to(writer);
}
