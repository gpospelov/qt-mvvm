// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodeldelegate.h"
#include <QDebug>

using namespace ModelView;

ViewModelDelegate::ViewModelDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

QWidget* ViewModelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    qDebug() << "ViewModelDelegate::createEditor" << parent << option << index;
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ViewModelDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    qDebug() << "ViewModelDelegate::setEditorData" << editor << index;
    QStyledItemDelegate::setEditorData(editor, index);
}

void ViewModelDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                     const QModelIndex& index) const
{
    qDebug() << "ViewModelDelegate::setModelData" << editor << model << index;
    QStyledItemDelegate::setModelData(editor, model, index);
}

void ViewModelDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                                             const QModelIndex& index) const
{
    qDebug() << "ViewModelDelegate::updateEditorGeometry" << editor << option << index;
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}
