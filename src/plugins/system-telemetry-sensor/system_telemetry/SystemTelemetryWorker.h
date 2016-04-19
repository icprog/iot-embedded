#ifndef SYSTEMTELEMETRYSENSOR_H
#define SYSTEMTELEMETRYSENSOR_H
#include "SensorWorker.h"
#include "TelemetryDataProvider.h"
#include <QFile>

class SystemTelemetryWorker: public SensorWorker
{
public:
    explicit SystemTelemetryWorker(const QString &name, QObject *parent = 0);

public slots:
    void onData(DataItem data);
    void start() override;
    void stop() override;

private slots:
    void onTimerTimeout();

private:
    DataItem createDataItem(double value, QString producer);

    const static QString TAG;
    const static QString MEM_USAGE_SENSOR_TAG;
    const static QString CPU_USAGE_SENSOR_TAG;
    const static QString LOAD_AVG_SENSOR_TAG;

    QFile* proc_loadavg_;
    QFile* proc_meminfo_;
    QFile* proc_stat_;

    SystemDataProvider *data_provider_;

    double load_avg_;
    double mem_usage_;
    double cpu_usage_;
};

#endif // SYSTEMTELEMETRYSENSOR_H
