// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "mex_util_cxx.h"

namespace arrow {
namespace matlab {
namespace mex {

std::string MDAString_to_utf8(const ::matlab::data::String input) {
  const std::string utf8_string_input = ::std::wstring_convert<
        std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(input);
  return utf8_string_input;
}


// mex_fcn_t lookup_function(const std::string& function_name) {
//   auto kv_pair = FUNCTION_MAP.find(function_name);
//   if (kv_pair == FUNCTION_MAP.end()) {
//     mexErrMsgIdAndTxt("MATLAB:arrow:UnknownCppFunction", "Unrecognized C++ function '%s'",
//                       function_name.c_str());
//   }
//   return kv_pair->second;
// }
    
} // namespace mex
} // namespace matlab
} // namespace arrow
