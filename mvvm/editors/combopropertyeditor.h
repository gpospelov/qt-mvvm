// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COMBOPROPERTYEDITOR_H
#define COMBOPROPERTYEDITOR_H

#include "customeditor.h"

class QComboBox;

namespace ModelView
{

//! Custom editor for QVariant based on ComboProperty.

class CORE_EXPORT ComboPropertyEditor : public CustomEditor
{
public:
    explicit ComboPropertyEditor(QWidget* parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected slots:
    virtual void onIndexChanged(int index);

private:
    std::vector<std::string> internLabels();
    int internIndex();
    void setConnected(bool isConnected);
    void update_components();
    QComboBox* m_box;
};

} // namespace ModelView

#endif // COMBOPROPERTYEDITOR_H
