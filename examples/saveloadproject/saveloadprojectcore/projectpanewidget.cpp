// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "projectpanewidget.h"
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <mvvm/widgets/widgetutils.h>

namespace
{
int widget_height()
{
    return ModelView::Utils::SizeOfLetterM().height() * 3;
}
} // namespace

ProjectPaneWidget::ProjectPaneWidget(QWidget* parent)
    : QWidget(parent)
    , m_current_project_title(new QLabel(" "))
    , m_current_project_dir(new QLabel(" "))
    , m_widget_color(QColor(Qt::white))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    setFixedHeight(widget_height());
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_current_project_title);
    layout->addWidget(m_current_project_dir);
}

//! Sets current project dir to 'project_dir', adjust title according to 'is_modified'.

void ProjectPaneWidget::setCurrentProject(const QString& project_dir, bool is_modified)
{
    m_active = true;
    m_project_dir = project_dir;

    auto trimmed_project_dir = ModelView::Utils::WithTildeHomePath(project_dir);
    auto project_title = ModelView::Utils::ProjectWindowTitle(project_dir, is_modified);

    m_current_project_dir->setText(trimmed_project_dir);
    m_current_project_dir->setToolTip(m_project_dir);
    m_current_project_title->setText(project_title);
}

//! Clear content of widget and make it inactive. Inactive widget doesnt' send signals when
//! user click on it.

void ProjectPaneWidget::clear()
{
    setActive(false);
    m_project_dir.clear();
    m_current_project_dir->setText({});
    m_current_project_dir->setToolTip({});
    m_current_project_title->setText({});
}

//! Set 'active' flag to the given value. 'False' means that the widget only shows the project
//! title, but doesn't react on mouse clicks and doesn't change the background on mouse
//! hover events.
void ProjectPaneWidget::setActive(bool value)
{
    m_active = value;
    update();
}

void ProjectPaneWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(0, 0, size().width(), size().height(), m_widget_color);
}

void ProjectPaneWidget::enterEvent(QEvent*)
{
    if (m_active)
        m_widget_color = QColor(Qt::lightGray);
    update();
}

void ProjectPaneWidget::leaveEvent(QEvent*)
{
    m_widget_color = QColor(Qt::white);
    update();
}

void ProjectPaneWidget::mousePressEvent(QMouseEvent* event)
{
    if (m_active && event->button() == Qt::LeftButton)
        projectSelected(m_project_dir);
}
