#include "tableviewdelegate.h"
#include "customtableview.h"
#include "detailsbutton.h"
#include "detailswidget.h"
#include "treeitem.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QSpinBox>

namespace
{
class DisabledFadingPanel : public Utils::FadingPanel
{
public:
    DisabledFadingPanel(QWidget* parent = nullptr) : Utils::FadingPanel(parent) {}
    void fadeTo(qreal) override {}
    void setOpacity(qreal) override {}
};

void setSpinBoxToDetailsWidget(Utils::DetailsWidget* details_widget, const QModelIndex&)
{
    DisabledFadingPanel* fading_widget = new DisabledFadingPanel(details_widget);
    auto layout_h = new QHBoxLayout();
    layout_h->addWidget(new QLabel("Number of repetitions:"));

    auto spinbox = new QSpinBox();
    spinbox->setValue(1);
    layout_h->addWidget(spinbox);

    fading_widget->setLayout(layout_h);
    details_widget->setToolWidget(fading_widget);
}

Utils::DetailsWidget* createDetailsWidget(QWidget* parent, const QModelIndex& index)
{
    auto result = new Utils::DetailsWidget(parent);
    setSpinBoxToDetailsWidget(result, index);

    auto internal_table = new CustomTableView();
    internal_table->setItemDelegate(new TableViewDelegate(internal_table));
    internal_table->setModel(const_cast<QAbstractItemModel*>(index.model()));
    internal_table->setRootIndex(index);
    internal_table->updateRepresentation();

    internal_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    internal_table->horizontalHeader()->setVisible(false);

    QString _CustomStyle = QString("QTableView::item {"
                                   "background-color: rgba(135, 206, 235);"
                                   "}");
    internal_table->setStyleSheet(_CustomStyle);

    result->setWidget(internal_table);
    return result;
}
} // namespace

TableViewDelegate::TableViewDelegate(CustomTableView* parent)
    : QStyledItemDelegate(parent), m_parent_table(parent)
{
}

QWidget* TableViewDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    if (index.isValid() && index.column() == 0 && index.data(Qt::UserRole) == TreeItem::Assembly) {
        auto result = createDetailsWidget(parent, index);
        result->setSummaryText("Assembly");
        result->setSummaryFontBold(true);

        // TODO: find a better way to notify the table view about the change in editor's size
        connect(result, &Utils::DetailsWidget::expanded, m_parent_table,
                [this](bool) { m_parent_table->resizeRowsToContents(); });
        return result;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}
