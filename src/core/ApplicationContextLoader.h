#ifndef APPLICATIONCONTEXTLOADER_H
#define APPLICATIONCONTEXTLOADER_H

#include <QObject>
#include <QSettings>
#include <memory>
#include "NodeContainer.h"

class ApplicationContextLoader : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationContextLoader(QObject *parent = 0);

    void loadApplicationContext(const QString &config_path);
    void loadTestContext();

    void setNodeContainer(NodeContainer *node_container);

signals:

public slots:

private:
    NodeContainer *node_container_;
    QSettings *node_settings_;
    QSettings *pipe_settings_;

//    std::unique_ptr<QSettings> settings_;
    void assertNodeContainerExists();

    const static QString TAG;

    const static QString NODE_SETTINGS_FILENAME;
    const static QString PIPE_SETTINGS_FILENAME;

    const static QString NODE_LIB_FILENAME_KEY;
    const static QString NODE_CLASSNAME_KEY;
    const static QString NODE_CONNECTIONS_KEY;
    const static QString NODE_TYPE_KEY;
};

#endif // APPLICATIONCONTEXTLOADER_H
