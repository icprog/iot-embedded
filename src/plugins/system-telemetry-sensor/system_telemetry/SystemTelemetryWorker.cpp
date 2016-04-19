#include "SystemTelemetryWorker.h"
#include <QDebug>
#include <QThread>
#include <stdexcept>
#include "dataitem.h"

const QString SystemTelemetryWorker::TAG = "SystemTelemetryProcessor";
const QString SystemTelemetryWorker::MEM_USAGE_SENSOR_TAG = "mem_usage";
const QString SystemTelemetryWorker::CPU_USAGE_SENSOR_TAG = "cpu_usage";
const QString SystemTelemetryWorker::LOAD_AVG_SENSOR_TAG = "load_avg";

SystemTelemetryWorker::SystemTelemetryWorker(const QString &name, QObject* parent) : SensorWorker(name, parent)
{
    qDebug()<<TAG<<": constructor() from thread: "<<QThread::currentThreadId();

    this->settings_->beginGroup(node_name_);

    // File setup
    this->proc_loadavg_ = new QFile(this->settings_->value("loadAvgPath").toString(), this);
    this->proc_meminfo_ = new QFile(this->settings_->value("meminfoPath").toString(), this);
    this->proc_stat_ = new QFile(this->settings_->value("statPath").toString(), this);
    qDebug()<<TAG<<": constructor() - /proc files handler created.";

    // Data provider setup
    data_provider_ = new SystemDataProvider(this);
    if(proc_loadavg_->exists())
        data_provider_->setLoadavgFile(proc_loadavg_);
    if(proc_meminfo_->exists())
        data_provider_->setMeminfoFile(proc_meminfo_);
    if(proc_stat_->exists())
        data_provider_->setStatFile(proc_stat_);

    // Timer setup
    this->timer_ = new QTimer(this);
    timer_->setInterval(this->settings_->value("sampleInterval").toInt());
    connect(timer_, &QTimer::timeout, this, &SystemTelemetryWorker::onTimerTimeout);
//    timer_->start();
    qDebug()<<TAG<<": constructor() - created and started timer.";

}

void SystemTelemetryWorker::onData(DataItem data)
{
    qDebug()<<TAG<<": onData() from thread: "<<QThread::currentThreadId();
}

void SystemTelemetryWorker::start()
{
    connect(this, SIGNAL(signalStart()), this->timer_, SLOT(start()) );
    emit signalStart();
}

void SystemTelemetryWorker::stop()
{
    connect(this, &SensorWorker::signalStop, this->timer_, &QTimer::stop );
    emit signalStop();
}

void SystemTelemetryWorker::onTimerTimeout()
{
//    qDebug()<<TAG<<": onTimerTimeout() from thread: "<<QThread::currentThreadId();

    try{
        load_avg_ = data_provider_->getLoadAverage();
        cpu_usage_ = data_provider_->getProcessorUsage();
        mem_usage_ = data_provider_->getMemoryUsage();
    } catch (std::runtime_error e) {
        qDebug()<<TAG<<": onTimerTimeout() - exception caught: "<<e.what();
        return;
    }

    DataItem load_avg_item = createDataItem(load_avg_, LOAD_AVG_SENSOR_TAG);
    emit dataReady(load_avg_item);

    DataItem cpu_usage_item = createDataItem(cpu_usage_, CPU_USAGE_SENSOR_TAG);
    emit dataReady(cpu_usage_item);

    DataItem mem_usage_item = createDataItem(mem_usage_, MEM_USAGE_SENSOR_TAG);
    emit dataReady(mem_usage_item);
}

DataItem SystemTelemetryWorker::createDataItem(double value, QString producer)
{
    DataItem item;
    QString sender = TAG+"/"+producer;

    item.setPayloadType("sensor");
    item.payload().insert("value", value);
    item.payload().insert("time", QDateTime::currentDateTime().toMSecsSinceEpoch());
    item.payload().insert("sender", sender.toUtf8());
    return item;
}
