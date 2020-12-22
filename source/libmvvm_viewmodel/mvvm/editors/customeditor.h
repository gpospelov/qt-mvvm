// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_CUSTOMEDITOR_H
#define MVVM_EDITORS_CUSTOMEDITOR_H

#include "mvvm/core/variant.h"
#include "mvvm/viewmodel_export.h"
#include <QWidget>

namespace ModelView {

//! Base class for all custom variant editors.

class MVVM_VIEWMODEL_EXPORT CustomEditor : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QVariant value MEMBER m_data READ data WRITE setData NOTIFY dataChanged USER true)

public:
    explicit CustomEditor(QWidget* parent = nullptr);

    QVariant data() const;

    virtual bool is_persistent() const;

public slots:
    void setData(const QVariant& data);

signals:
    //! Emmits signal when data was changed in an editor.
    void dataChanged(QVariant value);

protected:
    void setDataIntern(const QVariant& data);
    //! Should update widget components from m_data, if necessary.
    virtual void update_components() = 0;
    QVariant m_data;
};

} // namespace ModelView

#endif // MVVM_EDITORS_CUSTOMEDITOR_H
