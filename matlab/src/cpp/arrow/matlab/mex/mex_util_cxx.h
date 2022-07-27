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

// TODO: include a message about why these headers are necessary
//         Mention that including these headers will not be necessary in the future
//         Limitations 
//         Add a jira ticket that tracks this limitation and link to it
#include "cppmex/detail/mexErrorDispatch.hpp" // includes error APIs, used by mexApiAdapterImpl.hpp
#include "cppmex/detail/mexEngineUtilImpl.hpp"
#include "cppmex/detail/mexExceptionImpl.hpp"
#include "cppmex/detail/mexExceptionType.hpp"
#include "cppmex/detail/mexIOAdapterImpl.hpp" // includes arrayToImpl definition, which is required by mexApiAdapterImpl.hpp
// #include "cppmex/detail/mexFunctionAdapterImpl.hpp" // includes the mex gateway definition, cannot include this.
#include "cppmex/detail/mexApiAdapterImpl.hpp" // includes feval definition
#include "cppmex/detail/mexFutureImpl.hpp"
#include "cppmex/detail/mexTaskReferenceImpl.hpp"

namespace arrow {
namespace matlab {
namespace mex {
    
// ARROW_MATLAB_EXPORT std::string MDAString_to_utf8(const ::matlab::data::String input);

// Receive error that:
//     Undefined symbols for architecture x86_64:
//   "matlab::engine::MATLABEngine::feval(std::__1::basic_string<char16_t, std::__1::char_traits<char16_t>, std::__1::allocator<char16_t> > const&, int, std::__1::vector<matlab::data::Array, std::__1::allocator<matlab::data::Array> > const&, std::__1::shared_ptr<std::__1::basic_streambuf<char16_t, std::__1::char_traits<char16_t> > > const&, std::__1::shared_ptr<std::__1::basic_streambuf<char16_t, std::__1::char_traits<char16_t> > > const&)", referenced from:
//       arrow::matlab::mex::displayInMATLAB(std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char> >&, std::__1::shared_ptr<matlab::engine::MATLABEngine>) in mex_util_cxx.cc.o
// ld: symbol(s) not found for architecture x86_64
// Although it appears that 'matlab::engine::MATLABEngine::feval' should be included by 'mex.hpp'
ARROW_MATLAB_EXPORT void displayInMATLAB(std::ostringstream& stream, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr);

ARROW_MATLAB_EXPORT void errorInMATLAB(std::string errorID, std::ostringstream& stream, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr);

ARROW_MATLAB_EXPORT void checkArguments(::matlab::mex::ArgumentList outputs, ::matlab::mex::ArgumentList inputs, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr);

// ARROW_MATLAB_EXPORT mex_fcn_t lookup_function(const std::string& function_name, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr);
    
} // namespace mex
} // namespace matlab
} // namespace arrow
