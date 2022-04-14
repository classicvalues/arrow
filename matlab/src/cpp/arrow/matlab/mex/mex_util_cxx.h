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

#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <codecvt>

#include "MatlabDataArray.hpp"
#include "mex.hpp"


// #include "mex_functions_cxx.h"
#include "arrow/matlab/api/visibility.h"

namespace arrow {
namespace matlab {
namespace mex {
    
ARROW_MATLAB_EXPORT std::string MDAString_to_utf8(const ::matlab::data::String input);

// ARROW_MATLAB_EXPORT void displayInMATLAB(std::ostringstream& stream, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr);

// ARROW_MATLAB_EXPORT void checkArguments(std::vector<::matlab::data::Array> outputs, std::vector<::matlab::data::Array> inputs, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr);

// ARROW_MATLAB_EXPORT mex_fcn_t lookup_function(const std::string& function_name, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr);
    
} // namespace mex
} // namespace matlab
} // namespace arrow
