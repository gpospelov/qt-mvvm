// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#ifndef IMPORTFILEWIDGET_H
#define IMPORTFILEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QListView;
class QStringListModel;
QT_END_NAMESPACE

namespace DataImport
{

//! This is the main dialog for the data loader
class ImportFileWidget : public QWidget
{
    Q_OBJECT
    
public:
    ImportFileWidget(QWidget* parent = nullptr);
    ~ImportFileWidget() = default;

signals:
    void filesChanged(std::vector<std::string> files);

private:
    void createWidgets();
    void addFiles();
    void resetFiles();
    std::vector<std::string> currentFiles() const;
private:
    QListView* p_list_view{nullptr};
    QStringListModel* p_list_model{nullptr};

};
}

#endif // IMPORTFILEWIDGET_H