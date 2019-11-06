// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_MODEL_TAGROW_H
#define MVVM_MODEL_TAGROW_H

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

#endif  // MVVM_MODEL_TAGROW_H
