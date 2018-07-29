//
// Created by xiaobaiyey on 2018/7/28.
//

#include "Command.h"
#include <QProcess>
#include <QProcessEnvironment>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

void Command::checkEnvironment() {


}

bool Command::check_apktool() {
    QFile apktool(apk_tool_path);
    if (apktool.exists()) {
        return true;
    }
    return false;
}

QString Command::get_apktool_command(QString apk_path, QString out_dir) {
    QString cmd;
    if (out_dir.isEmpty()) {
        cmd = java_path + apk_tool_path + " d " + apk_path;
    } else {
        cmd = java_path + apk_tool_path + " d " + apk_path + " -o " + out_dir;
    }

    qDebug() << "apktool:" << cmd;
    return cmd;
}

Command::Command() {
}

QString Command::get_apltoll_command_b(QString source_dir, QString out_apk) {
    QString cmd;
    if (out_apk.isEmpty()) {
        cmd = java_path + apk_tool_path + " b " + source_dir;
    } else {
        cmd = java_path + apk_tool_path + " b " + source_dir + " -o " + out_apk;
    }

    qDebug() << "apktool:" << cmd;
    return cmd;
}

QString Command::get_tool_sign_command(QString source_dir, QString out_apk) {
    QString cmd;
    if (out_apk.isEmpty()) {
        cmd = sh_path + tool_sign_path + source_dir;
    } else {
        cmd = sh_path + tool_sign_path + source_dir + " -o " + out_apk;
    }

    qDebug() << "sign:" << cmd;
    return cmd;

}

QString Command::get_tool_repair_command(QString source_dir, QString out_apk) {
    QString cmd;
    if (out_apk.isEmpty()) {
        cmd = sh_path + tool_repair_path + source_dir;
    } else {
        cmd = sh_path + tool_repair_path + source_dir + " -o " + out_apk;
    }

    qDebug() << "repair:" << cmd;
    return cmd;
}

QString Command::get_tool_baksmali_command(QString source_dir, QString out_apk) {
    QString cmd;
    if (out_apk.isEmpty()) {
        cmd = sh_path + tool_baksmali_path + source_dir;
    } else {
        cmd = sh_path + tool_baksmali_path + source_dir + " -o " + out_apk;
    }

    qDebug() << "repair:" << cmd;
    return cmd;
}

QString Command::get_tool_smali_command(QString source_dir, QString out_apk) {
    QString cmd;
    if (out_apk.isEmpty()) {
        cmd = sh_path + tool_smali_path + source_dir;
    } else {
        cmd = sh_path + tool_smali_path + source_dir + " -o " + out_apk;
    }

    qDebug() << "repair:" << cmd;
    return cmd;
}

QString Command::get_tool_dex2jar_command(QString source_dir, QString out_apk) {
    QString cmd;
    if (out_apk.isEmpty()) {
        cmd = sh_path + tool_dex2jar_path + source_dir;
    } else {
        cmd = sh_path + tool_dex2jar_path + source_dir + " -o " + out_apk;
    }

    qDebug() << "repair:" << cmd;
    return cmd;
}

QString Command::get_tool_jar2dex_command(QString source_dir, QString out_apk) {
    QString cmd;
    if (out_apk.isEmpty()) {
        cmd = sh_path + tool_jar2dex_path + source_dir;
    } else {
        cmd = sh_path + tool_jar2dex_path + source_dir + " -o " + out_apk;
    }

    qDebug() << "repair:" << cmd;
    return cmd;
}

QString Command::get_tool_jd_jui_command(QString source_dir, QString out_apk) {
    QString cmd;

    cmd = cmd = java_path + tool_jd_jui_path + source_dir;
    // }

    qDebug() << "repair:" << cmd;
    return cmd;
}

QString Command::get_tool_jadx_jar_command(QString source_dir, QString out_apk) {
    QString cmd;

    cmd = sh_path + tool_jadx_path + source_dir;
    // }

    qDebug() << "repair:" << cmd;
    return cmd;
}
