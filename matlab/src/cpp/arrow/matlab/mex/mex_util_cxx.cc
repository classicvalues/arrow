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

using namespace ::matlab::data;

// No longer used, replaced by ::matlab::engine::convertUTF16StringToUTF8String
// std::string MDAString_to_utf8(const ::matlab::data::String input) {
//   const std::string utf8_string_input = ::std::wstring_convert<
//         std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(input);
//   return utf8_string_input;
// }

/* Helper function to print a stream to the MATLAB command prompt. */
void displayInMATLAB(std::ostringstream& stream, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr) {
    // Factory to create MATLAB data arrays
    ::matlab::data::ArrayFactory factory;

    // Pass stream content to MATLAB fprintf function
    matlabPtr->feval(u"fprintf", 0,
        std::vector<Array>({ factory.createScalar(stream.str()) }));
    // Clear stream buffer
    stream.str("");
}


/* Helper function to print a stream to the MATLAB command prompt. */
void errorInMATLAB(std::string errorID, std::ostringstream& stream, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr) {
    // std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr = getEngine();
    // Factory to create MATLAB data arrays
    ::matlab::data::ArrayFactory factory;

    // Pass stream content to MATLAB error function
        matlabPtr->feval(u"error",
            0,
            std::vector<::matlab::data::Array>({ factory.createScalar(errorID), 
                                                 factory.createScalar(stream.str()) }));
    // Clear stream buffer
    stream.str("");
}

void checkArguments(::matlab::mex::ArgumentList outputs, ::matlab::mex::ArgumentList inputs, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr) {
    // Check the number of arguments passed to this mex function
    if (inputs.size() < 1)
    {
      std::ostringstream stream;
      stream << "'arrow.cpp.call' requires at least one input argument, which must be the name of the C++ function to call.";
      errorInMATLAB("MATLAB:arrow:NotEnoughInputs", stream, matlabPtr);
    }

    // Check first input argument
    if (inputs[0].getType() != ::matlab::data::ArrayType::MATLAB_STRING ||
        inputs[0].getNumberOfElements() != 1)
    {
      std::ostringstream stream;
      stream << "The first input argument to 'arrow.cpp.call' must be a scalar string.";
      errorInMATLAB("MATLAB:arrow:ScalarString", stream, matlabPtr);
    }
}

// mex_fcn_t lookup_function(const std::string& function_name, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr) {
//   auto kv_pair = FUNCTION_MAP.find(function_name);
//   if (kv_pair == FUNCTION_MAP.end()) {
//     // TODO: refactor into error helper function
//     // Factory to create MATLAB data arrays
//     ::matlab::data::ArrayFactory factory;
//     matlabPtr->feval(u"error",
//         0,
//         std::vector<Array>({ factory.createScalar("Unrecognized C++ function: " + function_name) }));
//   }
//   return kv_pair->second;
// }
    
} // namespace mex
} // namespace matlab
} // namespace arrow
