// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALCONTROLPANEL_H
#define MATERIALCONTROLPANEL_H

#include <QWidget>

class QComboBox;
class QPushButton;
class MaterialViewController;

class MaterialControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialControlPanel(MaterialViewController& view_model, QWidget* parent = nullptr);
    ~MaterialControlPanel() override;

private:
    QPushButton* m_new_button;
    QPushButton* m_clone_button;
    QPushButton* m_remove_button;
    QComboBox* m_material_type_selector;
};

#endif // MATERIALCONTROLPANEL_H
