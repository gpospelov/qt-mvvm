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

#include <QListWidgetItem>
#include <QWidget>
#include <memory>
#include <QWidget>
#include <QProxyStyle>

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

namespace DataImport
{

// -------------------------------------------------
//! This is the tab widget side style
class CustomTabStyle : public QProxyStyle {
public:
    CustomTabStyle() : QProxyStyle("fusion"){};
  QSize sizeFromContents(ContentsType type, const QStyleOption* option,
                         const QSize& size, const QWidget* widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab) {
      s.transpose();
    }
    return s;
  }

  void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
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
class LineBlockWidget : public QWidget
{
    Q_OBJECT

public:
    LineBlockWidget(LineBlock* line_block = nullptr, QWidget* parent = nullptr);
    ~LineBlockWidget() = default;
    LineBlock* lineBlock() const;

signals:
    void parameterChanged();

private:
    void grabFromLineBlock();
    void setEnabled();
    void typeChanged();
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
    LineBlock* p_line_block;

    QTabWidget* p_tab_widget;
    SwitchSpace::Switch* p_active_checkbox;
    QComboBox* p_type_select;
    QSpinBox* p_line_start;
    QSpinBox* p_line_end;

    QComboBox* p_type_select;
    QComboBox* p_range_start;
    QComboBox* p_range_end;
    QComboBox* p_separators;

    QLineEdit* p_filter_name;
    QLineEdit* p_ignore_chars;
    QLineEdit* p_ignore_lines;

    QGridLayout* p_type_layout;
    QGridLayout* p_range_layout;
};

// -------------------------------------------------
//! This is the main dialog for the data loader
class ImportParameterWidget : public QWidget
{
    Q_OBJECT

public:
    ImportParameterWidget(ImportLogic* import_logic, QWidget* parent = nullptr);
    ~ImportParameterWidget() = default;

    void addLineBlock();
    void removeLineBlock();

signals:
    void parameterChanged();
    
private:
    void setLayout();
    void initialise();
    void connectAll();

private:
    ImportLogic* p_import_logic;

    std::vector<LineBlockWidget*> m_line_block_widgets;
    QListWidget* p_list_widget;
};
}

#endif // IMPORTPARAMETERWIDGET_H