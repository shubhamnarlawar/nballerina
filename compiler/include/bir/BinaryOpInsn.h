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

#ifndef __BINARYOPINSN__H__
#define __BINARYOPINSN__H__

#include "interfaces/NonTerminatorInsn.h"

namespace nballerina {

class Operand;

class BinaryOpInsn : public NonTerminatorInsn, public Translatable<BinaryOpInsn> {
  private:
    Operand rhsOp1;
    Operand rhsOp2;
    InstructionKind kind;

  public:
    BinaryOpInsn(Operand lhs, class BasicBlock &currentBB, Operand rhsOp1, Operand rhsOp2, InstructionKind kind)
        : NonTerminatorInsn(std::move(lhs), currentBB), rhsOp1(std::move(rhsOp1)), rhsOp2(std::move(rhsOp2)),
          kind(kind) {}
    friend class NonTerminatorInsnCodeGen;
};

} // namespace nballerina

#endif //!__BINARYOPINSN__H__
