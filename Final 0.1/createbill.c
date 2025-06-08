#include <stdio.h>
#include <string.h>

int menu();
typedef struct patient2
{
    int id;
    char name[50];
    int age;
    char gen;
    char disease[100];
    char admitDate[20];
} patient2;

void createbill(FILE *outFile, int fixedPatientId)
{
    system("cls"); // <-- Add this line
    patient2 p;
    int searchId, found = 0;
    char line[200];

    // Patient ID logic
    if (fixedPatientId > 0) {
        searchId = fixedPatientId;
    } else {
        printf("Enter Patient ID for billing: ");
        scanf("%d", &searchId);
        getchar();
    }

    FILE *fptr = fopen("patient.txt", "r");
    if (fptr == NULL) {
        printf("Error opening patient.txt\n");
        return;
    }

    while (fgets(line, sizeof(line), fptr)) {
        if (sscanf(line, "ID : %d", &p.id) == 1 && p.id == searchId) {
            // Read next 5 lines directly
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Name : %[^\n]", p.name);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Admit Date : %[^\n]", p.admitDate);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Age : %d", &p.age);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Gender : %c", &p.gen);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Disease : %[^\n]", p.disease);
            found = 1;
            break;
        }
    }
    fclose(fptr);

    if (!found) {
        printf("Patient with ID %d not found!\n", searchId);
        return;
    }

    // 2. Service Entry Section
    int nServices, nMedicines, nOther = 0, nDays, roomType, paymentStatus, paymentMode;
    float subtotal = 0, discount = 0, tax = 0, finalAmount = 0, advance = 0, balance = 0;
    float roomRate = 0, roomCharge = 0;
    char serviceName[10][50];
    int serviceQty[10];
    float serviceRate[10], serviceTotal[10];
    char medName[10][50];
    int medQty[10];
    float medRate[10], medTotal[10];
    char otherName[10][50];
    float otherCharge[10], otherTotal[10];

    printf("\nPatient Details:\n");
    printf("Name: %s\n", p.name);
    printf("Admit Date: %s\n", p.admitDate);
    printf("Age: %d\n", p.age);
    printf("Gender: %c\n", p.gen);
    printf("Disease: %s\n", p.disease);

    printf("\nHow many services/treatments? ");
    scanf("%d", &nServices);
    for(int i=0; i<nServices; i++) {
        printf("Service %d Name: ", i+1);
        scanf(" %[^\n]s", serviceName[i]);
        printf("Quantity: ");
        scanf("%d", &serviceQty[i]);
        printf("Unit Price: ");
        scanf("%f", &serviceRate[i]);
        serviceTotal[i] = serviceQty[i] * serviceRate[i];
        subtotal += serviceTotal[i];
    }

    printf("\nHow many medicines? ");
    scanf("%d", &nMedicines);
    for(int i=0; i<nMedicines; i++) {
        printf("Medicine %d Name: ", i+1);
        scanf(" %[^\n]s", medName[i]);
        printf("Quantity: ");
        scanf("%d", &medQty[i]);
        printf("Unit Price: ");
        scanf("%f", &medRate[i]);
        medTotal[i] = medQty[i] * medRate[i];
        subtotal += medTotal[i];
    }

    printf("\nRoom Type (1-General, 2-Private, 3-ICU): ");
    scanf("%d", &roomType);
    printf("Number of days admitted: ");
    scanf("%d", &nDays);
    if(roomType == 1) roomRate = 1000;
    else if(roomType == 2) roomRate = 2500;
    else if(roomType == 3) roomRate = 5000;
    else roomRate = 0;
    roomCharge = roomRate * nDays;
    subtotal += roomCharge;

    char otherChoice;
    printf("\nAny other charges? (y/n): ");
    scanf(" %c", &otherChoice);

    if (otherChoice == 'y' || otherChoice == 'Y') {
        printf("How many other charges? ");
        scanf("%d", &nOther);
        for(int i=0; i<nOther; i++) {
            printf("Other Charge %d Name: ", i+1);
            scanf(" %[^\n]s", otherName[i]);
            printf("Amount: ");
            scanf("%f", &otherCharge[i]);
            otherTotal[i] = otherCharge[i];
            subtotal += otherTotal[i];
        }
    }

    printf("\nEnter Discount (in %%): ");
    scanf("%f", &discount);
    printf("Enter Tax (in %%): ");
    scanf("%f", &tax);

    float discountAmt = subtotal * (discount/100.0);
    float taxAmt = (subtotal - discountAmt) * (tax/100.0);
    finalAmount = subtotal - discountAmt + taxAmt;

    printf("\nPayment Status (1-Paid, 2-Unpaid, 3-Partial): ");
    scanf("%d", &paymentStatus);
    printf("Payment Mode (1-Cash, 2-Card, 3-UPI, 4-Insurance): ");
    scanf("%d", &paymentMode);
    printf("Advance Payment (if any): ");
    scanf("%f", &advance);
    balance = finalAmount - advance;

    // 3. Bill Output (screen + file)
    FILE *billf = NULL;
    // File output
    if (outFile == NULL) {
        billf = fopen("bill.txt", "a");
        if (!billf) {
            printf("Error opening bill.txt for writing!\n");
            return;
        }
    } else {
        billf = outFile;
    }

    printf("\n\n================== HOSPITAL BILL ==================\n");
    printf("Patient ID: %d\nName: %s\nAge: %d\nGender: %c\nAdmit: %s\nDisease: %s\n", p.id, p.name, p.age, p.gen, p.admitDate, p.disease);
    printf("--------------------------------------------------\n");
    printf("Services/Treatments:\n");
    for(int i=0; i<nServices; i++)
        printf("  %s  Qty: %d  Rs.%.2f = Rs.%.2f\n", serviceName[i], serviceQty[i], serviceRate[i], serviceTotal[i]);

    printf("Medicines:\n");
    for(int i=0; i<nMedicines; i++)
        printf("  %s  Qty: %d  Rs.%.2f = Rs.%.2f\n", medName[i], medQty[i], medRate[i], medTotal[i]);

    printf("Room Charges: %d days x Rs.%.2f = Rs.%.2f\n", nDays, roomRate, roomCharge);

    if(nOther > 0) {
        printf("Other Charges:\n");
        for(int i=0; i<nOther; i++)
            printf("  %s = Rs.%.2f\n", otherName[i], otherTotal[i]);
    }
    printf("--------------------------------------------------\n");
    printf("Subtotal: Rs.%.2f\n", subtotal);
    printf("Discount: -Rs.%.2f\n", discountAmt);
    printf("Tax: +Rs.%.2f\n", taxAmt);
    printf("TOTAL PAYABLE: Rs.%.2f\n", finalAmount);
    printf("Advance Paid: Rs.%.2f\n", advance);
    printf("Balance Due: Rs.%.2f\n", balance);
    printf("Payment Status: %s\n", paymentStatus==1?"Paid":paymentStatus==2?"Unpaid":"Partial");
    printf("Payment Mode: %s\n", paymentMode==1?"Cash":paymentMode==2?"Card":paymentMode==3?"UPI":"Insurance");
    printf("==================================================\n");
    printf("Thank you for choosing our hospital!\n");
    printf("==================================================\n");
    printf("Press Enter to continue...");
    getchar(); getchar();

    // Header sirf ek hi baar print karo, bina extra \n ke
    fprintf(billf, "================== HOSPITAL BILL ==================\n");
    fprintf(billf, "Patient ID: %d\nName: %s\nAge: %d\nGender: %c\nAdmit: %s\nDisease: %s\n", p.id, p.name, p.age, p.gen, p.admitDate, p.disease);
    fprintf(billf, "--------------------------------------------------\n");
    fprintf(billf, "Services/Treatments:\n");
    for(int i=0; i<nServices; i++)
        fprintf(billf, "  %s  Qty: %d  Rs.%.2f = Rs.%.2f\n", serviceName[i], serviceQty[i], serviceRate[i], serviceTotal[i]);

    fprintf(billf, "Medicines:\n");
    for(int i=0; i<nMedicines; i++)
        fprintf(billf, "  %s  Qty: %d  Rs.%.2f = Rs.%.2f\n", medName[i], medQty[i], medRate[i], medTotal[i]);

    fprintf(billf, "Room Charges: %d days x Rs.%.2f = Rs.%.2f\n", nDays, roomRate, roomCharge);

    if(nOther > 0) {
        fprintf(billf, "Other Charges:\n");
        for(int i=0; i<nOther; i++)
            fprintf(billf, "  %s = Rs.%.2f\n", otherName[i], otherTotal[i]);
    }
    fprintf(billf, "--------------------------------------------------\n");
    fprintf(billf, "Subtotal: Rs.%.2f\n", subtotal);
    fprintf(billf, "Discount: -Rs.%.2f\n", discountAmt);
    fprintf(billf, "Tax: +Rs.%.2f\n", taxAmt);
    fprintf(billf, "TOTAL PAYABLE: Rs.%.2f\n", finalAmount);
    fprintf(billf, "Advance Paid: Rs.%.2f\n", advance);
    fprintf(billf, "Balance Due: Rs.%.2f\n", balance);
    fprintf(billf, "Payment Status: %s\n", paymentStatus==1?"Paid":paymentStatus==2?"Unpaid":"Partial");
    fprintf(billf, "Payment Mode: %s\n", paymentMode==1?"Cash":paymentMode==2?"Card":paymentMode==3?"UPI":"Insurance");
    fprintf(billf, "==================================================\n");
    fprintf(billf, "Thank you for choosing our hospital!\n");
    fprintf(billf, "==================================================\n");

    if (outFile == NULL) {
        fclose(billf);
    }
}
