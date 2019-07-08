#include "CellDecoratorInterface.h"
#include <QModelIndex>

CellDecoratorInterface::~CellDecoratorInterface() = default;

bool CellDecoratorInterface::hasValue(const QModelIndex& index, int role) const {
    auto value = index.data(role);
    return value.isValid() && !value.isNull();
}
