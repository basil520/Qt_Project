#pragma once

#include <QWidget>

class QTableView;
class QPushButton;
class QStandardItemModel;
class MySortFilterProxyModel;

class TableWidget final: public QWidget{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = nullptr);
    ~TableWidget() override = default;
private Q_SLOTS:
    void onUpButtonClicked(bool);
    void onSelectedSortColumnChanged(int);
private:
    uint8_t m_SortOrder{0};
    int m_SortedColumnIndex{0};
    QWidget* m_UpWidget{nullptr};
    QPushButton* m_UpButton{nullptr};
    QTableView* m_TableView{nullptr};
    QStandardItemModel* m_TableModel{nullptr};
    MySortFilterProxyModel* m_SortProxyModel{nullptr};
};

