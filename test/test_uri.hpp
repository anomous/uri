// Copyright 2016 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt of copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEST_URI_INC
#define TEST_URI_INC

#include <iterator>
#include <network/uri.hpp>
#include "../src/detail/uri_parse.hpp"

namespace test {
struct uri {

  explicit uri(const std::string &uri)
    : uri_(uri), view(uri_) {
    it = std::begin(view);
    last = std::end(view);
  }

  bool parse_uri() {
    return network::parse_uri(it, last, parts);
  }

  std::string parsed_till() const {
    return std::string(std::begin(view), it);
  }

  bool has_scheme() const {
    return static_cast<bool>(parts.scheme);
  }

  std::string scheme() const {
    return (*parts.scheme).to_string();
  }

  bool has_user_info() const {
    return static_cast<bool>(parts.user_info);
  }

  std::string user_info() const {
    return (*parts.user_info).to_string();
  }

  bool has_host() const {
    return static_cast<bool>(parts.host);
  }

  std::string host() const {
    return (*parts.host).to_string();
  }

  bool has_port() const {
    return static_cast<bool>(parts.port);
  }

  std::string port() const {
    return (*parts.port).to_string();
  }

  bool has_path() const {
    return static_cast<bool>(parts.path);
  }

  std::string path() const {
    return (*parts.path).to_string();
  }

  bool has_query() const {
    return static_cast<bool>(parts.query);
  }

  std::string query() const {
    return (*parts.query).to_string();
  }

  bool has_fragment() const {
    return static_cast<bool>(parts.fragment);
  }

  std::string fragment() const {
    return (*parts.fragment).to_string();
  }

  std::string uri_;
  network::string_view view;
  network::string_view::const_iterator it, last;
  network::uri_parts parts;

};
}  // namespace test

#endif //  TEST_URI_INC
