#include "TreeWidget.h"

#include <QTreeView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QStandardItem>
#include <QRandomGenerator>
#include <QStandardItemModel>

TreeWidget::TreeWidget(QWidget *parent)
    :QWidget(parent)
{
    m_TreeView = new QTreeView(this);
    m_TreeModel = new QStandardItemModel(m_TreeView);
    m_TreeModel->setHorizontalHeaderLabels({"col1", "col2", "col3", "col4", "col5"});
    for (int i = 0; i < 8; ++i) {
        QStandardItem *parentItem = new QStandardItem(QString("Row %1").arg(i + 1));
        for (int j = 0; j < 5; ++j) {
            int value = QRandomGenerator::global()->bounded(51);
            QStandardItem *item = new QStandardItem(QString::number(value));
            parentItem->setChild(0, j, item);
        }
        m_TreeModel->appendRow(parentItem);
    }
    m_TreeView->setModel(m_TreeModel);
    m_TreeView->expandAll();

    m_UpWidget = new QWidget(this);
    QHBoxLayout *upLayout = new QHBoxLayout(m_UpWidget);
    upLayout->setContentsMargins(0, 0, 0, 0);
    m_UpButton_1 = new QPushButton(QString::fromUtf8("置零"), m_UpWidget);
    connect(m_UpButton_1, &QPushButton::clicked, this, &TreeWidget::onFillZeroButtonClicked);
    upLayout->addWidget(m_UpButton_1);
    m_UpButton_2 = new QPushButton(QString::fromUtf8("过滤单行"), m_UpWidget);
    connect(m_UpButton_2, &QPushButton::clicked, this, &TreeWidget::onFilterOddButtonClicked);
    upLayout->addWidget(m_UpButton_2);
    QSpacerItem* spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding);
    upLayout->addItem(spacerItem);

    QVBoxLayout *aLayout = new QVBoxLayout(this);
    aLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(aLayout);

    aLayout->addWidget(m_UpWidget, 1);
    aLayout->addWidget(m_TreeView, 10);
}

void TreeWidget::onFillZeroButtonClicked(bool on) {
    Q_UNUSED(on)
    for (int i = 0; i < m_TreeModel->rowCount(); ++i) {
        QStandardItem *parentItem = m_TreeModel->item(i);
        for (int j = 0; j < parentItem->columnCount(); ++j) {
            QStandardItem *item = parentItem->child(0, j);
            if (item) {
                int value = item->text().toInt();
                if (value <= 25) {
                    item->setText("0");
                }
            }
        }
    }
}

void TreeWidget::onFilterOddButtonClicked(bool on) {
    Q_UNUSED(on)
    for (int i = m_TreeModel->rowCount() - 1; i >= 0; --i) {
        if ((i + 1) % 2 == 0) { // 偶数行号
            m_TreeModel->item(i - 1)->setText(QString("Row %1").arg(i / 2 + 1));
            m_TreeModel->removeRow(i);
        }
    }
}
