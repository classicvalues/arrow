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

#include <string>
#include <functional>
#include <unordered_map>

#include "mex.hpp"
#include "MatlabDataArray.hpp"

#include "arrow/matlab/feather/feather_functions_cxx.h"

namespace arrow {
namespace matlab {
namespace mex {
    
using namespace arrow::matlab::feather;
using mex_fcn_signature = void(std::vector<::matlab::data::Array> outputs, std::vector<::matlab::data::Array> inputs);
using mex_fcn_t = std::function<mex_fcn_signature>;

static const std::unordered_map<std::string, mex_fcn_t> FUNCTION_MAP = {
};
    // {"featherread", featherread}, {"featherwrite", featherwrite}};

} // namespace mex
} // namespace matlab
} // namespace arrow