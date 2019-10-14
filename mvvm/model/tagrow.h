// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_TAGROW_H
#define MVVM_TAGROW_H

#include "mvvm_export.h"
#include <string>

namespace ModelView
{

//! Aggregate to hold (tag, row) information for SessionModel.

struct CORE_EXPORT TagRow
{
    std::string tag = {};
    int row = -1;

    static TagRow defaultAppend();

    static TagRow append(const std::string& tag_name);

    bool operator==(const TagRow& other) const;
    bool operator!=(const TagRow& other) const;
};

} // namespace ModelView

#endif //  MVVM_TAGROW_H
