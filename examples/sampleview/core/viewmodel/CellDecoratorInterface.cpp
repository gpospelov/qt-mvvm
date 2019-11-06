// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "CellDecoratorInterface.h"
#include <QModelIndex>

CellDecoratorInterface::~CellDecoratorInterface() = default;

bool CellDecoratorInterface::hasValue(const QModelIndex& index, int role) const {
    auto value = index.data(role);
    return value.isValid() && !value.isNull();
}
