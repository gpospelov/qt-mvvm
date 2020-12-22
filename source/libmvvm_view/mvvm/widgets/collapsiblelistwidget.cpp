// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/collapsiblelistwidget.h"
#include "mvvm/widgets/collapsiblebar.h"
#include <QSplitter>
#include <QVBoxLayout>

using namespace ModelView;

CollapsibleListWidget::CollapsibleListWidget(QWidget* parent)
    : QWidget(parent), m_splitter(new QSplitter)
{
    m_splitter->setOrientation(Qt::Vertical);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_splitter);
}

void CollapsibleListWidget::addWidget(QWidget* widget, const QString& title, bool collapsed)
{
    // add bar which will be uncollapsible and will control the appearance of our widget
    auto bar = new CollapsibleBar(m_splitter);
    m_splitter->addWidget(bar);

    // add widget itself
    m_splitter->addWidget(widget);

    // setup bar for widget
    bar->setWidget(widget, title);
    m_splitter->setCollapsible(m_splitter->indexOf(bar), false);

    if (collapsed)
        widget->setVisible(false);
}
