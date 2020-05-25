// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importfilterwidget.h"
#include "importlinefilterwidget.h"
#include "resources.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSettings>
#include <QStyle>
#include <QToolButton>
#include <QVBoxLayout>

namespace DataImportGui
{

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
    p_list_widget->setObjectName("filter_list_widget");
    p_list_widget->setSpacing(0);
    p_list_widget->resize(LineFilterWidget().sizeHint().width() + 10, p_list_widget->height());
    p_list_widget->setAlternatingRowColors(true);
    p_list_widget->setDragDropMode(QAbstractItemView::InternalMove);
    p_list_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    p_list_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    p_list_widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    // Set up the buttons
    auto add_button = new QToolButton(this);
    add_button->setObjectName("add_filter_button");
    add_button->setIcon(QIcon(":/icons/playlist-plus.svg"));
    add_button->setToolTip("Add a seletion rule:\nSelection rules are meant to define the text "
                           "regions and their type.\n The order of these is relevant.");

    auto remove_button = new QToolButton(this);
    remove_button->setObjectName("remove_filter_button");
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

    line_filter =
        dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(items[0]))->lineFilter();
    line_filter->setType("Header");
    line_filter->setActive(true);
    line_filter->setStart(2);
    line_filter->setEnd(3);
    line_filter->setSeparator("Space ( )");
    line_filter->setColor("red");

    line_filter =
        dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(items[1]))->lineFilter();
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
            dynamic_cast<LineFilterWidget*>(p_list_widget->itemWidget(item))->lineFilter());
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
                    ->lineFilter();

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
        auto line_filter = widget->lineFilter();

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
        filter_order.push_back(widget->lineFilter());
    }
    p_import_logic->setLineFilterOrder(filter_order);
    emit parameterChanged();
}

//! This manages the naming by allowing only dofferent names and sends it upstream if changed
void ImportFilterWidget::processNameChanged(std::string name, LineFilterWidget* widget)
{
    if (!p_import_logic->nameInFilters(name)) {
        widget->lineFilter()->setName(name);
        emit namesChanged();
    }
    widget->grabFromLineFilter();
}

//! This manages the types as only one data type and one header type is allowed
void ImportFilterWidget::processTypeChanged(std::string type, LineFilterWidget* widget)
{
    auto line_filter = p_import_logic->typeInFilters(type);
    if (!line_filter || type == "Comments" || type == "Info") {
        widget->lineFilter()->setType(type);
    } else {
        line_filter->setType("Comments");
        widget->lineFilter()->setType(type);
    }
    resetFromLineFilters();
    emit typesChanged();
}

} // End of namespace DataImportGui
