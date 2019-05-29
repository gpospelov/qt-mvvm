// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodelcontroller.h"
#include "sessionitem.h"
#include "sessionmodel.h"

using namespace ModelView;

class ViewModelController::ViewModelControllerPrivate
{
public:
    ViewModelControllerPrivate(AbstractViewModel* view_model) : m_view_model(view_model), m_root_item(nullptr), m_session_model(nullptr) {}
    AbstractViewModel* m_view_model;
    SessionItem* m_root_item;
    SessionModel* m_session_model;
};

ViewModelController::ViewModelController(AbstractViewModel* view_model)
    : p_impl(std::make_unique<ViewModelControllerPrivate>(view_model))
{
}

ViewModelController::~ViewModelController() = default;
