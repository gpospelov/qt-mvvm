// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHWIDGETTOOLBAR_H
#define GRAPHWIDGETTOOLBAR_H

#include <QToolBar>

class QSlider;
class QSpinBox;
class QPushButton;
class QProgressBar;

//! Toolbar for GraphWidget. Contains elements to steer background simulation.

class GraphWidgetToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit GraphWidgetToolBar(QWidget* parent = nullptr);

signals:
    void valueChanged(int value);

public slots:
    void onProgressChanged(int value);

private:
    void add_wide_separator();
    void init_value_elements();
    void init_slowdown_elements();
    void init_flow_elements();

    QSpinBox* value_box{nullptr}; //! Input parameter for simulation.
    QSlider* value_slider{nullptr};    //! Input parameter for simulation.
    QSpinBox* slowdown_spinbox{nullptr}; //! Factor defining how slow simulation is.
    QProgressBar* progressbar{nullptr}; //! SImulation progressbar.
    QPushButton* cancel_button{nullptr}; //! Cancels simulation.
};

#endif // GRAPHWIDGETTOOLBAR_H
