// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include "SampleViewDelegate.h"

class MaterialViewController;

/*!
@class MaterialViewDelegate
@brief Default delegate for the material table. Processes mouse click events on checkbox column.
*/

class MaterialViewDelegate : public SampleViewDelegate
{
public:
    MaterialViewDelegate(MaterialViewController& controller, QObject* parent = nullptr);
    ~MaterialViewDelegate() override;

protected:
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option,
                     const QModelIndex& index) override;

private:
    MaterialViewController& m_controller;
};

#endif // CHECKBOXDELEGATE_H
