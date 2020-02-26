// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/refcontrolledviewmodel.h>
#include <mvvm/viewmodel/refviewitems.h>
#include <mvvm/viewmodel/refviewmodelcontroller.h>
#include <mvvm/viewmodel/viewmodelutils.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/model/sessionitem.h>

using namespace ModelView;

RefControlledViewModel::RefControlledViewModel(std::unique_ptr<RefViewModelController> controller,
                                               QObject* parent)
    : RefViewModel(parent), m_controller(std::move(controller))
{
    m_controller->setRootSessionItem(sessionModel()->rootItem());
}

SessionModel* RefControlledViewModel::sessionModel() const
{
    return m_controller->sessionModel();
}

SessionItem* RefControlledViewModel::rootSessionItem()
{
    return m_controller->rootSessionItem();
}

RefControlledViewModel::~RefControlledViewModel() = default;

void RefControlledViewModel::setRootSessionItem(SessionItem* item)
{
    m_controller->setRootSessionItem(item);
}

SessionItem* RefControlledViewModel::sessionItemFromIndex(const QModelIndex& index) const
{
    return index.isValid() ? itemFromIndex(index)->item() : m_controller->rootSessionItem();
}

RefViewItem* RefControlledViewModel::viewItemFromIndex(const QModelIndex& index) const
{
    return itemFromIndex(index);
}

QModelIndexList RefControlledViewModel::indexOfSessionItem(const SessionItem* item) const
{
    QModelIndexList result;
    for(auto view : m_controller->findViews(item))
        result.push_back(indexFromItem(view));
    return result;
}

std::vector<RefViewItem*> RefControlledViewModel::findViews(const SessionItem* item) const
{
    return m_controller->findViews(item);
}
