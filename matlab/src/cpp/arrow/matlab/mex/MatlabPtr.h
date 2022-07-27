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

#include <memory>
// #include <mutex>

#include "MatlabDataArray.hpp"
#include "mex.hpp"

// TODO: include a message about why these headers are necessary
//         Mention that including these headers will not be necessary in the future
//         Limitations 
//         Add a jira ticket that tracks this limitation and link to it
#include "cppmex/detail/mexErrorDispatch.hpp" // includes error APIs, used by mexApiAdapterImpl.hpp
// #include "cppmex/detail/mexEngineUtilImpl.hpp"
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

  class MatlabPtr {
  public:
    static bool initialized = false;
    MatlabPtr(std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr);
    static std::shared_ptr<::matlab::engine::MATLABEngine> GetMatlabPtr();
    ~MatlabPtr() = default;
  private:
    static std::shared_ptr<::matlab::engine::MATLABEngine> matlabPtr;
  };
}

} // namespace mex
} // namespace matlab
} // namespace arrow