// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_TAGROW_H
#define MVVM_MODEL_TAGROW_H

#include <mvvm/core/export.h>
#include <string>

namespace ModelView
{

//! Aggregate to hold (tag, row) information for SessionModel.

struct CORE_EXPORT TagRow {
    std::string tag = {};
    int row = -1;

    TagRow() {}

    TagRow(const std::string& name, int row = -1) : tag(name), row(row) {}
    TagRow(const char* name, int row = -1) : tag(name), row(row) {}

    static TagRow append(const std::string& tag_name = {});

    static TagRow prepend(const std::string& tag_name = {});

    bool operator==(const TagRow& other) const;
    bool operator!=(const TagRow& other) const;
};

} // namespace ModelView

#endif // MVVM_MODEL_TAGROW_H
