// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DATAROWSTRATEGY_H
#define DATAROWSTRATEGY_H

#include <memory>
#include <mvvm/viewmodel/rowstrategyinterface.h>

class QStandardItem;

namespace ModelView
{
class SessionItem;
}

//! Constructs the row strategy for the given data view model controller

class DataRowStrategy : public ModelView::RowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const override;

    std::vector<std::unique_ptr<ModelView::ViewItem>>
    constructRefRow(ModelView::SessionItem*) override;
};

#endif // DATAROWSTRATEGY_H
