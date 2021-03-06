/*
 * Copyright (c) 2021, WSO2 Inc. (http://www.wso2.org) All Rights Reserved.
 *
 * WSO2 Inc. licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef __BIRREADPACKAGE__H__
#define __BIRREADPACKAGE__H__

#include "bir/Package.h"
#include "interfaces/Parser.h"
#include "reader/ConstantPool.h"
#include <memory>

namespace nballerina {
class BIRReadPackage {
  private:
    static void readGlobalVar(Package &birPackage, Parser &reader, ConstantPoolSet &cp);

  public:
    static std::shared_ptr<Package> readModule(Parser &reader, ConstantPoolSet &cp);
};

} // namespace nballerina

#endif //!__BIRREADPACKAGE__H__
