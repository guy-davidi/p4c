/*
Copyright 2013-present Barefoot Networks, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef _IR_ID_H_
#define _IR_ID_H_

#include "lib/cstring.h"
#include "lib/error.h"
#include "lib/exceptions.h"
#include "lib/source_file.h"

namespace IR {

// An identifier.
struct ID : Util::IHasSourceInfo {
    Util::SourceInfo srcInfo;
    cstring name = nullptr;
    // We save the original name to show the user on error messages.
    // If originalName is nullptr the symbol has been generated by the compiler.
    cstring originalName = nullptr;
    ID() = default;
    ID(Util::SourceInfo si, cstring n, cstring o) : srcInfo(si), name(n), originalName(o) {
        if (n.isNullOrEmpty()) BUG("Identifier with no name");
    }
    ID(Util::SourceInfo si, cstring n) : srcInfo(si), name(n), originalName(n) {
        if (n.isNullOrEmpty()) BUG("Identifier with no name");
    }
    ID(const char* n) : ID(Util::SourceInfo(), n) {}  // NOLINT(runtime/explicit)
    ID(cstring n) : ID(Util::SourceInfo(), n) {}      // NOLINT(runtime/explicit)
    ID(cstring n, cstring old) : ID(Util::SourceInfo(), n, old) {}
    void dbprint(std::ostream& out) const {
        out << name;
        if (originalName != nullptr && originalName != name) out << "/" << originalName;
    }
    bool operator==(const ID& a) const { return name == a.name; }
    bool operator!=(const ID& a) const { return name != a.name; }
    explicit operator bool() const { return name; }
    operator cstring() const { return name; }
    bool isDontCare() const { return name == "_"; }
    Util::SourceInfo getSourceInfo() const override { return srcInfo; }
    cstring toString() const override { return originalName.isNullOrEmpty() ? name : originalName; }
};

}  // namespace IR
#endif  // _IR_ID_H_
