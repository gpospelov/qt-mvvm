// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodeldelegate.h"
#include "editorfactory.h"
#include <QDebug>

using namespace ModelView;

ViewModelDelegate::ViewModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent), m_editor_factory(std::make_unique<EditorFactory>())
{
}

ViewModelDelegate::~ViewModelDelegate() = default;

QWidget* ViewModelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    qDebug() << "ViewModelDelegate::createEditor" << parent << option << index;

    if (auto editor = m_editor_factory->createEditor(index)) {
        return editor;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
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
