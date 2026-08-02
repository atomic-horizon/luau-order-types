// This file is part of the Luau programming language and is licensed under MIT License; see LICENSE.txt for details
#pragma once

#include "Luau/DenseHash.h"
#include "Luau/FileResolver.h"
#include "Luau/Location.h"

#include <string>
#include <vector>

namespace Luau
{

class AstNode;
class AstStatBlock;

struct RequireTraceResult
{
    DenseHashMap<const AstNode*, ModuleInfo> exprs{nullptr};

    std::vector<std::pair<ModuleName, Location>> requireList;

#ifdef ORDER_STRING_REQUIRE
    // Order-style shared() requires. These participate fully in the dependency graph
    // (build ordering AND cycle detection - cycle visibility is what makes cyclic
    // requires resolve to `any` instead of embedding freeable cross-module TypeIds).
    // They are tracked separately so that ModuleHasCyclicDependency diagnostics can be
    // suppressed for cycles that pass through a shared() edge, which are intentional
    // in the Order framework.
    std::vector<std::pair<ModuleName, Location>> sharedRequireList;
#endif
};

RequireTraceResult traceRequires(FileResolver* fileResolver, AstStatBlock* root, const ModuleName& currentModuleName, const TypeCheckLimits& limits);

} // namespace Luau
