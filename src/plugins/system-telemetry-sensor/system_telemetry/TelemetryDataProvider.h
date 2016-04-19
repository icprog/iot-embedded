#ifndef SYSTEMDATAPROVIDER_H
#define SYSTEMDATAPROVIDER_H


#include <QObject>
#include <QFile>

class SystemDataProvider : public QObject
{
    Q_OBJECT
public:
    explicit SystemDataProvider(QObject *parent = 0);

    void setStatFile(QFile *stat);

    void setMeminfoFile(QFile *meminfo);

    void setLoadavgFile(QFile *loadavg);

    double getLoadAverage();

    double getProcessorUsage();

    double getMemoryUsage();

signals:

public slots:

private:
    QFile *loadavg_;
    QFile *meminfo_;
    QFile *stat_;

    static const QString TAG;
};

#endif // SYSTEMDATAPROVIDER_H
