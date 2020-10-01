// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

// ----------------------------------------------------------------------------
// https://stackoverflow.com/questions/8422760/combobox-of-checkboxes
// https://stackoverflow.com/questions/21186779/catch-mouse-button-pressed-signal-from-qcombobox-popup-menu
// https://gist.github.com/mistic100/c3b7f3eabc65309687153fe3e0a9a720
// ----------------------------------------------------------------------------

#include <QAbstractItemView>
#include <QComboBox>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QStandardItem>
#include <mvvm/editors/customeventfilters.h>
#include <mvvm/model/comboproperty.h>
#include <mvvm/editors/selectablecombobox.h>
#include <mvvm/utils/containerutils.h>

using namespace ModelView;

//! Provides custom style delegate for QComboBox to allow checkboxes.

class QCheckListStyledItemDelegate : public QStyledItemDelegate
{
public:
    QCheckListStyledItemDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const
    {
        auto styleOption = const_cast<QStyleOptionViewItem&>(option);
        styleOption.showDecorationSelected = false;
        QStyledItemDelegate::paint(painter, styleOption, index);
    }
};

// ----------------------------------------------------------------------------

SelectableComboBox::SelectableComboBox(QWidget* parent)
    : CustomEditor(parent), m_box(new QComboBox), m_wheel_event_filter(new WheelEventFilter(this)),
      m_model(new QStandardItemModel(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_box->installEventFilter(m_wheel_event_filter);
    m_box->view()->viewport()->installEventFilter(this);

    // Editable mode will be used to have None/Multiple labels on top
    m_box->setEditable(true);
    m_box->lineEdit()->setReadOnly(true);
    m_box->lineEdit()->installEventFilter(this);
    connect(m_box->lineEdit(), &QLineEdit::selectionChanged, m_box->lineEdit(),
            &QLineEdit::deselect);

    // transforms ordinary combo box into check list
    m_box->setItemDelegate(new QCheckListStyledItemDelegate(this));
    m_box->setModel(m_model);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);
    setConnected(true);
}

QSize SelectableComboBox::sizeHint() const
{
    return m_box->sizeHint();
}

QSize SelectableComboBox::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

//! Propagate check state from the model to ComboProperty.

void SelectableComboBox::onModelDataChanged(const QModelIndex& topLeft, const QModelIndex&,
                                                  const QVector<int>&)
{
    // on Qt 5.9 roles remains empty for checked state. It will stop working if uncomment.
    //    if (!roles.contains(Qt::CheckStateRole))
    //        return;

    auto item = m_model->itemFromIndex(topLeft);
    if (!item)
        return;

    ComboProperty comboProperty = m_data.value<ComboProperty>();
    auto state = item->checkState() == Qt::Checked ? true : false;
    comboProperty.setSelected(topLeft.row(), state);

    updateBoxLabel();
//    setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
}

//! Processes press event in QComboBox's underlying list view.

void SelectableComboBox::onClickedList(const QModelIndex& index)
{
    if (auto item = m_model->itemFromIndex(index)) {
        auto state = item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked;
        item->setCheckState(state);
    }
}

//! Handles mouse clicks on QComboBox elements.

bool SelectableComboBox::eventFilter(QObject* obj, QEvent* event)
{
    if (isClickToSelect(obj, event)) {
        // Handles mouse clicks on QListView when it is expanded from QComboBox
        // 1) Prevents list from closing while selecting items.
        // 2) Correctly calculates underlying model index when mouse is over check box style
        // element.
        const auto mouseEvent = static_cast<const QMouseEvent*>(event);
        auto index = m_box->view()->indexAt(mouseEvent->pos());
        onClickedList(index);
        return true;

    } else if (isClickToExpand(obj, event)) {
        // Expands box when clicking on None/Multiple label
        m_box->showPopup();
        return true;

    } else {
        // Propagate to the parent class.
        return QObject::eventFilter(obj, event);
    }
}

void SelectableComboBox::update_components()
{
    if (!m_data.canConvert<ComboProperty>())
        return;

    ComboProperty property = m_data.value<ComboProperty>();

    setConnected(false);
    m_model->clear();

    auto labels = property.values();
    auto selectedIndices = property.selectedIndices();

    for (size_t i = 0; i < labels.size(); ++i) {
        auto item = new QStandardItem(QString::fromStdString(labels[i]));
        m_model->invisibleRootItem()->appendRow(item);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setCheckable(true);

        auto state = Utils::Contains(selectedIndices, i) ? Qt::Checked : Qt::Unchecked;
        item->setData(state, Qt::CheckStateRole);
    }

    setConnected(true);
    updateBoxLabel();
}

void SelectableComboBox::setConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_model, &QStandardItemModel::dataChanged, this,
                &SelectableComboBox::onModelDataChanged);
    } else {
        disconnect(m_model, &QStandardItemModel::dataChanged, this,
                   &SelectableComboBox::onModelDataChanged);
    }
}

//! Update text on QComboBox with the label provided by combo property.

void SelectableComboBox::updateBoxLabel()
{
    ComboProperty combo = m_data.value<ComboProperty>();
    m_box->setCurrentText(QString::fromStdString(combo.label()));
}

bool SelectableComboBox::isClickToSelect(QObject* obj, QEvent* event) const
{
    return obj == m_box->view()->viewport() && event->type() == QEvent::MouseButtonRelease;
}

bool SelectableComboBox::isClickToExpand(QObject* obj, QEvent* event) const
{
    return obj == m_box->lineEdit() && event->type() == QEvent::MouseButtonRelease;
}
