#pragma once

// Include the actual MathWorks-authored MatlabDataArray.hpp header which defines the MDA APIs. #include "MatlabDataArray.hpp"
#include "mex.hpp"
 
namespace arrow {
    namespace matlab {
        namespace mex {
            using ArgumentList = ::matlab::mex::ArgumentList;
        }
    }
}