#include "pacparser.h"

#include <QMetaObject>

PacParser::PacParser(QObject *parent,const QString& contentOfScript):
    QObject(parent),
    engine(new QJSEngine(this)){

    engine->evaluate(contentOfScript);
    JSExtension extension(this);
    QJSValue extValue = engine->newQObject(&extension);


    const QMetaObject *metaobj = extension.metaObject();
    int count = metaobj->methodCount();
    for(int i=0;i<count;++i){
        QMetaMethod method = metaobj->method(i);
        if(method.methodType() == QMetaMethod::Method){
            QString name = method.name();
            engine->globalObject().setProperty(name,extValue.property(name));
        }
    }

}

QString PacParser::findProxyByURL(const QString& url,const QString& host){

    QJSValue global = engine->globalObject();
    QJSValue fun = global.property("FindProxyForURL");
    if ( !fun.isCallable() ) {
        return QString("DIRECT");
    }

    QJSValueList args;
    args << engine->toScriptValue( url ) << engine->toScriptValue( host );
    QJSValue val = fun.call( args );

    return val.toString();
}
