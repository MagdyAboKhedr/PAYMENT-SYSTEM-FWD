#include <stdio.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t NAME[50];
	uint8_t ch=1;
	uint32_t i=0;
	printf("ENTER CARD HOLDER NAME: ");
	scanf(" %[^\n]%*c",NAME);

	while(ch!='\0')
	{
		ch=NAME[i];
		i++;
	}

	if (NAME[0] == 0)
	{
		return WRONG_NAME;
	}
	else if (i<20 || i>24)
	{
		return WRONG_NAME;
	}
	for (i = 0; i < 25; i++)
	{
		cardData->cardHolderName[i] = NAME[i];
	}

	return OK;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t cardexp[20];
	uint32_t i=0, month, year;
	printf("ENTER EXPIRATION DATE [MM/YY]: ");
	scanf(" %[^\n]%*c",cardexp);
	if (cardexp[0]==0)
	{
		return WRONG_EXP_DATE;
	}
	else if(cardexp[5]!='\0')
	{
		return WRONG_EXP_DATE;
	}

	month = ((cardexp[0] - '0') * 10) + (cardexp[1] - '0');
	year = ((cardexp[3] - '0') * 10) + (cardexp[4] - '0');

	if (month < 1 || month>12 || cardexp[2] != '/' || year > 99 || year < 0)
	{
		return WRONG_EXP_DATE;
	}

	for (i = 0; i < 6; i++)
	{
		cardData->cardExpirationDate[i] = cardexp[i];
	}
	return OK;	
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t PAN[40];
	uint32_t i;
	printf("ENTER PAN NUMBER: ");
	scanf(" %[^\n]%*c",PAN);
	if (PAN[0] ==0)
	{
		return WRONG_PAN;
	}
	else if (PAN[19]!='\0')
	{
		return WRONG_PAN;
	}

	for (i = 0; i < 21; i++)
	{
		cardData->primaryAccountNumber[i] = PAN[i];
	}
	return OK;
}
