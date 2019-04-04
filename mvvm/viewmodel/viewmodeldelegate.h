// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef VIEWMODELDELEGATE_H
#define VIEWMODELDELEGATE_H

#include "global.h"
#include <QStyledItemDelegate>

class QStandardItem;

namespace ModelView
{

//! Base class for all view models to show content of  SessionModel in Qt views.

class CORE_EXPORT ViewModelDelegate : public QStyledItemDelegate
{
public:
    explicit ViewModelDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;
};

} // namespace ModelView

#endif // VIEWMODELDELEGATE_H
