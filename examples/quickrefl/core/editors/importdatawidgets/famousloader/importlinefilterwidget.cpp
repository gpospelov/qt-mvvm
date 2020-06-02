// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importlinefilterwidget.h"
#include "switch.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSizePolicy>
#include <QSpinBox>
#include <QTabWidget>
#include <QVBoxLayout>

#include <mvvm/editors/coloreditor.h>

namespace DataImportGui
{

// -------------------------------------------------
//! This is the constructor
LineFilterWidget::LineFilterWidget(DataImportLogic::LineFilter* line_filter, QWidget* parent)
    : QWidget(parent), p_line_filter(line_filter)
{
    createComponents();
    setLayout();
    initComponents();
    connectAll();
    setEnabled();
    grabFromLineFilter();
    connectSubcomponents();
}

//! Getter for the current lineblock
DataImportLogic::LineFilter* LineFilterWidget::lineFilter() const
{
    return p_line_filter;
}

//! Grab from the line block item
void LineFilterWidget::grabFromLineFilter()
{
    if (!p_line_filter)
        return;

    QList<QWidget*> object_list = this->findChildren<QWidget*>();
    foreach (QWidget* object, object_list) {
        object->blockSignals(true);
    }
    int start = p_line_filter->start();
    int end = p_line_filter->end();

    if (start + 1 == end) {
        p_range_start->setCurrentText(QString::fromStdString("At line"));
    } else {
        p_range_start->setCurrentText(QString::fromStdString("Between lines"));
    }

    if (end == -1) {
        p_range_end->setCurrentText(QString::fromStdString("and end of file."));
    } else {
        p_range_end->setCurrentText(QString::fromStdString("and"));
    }

    if (p_line_filter->active() != p_active_checkbox->isChecked()) {
        p_active_checkbox->setChecked(p_line_filter->active());
        p_active_checkbox->init(p_line_filter->active());
    }
    p_type_select->setCurrentText(QString::fromStdString(p_line_filter->type()));
    p_color_editor->setData(QColor(QString::fromStdString(p_line_filter->color())));
    p_line_start->setValue(p_line_filter->start());
    p_line_end->setValue(p_line_filter->end());
    p_separators->setCurrentText(QString::fromStdString(p_line_filter->separator()));
    p_filter_name->setText(QString::fromStdString(p_line_filter->name()));
    p_ignore_strings->setText(QString::fromStdString(p_line_filter->ignoreString()));

    setEnabled();
    typeVariation();
    startRangeChanged();
    endRangeChanged();

    foreach (QWidget* object, object_list) {
        object->blockSignals(false);
    }

    emit parameterChanged();
}

//! Create the subcomponents
void LineFilterWidget::createComponents()
{
    // Initialise all the widgets
    p_tab_widget = new QTabWidget(this);
    p_active_checkbox = new SwitchSpace::Switch(this);
    p_type_select = new QComboBox(this);
    p_line_start = new QSpinBox(this);
    p_line_end = new QSpinBox(this);
    p_color_editor = new ModelView::ColorEditor();
    p_range_start = new QComboBox(this);
    p_range_end = new QComboBox(this);
    p_separators = new QComboBox(this);
    p_filter_name = new QLineEdit(this);
    p_ignore_strings = new QLineEdit(this);
    p_ignore_lines = new QLineEdit(this);

    setSubwidgetStyles();
    setSubwidgetNames();
    setSubwidgetToolTips();
}

//! Set the style of the subwidgets
void LineFilterWidget::setSubwidgetStyles()
{
    p_style = std::make_unique<QProxyStyle>("fusion");
    p_type_select->setStyle(p_style.get());
    p_line_start->setStyle(p_style.get());
    p_line_end->setStyle(p_style.get());
    p_range_start->setStyle(p_style.get());
    p_range_end->setStyle(p_style.get());
    p_separators->setStyle(p_style.get());
    p_filter_name->setStyle(p_style.get());
    p_ignore_strings->setStyle(p_style.get());
    p_ignore_lines->setStyle(p_style.get());
}

//! Set the nam eof the ocmponents (moslty for testing)
void LineFilterWidget::setSubwidgetNames()
{
    p_type_select->setObjectName("line_filter_type_select");
    p_line_start->setObjectName("line_filter_line_start");
    p_line_end->setObjectName("line_filter_line_end");
    p_range_start->setObjectName("line_filter_range_start");
    p_range_end->setObjectName("line_filter_range_end");
    p_separators->setObjectName("line_filter_seprator_select");
    p_filter_name->setObjectName("line_filter_name");
    p_ignore_strings->setObjectName("line_filter_ignore_string");
    p_ignore_lines->setObjectName("line_filter_ignore_lines");
}

//! Set the tool tips of all the components
void LineFilterWidget::setSubwidgetToolTips()
{
    p_type_select->setToolTip("Select the type of this selection rule");
    p_active_checkbox->setToolTip("Turn this selection rule on or off");
    p_line_start->setToolTip("Select the starting line");
    p_line_end->setToolTip("Select the delimiter line");
    p_color_editor->setToolTip("Select the display color of this selection rul ein the text");
    p_range_start->setToolTip("Select the type of range wanted");
    p_range_end->setToolTip("Select the range type wanted");
    p_separators->setToolTip("Chose the wanted delimiter character");
    p_filter_name->setToolTip("Set a unique name for the selection rule");
    p_ignore_strings->setToolTip("Select the characters or strings wanted separated by comas");
    p_ignore_lines->setToolTip("Select the lines to ignore separated by comas");
}

//! Initalize the components
void LineFilterWidget::initComponents()
{
    p_tab_widget->setTabPosition(QTabWidget::West);
    p_tab_widget->tabBar()->setStyle(new CustomTabStyle());
    p_tab_widget->setStyle(p_style.get());
    p_tab_widget->setFixedHeight(p_tab_widget->widget(0)->sizeHint().height() + 10);
    p_tab_widget->setMinimumWidth(p_tab_widget->sizeHint().width());
    p_tab_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    p_color_editor->setContentsMargins(0, 0, 0, 0);
    p_color_editor->layout()->setContentsMargins(0, 0, 0, 0);
    p_color_editor->setData(QColor("blue"));
    p_color_editor->setAutoFillBackground(false);
    p_color_editor->layout()->takeAt(1);

    p_line_start->setMaximum(1e6);
    p_line_end->setMaximum(1e6);

    auto editor_pixmap = dynamic_cast<QLabel*>(p_color_editor->layout()->itemAt(0)->widget());
    if (editor_pixmap)
        editor_pixmap->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    editor_pixmap->setScaledContents(true);
    editor_pixmap->setFixedWidth(p_active_checkbox->sizeHint().width());

    p_filter_name->setFixedWidth(p_active_checkbox->sizeHint().width());
    p_filter_name->setFocusPolicy(Qt::StrongFocus);

    p_type_select->addItems(QStringList{"Header", "Units", "Data", "Comments", "Info"});
    p_range_start->addItems(QStringList{"Between lines", "At line"});
    p_range_end->addItems(QStringList{"and", "and end of file."});

    QStringList separators;
    if (p_line_filter) {
        auto separator_names = p_line_filter->separatorNames();
        for (auto& separator_name : separator_names) {
            separators << QString::fromStdString(separator_name);
        }
    }
    p_separators->addItems(separators);
}

//! Set the layout of the widget
void LineFilterWidget::setLayout()
{
    auto layout_item = new QHBoxLayout(this);

    auto sublayer_item = new QVBoxLayout();
    sublayer_item->addWidget(p_filter_name);
    sublayer_item->addWidget(p_active_checkbox);
    sublayer_item->addWidget(p_color_editor);

    layout_item->addLayout(sublayer_item);
    layout_item->addWidget(p_tab_widget);

    setTypeLayout();
    setRangeLayout();

    layout_item->setContentsMargins(5, 5, 5, 5);
    layout_item->setSpacing(5);
}

//! Set the layout of the widget
void LineFilterWidget::setTypeLayout()
{
    auto type_widget = new QWidget(p_tab_widget);
    p_type_layout = new QGridLayout(type_widget);

    p_type_layout->addWidget(new QLabel("Filter type:"), 0, 0);
    p_type_layout->addWidget(p_type_select, 0, 1);
    p_type_layout->addWidget(new QLabel("Separator:"), 1, 0);
    p_type_layout->addWidget(p_separators, 1, 1);
    p_type_layout->addWidget(new QLabel("Ignore strings:"), 2, 0);
    p_type_layout->addWidget(p_ignore_strings, 2, 1);

    for (int i = 0; i < p_type_layout->rowCount(); ++i) {
        auto label = dynamic_cast<QLabel*>(p_type_layout->itemAtPosition(i, 0)->widget());
        if (label)
            label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }

    p_type_layout->setContentsMargins(5, 5, 5, 5);
    p_type_layout->setHorizontalSpacing(5);
    p_type_layout->setVerticalSpacing(5);

    p_tab_widget->addTab(type_widget, "Type");
}

//! Set the layout of the widget
void LineFilterWidget::setRangeLayout()
{
    auto range_widget = new QWidget(p_tab_widget);
    p_range_layout = new QGridLayout(range_widget);

    p_range_layout->addWidget(p_range_start, 0, 0);
    p_range_layout->addWidget(p_line_start, 0, 1);
    p_range_layout->addWidget(p_range_end, 1, 0);
    p_range_layout->addWidget(p_line_end, 1, 1);
    p_range_layout->addWidget(new QLabel("Ignore following lines:"), 2, 0);
    p_range_layout->addWidget(p_ignore_lines, 2, 1);

    for (int i = 0; i < p_range_layout->rowCount(); ++i) {
        auto label = dynamic_cast<QLabel*>(p_range_layout->itemAtPosition(i, 0)->widget());
        if (label)
            label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }

    p_range_layout->setContentsMargins(5, 5, 5, 5);
    p_range_layout->setHorizontalSpacing(5);
    p_range_layout->setVerticalSpacing(5);

    p_tab_widget->addTab(range_widget, "Range");
}

//! Connect all the widgets of the layout
void LineFilterWidget::connectAll()
{
    connect(p_active_checkbox, &SwitchSpace::Switch::stateChanged, this,
            &LineFilterWidget::setEnabled);
    connect(p_type_select, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &LineFilterWidget::typeVariation);
    connect(p_range_start, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &LineFilterWidget::startRangeChanged);
    connect(p_range_end, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &LineFilterWidget::endRangeChanged);
}

//! Set enabled or disabled depending on the type
void LineFilterWidget::setEnabled()
{
    p_tab_widget->setEnabled(p_active_checkbox->isChecked());
    p_color_editor->setEnabled(p_active_checkbox->isChecked());
}

//! Widget logic when the type changed
void LineFilterWidget::typeVariation()
{
    bool visible = false;
    int current_index = p_type_select->currentIndex();
    (current_index < 3) ? (visible = true) : (visible = false);
    for (int i = 0; i < p_type_layout->columnCount(); ++i) {
        QWidget* widget = dynamic_cast<QWidget*>(p_type_layout->itemAtPosition(1, i)->widget());
        if (widget)
            widget->setVisible(visible);
        widget = dynamic_cast<QWidget*>(p_type_layout->itemAtPosition(2, i)->widget());
        if (widget)
            widget->setVisible(visible);
    }
}

//! Widget logic for the start range options
void LineFilterWidget::startRangeChanged()
{
    bool visible = false;
    (p_range_start->currentIndex() == 0) ? (visible = true) : (visible = false);
    for (int i = 0; i < p_range_layout->columnCount(); ++i) {
        QWidget* widget = dynamic_cast<QWidget*>(p_range_layout->itemAtPosition(1, i)->widget());
        if (widget)
            widget->setVisible(visible);
        widget = dynamic_cast<QWidget*>(p_range_layout->itemAtPosition(2, i)->widget());
        if (widget)
            widget->setVisible(visible);
    }
    endRangeChanged();
}

//! Widget logic for the end range options
void LineFilterWidget::endRangeChanged()
{
    bool visible = false;
    (p_range_end->isVisible() && p_range_end->currentIndex() == 0) ? (visible = true)
                                                                   : (visible = false);
    for (int i = 1; i < p_range_layout->columnCount(); ++i) {
        QWidget* widget = dynamic_cast<QWidget*>(p_range_layout->itemAtPosition(1, i)->widget());
        if (widget)
            widget->setVisible(visible);
    }
}

//! Connect all the present subcomponents to the dataChanged method
void LineFilterWidget::connectSubcomponents()
{
    QList<QWidget*> object_list = this->findChildren<QWidget*>();
    foreach (QWidget* object, object_list) {
        if (dynamic_cast<QComboBox*>(object))
            connect(dynamic_cast<QComboBox*>(object),
                    static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
                    &LineFilterWidget::dataChanged);
        if (dynamic_cast<QSpinBox*>(object))
            connect(dynamic_cast<QSpinBox*>(object),
                    static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
                    &LineFilterWidget::dataChanged);
        if (dynamic_cast<SwitchSpace::Switch*>(object))
            connect(dynamic_cast<SwitchSpace::Switch*>(object), &SwitchSpace::Switch::stateChanged,
                    this, &LineFilterWidget::dataChanged);
        if (dynamic_cast<ModelView::ColorEditor*>(object))
            connect(dynamic_cast<ModelView::ColorEditor*>(object),
                    &ModelView::ColorEditor::dataChanged, this, &LineFilterWidget::dataChanged);
        if (dynamic_cast<QLineEdit*>(object))
            connect(dynamic_cast<QLineEdit*>(object), &QLineEdit::editingFinished, this,
                    &LineFilterWidget::dataChanged);
    }
}

//! Submit the data change to the LineFilter element
void LineFilterWidget::dataChanged()
{
    if (!p_line_filter)
        return;

    if (p_filter_name->text().toStdString() != p_line_filter->name()) {
        emit nameChanged(p_filter_name->text().toStdString(), this);
        return;
    }

    if (p_type_select->currentText().toStdString() != p_line_filter->type()) {
        emit typeChanged(p_type_select->currentText().toStdString(), this);
        return;
    }

    if (p_line_start->value() >= p_line_end->value()) {
        p_line_end->blockSignals(true);
        p_line_end->setValue(p_line_start->value() + 1);
        p_line_end->blockSignals(false);
    }

    int start = 0;
    int end = 0;
    if (p_range_start->currentIndex() == 1) {
        start = p_line_start->value();
        end = start + 1;
    } else {
        start = p_line_start->value();
        if (p_range_end->currentIndex() == 1) {
            end = -1;
        } else {
            end = p_line_end->value();
        }
    }

    p_line_filter->setActive(p_active_checkbox->isChecked());
    p_line_filter->setSeparator(p_separators->currentText().toStdString());
    p_line_filter->setColor(p_color_editor->data().value<QColor>().name().toStdString());
    p_line_filter->setIgnoreString(p_ignore_strings->text().toStdString());
    p_line_filter->setStart(start);
    p_line_filter->setEnd(end);

    emit parameterChanged();
}

} // End of namespace DataImportGui
