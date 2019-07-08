#ifndef MATERIALTABLEWIDGET_H
#define MATERIALTABLEWIDGET_H

#include "MaterialViewController.h"
#include "mvvm_global.h"
#include <QWidget>
#include <memory>

class QTableView;
class MaterialModel;
class QStyledItemDelegate;

/*!
@class MaterialTableWidget
@brief Shows content of material container in table-like view.
*/

class CORE_EXPORT MaterialTableWidget : public QWidget
{
public:
    explicit MaterialTableWidget(MaterialModel* material_model, QWidget* parent = nullptr);
    ~MaterialTableWidget() override;

private:
    MaterialViewController m_controller;
    std::unique_ptr<QStyledItemDelegate> m_delegate;
    QTableView* m_material_table;
};

#endif // MATERIALTABLEWIDGET_H
