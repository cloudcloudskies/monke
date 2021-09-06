// averysumner - monke
// pack.hh
// contains declarations for pack class
// Copyright 2021 averysumner
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org / licenses / LICENSE - 2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissionsand
// limitations under the License.

#ifndef MONKE_PACK_HH
#define MONKE_PACK_HH

#include <string_view>

namespace monke {

class Pack {
  public:
    static void unpack(std::string_view __input_path, std::string_view __output_path, std::string_view __password);
    static void pack(std::string_view __input_path, std::string_view __output_path, std::string_view __password);
};

} // namespace monke

#endif // MONKE_PACK_HH