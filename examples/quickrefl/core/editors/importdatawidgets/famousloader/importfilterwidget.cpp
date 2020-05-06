// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importfilterwidget.h"
#include "styleutils.h"
#include "switch.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QSizePolicy>
#include <QSpinBox>
#include <QTabWidget>
#include <QToolButton>
#include <QVBoxLayout>

#include <mvvm/editors/coloreditor.h>
#include <mvvm/editors/styleutils.h>

#include "resources.h"
#include <iostream>

namespace DataImportGui
{

// -------------------------------------------------
//! This is the constructor
LineFilterWidget::LineFilterWidget(DataImportLogic::LineFilter* line_filter, QWidget* parent)
    : QWidget(parent), p_line_filter(line_filter)
{
    createComponents();
    setToolTips();
    setLayout();
    initComponents();
    connectAll();
    setEnabled();
    grabFromLineFilter();
    connectSubcomponents();
}

//! Getter for the current lineblock
DataImportLogic::LineFilter* LineFilterWidget::lineBlock() const
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

    // Set the coherent fusion style for the subcmponents
    p_type_select->setStyle(new QProxyStyle("fusion"));
    p_line_start->setStyle(new QProxyStyle("fusion"));
    p_line_end->setStyle(new QProxyStyle("fusion"));
    p_range_start->setStyle(new QProxyStyle("fusion"));
    p_range_end->setStyle(new QProxyStyle("fusion"));
    p_separators->setStyle(new QProxyStyle("fusion"));
    p_filter_name->setStyle(new QProxyStyle("fusion"));
    p_ignore_strings->setStyle(new QProxyStyle("fusion"));
    p_ignore_lines->setStyle(new QProxyStyle("fusion"));
}

//! Set the tool tips of all the components
void LineFilterWidget::setToolTips()
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
    p_tab_widget->setStyle(new QProxyStyle("fusion"));
    p_tab_widget->setFixedHeight(p_tab_widget->widget(0)->sizeHint().height() + 10);
    p_tab_widget->setMinimumWidth(p_tab_widget->sizeHint().width());
    p_tab_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    p_color_editor->setContentsMargins(0, 0, 0, 0);
    p_color_editor->layout()->setContentsMargins(0, 0, 0, 0);
    p_color_editor->setData(QColor("blue"));
    p_color_editor->setAutoFillBackground(false);
    p_color_editor->layout()->takeAt(1);

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

// -------------------------------------------------
//! This is the constructor
ImportFilterWidget::ImportFilterWidget(DataImportLogic::ImportLogic* import_logic, QWidget* parent)
    : QWidget(parent), p_import_logic(import_logic)
{
    setLayout();
}

//! Set all the layouts and positioning of the items
void ImportFilterWidget::setLayout()
{
    // Set up the QListWidget
    p_list_widget = new QListWidget(this);
    p_list_widget->setSpacing(0);
    p_list_widget->resize(LineFilterWidget().sizeHint().width() + 10, p_list_widget->height());
    p_list_widget->setAlternatingRowColors(true);
    p_list_widget->setDragDropMode(QAbstractItemView::InternalMove);
    p_list_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p_list_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    p_list_widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    // Set up the buttons
    auto add_button = new QToolButton(this);
    add_button->setIcon(QIcon(":/icons/playlist-plus.svg"));
    add_button->setToolTip("Add a seletion rule:\nSelection rules are meant to define the text "
                           "regions and their type.\n The order of these is relevant.");

    auto remove_button = new QToolButton(this);
    remove_button->setIcon(QIcon(":/icons/playlist-remove.svg"));
    remove_button->setToolTip("Remove the selected selection rule.");

    // Set the layout
    auto widget_layout = new QHBoxLayout(this);
    auto side_layout = new QVBoxLayout();
    side_layout->addWidget(add_button);
    side_layout->addWidget(remove_button);
    side_layout->addStretch();
    widget_layout->addWidget(p_list_widget);
    widget_layout->addLayout(side_layout);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    // Connect the buttons
    connect(add_button, &QToolButton::clicked, this, &ImportFilterWidget::addLineFilter);
    connect(remove_button, &QToolButton::clicked, this, &ImportFilterWidget::removeLineFilter);
    connect(p_list_widget->model(), &QAbstractItemModel::rowsMoved, this,
            &ImportFilterWidget::handleInternalMoveEvent);
}

//! Initial display
void ImportFilterWidget::initialise()
{
    for (int i = 0; i < 2; ++i) {
        addLineFilter();
    }

    DataImportLogic::LineFilter* line_filter;
    QList<QListWidgetItem*> items = p_list_widget->findItems("*", Qt::MatchWildcard);

    line_filter = dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(items[0]))->lineBlock();
    line_filter->setType("Header");
    line_filter->setActive(true);
    line_filter->setStart(2);
    line_filter->setEnd(3);
    line_filter->setSeparator("Space ( )");
    line_filter->setColor("red");

    line_filter = dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(items[1]))->lineBlock();
    line_filter->setType("Data");
    line_filter->setActive(true);
    line_filter->setStart(3);
    line_filter->setEnd(-1);
    line_filter->setSeparator("Space ( )");
    line_filter->setColor("blue");

    resetFromLineFilters();
}

//! Add a line block with the according line block object in the ImportLogic
void ImportFilterWidget::addLineFilter()
{
    auto line_filter =
        p_import_logic->addLineFilter("Filter " + std::to_string(p_list_widget->count()));

    line_filter->setType("Comments");
    line_filter->setActive(true);
    line_filter->setStart(0);
    line_filter->setEnd(1);
    line_filter->setSeparator("Space ( )");
    line_filter->setColor("green");

    auto temp_widget = new LineFilterWidget(line_filter, p_list_widget);
    auto temp_item = new QListWidgetItem();
    temp_item->setSizeHint(temp_widget->sizeHint());
    p_list_widget->addItem(temp_item);
    p_list_widget->setItemWidget(temp_item, temp_widget);
    p_list_widget->setMinimumWidth(temp_widget->sizeHint().width()
                                   + qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent));

    connect(temp_widget, &LineFilterWidget::parameterChanged,
            [this]() { emit parameterChanged(); });

    connect(temp_widget, &LineFilterWidget::nameChanged, this,
            &ImportFilterWidget::processNameChanged);

    connect(temp_widget, &LineFilterWidget::typeChanged, this,
            &ImportFilterWidget::processTypeChanged);

    emit parameterChanged();
}

//! Remove the current line block with the according line block object in the ImportLogic
void ImportFilterWidget::removeLineFilter()
{
    QList<QListWidgetItem*> items = p_list_widget->selectedItems();
    foreach (QListWidgetItem* item, items) {
        p_import_logic->removeLineFilter(
            dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(item))->lineBlock());
        delete p_list_widget->takeItem(p_list_widget->row(item));
    }
}

//! Read the settings froma QSetting structure
void ImportFilterWidget::readSettings(QSettings& settings)
{
    settings.beginGroup("Filters");
    if (settings.childGroups().count() != 0) {
        for (auto group_name : settings.childGroups()) {
            addLineFilter();
            auto line_filter =
                dynamic_cast<LineFilterWidget*>(
                    p_list_widget->itemWidget(p_list_widget->item(p_list_widget->count() - 1)))
                    ->lineBlock();

            settings.beginGroup(group_name);
            line_filter->setName(settings.value("Name", "").toString().toStdString());
            line_filter->setType(settings.value("Type", "Comments").toString().toStdString());
            line_filter->setActive(settings.value("Active", true).toBool());
            line_filter->setStart(settings.value("Start", 0).toInt());
            line_filter->setEnd(settings.value("End", 1).toInt());
            line_filter->setSeparator(
                settings.value("Separator", "Space ( )").toString().toStdString());
            line_filter->setColor(settings.value("Color", "black").toString().toStdString());
            line_filter->setIgnoreString(
                settings.value("IgnoreString", "").toString().toStdString());
            settings.endGroup();
        }
        resetFromLineFilters();
    } else {
        initialise();
    }
    settings.endGroup();
}

//! Write the settings from a QSetting structure
void ImportFilterWidget::writeSettings(QSettings& settings)
{
    settings.beginGroup("Filters");
    settings.remove("");
    settings.endGroup();

    settings.beginGroup("Filters");
    for (int row = 0; row < p_list_widget->count(); row++) {
        auto item = p_list_widget->item(row);
        auto widget = dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(item));
        auto line_filter = widget->lineBlock();

        settings.beginGroup(QString::number(row));
        settings.setValue("Name", QString::fromStdString(line_filter->name()));
        settings.setValue("Type", QString::fromStdString(line_filter->type()));
        settings.setValue("Active", line_filter->active());
        settings.setValue("Start", line_filter->start());
        settings.setValue("End", line_filter->end());
        settings.setValue("Separator", QString::fromStdString(line_filter->separator()));
        settings.setValue("Color", QString::fromStdString(line_filter->color()));
        settings.setValue("IgnoreString", QString::fromStdString(line_filter->ignoreString()));
        settings.endGroup();
    }
    settings.endGroup();
}

//! Reset all the info in the linblockwidgets from the linblock items
void ImportFilterWidget::resetFromLineFilters() const
{
    QList<QListWidgetItem*> items = p_list_widget->findItems("*", Qt::MatchWildcard);
    foreach (QListWidgetItem* item, items) {
        dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(item))->grabFromLineFilter();
    }
}

//! Reset all the info in the linblockwidgets from the linblock items
void ImportFilterWidget::handleInternalMoveEvent()
{
    std::vector<DataImportLogic::LineFilter*> filter_order;
    for (int row = 0; row < p_list_widget->count(); row++) {
        auto item = p_list_widget->item(row);
        auto widget = dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(item));
        filter_order.push_back(widget->lineBlock());
    }
    p_import_logic->setLineFilterOrder(filter_order);
    emit parameterChanged();
}

//! This manages the naming by allowing only dofferent names and sends it upstream if changed
void ImportFilterWidget::processNameChanged(std::string name, LineFilterWidget* widget)
{
    if (!p_import_logic->nameInBlocks(name)) {
        widget->lineBlock()->setName(name);
        emit namesChanged();
    }
    widget->grabFromLineFilter();
}

//! This manages the types as only one data type and one header type is allowed
void ImportFilterWidget::processTypeChanged(std::string type, LineFilterWidget* widget)
{
    auto line_filter = p_import_logic->typeInBlocks(type);
    if (!line_filter || type == "Comments" || type == "Info") {
        widget->lineBlock()->setType(type);
    } else {
        line_filter->setType("Comments");
        widget->lineBlock()->setType(type);
    }
    resetFromLineFilters();
    emit typesChanged();
}

} // End of namespace DataImportGui
