// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MaterialTableDecorator.h"
#include <QModelIndex>
#include <QStyleOptionViewItem>

MaterialTableDecorator::~MaterialTableDecorator() = default;

bool MaterialTableDecorator::hasCustomDecoration(const QModelIndex& index) const
{
    return SampleViewDecorator::hasCustomDecoration(index) || hasDecorationImpl(index);
}

void MaterialTableDecorator::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index)
{
    SampleViewDecorator::initStyleOption(option, index);

    if (!option || !hasDecorationImpl(index))
        return;

    option->features &= ~QStyleOptionViewItem::HasDisplay;
    option->text = QString();
}

bool MaterialTableDecorator::hasDecorationImpl(const QModelIndex& index) const
{
    return hasValue(index, Qt::DecorationRole);
}
