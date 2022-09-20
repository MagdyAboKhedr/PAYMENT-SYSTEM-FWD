#include <stdio.h>
#include "card.h"
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{ 
    uint8_t Date[40];
	uint32_t i=0;
	printf("ENTER Transaction Date: ");
	scanf(" %[^\n]%*c",Date);

    if (Date[0] == 0)
		return WRONG_DATE;

	else if (Date[10]!='\0')
		return WRONG_DATE;
    uint32_t day =  ((Date[0] - '0') * 10) + (Date[1] - '0');
    uint32_t month = ((Date[3] - '0') * 10) + (Date[4] - '0');
	uint32_t year = ((Date[8] - '0') * 10) + (Date[9] - '0');

    if (day < 1 || day>30 || month < 1 || month>12 || Date[2] != '/' || year > 99 || year < 0)
		return WRONG_DATE;

    for (i = 0; i < 11; i++)
		termData->transactionDate[i] = Date[i];

	return OK2;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    uint8_t index = 0;
    uint8_t year_trans = termData.transactionDate[9] + termData.transactionDate[8]*10;
    uint8_t month_trans = termData.transactionDate[4] + termData.transactionDate[3]*10;
    uint8_t year_expire = cardData.cardExpirationDate[4] + cardData.cardExpirationDate[3]*10;
    uint8_t month_expire = cardData.cardExpirationDate[1] + cardData.cardExpirationDate[0]*10;

    if (year_trans > year_expire)
        return EXPIRED_CARD; 

    else if (month_trans > month_expire )
        return EXPIRED_CARD; 

    return OK2;
}
  
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf ("Please enter the transaction amount : ");
    scanf ("%f",&termData->transAmount);

    if (termData->transAmount < 0 )
        return INVALID_AMOUNT; 
    return OK2;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount > termData->maxTransAmount)
        return EXCEED_MAX_AMOUNT; 

    return OK2;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    printf ("Enter Maximum Amount : ");
    scanf ("%f",&termData->maxTransAmount);

    if (termData->maxTransAmount < 0 )
        return INVALID_MAX_AMOUNT; 

    return OK2;
}
