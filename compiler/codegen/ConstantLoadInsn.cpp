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

#include "ConstantLoad.h"
#include "Function.h"
#include "Operand.h"
#include "Package.h"
#include "Variable.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"

namespace nballerina {

// With Nil Type setting only Type Tag because value will be zero with NIL Type.
ConstantLoadInsn::ConstantLoadInsn(const Operand &lhs, BasicBlock &currentBB)
    : NonTerminatorInsn(lhs, currentBB), typeTag(TYPE_TAG_NIL) {}

ConstantLoadInsn::ConstantLoadInsn(const Operand &lhs, BasicBlock &currentBB, int64_t intVal)
    : NonTerminatorInsn(lhs, currentBB), typeTag(TYPE_TAG_INT), value(intVal) {}

ConstantLoadInsn::ConstantLoadInsn(const Operand &lhs, BasicBlock &currentBB, float floatVal)
    : NonTerminatorInsn(lhs, currentBB), typeTag(TYPE_TAG_FLOAT), value(floatVal) {}

ConstantLoadInsn::ConstantLoadInsn(const Operand &lhs, BasicBlock &currentBB, bool boolVal)
    : NonTerminatorInsn(lhs, currentBB), typeTag(TYPE_TAG_BOOLEAN), value(boolVal) {}

ConstantLoadInsn::ConstantLoadInsn(const Operand &lhs, BasicBlock &currentBB, std::string str)
    : NonTerminatorInsn(lhs, currentBB), typeTag(TYPE_TAG_STRING), value(std::move(str)) {}

llvm::FunctionCallee ConstantLoadInsn::getNewString(llvm::Module &module) {
    const std::string newString = "new_string";
    auto *funcType =
        llvm::FunctionType::get(llvm::Type::getInt8PtrTy(module.getContext()),
                                llvm::ArrayRef<llvm::Type *>({llvm::Type::getInt8PtrTy(module.getContext()),
                                                              llvm::Type::getInt64Ty(module.getContext())}),
                                false);
    return module.getOrInsertFunction(newString, funcType);
}

void ConstantLoadInsn::translate(llvm::Module &module, llvm::IRBuilder<> &builder) {
    const auto &lhsOp = getLhsOperand();
    const auto &funcRef = getFunctionRef();
    auto *lhsRef = funcRef.getLLVMLocalOrGlobalVar(lhsOp, module);

    assert(funcRef.getLocalOrGlobalVariable(lhsOp).getType().getTypeTag() == typeTag);
    llvm::Value *constRef = nullptr;
    switch (typeTag) {
    case TYPE_TAG_INT: {
        constRef = builder.getInt64(std::get<int64_t>(value));
        break;
    }
    case TYPE_TAG_FLOAT: {
        constRef = llvm::ConstantFP::get(module.getContext(), llvm::APFloat(std::get<float>(value)));
        break;
    }
    case TYPE_TAG_BOOLEAN: {
        if (std::get<bool>(value)) {
            constRef = builder.getInt8(1);
        } else {
            constRef = builder.getInt8(0);
        }
        break;
    }
    case TYPE_TAG_STRING:
    case TYPE_TAG_CHAR_STRING: {
        std::string stringValue = std::get<std::string>(value);
        llvm::Constant *llvmConst = llvm::ConstantDataArray::getString(module.getContext(), stringValue);
        auto *globalStringValue = new llvm::GlobalVariable(module, llvmConst->getType(), false,
                                                           llvm::GlobalValue::PrivateLinkage, llvmConst, ".str");
        globalStringValue->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
        globalStringValue->setAlignment(llvm::Align(1));
        auto *valueRef = builder.CreateInBoundsGEP(
            globalStringValue, llvm::ArrayRef<llvm::Value *>({builder.getInt64(0), builder.getInt64(0)}), "simple");
        auto addedStringRef = getNewString(module);
        constRef = builder.CreateCall(
            addedStringRef, llvm::ArrayRef<llvm::Value *>({valueRef, builder.getInt64(stringValue.length())}));
        break;
    }
    case TYPE_TAG_NIL: {
        const auto &lhsOpName = lhsOp.getName();
        if (funcRef.isMainFunction() && (lhsOpName == funcRef.getReturnVar()->getName())) {
            return;
        }
        auto *nillRef = getPackageRef().getGlobalNilVar();
        constRef = builder.CreateLoad(nillRef, lhsOpName + "_temp");
        break;
    }
    default:
        llvm_unreachable("Unknown Type");
    }

    builder.CreateStore(constRef, lhsRef);
}

} // namespace nballerina
