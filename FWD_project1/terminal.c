#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	SYSTEMTIME CurrentDate;
	GetSystemTime(&CurrentDate);

	termData->transactionDate[0] = (CurrentDate.wDay / 10) + '0';
	termData->transactionDate[1] = (CurrentDate.wDay % 10) + '0';
	termData->transactionDate[2] = '/';
	termData->transactionDate[3] = (CurrentDate.wMonth / 10) + '0';
	termData->transactionDate[4] = (CurrentDate.wMonth % 10) + '0';
	termData->transactionDate[5] = '/';
	termData->transactionDate[6] = (CurrentDate.wYear / 1000) + '0';
	termData->transactionDate[7] = ((CurrentDate.wYear / 100) % 10) + '0';
	termData->transactionDate[8] = ((CurrentDate.wYear / 10) % 10) + '0';
	termData->transactionDate[9] = (CurrentDate.wYear % 10) + '0';


	if (strlen(termData->transactionDate) <10 || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/' || termData->transactionDate[0] == '\0')
	{
		return WRONG_DATE;
	}
	else { return Ok; }
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	char exp_year[2];
	char exp_month[2];
	exp_year[0] = cardData.cardExpirationDate[3];
	exp_year[1] = cardData.cardExpirationDate[4];
	
	exp_month[0] = cardData.cardExpirationDate[0];
	exp_month[1] = cardData.cardExpirationDate[1];

	char current_year[2];
	char current_month[2];
	current_year[0] = termData.transactionDate[8];
	current_year[1] = termData.transactionDate[9];

	current_month[0] = termData.transactionDate[3];
	current_month[1] = termData.transactionDate[4];

	if (strcmp(exp_year, current_year)>0)
	{
		return Ok;
	}
	else if (strcmp(exp_year, current_year)==0)
	{
		if (strcmp(exp_month, current_month) > 0)
		{
			return Ok;
		}
		else
		{
			return EXPIRED_CARD;
		}
	}
	else
	{
		return EXPIRED_CARD;
	}
}
/*EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t termData)
{
	printf("Enter Transaction amount\n");
	scanf_s("%f",&termData.transAmount);
	if (termData.transAmount <= 0)
		return INVALID_AMOUNT;
	else
	{
		return Ok;
	}
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Enter the maximum allowed amount for terminal\n");
	scanf_s("%f", &termData->maxTransAmount);
	
	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else
	{
		return Ok;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return Ok;
	}
}