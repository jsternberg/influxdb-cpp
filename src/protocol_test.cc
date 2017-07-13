#include "catch.hpp"

#include "influxdb.hpp"
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

TEST_CASE( "check the content type - line protocol v1", "[line-protocol]" ) {
  influxdb::protocol::v1 protocol;
  const char *content_type = protocol.content_type();
  REQUIRE( strcmp(content_type, "application/x-influxdb-line-protocol-v1") == 0 );
}

TEST_CASE( "write a point - line protocol v1", "[line-protocol]" ) {
  influxdb::protocol::v1 protocol;
  stringstream ss;

  influxdb::point pt("cpu");
  pt.tags.push_back(influxdb::tag("host", "server01"));
  pt.fields.push_back(influxdb::field("value", 2.0));
  protocol.encode(ss, pt);

  string exp = "cpu,host=server01 value=2.000";
  REQUIRE( exp == ss.str() );
}
