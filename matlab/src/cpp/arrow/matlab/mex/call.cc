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
#include<string>
// #include<memory>

#include "mex.hpp"
#include "mexAdapter.hpp"
// TODO: Import after conversion
// #include "mex_util.h"
// TODO: Can use to simplify code, may make dependencies harder to understand
using namespace matlab::data;
using matlab::mex::ArgumentList;
class MexFunction : public matlab::mex::Function {
private:
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr;
public:
    /* Constructor for the class. */
    MexFunction() {
      matlabPtr = getEngine();
    }

    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
      // Print the function name
      const CharArray function_name = inputs[0];
      std::ostringstream stream;
      stream<< "Function name: " << function_name.toAscii() << std::endl;
      displayInMATLAB(std::move(stream));

      // // Get function pointer based on inputs from MATLAB
      // auto fcn = lookup_function(get_function_name(inputs[0]));
      // Get all inputs after the function name
      // std::vector<matlab::data::TypedArray<matlab::data::Array>> inputArgs(inputs.begin() + 1, inputs.end());
      // // Call function with input and output argument lists
      // fcn(outputs, inputArgs)
    }

    /* Helper function to print a stream to the MATLAB command prompt. */
    void displayInMATLAB(std::ostringstream stream) {
      // https://uk.mathworks.com/help/matlab/matlab_external/displaying-output-in-matlab-command-window.html
      ArrayFactory factory;
      matlabPtr->feval(u"fprintf", 0, std::vector<Array>
              ({ factory.createScalar(stream.str())}));
    }

    void checkArguments(ArgumentList outputs, ArgumentList inputs) {
        // Get pointer to engine
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();

        // Get array factory
        ArrayFactory factory;

        // Check first input argument
        if (inputs[0].getType() != ArrayType::CHAR ||
            inputs[0].getNumberOfElements() != 1)
        {
            matlabPtr->feval(u"error",
                0,
                std::vector<Array>({ factory.createScalar("First input must be scalar double") }));
        }

        // Check second input argument
        if (inputs[1].getType() != ArrayType::DOUBLE)
        {
            matlabPtr->feval(u"error",
                0,
                std::vector<Array>({ factory.createScalar("Input must be double array") }));
        }
        // Check number of outputs
        if (outputs.size() > 1) 
        {
            matlabPtr->feval(u"error",
                0,
                std::vector<Array>({ factory.createScalar("Only one output is returned") }));
        }
    }
};
