#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "keypair.h"
#include <QtGlobal>
#include "operation.h"
#include "xdr/stellartransaction.h"
#include "memo.h"
#include "network.h"
#include <exception>
#include "transactionbuilderaccount.h"
#include <QObject>
/**
 * Represents <a href="https://www.stellar.org/developers/learn/concepts/transactions.html" target="_blank">Transaction</a> in Stellar network.
 */
class Transaction : public QObject
{

    Q_OBJECT

    const int BASE_FEE = 100;
    int m_fee;
    KeyPair* m_sourceAccount;
    quint64 m_sequenceNumber;
    QVector<Operation*> m_operations;
    Memo *m_memo;
    QVector<stellar::DecoratedSignature> m_signatures;

    friend class Builder;

    Transaction(KeyPair* sourceAccount, quint64 sequenceNumber, QVector<Operation*> operations, Memo* memo);


public:
    virtual ~Transaction();
    /**
      * Adds a new signature ed25519PublicKey to this transaction.
      * @param signer {@link KeyPair} object representing a signer
      */
    void sign(KeyPair* signer);

     /**
      * Adds a new sha256Hash signature to this transaction by revealing preimage.
      * @param preimage the sha256 hash of preimage should be equal to signer hash
      */
    void sign(QByteArray preimage);

         /**
      * Returns transaction hash.
      */
     QByteArray hash();

     /**
      * Returns signature base.
      */
     QByteArray signatureBase();

     KeyPair* getSourceAccount();

     quint64 getSequenceNumber();

     QVector<stellar::DecoratedSignature> getSignatures();

     Memo* getMemo();

     /**
      * Returns fee paid for transaction in stroops (1 stroop = 0.0000001 XLM).
      */
     int getFee();

     /**
      * Generates Transaction XDR object.
      */
     stellar::Transaction toXdr();

     /**
      * Generates TransactionEnvelope XDR object. Transaction need to have at least one signature.
      */
     stellar::TransactionEnvelope toEnvelopeXdr();

     /**
      * Returns base64-encoded TransactionEnvelope XDR object. Transaction need to have at least one signature.
      */
     QString toEnvelopeXdrBase64();

     /**
      * Builds a new Transaction object.
      */
     class Builder {
         TransactionBuilderAccount *m_sourceAccount;
         Memo *m_memo;
         QVector<Operation*> m_operations;
     public:
         /**
        * Construct a new transaction builder.
        * @param sourceAccount The source account for this transaction. This account is the account
        * who will use a sequence number. When build() is called, the account object's sequence number
        * will be incremented.
        */
         Builder(TransactionBuilderAccount *sourceAccount);
        ~Builder();

         int getOperationsCount();

         /**
        * Adds a new <a href="https://www.stellar.org/developers/learn/concepts/list-of-operations.html" target="_blank">operation</a> to this transaction.
        * @param operation, you lose the ownership of the object, don't delete it.
        * @return Builder object so you can chain methods.
        * @see Operation
        */
         Builder& addOperation(Operation* operation);

         /**
        * Adds a <a href="https://www.stellar.org/developers/learn/concepts/transactions.html" target="_blank">memo</a> to this transaction.
        * @param memo, you lose the ownership of the object, don't delete it.
        * @return Builder object so you can chain methods.
        * @see Memo
        */
         Builder& addMemo(Memo* memo);

         /**
        * Builds a transaction. It will increment sequence number of the source account.
        * You take ownership of the object so delete it when you don't need anymore.
        */
         Transaction* build();
     };
};
Transaction* checkNotNull(Transaction* transaction, const char *error);



#endif // TRANSACTION_H
