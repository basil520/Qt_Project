#pragma once

#include <QMainWindow>

class QMenuBar;
class QToolBar;
class QStatusBar;
class QTabWidget;

class MainWindow final : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
private Q_SLOTS:
    void onNewPageActionTriggered(bool);
    void onOutputActionTriggered(bool);
    void onTabWidgetTabCloseRequested(int);
private:
    QMenuBar* m_MenuBar{nullptr};
    QToolBar* m_ToolBar{nullptr};
    QStatusBar* m_StatusBar{nullptr};
    QTabWidget* m_CentralTabWidget{nullptr};
};