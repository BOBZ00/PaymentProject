#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "server.h"

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_serverError_t x=isValidAccount(&transData->cardHolderData);
	EN_serverError_t y = isAmountAvailable(&transData->terminalData, &transData->cardHolderData);

	printf("Transaction amount %f", transData->terminalData.transAmount);
	if (x == OKK)
	{
		if (y==OKK)
		{
			if (saveTransaction(&transData,x,y)==OKK)
			{
				printf("saved\n");
				for (char i = 0; i < 4; i++)
				{
					if (strcmp(valid_account[i].primaryAccountNumber, &transData->cardHolderData.primaryAccountNumber) == 0)
					{
						valid_account[i].balance = valid_account[i].balance - transData->terminalData.transAmount;
						printf("Your current balance is %f\n", valid_account[i].balance);
						return APPROVED;
					}
				}
			}
			else
			{
				printf("INTERNAL_SERVER_ERROR");
				return INTERNAL_SERVER_ERROR;
			}
		}
		else
		{
			printf("DECLINED_INSUFFECIENT_FUND");
			return DECLINED_INSUFFECIENT_FUND;
		}
	}
	else
	{
		printf("DECLINED_STOLEN_CARD");
		return DECLINED_STOLEN_CARD;
	}
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{

		for (int i = 0; i < 4; i++)

		{
			if (strcmp(valid_account[i].primaryAccountNumber,&cardData->primaryAccountNumber)==0)
			{
				printf("valid account\n");
				return OKK;
			}

		}
		printf("not found\n");
		return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_cardData_t* cardData)
{
		for (char i = 0; i < 4; i++)
		{
			if (strcmp(valid_account[i].primaryAccountNumber, &cardData->primaryAccountNumber) == 0)
			{
				if (termData->transAmount > valid_account[i].balance)
				{
					return LOW_BALANCE;
				}
				else
				{
					printf("balance availabe\n");
					return OKK;
				}
			}
		}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData, EN_serverError_t valid_check, EN_serverError_t amount_check)
{
	if (amount_check == OKK && valid_check == OKK)
	{
		strcpy_s(valid_transaction[valid_Transaction_counter].cardHolderData.cardExpirationDate, sizeof(transData->cardHolderData.cardExpirationDate), transData->cardHolderData.cardExpirationDate);
		strcpy_s(valid_transaction[valid_Transaction_counter].cardHolderData.cardHolderName, sizeof(transData->cardHolderData.cardHolderName), transData->cardHolderData.cardHolderName);
		strcpy_s(valid_transaction[valid_Transaction_counter].cardHolderData.primaryAccountNumber, sizeof(transData->cardHolderData.primaryAccountNumber), transData->cardHolderData.primaryAccountNumber);

		strcpy_s(valid_transaction[valid_Transaction_counter].terminalData.transactionDate, sizeof(transData->terminalData.transactionDate), transData->terminalData.transactionDate);
		valid_transaction[valid_Transaction_counter].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
		valid_transaction[valid_Transaction_counter].terminalData.transAmount = transData->terminalData.transAmount;


		transData->transactionSequenceNumber = Transaction_sequence_counter;

		Transaction_sequence_counter++;
		valid_transaction[valid_Transaction_counter].transactionSequenceNumber = transData->transactionSequenceNumber;
		//transData->transState = recieveTransactionData(transData);
		valid_Transaction_counter++;
		return OKK;
	}
	else return SAVING_FAILED;
}