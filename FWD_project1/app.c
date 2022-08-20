#include <stdio.h>
#include <Windows.h>
#include "app.h"
#include "card.h"
#include "terminal.h"
#include "server.h"

ST_cardData_t card1;
ST_terminalData_t term1;
ST_transaction_t trans1;

void appStart(void)
{
	trans1.cardHolderData = card1;
	trans1.terminalData = term1;

	EN_cardError_t cN = getCardHolderName(&card1);
	strcpy_s(trans1.cardHolderData.cardHolderName,sizeof(card1.cardHolderName), card1.cardHolderName);
	
	EN_cardError_t cD = getCardExpiryDate(&card1);
	strcpy_s(trans1.cardHolderData.cardExpirationDate, sizeof(card1.cardExpirationDate), card1.cardExpirationDate);
	
	EN_cardError_t cP = getCardPAN(&card1);
	strcpy_s(trans1.cardHolderData.primaryAccountNumber, sizeof(card1.primaryAccountNumber), card1.primaryAccountNumber);

	EN_terminalError_t stMaxA = setMaxAmount(&term1);
	trans1.terminalData.maxTransAmount = term1.maxTransAmount;

	if (cN == OK &&
		cD == OK &&
		cP == OK &&
		stMaxA==Ok)
	{
		EN_terminalError_t tD = getTransactionDate(&term1);
		strcpy_s(trans1.terminalData.transactionDate, sizeof(term1.transactionDate)+1, term1.transactionDate);

		EN_terminalError_t cExp = isCardExpired(card1, term1);
		if (cExp == Ok)
		{
			EN_terminalError_t gtTA = getTransactionAmount(&term1);
			trans1.terminalData.transAmount = term1.transAmount;


			EN_terminalError_t isBlwMax = isBelowMaxAmount(&term1);
			if(isBlwMax==Ok)
			{
					EN_transState_t rcvTrans = recieveTransactionData(&trans1);
					trans1.transState = rcvTrans;
			}
			else if (isBlwMax== EXCEED_MAX_AMOUNT)
			{
				printf("Transaction Declined you exceeded the Max terminal allowance\n");
			}
		}
		else if (cExp== EXPIRED_CARD)
		{
			printf("Transaction Declined Card Expired");
		}
		

	}
	printf("Please enter your Data correctly");

	
}