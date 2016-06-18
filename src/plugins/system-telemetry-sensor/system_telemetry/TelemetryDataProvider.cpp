#include "TelemetryDataProvider.h"
#include <stdexcept>
#include <QDebug>
#include <QThread>
const QString SystemDataProvider::TAG = "SystemDataProvider";
SystemDataProvider::SystemDataProvider(QObject *parent) : QObject(parent),
                                                          stat_(nullptr),
                                                          meminfo_(nullptr),
                                                          loadavg_(nullptr)

{

}

void SystemDataProvider::setStatFile(QFile *stat)
{
    stat_ = stat;
}

void SystemDataProvider::setMeminfoFile(QFile *meminfo)
{
    meminfo_ = meminfo;
}

void SystemDataProvider::setLoadavgFile(QFile *loadavg)
{
    loadavg_ = loadavg;
}

double SystemDataProvider::getLoadAverage()
{
    double result = 0;
    qDebug()<<TAG<<": getLoadAverage() from thread: "<<QThread::currentThreadId();
    QByteArray load_avg_content;
    if(loadavg_ != nullptr){
        bool res = loadavg_->open(QFile::ReadOnly);
        if(res == true && loadavg_->isReadable()){
            load_avg_content = loadavg_->readAll();
            QList<QByteArray> loadavg_content_split = load_avg_content.split(' ');
            result = loadavg_content_split[0].toDouble();
        }
        else{
            loadavg_->close();
            throw new std::runtime_error("Unable to load /proc/loadavg file");
        }
    }
    else throw new std::runtime_error("File handler for /proc/loadavg not exists");
    loadavg_->close();
    return result;
}

double SystemDataProvider::getProcessorUsage()
{
    double result;
    qDebug()<<TAG<<": getProcessorUsage() from thread: "<<QThread::currentThreadId();
    QByteArray content;
    if(stat_ != nullptr){
        bool res = stat_->open(QFile::ReadOnly);
        if(res == true && stat_->isReadable()){
            content = stat_->readAll();
            QList<QByteArray> content_columns = content.split('\n').at(0).split(' ');
            int user, nice, system, idle, iowait, irq, softirq, total;
            user = content_columns[1].toInt();
            nice = content_columns[2].toInt();
            system = content_columns[3].toInt();
            idle = content_columns[4].toInt();
            iowait = content_columns[5].toInt();
            irq = content_columns[6].toInt();
            softirq = content_columns[7].toInt();
            total = user + nice + system + idle + iowait + irq + softirq;

            result = (double)(user + nice + system + irq + softirq)/total;
        }
        else{
            stat_->close();
            throw new std::runtime_error("Unable to load /proc/stat file");
        }
    }
    else throw new std::runtime_error("File handler for /proc/stat not exists");
    stat_->close();
    return result;
}

double SystemDataProvider::getMemoryUsage()
{
    double result = 0;
    qDebug()<<TAG<<": getMemoryUsage() from thread: "<<QThread::currentThreadId();
    QByteArray content;
    if(meminfo_ != nullptr){
        bool res = meminfo_->open(QFile::ReadOnly);
        if(res == true && meminfo_->isReadable()){
            content = meminfo_->readAll();
            QList<QByteArray> content_split = content.split('\n').at(1).split(' ');
            while(content_split.contains("")){
                content_split.removeOne("");
            }

            result = content_split[1].toDouble();
        }
        else{
            meminfo_->close();
            throw new std::runtime_error("Unable to load /proc/meminfo file");
        }
    }
    else throw new std::runtime_error("File handler for /proc/meminfo not exists");
    meminfo_->close();
    return result;
}
