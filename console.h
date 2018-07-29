#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QPlainTextEdit>

class Console : public QObject {
Q_OBJECT

public:
    Console();

    explicit Console(QObject *parent, QString cmd, QPlainTextEdit *);

    ~Console() override;

    void run();

private slots:


    void start_process();

    void start_read_output();

    void start_read_err_output();

    void finish_process(int exitCode, QProcess::ExitStatus exitStatus);

protected:
    QString cmd;
    QProcess process;
    QPlainTextEdit *console_text;
};

#endif // CONSOLE_H