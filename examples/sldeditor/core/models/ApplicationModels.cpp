// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "ApplicationModels.h"
#include "ViewItemsModel.h"
#include <mvvm/core/modeldocuments.h>
#include <mvvm/model/sessionitem.h>

using namespace ModelView;

struct ApplicationModels::ApplicationModelsImpl {
    std::unique_ptr<ViewItemsModel> m_view_items_model;

    ApplicationModelsImpl()
    {
        m_view_items_model = std::make_unique<ViewItemsModel>();
    }
};

ApplicationModels::ApplicationModels() : p_impl(std::make_unique<ApplicationModelsImpl>()) {}

ApplicationModels::~ApplicationModels() = default;

ViewItemsModel* ApplicationModels::viewItemsModel()
{
    return p_impl->m_view_items_model.get();
}
