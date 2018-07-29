//
// Created by xiaobaiyey on 2018/7/28.
//

#ifndef PROJECT_NAME_COMMAND_H
#define PROJECT_NAME_COMMAND_H


#include <QString>

class Command {

public:
    explicit Command();

    void checkEnvironment();

    QString get_apktool_command(QString apk_path, QString out_dir);

    QString get_apltoll_command_b(QString source_dir, QString out_apk);

    QString get_tool_sign_command(QString source_dir, QString out_apk);

    QString get_tool_repair_command(QString source_dir, QString out_apk);

    QString get_tool_baksmali_command(QString source_dir, QString out_apk);

    QString get_tool_smali_command(QString source_dir, QString out_apk);

    QString get_tool_dex2jar_command(QString source_dir, QString out_apk);

    QString get_tool_jar2dex_command(QString source_dir, QString out_apk);

    QString get_tool_jd_jui_command(QString source_dir, QString out_apk);

    QString get_tool_jadx_jar_command(QString source_dir, QString out_apk);

private:
    QString java_path = "java -jar ";
    QString sh_path = "sh ";

    bool check_apktool();

    QString apk_tool_path = "./bin/apktool/apktool.jar ";
    QString tool_sign_path = "./bin/dex-tools/d2j-apk-sign.sh ";
    QString tool_repair_path = "./bin/dex-tools/d2j-dex-recompute-checksum.sh ";
    QString tool_baksmali_path = "./bin/dex-tools/d2j-baksmali.sh ";
    QString tool_smali_path = "./bin/dex-tools/d2j-smali.sh ";
    QString tool_dex2jar_path = "./bin/dex-tools/d2j-dex2jar.sh ";
    QString tool_jar2dex_path = "./bin/dex-tools/d2j-jar2dex.sh ";
    QString tool_jd_jui_path = "./bin/jd-jui/jd-gui.jar ";
    QString tool_jadx_path = "./bin/jadx/bin/jadx-gui ";
    QString cur_path;

};


#endif //PROJECT_NAME_COMMAND_H
