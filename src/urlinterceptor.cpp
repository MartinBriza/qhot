#include "urlinterceptor.h"

UrlInterceptor::UrlInterceptor()
    :QObject(nullptr)
    ,QQmlAbstractUrlInterceptor()
{
}

QUrl UrlInterceptor::intercept(const QUrl &path, QQmlAbstractUrlInterceptor::DataType type)
{
    Q_UNUSED(type)
    if(!path.toLocalFile().isEmpty()) {
        emit newFile(path);
    }
    auto test = path.toString();
    if (test.startsWith("qrc:/qt/qml/Lith/Style/") && !test.endsWith("qmldir")) {
        test.replace("qrc:/qt/qml/Lith/Style/", "/home/mbriza/code/Lith/modules/Lith/Style/");
        auto url = QUrl::fromLocalFile(test);
        emit newFile(url);
        return url;
    }
    return path;
}

UrlInterceptor* UrlInterceptor::self()
{
    static UrlInterceptor self;
    return &self;
}

UrlInterceptor::~UrlInterceptor() = default;
