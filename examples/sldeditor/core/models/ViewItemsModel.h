// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef VIEWITEMSMODEL_H
#define VIEWITEMSMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <vector>

namespace ModelView
{
class ExternalProperty;
}

/*!
@class ViewItemsModel
@brief This holds the model for all the graphical elements of the sld editor
*/

class ViewItemsModel : public ModelView::SessionModel
{
public:
    ViewItemsModel();

    static ModelView::ExternalProperty undefined_material();

    std::vector<ModelView::ExternalProperty> material_data();

    ModelView::ExternalProperty material_property(const std::string& id);

private:

};

#endif //  VIEWITEMSMODEL_H
