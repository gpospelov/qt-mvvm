// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALTABLEROWCONSTRUCTOR_H
#define MATERIALTABLEROWCONSTRUCTOR_H

#include "rowconstructorinterface.h"

//! Constructs row of QStandardItem's for MaterialItem.

class CORE_EXPORT MaterialTableRowConstructor : public ModelView::RowConstructorInterface
{
public:
    QList<QStandardItem*> constructRow(ModelView::SessionItem* item);
    int columnCount() const;
    QStringList horizontalHeaderLabels() const;
};


#endif // MATERIALTABLEROWCONSTRUCTOR_H

