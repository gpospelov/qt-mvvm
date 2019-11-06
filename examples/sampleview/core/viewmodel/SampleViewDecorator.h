// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEVIEWDECORATOR_H
#define SAMPLEVIEWDECORATOR_H

#include "CellDecoratorInterface.h"

/*!
@class SampleViewDecorator
@brief Default decorator for SampleViewDelegate. Features decoration for double-valued items.
*/

class SampleViewDecorator : public CellDecoratorInterface
{
public:
    ~SampleViewDecorator() override;
    virtual bool hasCustomDecoration(const QModelIndex& index) const override;
    virtual void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) override;

private:
    bool hasDecorationImpl(const QModelIndex& index) const;
};

#endif // SAMPLEVIEWDECORATOR_H
