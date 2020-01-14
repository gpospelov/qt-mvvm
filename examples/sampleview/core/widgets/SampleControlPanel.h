// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLECONTROLPANEL_H
#define SAMPLECONTROLPANEL_H

#include <QWidget>

class QPushButton;
class SampleTreeController;

class SampleControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit SampleControlPanel(SampleTreeController& sample_controller, QWidget* parent = nullptr);
    ~SampleControlPanel() override;

private:
    QPushButton* m_new_multilayer_button;
    QPushButton* m_new_layer_button;
    QPushButton* m_clone_button;
    QPushButton* m_remove_button;
};

#endif // SAMPLECONTROLPANEL_H
