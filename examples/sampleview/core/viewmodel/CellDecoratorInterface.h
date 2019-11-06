// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CELLDECORATORINTERFACE_H
#define CELLDECORATORINTERFACE_H

class QModelIndex;
class QStyleOptionViewItem;

/*!
@class CellDecoratorInterface
@brief Generates cell decorations. Intended for use with SampleViewDelegate and its descendants.
*/

class CellDecoratorInterface
{
public:
    virtual ~CellDecoratorInterface();
    virtual bool hasCustomDecoration(const QModelIndex& index) const = 0;
    virtual void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) = 0;

protected:
    bool hasValue(const QModelIndex& index, int role) const;
};

#endif //  CELLDECORATORINTERFACE_H
