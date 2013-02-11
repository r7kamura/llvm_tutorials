// Inlclude header files from /usr/local/include/.
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/IRBuilder.h"

// The entry point of this program.
int main() {
  // Define a LLVM context.
  // A LLVM context is like a class which provides a context where variables are defined.
  llvm::LLVMContext& context = llvm::getGlobalContext();

  // Define a LLVM module named "top".
  // This name "top" can be anything.
  // A module is a top-level container of other LLVM IR objects.
  // A module can contain global-variables, functions, other dependent modules, and so on.
  // In this case, this module contains the main function.
  //
  // Output:
  //
  //   ; ModuleID = 'top'
  //
  llvm::Module *module = new llvm::Module("top", context);

  // Provides some APIs for creating LLVM assembly code.
  llvm::IRBuilder<> builder(context);

  // Define the ret-val's type of main function.
  llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);

  // Define the main function with passing the previously defined funcType.
  //
  // Output:
  //
  //   declare void @main()
  //
  llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

  // Define a BasicBlock, which is a set of commands of LLVM IR.
  // A BasicBlock can contain a label. In this case, it has a label named "entrypoint".
  // As you can understand from its 3rd argument, this BasicBlock is contained in the main function.
  //
  // When a function has any BasicBlock, that is written with define keyword.
  //
  // Output:
  //
  //   define void @main() {
  //     entrypoint:
  //   }
  //
  llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
  builder.SetInsertPoint(entry);

  // Define a global variable for a string "Hello, world!\n".
  //
  // Output:
  //
  //   @0 = private unnamed_addr constant [15 x i8] c"Hello, world!\0A\00"
  //
  llvm::Value *helloWorld = builder.CreateGlobalStringPtr("Hello, world!\n");

  // Declare the puts function with i32 ret-val and i18* argument.
  //
  // Output:
  //
  //   declare i32 @puts(i8*)
  //
  std::vector<llvm::Type*> putsArgs;
  putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
  llvm::ArrayRef<llvm::Type*> argsRef(putsArgs);
  llvm::FunctionType *putsType = llvm::FunctionType::get(builder.getInt32Ty(), argsRef, false);
  llvm::Constant *putsFunc = module->getOrInsertFunction("puts", putsType);

  // Call puts("Hello, world!\n").
  //
  // Output:
  //
  //   %0 = call i32 @puts(i8* getelementptr inbounds ([15 x i8]* @0, i32 0, i32 0))
  //
  builder.CreateCall(putsFunc, helloWorld);

  // Return from the main function with void.
  //
  // Output:
  //
  //   ret void;
  //
  builder.CreateRetVoid();

  // Dump the content of the module.
  //
  // Output:
  //
  //   ; ModuleID = 'top'
  //   @0 = private unnamed_addr constant [15 x i8] c"Hello, world!\0A\00"
  //
  //   define i32 @main() {
  //   entrypoint:
  //     %0 = call i32 @puts(i8* getelementptr inbounds ([15 x i8]* @0, i32 0, i32 0))
  //     ret void
  //   }
  //
  //   declare i32 @puts(i8*)
  //
  module->dump();
}
