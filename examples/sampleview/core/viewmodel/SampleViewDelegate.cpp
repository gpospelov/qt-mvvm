// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SampleViewDelegate.h"
#include "SampleEditorFactory.h"
#include <QApplication>
#include <mvvm/viewmodel/defaultcelldecorator.h>

SampleViewDelegate::SampleViewDelegate(QObject* parent)
    : QStyledItemDelegate(parent),
      m_cell_decorator(std::make_unique<ModelView::DefaultCellDecorator>())
{
    setItemEditorFactory(SampleEditorFactory::createStandardSampleEditorFactory().release());
}

SampleViewDelegate::~SampleViewDelegate() = default;

void SampleViewDelegate::initStyleOption(QStyleOptionViewItem* option,
                                         const QModelIndex& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    if (m_cell_decorator && m_cell_decorator->hasCustomDecoration(index))
        m_cell_decorator->initStyleOption(option, index);
}

void SampleViewDelegate::setCellDecorator(decoration_ptr cell_decoration)
{
    m_cell_decorator = std::move(cell_decoration);
}
