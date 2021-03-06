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

#ifndef __TERMINATORINSN__H__
#define __TERMINATORINSN__H__

#include "interfaces/AbstractInstruction.h"
#include "interfaces/Translatable.h"
#include <string>

namespace nballerina {

class TerminatorInsn : public AbstractInstruction, virtual public TranslatableInterface {
  protected:
    std::string thenBBID;
    InstructionKind kind;
    TerminatorInsn(class Operand lhs, class BasicBlock &currentBB, std::string thenBBID)
        : AbstractInstruction(std::move(lhs), currentBB), thenBBID(std::move(thenBBID)),
          kind(INSTRUCTION_NOT_AN_INSTRUCTION) {}

  public:
    virtual ~TerminatorInsn() = default;
};

} // namespace nballerina

#endif //!__TERMINATORINSN__H__
