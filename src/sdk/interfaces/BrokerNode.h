#ifndef BROKERNODE_H
#define BROKERNODE_H
#include <QObject>
#include <QString>
#include <dataitem.h>

/**
 * @brief The BrokerNode interface
 * @note Broker Node is responsible for formatting data in manner required by external applications, e.g. cloud platforms
 */
class BrokerNode : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief BrokerNode Constructor
     * @param name Node name
     * @param parent Node parent QObject
     */
    explicit BrokerNode(const QString& name, QObject *parent = 0) : QObject(parent) {}
    virtual ~BrokerNode() {}

    /**
     * @brief getName Returns node name
     */
    virtual QString getName() = 0;


public slots:

    /**
     * @brief start Slot to start processing. If not neccessary, should be implemented as empty function.
     */
    virtual void start() = 0;

    /**
     * @brief stop Slot to stop processing. If not neccessary, should be implemented as empty function.
     */
    virtual void stop() = 0;

    /**
     * @brief processData Performs data processing.
     * @param data Data to be processed
     */
    virtual void processData(DataItem data) = 0;

signals:
    /**
     * @brief dataProcessed Signal emitted when data is processed and ready to go to next stage
     * @param data Data Item
     */
    void dataProcessed(DataItem data);

    /**
     * @brief onStopped Signal emitted when node stops processing, e.g. in error situation
     */
    void onStopped();
};

#endif // NODE_H
