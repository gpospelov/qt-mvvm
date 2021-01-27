// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/viewmodeldelegate.h"
#include "mvvm/editors/customeditor.h"
#include "mvvm/editors/defaulteditorfactory.h"
#include "mvvm/viewmodel/defaultcelldecorator.h"
#include <QApplication>

namespace {
const double scale_default_height_factor{1.2};
}

using namespace ModelView;

ViewModelDelegate::ViewModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
    , m_editor_factory(std::make_unique<DefaultEditorFactory>())
    , m_cell_decoration(std::make_unique<DefaultCellDecorator>())
{
}

ViewModelDelegate::~ViewModelDelegate() = default;

void ViewModelDelegate::setEditorFactory(std::unique_ptr<EditorFactoryInterface> editor_factory)
{
    m_editor_factory = std::move(editor_factory);
}

void ViewModelDelegate::setCellDecoration(std::unique_ptr<CellDecoratorInterface> cell_decoration)
{
    m_cell_decoration = std::move(cell_decoration);
}

QWidget* ViewModelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    if (auto editor = m_editor_factory->createEditor(index)) {
        editor->setParent(parent);
        connect(editor.get(), &CustomEditor::dataChanged, this,
                &ViewModelDelegate::onCustomEditorDataChanged);
        return editor.release();
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ViewModelDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (!index.isValid())
        return;

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

    if (auto customEditor = dynamic_cast<CustomEditor*>(editor)) {
        model->setData(index, customEditor->data());
    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

//! Increases height of the row by 20% wrt the default.

QSize ViewModelDelegate::sizeHint(const QStyleOptionViewItem& option,
                                  const QModelIndex& index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight(static_cast<int>(result.height() * scale_default_height_factor));
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
    auto editor = qobject_cast<CustomEditor*>(sender());
    emit commitData(editor);
    if (!editor->is_persistent())
        emit closeEditor(editor);
}

void ViewModelDelegate::initStyleOption(QStyleOptionViewItem* option,
                                        const QModelIndex& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    if (m_cell_decoration && m_cell_decoration->hasCustomDecoration(index))
        m_cell_decoration->initStyleOption(option, index);
}
