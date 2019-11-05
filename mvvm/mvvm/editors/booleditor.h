// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_BOOLEDITOR_H
#define MVVM_BOOLEDITOR_H

#include <mvvm/editors/customeditor.h>

class QCheckBox;

namespace ModelView
{

//! Custom editor for QVariant based on bool values.

class CORE_EXPORT BoolEditor : public CustomEditor
{
public:
    explicit BoolEditor(QWidget* parent = nullptr);

    bool is_persistent() const override;

private slots:
    void onCheckBoxChange(bool value);

private:
    void update_components() override;
    QCheckBox* m_checkBox;
};

} // namespace ModelView

#endif // MVVM_BOOLEDITOR_H
