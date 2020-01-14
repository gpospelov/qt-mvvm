// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "LayerTableWidget.h"
#include "ApplicationModels.h"
#include "CustomModelDelegate.h"
#include "SampleControlPanel.h"
#include <QHeaderView>
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

namespace
{
QTreeView* createSampleView(SampleTreeController& controller, QAbstractItemDelegate* delegate);
}

LayerTableWidget::LayerTableWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_controller(models ? models->sampleModel() : nullptr),
      m_delegate(std::make_unique<CustomModelDelegate>(models)),
      m_sample_table(createSampleView(m_controller, m_delegate.get()))
{
    auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(new SampleControlPanel(m_controller));
    layout->addWidget(m_sample_table);
}

LayerTableWidget::~LayerTableWidget() = default;

namespace
{
QTreeView* createSampleView(SampleTreeController& controller, QAbstractItemDelegate* delegate)
{
    std::unique_ptr<QTreeView> result(new QTreeView);
    result->setModel(&controller.viewModel());
    result->setSelectionModel(&controller.selectionModel());
    result->setItemDelegate(delegate);

    result->setAlternatingRowColors(true);
    result->expandAll();
    result->header()->setSectionResizeMode(QHeaderView::Stretch);
    result->setDragDropMode(QAbstractItemView::InternalMove);

    return result.release();
}
} // namespace
