// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALTABLEDECORATOR_H
#define MATERIALTABLEDECORATOR_H

#include "SampleViewDecorator.h"

/*!
@class MaterialTableDecorator
@brief A decorator for MaterialTableDelegate. Features text removal from decorated items.
*/

class MaterialTableDecorator : public SampleViewDecorator
{
public:
    ~MaterialTableDecorator() override;

    bool hasCustomDecoration(const QModelIndex& index) const override;
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) override;

private:
    bool hasDecorationImpl(const QModelIndex& index) const;
};

#endif // MATERIALTABLEDECORATOR_H
