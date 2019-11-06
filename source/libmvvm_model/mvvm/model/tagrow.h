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

#include <mvvm/core/export.h>
#include <string>

namespace ModelView
{

//! Aggregate to hold (tag, row) information for SessionModel.

struct CORE_EXPORT TagRow
{
    std::string tag = {};
    int row = -1;

    static TagRow append(const std::string& tag_name = {});

    static TagRow prepend(const std::string& tag_name = {});

};

} // namespace ModelView

CORE_EXPORT bool operator==(const ModelView::TagRow& left, const ModelView::TagRow& right);
CORE_EXPORT bool operator!=(const ModelView::TagRow& left, const ModelView::TagRow& right);

#endif //  MVVM_TAGROW_H
