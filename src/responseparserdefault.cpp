#include "responseparserdefault.h"

ResponseParserDefault::ResponseParserDefault(ChorusDevice * device): ResponseParser(device)
{
    qDebug() << "ResponseParserV4 created";
}

ResponseParserDefault::~ResponseParserDefault(){

}

void ResponseParserDefault::parse(QString cmd){
    if(cmd.at(0).toLatin1() == '#')
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setApi(tmp);
        } else {
            qCritical() << "invalid api";
        }

    } else {
        qCritical() << "invalid property for default parser: " << cmd;
    }
}
