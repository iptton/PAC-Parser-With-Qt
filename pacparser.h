#ifndef PACPARSER_H
#define PACPARSER_H

#include <QObject>
#include <QtCore>
#include <QJSEngine>
#include <QJSValue>
#include "jsextension.h"

class PacParser : public QObject{
public:
    PacParser(QObject *parent,const QString& contentOfScript);

    QString findProxyByURL(const QString& url,const QString& host);

private:
    QJSEngine *engine;

    static QList<QString> properties;
};

#endif // PACPARSER_H
