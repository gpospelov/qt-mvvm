// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MAINBARWIDGET_H
#define MAINBARWIDGET_H

#include <QWidget>
#include <map>
class QStackedWidget;
class QHBoxLayout;
class QPushButton;

//! Widget container with functionality similar to QTabWidget. Has large button bar on top,
//! and stacked widget at bottom.

class MainBarWidget : public QWidget
{
    Q_OBJECT

public:
    MainBarWidget(QWidget* parent = nullptr);
    ~MainBarWidget();

    void addWidget(QWidget* widget, const QString& title);

    void setCurrentIndex(int index);

private:
    QStackedWidget* stacked_widget{nullptr};
    QHBoxLayout* button_layout{nullptr};
    std::map<int, QPushButton*> index_to_button;
};

#endif // MAINBARWIDGET_H
