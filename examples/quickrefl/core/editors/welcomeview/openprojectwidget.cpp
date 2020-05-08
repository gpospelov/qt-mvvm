// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "openprojectwidget.h"

OpenProjectWidget::OpenProjectWidget(QWidget *parent) : QWidget(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::darkBlue);
    setAutoFillBackground(true);
    setPalette(palette);
}
