#include "MainWindow.h"
#include "DDSTextWidget.h"
#include "TableWidget.h"
#include "TreeWidget.h"
#include "MyWidget.h"

#include "IDL/IDL_TypeSupport.h"

#include <QLabel>
#include <QDebug>
#include <QTabBar>
#include <QWidget>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    resize(800,600);
    setWindowTitle(QString::fromUtf8("界面程序-（郭敏）-2025/3/16"));
    setWindowIcon(QIcon(":/images/images/WindowIcon.webp"));

    m_MenuBar = new QMenuBar(this);
    QMenu* fileMenu = new QMenu(QString::fromUtf8("文件"), m_MenuBar);
    m_MenuBar->addMenu(fileMenu);

    QMenu* viewMenu = new QMenu(QString::fromUtf8("视图"), m_MenuBar);
    m_MenuBar->addMenu(viewMenu);
    QAction* openPageAction = new QAction(QString::fromUtf8("new page"), viewMenu);
    connect(openPageAction, &QAction::triggered, this, &MainWindow::onNewPageActionTriggered);
    viewMenu->addAction(openPageAction);

    QMenu* settingMenu = new QMenu(QString::fromUtf8("设置"), m_MenuBar);
    m_MenuBar->addMenu(settingMenu);

    QMenu* helpMenu = new QMenu(QString::fromUtf8("帮助"), m_MenuBar);
    m_MenuBar->addMenu(helpMenu);

    setMenuBar(m_MenuBar);

    m_ToolBar = new QToolBar(this);
    QAction *outputAction_1 = new QAction(QIcon(":/images/images/a.png"), "1");
    QAction *outputAction_2 = new QAction(QIcon(":/images/images/b.png"), "2");
    QAction *outputAction_3 = new QAction(QIcon(":/images/images/c.png"),"3");
    QAction *outputAction_4 = new QAction(QIcon(":/images/images/d.png"), "4");
    QAction *outputAction_5 = new QAction(QIcon(":/images/images/e.png"), "5");

    m_ToolBar->addAction(outputAction_1);
    m_ToolBar->addAction(outputAction_2);
    m_ToolBar->addAction(outputAction_3);
    m_ToolBar->addAction(outputAction_4);
    m_ToolBar->addAction(outputAction_5);

    connect(outputAction_1, &QAction::triggered, this, &MainWindow::onOutputActionTriggered);
    connect(outputAction_2, &QAction::triggered, this, &MainWindow::onOutputActionTriggered);
    connect(outputAction_3, &QAction::triggered, this, &MainWindow::onOutputActionTriggered);
    connect(outputAction_4, &QAction::triggered, this, &MainWindow::onOutputActionTriggered);
    connect(outputAction_5, &QAction::triggered, this, &MainWindow::onOutputActionTriggered);

    addToolBar(m_ToolBar);

    m_StatusBar = new QStatusBar(this);
    QLabel* label_1 = new QLabel(QString::fromUtf8("left alignment"), m_StatusBar);
    label_1->setAlignment(Qt::AlignLeft);
    QLabel* label_2 = new QLabel(QString::fromUtf8("right alignment"), m_StatusBar);
    label_2->setAlignment(Qt::AlignRight);
    QLabel* label_3 = new QLabel(QString::fromUtf8("right aligenment"), m_StatusBar);
    label_3->setAlignment(Qt::AlignRight);
    m_StatusBar->addWidget(label_1, 1);
    m_StatusBar->addWidget(label_2, 1);
    m_StatusBar->addWidget(label_3, 1);
    setStatusBar(m_StatusBar);

    m_CentralTabWidget = new QTabWidget(this);
    m_CentralTabWidget->setTabsClosable(true);;
    connect(m_CentralTabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabWidgetTabCloseRequested);
    setCentralWidget(m_CentralTabWidget);

    QWidget* widget = new QWidget(m_CentralTabWidget);
    m_CentralTabWidget->addTab(widget, "widget");
    m_CentralTabWidget->tabBar()->setTabButton(0, QTabBar::RightSide, nullptr);

    MyWidget* myWidget = new MyWidget(m_CentralTabWidget);
    m_CentralTabWidget->addTab(myWidget, "MyWidget");
    m_CentralTabWidget->tabBar()->setTabButton(1, QTabBar::RightSide, nullptr);

    TableWidget* tableWidget = new TableWidget(m_CentralTabWidget);
    m_CentralTabWidget->addTab(tableWidget, "TableWidget");
    m_CentralTabWidget->tabBar()->setTabButton(2, QTabBar::RightSide, nullptr);

    TreeWidget* treeWidget = new TreeWidget(m_CentralTabWidget);
    m_CentralTabWidget->addTab(treeWidget, "TreeWidget");
    m_CentralTabWidget->tabBar()->setTabButton(3, QTabBar::RightSide, nullptr);

    DDSTextWidget* ddsWidget = new DDSTextWidget(m_CentralTabWidget);
    m_CentralTabWidget->addTab(ddsWidget, "DDSTextWidget");
    m_CentralTabWidget->tabBar()->setTabButton(4, QTabBar::RightSide, nullptr);
}

MainWindow::~MainWindow() = default;

void MainWindow::onNewPageActionTriggered(bool checked) {
    Q_UNUSED(checked);
    QWidget* w = new QWidget(m_CentralTabWidget);
    m_CentralTabWidget->addTab(w, QString("new page"));
}

void MainWindow::onOutputActionTriggered(bool checked) {
    Q_UNUSED(checked);
    qDebug() << "OutputActionTriggered";
}

void MainWindow::onTabWidgetTabCloseRequested(int index) {
    m_CentralTabWidget->removeTab(index);
}
