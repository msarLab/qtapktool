#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "console.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    void init_envnt();
    void init_radiobutton();
    void get_file_path(QString url);

private slots:
    void show_about_me();
    void drop_file_path(QDragEnterEvent* qDragEnterEvent);
    void grout_radio_change(int index);
    void chose_file_();
    void chose_dir();
    void run_cmd();
    void claer_log();
    void export_log();
protected:
    void dropEvent(QDropEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;

private:
    Ui::MainWindow *ui;


private:
    QButtonGroup* radio_group;
    Console* console;
    int radio_button_checked_index;
};

#endif // MAINWINDOW_H
