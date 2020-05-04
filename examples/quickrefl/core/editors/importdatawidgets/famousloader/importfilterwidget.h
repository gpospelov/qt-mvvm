// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTFILTERWIDGET_H
#define IMPORTFILTERWIDGET_H

#include <QListWidgetItem>
#include <QProxyStyle>
#include <QWidget>
#include <memory>

#include "importlogic.h"

QT_BEGIN_NAMESPACE
class QSpinBox;
class QColor;
class QLabel;
class QComboBox;
class QLineEdit;
class QListWidget;
class QHBoxLayout;
class QLineEdit;
class QTabWidget;
class QGridLayout;
QT_END_NAMESPACE

namespace ModelView
{
class ColorEditor;
}

namespace SwitchSpace
{
class Switch;
}

namespace DataImportGui
{

// -------------------------------------------------
//! This is the tab widget side style
class CustomTabStyle : public QProxyStyle
{
public:
    CustomTabStyle() : QProxyStyle("fusion"){};
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size,
                           const QWidget* widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
        }
        return s;
    }

    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter,
                     const QWidget* widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
                QStyleOptionTab opt(*tab);
                opt.shape = QTabBar::RoundedNorth;
                QProxyStyle::drawControl(element, &opt, painter, widget);
                return;
            }
        }
        QProxyStyle::drawControl(element, option, painter, widget);
    }
};

// -------------------------------------------------
//! This is the main dialog for the data loader
class LineFilterWidget : public QWidget
{
    Q_OBJECT

public:
    LineFilterWidget(DataImportLogic::LineFilter* line_block = nullptr, QWidget* parent = nullptr);
    ~LineFilterWidget() = default;
    DataImportLogic::LineFilter* lineBlock() const;
    void grabFromLineFilter();

signals:
    void parameterChanged();
    void nameChanged(std::string name, LineFilterWidget*);
    void typeChanged(std::string type, LineFilterWidget*);

private:
    void setEnabled();
    void typeVariation();
    void startRangeChanged();
    void endRangeChanged();
    void connectSubcomponents();

    void createComponents();
    void initComponents();
    void setLayout();
    void setTypeLayout();
    void setRangeLayout();
    void connectAll();

    void dataChanged();

private:
    DataImportLogic::LineFilter* p_line_block;

    QTabWidget* p_tab_widget;
    SwitchSpace::Switch* p_active_checkbox;
    ModelView::ColorEditor* p_color_editor;
    QSpinBox* p_line_start;
    QSpinBox* p_line_end;

    QComboBox* p_type_select;
    QComboBox* p_range_start;
    QComboBox* p_range_end;
    QComboBox* p_separators;

    QLineEdit* p_filter_name;
    QLineEdit* p_ignore_strings;
    QLineEdit* p_ignore_lines;

    QGridLayout* p_type_layout;
    QGridLayout* p_range_layout;
};

// -------------------------------------------------
//! This is the main dialog for the data loader
class ImportFilterWidget : public QWidget
{
    Q_OBJECT

public:
    ImportFilterWidget(DataImportLogic::ImportLogic* import_logic, QWidget* parent = nullptr);
    ~ImportFilterWidget() = default;

    void addLineFilter();
    void removeLineFilter();

signals:
    void parameterChanged();
    void namesChanged();
    void typesChanged();

private slots:
    void processNameChanged(std::string name, LineFilterWidget* widget);
    void processTypeChanged(std::string type, LineFilterWidget* widget);

private:
    void setLayout();
    void initialise();
    void connectAll();
    void resetFromLineFilters() const;

private:
    DataImportLogic::ImportLogic* p_import_logic;

    std::vector<LineFilterWidget*> m_line_block_widgets;
    QListWidget* p_list_widget;
};

} // End of namespace DataImportGui

#endif // IMPORTFILTERWIDGET_H