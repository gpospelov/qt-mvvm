// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SampleViewDecorator.h"
#include <mvvm/widgets/scientificspinbox.h>
#include <QModelIndex>
#include <QStyleOptionViewItem>

SampleViewDecorator::~SampleViewDecorator() = default;

bool SampleViewDecorator::hasCustomDecoration(const QModelIndex& index) const
{
    return hasDecorationImpl(index);
}

void SampleViewDecorator::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index)
{
    if (!option || !hasDecorationImpl(index))
        return;

    option->text = ModelView::ScientificSpinBox::toString(index.data(Qt::EditRole).value<double>(), 4);
}

bool SampleViewDecorator::hasDecorationImpl(const QModelIndex &index) const
{
    if (!hasValue(index, Qt::EditRole))
        return false;

    QVariant data = index.data(Qt::EditRole);
    return data.type() == QVariant::Double;
}
