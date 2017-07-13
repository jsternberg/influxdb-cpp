#include "influxdb.hpp"
#include <string.h>
#include <string>
#include <curl/curl.h>

struct string_buffer {
  const char *buf;
  size_t len;
};

static size_t write_string_callback(char *buffer, size_t size, size_t nitems, void *in) {
  struct string_buffer *s = (struct string_buffer *) in;
  size_t towrite = size * nitems;
  if (towrite > s->len) {
    towrite = s->len;
  }
  memcpy(buffer, s->buf, towrite);
  s->buf += towrite;
  s->len -= towrite;
  return towrite;
}

namespace influxdb {

http_writer& http_writer::write(const char *s, size_t len) {
  CURL *handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL, "http://127.0.0.1:8086/write?db=db0");
  curl_easy_setopt(handle, CURLOPT_POST, 1L);

  const influxdb::protocol &p = this->protocol();
  std::string header = "Content-Type: ";
  header += p.content_type();

  struct curl_slist *headers = curl_slist_append(NULL, header.c_str());
  curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(handle, CURLOPT_READFUNCTION, write_string_callback);
  struct string_buffer buf = { s, len };
  curl_easy_setopt(handle, CURLOPT_READDATA, &buf);
  curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, len);

  //long http_code = 0;
  CURLcode res = curl_easy_perform(handle);
  if (res != CURLE_OK) {
    curl_slist_free_all(headers);
    curl_easy_cleanup(handle);
    // TODO(jsternberg): Throw an error or set a bit for an error.
    return *this;
  }

  //curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);
  curl_slist_free_all(headers);
  curl_easy_cleanup(handle);
  return *this;
}

}
