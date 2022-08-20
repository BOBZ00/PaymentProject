#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <Windows.h>
#include "card.h"
#include "terminal.h"

typedef unsigned long int uint32_t;

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef enum EN_serverError_t
{
	OKK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

static ST_accountsDB_t valid_account[255] = { {5000,"1234567890123456" },{12000,"4848902028992849"},{9000,"1498901004992750"} };
static ST_transaction_t valid_transaction[255]={0};
static int valid_Transaction_counter=0;
static int Transaction_sequence_counter=0;


EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_cardData_t *cardData);
EN_serverError_t saveTransaction(ST_transaction_t* transData,EN_serverError_t valid_check,EN_serverError_t amount_check);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
