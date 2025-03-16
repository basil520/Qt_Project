#pragma once

#include <QWidget>

class QTreeView;
class QPushButton;
class QStandardItemModel;

class TreeWidget final: public QWidget{
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr);
    ~TreeWidget() override = default;
private Q_SLOTS:
    void onFillZeroButtonClicked(bool);
    void onFilterOddButtonClicked(bool);
private:
    QWidget* m_UpWidget{nullptr};
    QPushButton* m_UpButton_1{nullptr};
    QPushButton* m_UpButton_2{nullptr};
    QTreeView* m_TreeView{nullptr};
    QStandardItemModel* m_TreeModel{nullptr};
};