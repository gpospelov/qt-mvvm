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

struct BackEnd::BackEndImpl {
    TableModel* m_tableModel{nullptr};

    BackEndImpl() : m_tableModel(new TableModel) {}
};

BackEnd::BackEnd(QObject* parent) : QObject(parent), p_impl(std::make_unique<BackEndImpl>()) {}

BackEnd::~BackEnd() = default;

TableModel* BackEnd::tableModel() const
{
    return p_impl->m_tableModel;
}
