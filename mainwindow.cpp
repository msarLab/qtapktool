#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QMimeData>
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QRadioButton>
#include "Command.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //固定窗体大小
    this->setFixedSize(this->width(), this->height());
    this->setWindowTitle("Android逆向助手");
    //接受拖扯事件
    this->ui->input_line_text->setAcceptDrops(true);
    this->ui->input_line_text->setDragEnabled(true);
    radio_button_checked_index = 0;
    init_radiobutton();
    //初始化相关事件
    this->init_envnt();

}


void MainWindow::init_envnt() {


}

MainWindow::~MainWindow() {
    delete radio_group;
    delete ui;
}


void MainWindow::show_about_me() {
    qDebug() << "clicked";
}

void MainWindow::drop_file_path(QDragEnterEvent *qDragEnterEvent) {
    qDebug() << "drop";
}

void MainWindow::dropEvent(QDropEvent *event) {
    QWidget::dropEvent(event);
    qDebug() << "drop in";
    QList<QUrl> list = event->mimeData()->urls();
    if (list.empty()) {
        return;
    }
    QString fileName = list.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }
    get_file_path(fileName);

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    QWidget::dragEnterEvent(event);
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->accept();
        event->acceptProposedAction();
        //qDebug() << "drag" << event->source();
    }

}

void MainWindow::init_radiobutton() {
    //统一信号和槽
    radio_group = new QButtonGroup(this);

    //寻找子控件
    QTabWidget *groupBox = this->ui->org_table_widget;
    QList<QRadioButton *> rad = groupBox->findChildren<QRadioButton *>();
    qDebug() << "radio:" << rad.size();

    for (int i = 0; i < rad.size(); ++i) {
        radio_group->addButton(rad.at(i), i);
    }
    //链接信号和槽
    connect(radio_group, SIGNAL(buttonClicked(int)), this, SLOT(grout_radio_change(int)));
}

/**
 * 处理radiobuton 函数
 * @param index 索引值
 */
void MainWindow::grout_radio_change(int index) {
    QRadioButton *radioButton = dynamic_cast<QRadioButton *>(radio_group->button(index));
    qDebug() << radioButton->objectName();
    radio_button_checked_index = index;
    qDebug() << "index" << index;
    this->ui->input_line_text->clear();
    this->ui->out_path_text->clear();
}

/**
 * 选择输入路径
 */
void MainWindow::chose_file_() {
    QString file = QFileDialog::getOpenFileName(this, "选择文件", QDir::homePath(), "File(*.apk *.dex *.jar)");
    qDebug() << "chose:" << file;
    get_file_path(file);
}

/**
 * 配置输入输出路径
 * @param fileName
 */
void MainWindow::get_file_path(QString fileName) {
    qDebug() << fileName;
    QFileInfo qFileInfo(fileName);
    //获取文件扩展名
    QString ext = qFileInfo.suffix();
    qDebug() << "扩展名：" << ext;
    QString select_type;
    //判断文件扩展名是否正确
    this->ui->input_line_text->clear();
    this->ui->out_path_text->clear();
    switch (radio_button_checked_index) {
        case 0:
            select_type = "apk";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
                QString dir = qFileInfo.absolutePath().replace("." + ext, "", Qt::CaseInsensitive);
                //获取当前文件的文件名称，不带扩展名
                QString base_name = qFileInfo.completeBaseName();
                base_name.append("_out");
                dir.append("/");
                dir.append(base_name);
                this->ui->out_path_text->setText(dir);
            }
            break;
        case 1:
            if (qFileInfo.isDir()) {
                this->ui->input_line_text->setText(fileName);
                this->ui->out_path_text->setText(fileName + "build.apk");
            }
            break;
        case 2:
            select_type = "apk";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
                QString dir = qFileInfo.absolutePath().replace("." + ext, "", Qt::CaseInsensitive);
                //获取当前文件的文件名称，不带扩展名
                QString base_name = qFileInfo.completeBaseName();
                base_name.append("_sign.apk");
                dir.append("/");
                dir.append(base_name);
                this->ui->out_path_text->setText(dir);
            }
            break;
        case 3:
            select_type = "dex";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
                QString dir = qFileInfo.absolutePath().replace("." + ext, "", Qt::CaseInsensitive);
                //获取当前文件的文件名称，不带扩展名
                QString base_name = qFileInfo.completeBaseName();
                base_name.append("_repair.dex");
                dir.append("/");
                dir.append(base_name);
                this->ui->out_path_text->setText(dir);
            }
            break;
        case 4:
            select_type = "dex";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
                QString dir = qFileInfo.absolutePath().replace("." + ext, "", Qt::CaseInsensitive);
                //获取当前文件的文件名称，不带扩展名
                QString base_name = qFileInfo.completeBaseName();
                base_name.append("_baksmali");
                base_name.append("/");
                dir.append("/");
                dir.append(base_name);
                this->ui->out_path_text->setText(dir);
            }
            break;
        case 5:
            if (qFileInfo.isDir()) {
                this->ui->input_line_text->setText(fileName);
                this->ui->out_path_text->setText(fileName + "build.dex");
            }
            break;
        case 6:
            select_type = "dex";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
                QString dir = qFileInfo.absolutePath().replace("." + ext, "", Qt::CaseInsensitive);
                //获取当前文件的文件名称，不带扩展名
                QString base_name = qFileInfo.completeBaseName();
                base_name.append("_dextojar.jar");
                dir.append("/");
                dir.append(base_name);
                this->ui->out_path_text->setText(dir);
            }
            break;
        case 7:
            select_type = "jar";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
                QString dir = qFileInfo.absolutePath().replace("." + ext, "", Qt::CaseInsensitive);
                //获取当前文件的文件名称，不带扩展名
                QString base_name = qFileInfo.completeBaseName();
                base_name.append("_jartodex.dex");
                dir.append("/");
                dir.append(base_name);
                this->ui->out_path_text->setText(dir);
            }
            break;
        case 8:
        case 9:
            select_type = "jar";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
            }
            break;
        case 10:
            select_type = "dex";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
            }
            break;
        case 11:
            select_type = "apk";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
            }
            break;
        case 12:
            select_type = "apk";
            if (ext.compare(select_type, Qt::CaseInsensitive) == 0) {
                this->ui->input_line_text->setText(fileName);
                QString dir = qFileInfo.absolutePath().replace("." + ext, "", Qt::CaseInsensitive);
                //获取当前文件的文件名称，不带扩展名
                QString base_name = qFileInfo.completeBaseName();
                base_name.append("_apktojar.jar");
                dir.append("/");
                dir.append(base_name);
                this->ui->out_path_text->setText(dir);
            }
            break;
        default:
            qDebug() << "radio select erro";
            return;
    }

}

/**
 * 选择输出路径
 */
void MainWindow::chose_dir() {
    QString file = QFileDialog::getExistingDirectory(this, "选择文件夹", QDir::homePath());
    qDebug() << "chose dir:" << file;
    if (file.isEmpty())return;
    this->ui->out_path_text->setText(file);
}

void MainWindow::run_cmd() {
    Command command;
    QString cmd;
    QString input = this->ui->input_line_text->text();

    QString out = this->ui->out_path_text->text();
    switch (radio_button_checked_index) {
        case 0:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "输出出文件夹路径为空\n使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_apktool_command(input, out);
            break;
        case 1:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件夹输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "检查输出路径\n则将使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_apltoll_command_b(input, out);
        case 2:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "检查输出路径\n则将使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_tool_sign_command(input, out);
            break;
        case 3:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "检查输出路径\n则将使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_tool_repair_command(input, out);
            break;
        case 4:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "检查输出路径\n则将使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_tool_baksmali_command(input, out);
            break;
        case 5:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "检查输出路径\n则将使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_tool_smali_command(input, out);
            break;
        case 6:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "检查输出路径\n则将使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_tool_dex2jar_command(input, out);
            break;
        case 7:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "检查输出路径\n则将使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_tool_jar2dex_command(input, out);
            break;
        case 8:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            cmd = command.get_tool_jd_jui_command(input, out);
            break;

        case 9:
        case 10:
        case 11:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            cmd = command.get_tool_jadx_jar_command(input, out);
            break;
        case 12:
            if (input.isEmpty() || !QFile(input).exists()) {
                QMessageBox::warning(this, "错误", "检查文件输入路径", QMessageBox::Ok);
                return;
            }
            if (out.isEmpty()) {
                QMessageBox::warning(this, "错误", "检查输出路径\n则将使用默认设置", QMessageBox::Ok);
            }
            cmd = command.get_tool_dex2jar_command(input, out);
            break;
    }
    console = new Console(this, cmd, this->ui->log_plainTextEdit);
    console->run();

}

void MainWindow::claer_log() {

    this->ui->log_plainTextEdit->clear();
}

void MainWindow::export_log() {
    QString text = this->ui->log_plainTextEdit->toPlainText();
    QString out_file_path = QFileDialog::getSaveFileName(this, "保存文件", QDir::homePath(), "FILE(*.txt)", nullptr);
    if (out_file_path.isEmpty() || out_file_path.length() == 0)
        return;
    QFile file(out_file_path);
    file.open(QFile::WriteOnly);
    file.write(text.toLocal8Bit());
    file.close();
}






