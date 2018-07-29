#include "console.h"
#include <QProcess>
#include "mainwindow.h"
#include <QDebug>
#include <QScrollBar>

Console::Console() {

}


Console::Console(QObject *parent, QString cmd, QPlainTextEdit *con) : QObject(parent), cmd(cmd), console_text(con) {

}

Console::~Console() {


}


void Console::start_process() {
    qDebug() << "开始啦";
}

void Console::start_read_output() {
    QString data = QString(process.readAllStandardOutput());
    //data = data.replace("\r\n", "\n");
    // qDebug() << data;
    console_text->insertPlainText(data);
    //ScrollBar自动滚动
    console_text->verticalScrollBar()->setValue(console_text->verticalScrollBar()->maximum());


}

void Console::start_read_err_output() {
    console_text->insertPlainText("出错了:\n");
    QString data = QString(process.readAllStandardError());
    //data = data.replace("\r\n", "\n");
    // qDebug() << data;
    console_text->insertPlainText(data);
    //ScrollBar自动滚动
    console_text->verticalScrollBar()->setValue(console_text->verticalScrollBar()->maximum());
}

void Console::finish_process(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "结束啦：" << process.state();
    console_text->insertPlainText("执行完成\n\n\n");

}

void Console::run() {
    //如果进程没结束，强制杀死，然后结束绑定
    if (process.state() == QProcess::Running) {
        process.kill();
        process.waitForFinished();
        disconnect(&process, SIGNAL(started()), this, SLOT(start_process()));
        disconnect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(start_read_output()));
        disconnect(&process, SIGNAL(readyReadStandardError()), this, SLOT(start_read_err_output()));
        disconnect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this,
                   SLOT(finish_process(int, QProcess::ExitStatus)));
        if (process.state() == QProcess::Running) {
            qDebug() << "runing";
            return;
        }
    } else {
        console_text->insertPlainText("开始执行:"+cmd+"\n");
        process.start(cmd);
        //progress.readAllStandardOutput();
        //connect(progress, SIGNAL(readyReadStandardOutput()), this, SLOT(redFromStdOut()));
        connect(&process, SIGNAL(started()), this, SLOT(start_process()));
        connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(start_read_output()));
        connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(start_read_err_output()));
        connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this,
                SLOT(finish_process(int, QProcess::ExitStatus)));
        process.waitForStarted();
    }

}





