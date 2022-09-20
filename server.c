#include "card.h"
#include "terminal.h"
#include "server.h"
#include <stdio.h>

//Database
ST_accountsDB_t serverSideAccountsDB[255] = {5000,"1111 2222 3333 4444"};
ST_transaction_t serverSideTransactionsDB[255] = {0};
uint8_t currentUser;
uint8_t dataBaseIndex=0;

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    EN_serverError_t retError;
    retError = isValidAccount(&transData->cardHolderData);
    if (retError==ACCOUNT_NOT_FOUND)
        return DECLINED_STOLEN_CARD;

    retError = isAmountAvailable(&transData->terminalData);
    if (retError==LOW_BALANCE)
        return DECLINED_INSUFFECIENT_FUND;
    retError = saveTransaction(transData);
    if (retError==SAVING_FAILED)
        return INTERNAL_SERVER_ERROR;

    return APPROVED;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    uint32_t i,j;
    uint8_t counter=0;
    for(i=0;i<=255;i++)
    {
        for(j=0;j<20;j++)
        {
            if (cardData->primaryAccountNumber[j] == serverSideAccountsDB[i].primaryAccountNumber[j])
                counter++;
        }
        if(counter==20) 
        {
            currentUser=i;
            return OK3;
        }
        counter=0;     
    }
    return ACCOUNT_NOT_FOUND; 
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if (termData->transAmount < serverSideAccountsDB[currentUser].balance)
    {
        serverSideAccountsDB[currentUser].balance -= termData->transAmount;
        return OK3;
    }
    else
        return LOW_BALANCE;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    if(serverSideTransactionsDB[dataBaseIndex].transactionSequenceNumber<255)
    {
        serverSideTransactionsDB[dataBaseIndex].cardHolderData=transData->cardHolderData;
        serverSideTransactionsDB[dataBaseIndex].terminalData=transData->terminalData;
        serverSideTransactionsDB[dataBaseIndex].transState=APPROVED;
        serverSideTransactionsDB[dataBaseIndex].transactionSequenceNumber=dataBaseIndex;
        dataBaseIndex++;
        return OK3;
    }
    else
        return SAVING_FAILED;
}