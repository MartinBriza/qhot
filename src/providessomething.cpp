#include "providessomething.h"
#include "urlinterceptor.h"

#include <QDirIterator>
#include <QJSEngine>
#include <QQmlEngine>
#include <QCoreApplication>

ProvidesSomething::ProvidesSomething()
{
    connect(UrlInterceptor::self(), &UrlInterceptor::newFile, this, [this](const QUrl& path){
        _fileSystemWatcher.addPath(path.toLocalFile());
    });

    connect(&_fileSystemWatcher, &QFileSystemWatcher::fileChanged, this, [this](const QString& path){
        Q_UNUSED(path)
        emit filePathChanged();
    });
}

void ProvidesSomething::resetEngine()
{
    m_engine->collectGarbage();
    QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete);
    QCoreApplication::processEvents();
    m_engine->clearComponentCache();
    QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete);
    QCoreApplication::processEvents();
    emit resetDone();
}

void ProvidesSomething::setEngine(QQmlEngine* engine)
{
    m_engine = engine;
}

QObject* ProvidesSomething::qmlSingletonRegister(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(scriptEngine)

    engine->setObjectOwnership(self(), QQmlEngine::CppOwnership);
    return self();
}

ProvidesSomething* ProvidesSomething::self()
{
    static ProvidesSomething self;
    return &self;
}

ProvidesSomething::~ProvidesSomething() = default;
