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
    // Order-style shared() requires: these are added to requireSet for build ordering
    // but NOT to requireLocations, so they are excluded from cycle error detection.
    // This allows intentional cyclic dependencies between Order services without
    // triggering ModuleHasCyclicDependency errors.
    std::vector<std::pair<ModuleName, Location>> sharedRequireList;
#endif
};

RequireTraceResult traceRequires(FileResolver* fileResolver, AstStatBlock* root, const ModuleName& currentModuleName, const TypeCheckLimits& limits);

} // namespace Luau
