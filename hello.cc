#include <clang/Frontend/ASTUnit.h>
#include <fmt/base.h>
#include <fmt/core.h>

#include <llvm/Support//TargetSelect.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/ManagedStatic.h>

#include <oneapi/tbb/blocked_range.h>
#include <oneapi/tbb/parallel_for.h>
#include <tbb/parallel_for.h>

#include "clang/Frontend/CompilerInstance.h"


int main()
{
    fmt::print("Hello vcpkg\n");
    FMT_VERSION;

    llvm::InitializeNativeTarget();

    tbb::parallel_for(tbb::blocked_range(0, 10), [](const auto &range) {
        for (auto i = range.begin(); i != range.end(); ++i) {
            fmt::print("tbb: {}\n", i);
        }
    });

    clang::CompilerInstance Clang;
    return 0;
}