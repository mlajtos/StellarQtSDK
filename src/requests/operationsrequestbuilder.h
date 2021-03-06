#ifndef OPERATIONSREQUESTBUILDER_H
#define OPERATIONSREQUESTBUILDER_H
#include "requestbuilder.h"
#include "../responses/operations/operationresponse.h"
#include "../responses/genericoperation.h"
#include "../responses/operationpage.h"
class KeyPair;
/**
 * Builds requests connected to operations.
 */
class OperationsRequestBuilder : public RequestBuilder
{
public:
    OperationsRequestBuilder(Server* server);
    /**
       * Requests specific <code>uri</code> and returns {@link OperationResponse}.
       * This method is helpful for getting the links.
       * @throws IOException
       */
    GenericOperation* operation(QUrl uri);

    /**
       * Requests <code>GET /operations/{operationId}</code>
       * @see <a href="https://www.stellar.org/developers/horizon/reference/operations-single.html">Operation Details</a>
       * @param operationId Operation to fetch
       * @throws IOException
       */
    GenericOperation* operation(qint64 operationId);

    /**
       * Builds request to <code>GET /accounts/{account}/operations</code>
       * @see <a href="https://www.stellar.org/developers/horizon/reference/operations-for-account.html">Operations for Account</a>
       * @param account Account for which to get operations
       */
    OperationsRequestBuilder& forAccount(KeyPair* account);

    /**
       * Builds request to <code>GET /ledgers/{ledgerSeq}/operations</code>
       * @see <a href="https://www.stellar.org/developers/horizon/reference/operations-for-ledger.html">Operations for Ledger</a>
       * @param ledgerSeq Ledger for which to get operations
       */
    OperationsRequestBuilder& forLedger(qint64 ledgerSeq);

    /**
       * Builds request to <code>GET /transactions/{transactionId}/operations</code>
       * @see <a href="https://www.stellar.org/developers/horizon/reference/operations-for-transaction.html">Operations for Transaction</a>
       * @param transactionId Transaction ID for which to get operations
       */
    OperationsRequestBuilder& forTransaction(QString transactionId);

    /**
       * Requests specific <code>uri</code> and returns {@link Page} of {@link OperationResponse}.
       * This method is helpful for getting the next set of results.
       * @return {@link Page} of {@link OperationResponse}
       */
    OperationPage* execute(QUrl uri);

    /**
       * Build and execute request.
       * @return {@link Page} of {@link OperationResponse}
       */
    OperationPage* execute();

    OperationsRequestBuilder& cursor(QString token);

    OperationsRequestBuilder& limit(int number);

    OperationsRequestBuilder& order(RequestBuilder::Order direction);
};

#endif // OPERATIONSREQUESTBUILDER_H
