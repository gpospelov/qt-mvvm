// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodeldelegate.h"
#include "comboproperty.h"
#include "customeditor.h"
#include "defaulteditorfactory.h"
#include "defaultcelldecoration.h"
#include <QApplication>
#include <QDebug>

using namespace ModelView;

ViewModelDelegate::ViewModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent), m_editor_factory(std::make_unique<DefaultEditorFactory>()), m_cell_decoration(std::make_unique<DefaultCellDecoration>())
{
}

void ViewModelDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const
{
    if (m_cell_decoration->hasCustomDecoration(index)) {
        QString text = QString::fromStdString(m_cell_decoration->cellText(index));
        paintCustomLabel(painter, option, index, text);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

ViewModelDelegate::~ViewModelDelegate() = default;

QWidget* ViewModelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    qDebug() << "ViewModelDelegate::createEditor" << parent << option << index;

    if (auto editor = m_editor_factory->createEditor(index, parent)) {
        connect(editor, &CustomEditor::dataChanged, this,
                &ViewModelDelegate::onCustomEditorDataChanged);
        return editor;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void ViewModelDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (!index.isValid())
        return;

    qDebug() << "ViewModelDelegate::setEditorData" << editor << index;

    if (auto customEditor = dynamic_cast<CustomEditor*>(editor))
        customEditor->setData(index.data());
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

void ViewModelDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                     const QModelIndex& index) const
{
    if (!index.isValid())
        return;

    qDebug() << "ViewModelDelegate::setModelData" << editor << model << index;

    if (auto customEditor = dynamic_cast<CustomEditor*>(editor)) {
        model->setData(index, customEditor->data());
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

//! Increases height of the row by 20% wrt the default.

QSize ViewModelDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight(static_cast<int>(result.height() * 1.2));
    return result;
}

//! Makes an editor occupying whole available space in a cell. If cell contains an icon
//! as a decoration (i.e. icon of material property), it will be hidden as soon as editor
//! up and running.

void ViewModelDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                                             const QModelIndex& index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    editor->setGeometry(option.rect);
}

void ViewModelDelegate::onCustomEditorDataChanged()
{
    qDebug() << "ViewModelDelegate::onCustomEditorDataChanged";
    CustomEditor* editor = qobject_cast<CustomEditor*>(sender());
    emit commitData(editor);
    if (!editor->is_persistent())
        emit closeEditor(editor);
}

void ViewModelDelegate::paintCustomLabel(QPainter* painter, const QStyleOptionViewItem& option,
                                         const QModelIndex& index, const QString& text) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index); // calling original method to take into accounts colors etc
    opt.text = displayText(text, option.locale); // by overriding text with ours
    const QWidget* widget = opt.widget;
    QStyle* style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
}
