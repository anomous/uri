// Copyright 2016 Glyn Matthews.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "uri_advance_parts.hpp"
#include <iterator>
#include <utility>
#include <limits>

namespace network {
namespace detail {
namespace {
template <class Iterator>
string_view copy_part(Iterator first, Iterator last,
                      string_view::const_iterator &it) {
  auto part_first = it;
  std::advance(it, std::distance(first, last));
  const char *ptr = &(*part_first);
  return string_view(ptr, it - part_first);
}
}  // namespace

string_view copy_part(const std::string &uri, string_view::const_iterator &it) {
  return copy_part(std::begin(uri), std::end(uri), it);
}

void advance_parts(string_view &uri_view, uri_parts &parts,
                   const uri_parts &existing_parts) {
  auto first = std::begin(uri_view);

  auto it = first;
  if (auto scheme = existing_parts.scheme) {
    parts.scheme = copy_part(std::begin(*scheme), std::end(*scheme), it);

    // ignore : for all URIs
    if (*it == ':') {
      ++it;
    }

    // ignore // for hierarchical URIs
    if (existing_parts.host) {
      while (*it == '/') {
        ++it;
      }
    }
  }

  if (auto user_info = existing_parts.user_info) {
    parts.user_info =
      copy_part(std::begin(*user_info), std::end(*user_info), it);
    ++it;  // ignore @
  }

  if (auto host = existing_parts.host) {
    parts.host = copy_part(std::begin(*host), std::end(*host), it);
  }

  if (auto port = existing_parts.port) {
    ++it;  // ignore :
    parts.port = copy_part(std::begin(*port), std::end(*port), it);
  }

  if (auto path = existing_parts.path) {
    parts.path = copy_part(std::begin(*path), std::end(*path), it);
  }

  if (auto query = existing_parts.query) {
    ++it;  // ignore ?
    parts.query = copy_part(std::begin(*query), std::end(*query), it);
  }

  if (auto fragment = existing_parts.fragment) {
    ++it;  // ignore #
    parts.fragment = copy_part(std::begin(*fragment), std::end(*fragment), it);
  }
}
}  // namespace detail
}  // namespace network
