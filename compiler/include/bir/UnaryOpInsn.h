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

#ifndef __UNARYOPINSN__H__
#define __UNARYOPINSN__H__

#include "interfaces/NonTerminatorInsn.h"

namespace nballerina {

class Operand;

class UnaryOpInsn : public NonTerminatorInsn, public Translatable<UnaryOpInsn> {
  private:
    Operand rhsOp;
    InstructionKind kind;

  public:
    UnaryOpInsn(Operand lhs, BasicBlock &currentBB, Operand rhs, InstructionKind kind)
        : NonTerminatorInsn(std::move(lhs), currentBB), rhsOp(std::move(rhs)), kind(kind) {}
    friend class NonTerminatorInsnCodeGen;
};

} // namespace nballerina

#endif //!__UNARYOPINSN__H__
