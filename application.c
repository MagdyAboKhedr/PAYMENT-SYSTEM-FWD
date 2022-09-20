#include <stdio.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
#include "application.h"

ST_cardData_t userCard;
ST_terminalData_t terminalData;
ST_transaction_t serverAuth;

void appStart(void)
{
    EN_cardError_t error;
    do
    {
        error = getCardHolderName(&userCard);
        error != OK ? printf("Wrong Name, Please Try Again\n") : printf("\n");
    }while (error!=OK);
    do
    {
        error = getCardExpiryDate(&userCard);
        error != OK ? printf("Wrong Expiry Date, Please Try Again\n") : printf("\n");
    }while (error!=OK);
    do
    {
        error = getCardPAN(&userCard);
        error != OK ? printf("Wrong PAN Number, Please Try Again\n") : printf("\n");
    }while (error!=OK);

    EN_terminalError_t error2;
    do
    {
        error2 = getTransactionDate(&terminalData);
        error2 != OK ? printf("Wrong Date, Please Try Again\n") : printf("\n");
    }while (error2!=OK2);

    if(isCardExpired(userCard,terminalData)!=OK2)
    {
        printf("Card Expired\n\n");
        return;
    }
    printf("Valid Card\n\n");

    do
    {
        error2 = setMaxAmount(&terminalData);
        error2 != OK2 ? printf("Invalid Amount, Please Try Again\n") : printf("\n");
    }while (error2!=OK2);

    do
    {
        error2 = getTransactionAmount(&terminalData);
        error2 != OK2 ? printf("Invalid Amount, Please Try Again\n") : printf("\n");
    }while (error2!=OK2);

    if(isBelowMaxAmount(&terminalData)!=OK2)
    {
        printf("Max Amount Exceeded\n\n");
        return;
    }
    printf("Contacting Server ...\n\n");

    serverAuth.cardHolderData = userCard;
    serverAuth.terminalData = terminalData;

    EN_serverError_t error3;
    error3 = recieveTransactionData(&serverAuth);
    switch (error3)
    {
    case APPROVED:                   printf("Transaction Completed\n\n");break;
    case DECLINED_INSUFFECIENT_FUND: printf("Insufficient Funds\n\n");break;
    case DECLINED_STOLEN_CARD:       printf("STOLEN CARD\n\n");break;
    case INTERNAL_SERVER_ERROR:      printf("Internal Server Error\n\n");break;
    }
}

