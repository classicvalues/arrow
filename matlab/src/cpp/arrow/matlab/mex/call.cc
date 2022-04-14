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
// #include <mex.h>
// #include "mex_util.h"
// void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
//   using namespace arrow::matlab::mex;
//   checkNumArgs(nrhs);
//   auto fcn = lookup_function(get_function_name(prhs[0]));
//   fcn(nlhs, plhs, nrhs - 1, ++prhs);
// }

// ----------- C++ mex implementation -----------
#include <string>
#include <algorithm>

// #include "mex.hpp"
#include "mexAdapter.hpp"

#include "mex_util_cxx.h"

using namespace matlab::data;

class MexFunction : public matlab::mex::Function {

private:
    // Pointer to MATLAB engine to call fprintf 
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr;

public:
    /* Constructor for the class. */
    MexFunction() {
      matlabPtr = getEngine();
    }

    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {

        // Validate input arguments
        checkArguments(outputs, inputs, matlabPtr);

        // Debugging: print to MATLAB by passing an ostringstream's contents to fprintf, via feval
        // Create an output stream
        std::ostringstream stream;

        stream << "Number of arguments: " << std::to_string(inputs.size()) << std::endl;

        for (const matlab::data::TypedArray<matlab::data::MATLABString> array : inputs) {
            if (array[0].has_value()) {
                const matlab::data::String string_input = String(array[0]);

                // Convert the UTF-16 string to UTF-8 before adding to stream
                // https://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16
                // matlab engine function to convert: https://codesearch.mathworks.com/fileView?searchText=mexEngineUtilImpl&searchField=filename&cluster=Bmain&template_id=1&relPath=matlab%2Fextern%2Finclude%2Fcppmex%2Fdetail%2F&filename=mexEngineUtilImpl.hpp&searchType=basicIndex
                std::string utf8_string_input = arrow::matlab::mex::MDAString_to_utf8(string_input);
                stream << "Argument: " << utf8_string_input << std::endl;
            }  
        }

        displayInMATLAB(stream, matlabPtr);

        // // Get function pointer based on inputs from MATLAB
        // auto array = inputs[0];
        // const matlab::data::String string_input = String(array[0]);
        // std::string utf8_string_input = arrow::matlab::mex::MDAString_to_utf8(string_input);
        // auto fcn = lookup_function(arrow::matlab::mex::MDAString_to_utf8(string_input), matlabPtr);

        // Get all inputs after the function name
        // std::vector<matlab::data::TypedArray<matlab::data::Array>> inputArgs(inputs.begin() + 1, inputs.end());
        
        // Call function with input and output argument lists
        // fcn(outputs, inputArgs)
    }

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

void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs, std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr) {
    // Check the number of arguments passed to this mex function
    if (inputs.size() < 1)
    {
        // TODO: refactor into error helper function
        // Factory to create MATLAB data arrays
        ::matlab::data::ArrayFactory factory;

        matlabPtr->feval(u"error",
            0,
            std::vector<Array>({ factory.createScalar("'arrow.cpp.call' requires at least one input argument, which must be the "
                    "name of the C++ function to call.") }));
    }

    // Check first input argument
    if (inputs[0].getType() != ArrayType::MATLAB_STRING ||
        inputs[0].getNumberOfElements() != 1)
    {
        // TODO: refactor into error helper function
        // Factory to create MATLAB data arrays
        ::matlab::data::ArrayFactory factory;
        matlabPtr->feval(u"error",
            0,
            std::vector<Array>({ factory.createScalar("The first input argument to 'arrow.cpp.call' must be a scalar string") }));
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
};


    // Print to MATLAB by passing matlab::data::StringArrays to join, then fprintf, via feval
    // const matlab::data::StringArray string_array_arg_1 = inputs[0];
    // if (string_array_arg_1[0].has_value()) {
    //     // const matlab::data::String function_name = String(string_array_arg_1[0]);
    //     matlab::data::StringArray printStringArray = factory.createArray<matlab::data::MATLABString>({ 1,3 }, 
    //             { matlab::data::MATLABString(u"Function name:"), 
    //               string_array_arg_1[0], 
    //               matlab::data::MATLABString(u"\n") });
    //     displayStringArrayInMATLAB(printStringArray);
    // }

    // void displayStringArrayInMATLAB(matlab::data::StringArray toPrint) {
    //     // https://uk.mathworks.com/help/matlab/matlab_external/displaying-output-in-matlab-command-window.html
    //     std::vector<matlab::data::Array> joinedString = matlabPtr->feval(u"join", 1,  std::vector<Array>({toPrint}));
    //     matlabPtr->feval(u"fprintf", 0,  joinedString);
    // }