#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>
#include <QPluginLoader>
#include <QDebug>

class PluginLoader : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = 0);
    template<typename T>
    T* loadPlugin(const QString &path) {
        QPluginLoader loader(path);
        QObject* plugin = loader.instance();
        if(plugin) {
           qDebug()<<"PluginLoader: loadPlugin() - plugin loaded from path: "<<path;
           return qobject_cast<T*>(plugin);
        }
        else throw new std::runtime_error("Unable to load plugin");
    }
};

#endif // PLUGINLOADER_H
