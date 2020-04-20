// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#ifndef IMPORTPARAMETERWIDGET_H
#define IMPORTPARAMETERWIDGET_H

#include <memory>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QSpinBox;
class QColor;
QT_END_NAMESPACE

namespace ModelView
{
    class ColorEditor;
}

namespace DataImport
{

//! This is the main dialog for the data loader
class ImportParameterWidget : public QWidget
{
    Q_OBJECT

public:
    ImportParameterWidget(QWidget* parent = nullptr);
    ~ImportParameterWidget() = default;

    std::vector<bool> stringPresent() const;
    std::vector<int> stringLocation() const;
    std::vector<QColor> stringColor() const;

signals:
    void valuesChanged();

private:
    void checkValues(int start);
    void createWidgets();
    void setLayout();
    void setInitialState();
    void connectAll();

private:
    std::vector<QCheckBox*> m_checkboxes;
    std::vector<QSpinBox*> m_spinboxes;
    std::vector<ModelView::ColorEditor*> m_color_editors;
};
}

#endif // IMPORTPARAMETERWIDGET_H