// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <mvvm/model/compounditem.h>
#include <mvvm/model/sessionmodel.h>
#include <string>

namespace CellEditors
{

//! Demo item demonstrating supported properties.

class DemoPropertiesItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_BOOL_PROPERTY = "P_BOOL_PROPERTY";
    static inline const std::string P_INTEGER_PROPERTY = "P_INTEGER_PROPERTY";
    static inline const std::string P_STRING_PROPERTY = "P_STRING_PROPERTY";
    static inline const std::string P_DOUBLE_PROPERTY = "P_DOUBLE_PROPERTY";
    static inline const std::string P_COLOR_PROPERTY = "P_COLOR_PROPERTY";
    static inline const std::string P_COMBO_PROPERTY = "P_COMBO_PROPERTY";
    static inline const std::string P_SELECTABLE_COMBO_PROPERTY = "P_SELECTABLE_COMBO_PROPERTY";
    static inline const std::string P_EXTERNAL_PROPERTY = "P_EXTERNAL_PROPERTY";

    DemoPropertiesItem();
};

//! Main application model.

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();
};

} // namespace CellEditors

#endif
