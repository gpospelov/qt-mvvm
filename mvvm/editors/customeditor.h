// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef CUSTOMEDITOR_H
#define CUSTOMEDITOR_H

#include "global.h"
#include <QWidget>
#include <QVariant>

class QStandardItem;

namespace ModelView
{

class SessionModel;
class SessionItem;
class ViewItem;

//! Base class for all custom variant editors.

class CORE_EXPORT CustomEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CustomEditor(QWidget* parent = nullptr);

    QVariant data() const;

    virtual bool is_persistent() const;

public slots:
    void setData(const QVariant& data);

signals:
    //! Emmits signal when data was changed in an editor.
    void dataChanged();

protected:
    void setDataIntern(const QVariant& data);
    virtual void update_components() = 0;
    QVariant m_data;
};

} // namespace ModelView

#endif // CUSTOMEDITOR_H
