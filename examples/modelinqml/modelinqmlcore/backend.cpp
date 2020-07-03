// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <modelinqmlcore/backend.h>
#include <modelinqmlcore/tablemodel.h>

BackEnd::BackEnd(QObject* parent) : QObject(parent), m_tableModel(new TableModel)
{

}

TableModel* BackEnd::tableModel() const
{
    return m_tableModel;
}
