#ifndef SERVER_H
#define SERVER_H
#include <QUrl>
#include <QNetworkAccessManager>
#include "requests/accountsrequestbuilder.h"
#include "requests/paymentsrequestbuilder.h"
#include "requests/transactionsrequestbuilder.h"
#include "requests/tradesrequestbuilder.h"
#include "requests/pathsrequestbuilder.h"
#include "requests/orderbookrequestbuilder.h"
#include "requests/offersrequestbuilder.h"
#include "requests/ledgersrequestbuilder.h"
#include "requests/operationsrequestbuilder.h"
#include "requests/effectsrequestbuilder.h"
#include <QTimer>
#include <QHash>
class Transaction;
class SubmitTransactionResponse;
/**
 * Main class used to connect to Horizon server.
 */
class Server : public QObject
{
    Q_OBJECT
    QUrl m_serverURI;
    QNetworkAccessManager *m_httpClient;

    QString escapeUri(QString uri);
    QNetworkRequest prepareRequest();

public:
    template<class T>
    T* get(RequestBuilder * rb )
    {
        if(rb->requestUri().isEmpty())
            rb->buildUri();
        //qDebug() << "REQUEST "<< rb->requestUri();
        QNetworkRequest request(rb->requestUri());
        if(rb->streamMode())
            request.setRawHeader("Accept","text/event-stream");
        QNetworkReply * r = m_httpClient->get(request);
        auto response = new T(r);
        response->setParent(this);//so it is not collected by QML
        return response;
    }

    Server(QString uri);

    ~Server();

    QUrl serverURI();

    /**
         * Returns {@link AccountsRequestBuilder} instance.
         */
    AccountsRequestBuilder accounts();

    /**
         * Returns {@link EffectsRequestBuilder} instance.
         */
    EffectsRequestBuilder effects();

    /**
    * Returns {@link LedgersRequestBuilder} instance.
    */
    LedgersRequestBuilder ledgers();

    /**
    * Returns {@link OffersRequestBuilder} instance.
    */
    OffersRequestBuilder offers();

    /**
         * Returns {@link OperationsRequestBuilder} instance.
         */
    OperationsRequestBuilder operations();

    /**
         * Returns {@link OrderBookRequestBuilder} instance.
         */
    OrderBookRequestBuilder orderBook();
    /**
         * Returns {@link TradesRequestBuilder} instance.
         */
    TradesRequestBuilder trades();

    /**
         * Returns {@link PathsRequestBuilder} instance.
         */
    PathsRequestBuilder paths();

    /**
         * Returns {@link PaymentsRequestBuilder} instance.
         */
    PaymentsRequestBuilder payments();

    /**
         * Returns {@link TransactionsRequestBuilder} instance.
         */
    TransactionsRequestBuilder transactions();

    /**
         * Submits transaction to the network.
         * @param transaction transaction to submit to the network.
         * Async method, you will get the response at transactionResponse signal
         * You lose ownership of the object so don't delete it.
         * You will have to delete the response returned by transactionResponse signal
         * @throws IOException
         */
    void submitTransaction(Transaction* transaction);

    //        /**
    //         * To support mocking a client
    //         * @param httpClient
    //         */
    //        void setHttpClient(HttpClient httpClient) {
    //            this.httpClient = httpClient;
    //    }
private slots:
    void processSubmitTransactionResponse();

signals:
    void transactionResponse(SubmitTransactionResponse * response);
    void transactionError();
};


#endif // SERVER_H
