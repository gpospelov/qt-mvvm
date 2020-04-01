// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef QUICKSIMEDITORTOOLBAR_H
#define QUICKSIMEDITORTOOLBAR_H

#include <QToolBar>

class QSlider;
class QSpinBox;
class QPushButton;
class QProgressBar;
class QCheckBox;

//! Toolbar for QuickSimEditor.
//! Contains live simulation button, cancel button, simulation progress bar and settings buttons.

class QuickSimEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit QuickSimEditorToolBar(QWidget* parent = nullptr);

signals:
    void realTimeRequest(bool);
    void runSimulationRequest();
    void cancelPressed();
    void instrumentSettingsRequest();
    void resetViewRequest();
    void plotSettingsRequest();

public slots:
    void onProgressChanged(int value);

private:
    void add_wide_separator();
    void setup_simulation_elements();
    void setup_plot_elements();

    QCheckBox* live_checkbox{nullptr};
    QSpinBox* delay_spinbox{nullptr};    //! Factor defining how slow simulation is.
    QProgressBar* progressbar{nullptr};  //! Simulation progressbar.
    QPushButton* cancel_button{nullptr}; //! Cancels simulation.
};

#endif // QUICKSIMEDITORTOOLBAR_H
