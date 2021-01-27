// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/viewmodel.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/viewmodel/standardviewitems.h"
#include "mvvm/viewmodel/viewmodelcontroller.h"

using namespace ModelView;

ViewModel::ViewModel(std::unique_ptr<ViewModelController> controller, QObject* parent)
    : ViewModelBase(parent), m_controller(std::move(controller))
{
    m_controller->setViewModel(this);
    m_controller->setRootSessionItem(sessionModel()->rootItem());
}

QVariant ViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        auto data = m_controller->horizontalHeaderLabels();
        if (section < data.size())
            return data.at(section);
    }
    return QVariant();
}

SessionModel* ViewModel::sessionModel() const
{
    return m_controller->sessionModel();
}

SessionItem* ViewModel::rootSessionItem()
{
    return m_controller->rootSessionItem();
}

ViewModel::~ViewModel() = default;

void ViewModel::setRootSessionItem(SessionItem* item)
{
    if (!item)
        throw std::runtime_error("Error in ViewModel: atttemp to set nulptr as root item");
    m_controller->setRootSessionItem(item);
}

SessionItem* ViewModel::sessionItemFromIndex(const QModelIndex& index) const
{
    return index.isValid() ? itemFromIndex(index)->item() : m_controller->rootSessionItem();
}

ViewItem* ViewModel::viewItemFromIndex(const QModelIndex& index) const
{
    return itemFromIndex(index);
}

//! Returns list of model indices representing given SessionItem.

QModelIndexList ViewModel::indexOfSessionItem(const SessionItem* item) const
{
    QModelIndexList result;
    for (auto view : m_controller->findViews(item))
        result.push_back(indexFromItem(view));
    return result;
}

//! Returns vector of all ViewItem's representing given SessionItem.

std::vector<ViewItem*> ViewModel::findViews(const SessionItem* item) const
{
    return m_controller->findViews(item);
}
