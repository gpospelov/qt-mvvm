// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_EDITORS_COMBOPROPERTYEDITOR_H
#define MVVM_EDITORS_COMBOPROPERTYEDITOR_H

#include <mvvm/editors/customeditor.h>

class QComboBox;

namespace ModelView
{

//! Custom editor for QVariant based on ComboProperty.

class CORE_EXPORT ComboPropertyEditor : public CustomEditor
{
public:
    explicit ComboPropertyEditor(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected slots:
    virtual void onIndexChanged(int index);

private:
    std::vector<std::string> internLabels();
    int internIndex();
    void setConnected(bool isConnected);
    void update_components() override;
    QComboBox* m_box;
};

} // namespace ModelView

#endif  // MVVM_EDITORS_COMBOPROPERTYEDITOR_H
