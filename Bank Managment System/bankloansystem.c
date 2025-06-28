#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Loan structure
struct Loan {
    int id;
    char name[50];
    char loanType[30];
    float amount;
    int duration;
    float interest;
};

struct Payment {
    int loanId;
    float paidAmount;
};

// Function declarations
void applyLoan();
void loanDetails();
void loanPayments();
void allLoanDetails();
void remainingLoanDetails();
void makePayment(int loanId);
void viewPaymentHistory(int loanId);
void checkRemainingBalance(int loanId);
int loanIdExists(int id);
int main2();

int main2() {
    int choice;

    while (1) {
	system("cls");
	printf("============================\n");
	printf("   LOAN MANAGEMENT SYSTEM\n");
	printf("============================\n");
	printf("1. Apply for Loan\n");
	printf("2. Loan Details\n");
	printf("3. Payment\n");
	printf("4. Exit\n");
	printf("============================\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) {
    case 1: applyLoan(); break;
    case 2: loanDetails(); break;
    case 3: loanPayments(); break;
    case 4: exit(0);
    default:
	printf("Invalid choice! Try again.\n");
	system("pause");
}
    }

    return 0;
}

int loanIdExists(int id) {
    struct Loan loan;
    FILE *fp = fopen("loans.txt", "r");

    if (fp == NULL)
	return 0; // No file = no loans yet

    while (fread(&loan, sizeof(loan), 1, fp)) {
	if (loan.id == id) {
	    fclose(fp);
	    return 1; // ID exists
	}
    }

    fclose(fp);
    return 0; // ID is unique
}


void applyLoan() {
    struct Loan loan;
    FILE *fp;
    float rate = 0.1f;
    system("cls");

    printf("============================\n");
    printf("   APPLY FOR LOAN\n");
    printf("============================\n");

    do {
    printf("Enter Loan ID: ");
    scanf("%d", &loan.id);

    if (loanIdExists(loan.id)) {
	printf("This Loan ID already exists. Please enter a different ID.\n");
      }
    }
    while (loanIdExists(loan.id));

    getchar();

    printf("Enter Name: ");
    fgets(loan.name, sizeof(loan.name), stdin);
    loan.name[strcspn(loan.name, "\n")] = 0;

    printf("Enter Loan Type: ");
    fgets(loan.loanType, sizeof(loan.loanType), stdin);
    loan.loanType[strcspn(loan.loanType, "\n")] = 0;

    printf("Enter Loan Amount: ");
    scanf("%f", &loan.amount);

    printf("Enter Loan Duration (in years): ");
    scanf("%d", &loan.duration);

    loan.interest = loan.amount * rate * loan.duration;

    fp = fopen("loans.txt", "a");
    if (fp == NULL) {
	printf("Error opening file.\n");
	system("pause");
	return;
    }

    fwrite(&loan, sizeof(loan), 1, fp);
    fclose(fp);

    printf("\nLoan Application Submitted Successfully!\n");
    printf("Interest: Rs. %.2f\n", loan.interest);
    system("pause");
}

void remainingLoanDetails() {
    struct Loan loan;
    struct Payment payment;
    FILE *loanFile = fopen("loans.txt", "r");
    FILE *payFile;
    float totalPaid;
    float totalLoan;
    int found = 0;
    int count = 0;
    int backChoice;

    system("cls");
    printf("============================\n");
    printf("        LOAN DETAILS\n");
    printf("============================\n");

    if (loanFile == NULL) {
	printf("No loan records found.\n");
	system("pause");
	return;
    }

    while (fread(&loan, sizeof(loan), 1, loanFile)) {
	found = 1;
	totalPaid = 0;

	// Calculate total paid
	payFile = fopen("payments.txt", "r");
	if (payFile != NULL) {
	    while (fread(&payment, sizeof(payment), 1, payFile)) {
		if (payment.loanId == loan.id) {
		    totalPaid += payment.paidAmount;
		}
	    }
	    fclose(payFile);
	}

	totalLoan = loan.amount + loan.interest;

	// Skip loans that are fully paid
	if (totalPaid >= totalLoan) {
	    continue;
	}

	// Display loan
	printf("Loan ID      : %d\n", loan.id);
	printf("Name         : %s\n", loan.name);
	printf("Loan Type    : %s\n", loan.loanType);
	printf("Amount       : Rs. %.2f\n", loan.amount);
	printf("Interest     : Rs. %.2f\n", loan.interest);
	printf("Total Due    : Rs. %.2f\n", totalLoan);
	printf("Paid         : Rs. %.2f\n", totalPaid);
	printf("Remaining    : Rs. %.2f\n", totalLoan - totalPaid);
	printf("-----------------------------\n");

	count++;

	// Pause every 5 loans
	if (count % 5 == 0) {
	    printf("Press any key to see more...");
	    getchar();
	    getchar(); // flush
	    system("cls");
	    printf("============================\n");
	    printf("        LOAN DETAILS\n");
	    printf("============================\n");
	}
    }

    fclose(loanFile);

    if (!found || count == 0) {
	printf("No active (unpaid) loans found.\n");
    }

    system("pause");
}


void loanPayments() {
    int subChoice, id;

    do {
	system("cls");
	printf("============================\n");
	printf("         PAYMENT MENU\n");
	printf("============================\n");
	printf("Enter Loan ID: ");
	scanf("%d", &id);

	if (!loanIdExists(id)) {
	    printf("\nInvalid Loan ID! Try again.\n");
	    system("pause");
	}
    } while (!loanIdExists(id));

    // ? Only enter payment menu if ID is valid
    while (1) {
	system("cls");
	printf("============================\n");
	printf("        PAYMENT OPTIONS\n");
	printf("============================\n");
	printf("Loan ID: %d\n", id);
	printf("1. Make a Payment\n");
	printf("2. View Payment History\n");
	printf("3. Check Remaining Balance\n");
	printf("4. Back to Main Menu\n");
	printf("============================\n");
	printf("Enter your choice: ");
	scanf("%d", &subChoice);

	switch (subChoice) {
	    case 1: makePayment(id); break;
	    case 2: viewPaymentHistory(id); break;
	    case 3: checkRemainingBalance(id); break;
	    case 4: return;
	    default:
		printf("Invalid choice!\n");
		system("pause");
	}
    }
}


void makePayment(int loanId) {
    struct Loan loan;
    struct Payment payment;
    FILE *loanFile = fopen("loans.txt", "r");
    FILE *payFile;
    float totalPaid = 0;
    float totalLoan = 0;
    float remaining = 0;
    float newPayment;
    int found = 0;


    if (loanFile == NULL) {
	printf("Loan file not found.\n");
	system("pause");
	return;
    }

    // Find the loan
    while (fread(&loan, sizeof(loan), 1, loanFile)) {
	if (loan.id == loanId) {
	    found = 1;
	    break;
	}
    }
    fclose(loanFile);

    if (!found) {
	printf("Loan ID not found.\n");
	system("pause");
	return;
    }

    // Calculate total paid
    payFile = fopen("payments.txt", "r");
    if (payFile != NULL) {
	while (fread(&payment, sizeof(payment), 1, payFile)) {
	    if (payment.loanId == loanId) {
		totalPaid += payment.paidAmount;
	    }
	}
	fclose(payFile);
    }

    totalLoan = loan.amount + loan.interest;
    remaining = totalLoan - totalPaid;

    if (remaining <= 0) {
	printf("You have already cleared your loan.\n");
	system("pause");
	return;
    }

    // Prompt for payment
    printf("Remaining Balance: Rs. %.2f\n", remaining);
    printf("Enter amount to pay: ");
    scanf("%f", &newPayment);

    if (newPayment > remaining) {
	printf("Payment exceeds remaining balance! Remaining: Rs. %.2f\n", remaining);
	system("pause");
	return;
    }

    // Record payment
    payment.loanId = loanId;
    payment.paidAmount = newPayment;

    payFile = fopen("payments.txt", "a");
    if (payFile == NULL) {
	printf("Error opening payment file.\n");
	system("pause");
	return;
    }

    fwrite(&payment, sizeof(payment), 1, payFile);
    fclose(payFile);

    printf("Payment of Rs. %.2f recorded successfully!\n", newPayment);
    system("pause");
}


void viewPaymentHistory(int loanId) {
    struct Payment payment;
    FILE *fp = fopen("payments.txt", "r");
    int found = 0;

    printf("Payment History for Loan ID %d:\n", loanId);
    printf("-----------------------------\n");

    if (fp == NULL) {
	printf("No payments found.\n");
    } else {
	while (fread(&payment, sizeof(payment), 1, fp)) {
	    if (payment.loanId == loanId) {
		printf("Paid Amount: Rs. %.2f\n", payment.paidAmount);
		found = 1;
	    }
	}
	fclose(fp);

	if (!found)
	    printf("No payments made for this loan.\n");
    }

    system("pause");
}

void checkRemainingBalance(int loanId) {
    struct Loan loan;
    struct Payment payment;
    FILE *loanFile = fopen("loans.txt", "r");
    FILE *payFile = fopen("payments.txt", "r");
    float totalPaid = 0;
    float totalLoan = 0;
    float remaining = 0;
    int found = 0;

    if (loanFile == NULL) {
	printf("Loan file not found.\n");
	system("pause");
	return;
    }

    while (fread(&loan, sizeof(loan), 1, loanFile)) {
	if (loan.id == loanId) {
	    found = 1;
	    break;
	}
    }
    fclose(loanFile);

    if (!found) {
	printf("Loan ID not found.\n");
	system("pause");
	return;
    }

    if (payFile != NULL) {
	while (fread(&payment, sizeof(payment), 1, payFile)) {
	    if (payment.loanId == loanId) {
		totalPaid += payment.paidAmount;
	    }
	}
	fclose(payFile);
    }

    // Now calculate balance
    totalLoan = loan.amount + loan.interest;
    remaining = totalLoan - totalPaid;

    printf("Total Loan Amount (with interest): Rs. %.2f\n", totalLoan);
    printf("Total Paid: Rs. %.2f\n", totalPaid);
    printf("Remaining Balance: Rs. %.2f\n", remaining);
    system("pause");
}

void loanDetails() {
    int subChoice;

    do {
	system("cls");
	printf("============================\n");
	printf("        LOAN DETAILS\n");
	printf("============================\n");
	printf("1. All Loans\n");
	printf("2. Remaining (Unpaid) Loans\n");
	printf("3. Back to Main Menu\n");
	printf("============================\n");
	printf("Enter your choice: ");
	scanf("%d", &subChoice);

	switch (subChoice) {
	    case 1:
		allLoanDetails();
		break;
	    case 2:
		remainingLoanDetails();
		break;
	    case 3:
		return;
	    default:
		printf("Invalid choice!\n");
		system("pause");
	}
    } while (subChoice != 3);
}
void allLoanDetails() {
    struct Loan loan;
    FILE *fp = fopen("loans.txt", "r");
    int count = 0;

    system("cls");
    printf("============================\n");
    printf("        ALL LOANS\n");
    printf("============================\n");

    if (fp == NULL) {
	printf("No loan records found.\n");
	system("pause");
	return;
    }

    while (fread(&loan, sizeof(loan), 1, fp)) {
	printf("Loan ID      : %d\n", loan.id);
	printf("Name         : %s\n", loan.name);
	printf("Loan Type    : %s\n", loan.loanType);
	printf("Amount       : Rs. %.2f\n", loan.amount);
	printf("Interest     : Rs. %.2f\n", loan.interest);
	printf("Duration     : %d years\n", loan.duration);
	printf("-----------------------------\n");
	count++;

	if (count % 5 == 0) {
	    printf("Press Enter to see more...");
	    getchar();
	    getchar(); // flush
	    system("cls");
	    printf("============================\n");
	    printf("        ALL LOANS\n");
	    printf("============================\n");
	}
    }

    fclose(fp);

    if (count == 0) {
	printf("No loan records to display.\n");
    }

    system("pause");
}

