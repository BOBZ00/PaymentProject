#include <stdio.h>
#include <string.h>
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Enter card holder name\n");
	gets( cardData->cardHolderName);
	if (strlen(cardData->cardHolderName) < 22 || strlen(cardData->cardHolderName) > 24 || cardData->cardHolderName[0]=='\0')
	{
		return WRONG_NAME;
	}
	else { return OK; }

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Enter card expiry date\n");
	gets(cardData->cardExpirationDate);
	if (strlen(cardData->cardExpirationDate) !=5 || cardData->cardExpirationDate[2] != '/' || cardData->cardExpirationDate[0] == '\0')
	{
		return WRONG_EXP_DATE;
	}
	else  {return OK; }
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Enter card PAN\n");
	gets(cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 || cardData->primaryAccountNumber[0] == '\0')
	{
		return WRONG_PAN;
	}

	else {
		return OK; }
}