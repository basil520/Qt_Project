#include "TableWidget.h"

#include <QTableView>
#include <QSpacerItem>
#include <QPushButton>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QRandomGenerator>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

class MySortFilterProxyModel final : public QSortFilterProxyModel {
public:
    explicit MySortFilterProxyModel(QObject *parent = nullptr) {

    }
    ~MySortFilterProxyModel() override = default;
protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override {
        int32_t leftData = left.data(Qt::DisplayRole).toInt();
        int32_t rightData = right.data(Qt::DisplayRole).toInt();
        return leftData < rightData;
    }
};

TableWidget::TableWidget(QWidget *parent)
    :QWidget(parent)
{
    m_TableView = new QTableView(this);
    m_TableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_TableView->setSelectionBehavior(QAbstractItemView::SelectColumns);
    m_TableView->verticalHeader()->setVisible(false);
    m_TableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_TableModel = new QStandardItemModel(m_TableView);
    m_TableModel->setHorizontalHeaderLabels({"col1", "col2", "col3", "col4", "col5"});
    for(int i = 0; i < 8; i ++) {
        for(int j = 0; j < 5; j ++) {
            QStandardItem *item = new QStandardItem(QString("%1").arg(QRandomGenerator::global()->bounded(1, 1000)));
            m_TableModel->setItem(i , j, item);
        }
    }
    m_SortProxyModel = new MySortFilterProxyModel(m_TableView);
    m_SortProxyModel->setSourceModel(m_TableModel);
    m_TableView->setModel(m_SortProxyModel);

    connect(m_TableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &TableWidget::onSelectedSortColumnChanged);

    m_UpWidget = new QWidget(this);
    QHBoxLayout *upLayout = new QHBoxLayout(m_UpWidget);
    upLayout->setContentsMargins(0, 0, 0, 0);
    m_UpButton = new QPushButton(QString("sort by column: %1").arg(m_SortedColumnIndex + 1), m_UpButton);
    connect(m_UpButton, &QPushButton::clicked, this, &TableWidget::onUpButtonClicked);
    upLayout->addWidget(m_UpButton);
    QSpacerItem* spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    upLayout->addItem(spacerItem);

    QVBoxLayout *aLayout = new QVBoxLayout(this);
    aLayout->setContentsMargins(0, 0, 0, 0);
    aLayout->addWidget(m_UpWidget, 1);
    aLayout->addWidget(m_TableView, 10);
}

void TableWidget::onUpButtonClicked(bool on) {
    Q_UNUSED(on);
    m_SortProxyModel->sort(m_SortedColumnIndex, static_cast<Qt::SortOrder>(m_SortOrder = !m_SortOrder));
}

void TableWidget::onSelectedSortColumnChanged(int index) {
    m_SortedColumnIndex = index;
    m_UpButton->setText(QString("sort by column: %1").arg(m_SortedColumnIndex + 1));
}
