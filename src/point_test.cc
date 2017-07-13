#include "catch.hpp"
#include "influxdb.hpp"
#include <string>
#include <sstream>
using namespace std;

TEST_CASE( "write a point using an ostream", "[point]" ) {
  influxdb::point pt("cpu");
  pt.fields.push_back(influxdb::field("value", 2.0));

  stringstream ss;
  pt.write_to(ss);

  string exp = "cpu value=2.000";
  REQUIRE( exp == ss.str() );
}
