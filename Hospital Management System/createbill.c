#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "impfunc.h"

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
    system("cls");
    patient2 p;
    int searchId, found = 0;
    char line[200];
    char buffer[100];

    printf("Press ESC to go back to previous field.\n\n");

    // Patient ID logic
    if (fixedPatientId > 0) {
        searchId = fixedPatientId;
    } else {
        int step = 0;
        while (step < 1) {
            if (getInputWithEsc("Enter Patient ID for billing: ", buffer, sizeof(buffer))) {
                return;
            }
            if (sscanf(buffer, "%d", &searchId) == 1)
                step++;
            else
                printf("Invalid input! Please enter a valid number.\n");
        }
    }

    FILE *fptr = fopen("patient.txt", "r");
    if (fptr == NULL) {
        printf("Error opening patient.txt\n");
        return;
    }

    while (fgets(line, sizeof(line), fptr)) {
        if (sscanf(line, "ID : %d", &p.id) == 1 && p.id == searchId) {
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

    // Step-wise input for bill details
    int step = 0;
    int nServices = 0, nMedicines = 0, nOther = 0, nDays = 0, roomType = 0, paymentStatus = 0, paymentMode = 0;
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
    char otherChoice;

    while (step < 10) {
        switch (step) {
            case 0:
                printf("\nPatient Details:\n");
                printf("Name: %s\n", p.name);
                printf("Admit Date: %s\n", p.admitDate);
                printf("Age: %d\n", p.age);
                printf("Gender: %c\n", p.gen);
                printf("Disease: %s\n", p.disease);
                step++;
                break;
            case 1:
                if (getInputWithEsc("How many services/treatments? ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%d", &nServices) == 1 && nServices >= 0 && nServices <= 10) {
                    for (int i = 0; i < nServices; i++) {
                        if (getInputWithEsc("Service Name: ", serviceName[i], sizeof(serviceName[i]))) { i--; if (i < 0) { step--; break; } continue; }
                        if (getInputWithEsc("Quantity: ", buffer, sizeof(buffer))) { i--; if (i < 0) { step--; break; } continue; }
                        sscanf(buffer, "%d", &serviceQty[i]);
                        if (getInputWithEsc("Unit Price: ", buffer, sizeof(buffer))) { i--; if (i < 0) { step--; break; } continue; }
                        sscanf(buffer, "%f", &serviceRate[i]);
                        serviceTotal[i] = serviceQty[i] * serviceRate[i];
                        subtotal += serviceTotal[i];
                    }
                    step++;
                } else {
                    printf("Invalid number! (0-10 allowed)\n");
                }
                break;
            case 2:
                if (getInputWithEsc("How many medicines? ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%d", &nMedicines) == 1 && nMedicines >= 0 && nMedicines <= 10) {
                    for (int i = 0; i < nMedicines; i++) {
                        if (getInputWithEsc("Medicine Name: ", medName[i], sizeof(medName[i]))) { i--; if (i < 0) { step--; break; } continue; }
                        if (getInputWithEsc("Quantity: ", buffer, sizeof(buffer))) { i--; if (i < 0) { step--; break; } continue; }
                        sscanf(buffer, "%d", &medQty[i]);
                        if (getInputWithEsc("Unit Price: ", buffer, sizeof(buffer))) { i--; if (i < 0) { step--; break; } continue; }
                        sscanf(buffer, "%f", &medRate[i]);
                        medTotal[i] = medQty[i] * medRate[i];
                        subtotal += medTotal[i];
                    }
                    step++;
                } else {
                    printf("Invalid number! (0-10 allowed)\n");
                }
                break;
            case 3:
                if (getInputWithEsc("Room Type (1-General, 2-Private, 3-ICU): ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%d", &roomType) == 1 && roomType >= 1 && roomType <= 3) {
                    step++;
                } else {
                    printf("Invalid room type!\n");
                }
                break;
            case 4:
                if (getInputWithEsc("Number of days admitted: ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%d", &nDays) == 1 && nDays > 0) {
                    if(roomType == 1) roomRate = 1000;
                    else if(roomType == 2) roomRate = 2500;
                    else if(roomType == 3) roomRate = 5000;
                    else roomRate = 0;
                    roomCharge = roomRate * nDays;
                    subtotal += roomCharge;
                    step++;
                } else {
                    printf("Invalid number of days!\n");
                }
                break;
            case 5:
                if (getInputWithEsc("Any other charges? (y/n): ", buffer, sizeof(buffer))) { step--; continue; }
                otherChoice = buffer[0];
                if (otherChoice == 'y' || otherChoice == 'Y') {
                    if (getInputWithEsc("How many other charges? ", buffer, sizeof(buffer))) { step--; continue; }
                    if (sscanf(buffer, "%d", &nOther) == 1 && nOther >= 0 && nOther <= 10) {
                        for (int i = 0; i < nOther; i++) {
                            if (getInputWithEsc("Other Charge Name: ", otherName[i], sizeof(otherName[i]))) { i--; if (i < 0) { step--; break; } continue; }
                            if (getInputWithEsc("Amount: ", buffer, sizeof(buffer))) { i--; if (i < 0) { step--; break; } continue; }
                            sscanf(buffer, "%f", &otherCharge[i]);
                            otherTotal[i] = otherCharge[i];
                            subtotal += otherTotal[i];
                        }
                    } else {
                        printf("Invalid number! (0-10 allowed)\n");
                        continue;
                    }
                }
                step++;
                break;
            case 6:
                if (getInputWithEsc("Enter Discount (in %%): ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%f", &discount) == 1 && discount >= 0 && discount <= 100) {
                    step++;
                } else {
                    printf("Invalid discount!\n");
                }
                break;
            case 7:
                if (getInputWithEsc("Enter Tax (in %%): ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%f", &tax) == 1 && tax >= 0 && tax <= 100) {
                    step++;
                } else {
                    printf("Invalid tax!\n");
                }
                break;
            case 8:
                if (getInputWithEsc("Payment Status (1-Paid, 2-Unpaid, 3-Partial): ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%d", &paymentStatus) == 1 && paymentStatus >= 1 && paymentStatus <= 3) {
                    step++;
                } else {
                    printf("Invalid payment status!\n");
                }
                break;
            case 9:
                if (getInputWithEsc("Payment Mode (1-Cash, 2-Card, 3-UPI, 4-Insurance): ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%d", &paymentMode) == 1 && paymentMode >= 1 && paymentMode <= 4) {
                    step++;
                } else {
                    printf("Invalid payment mode!\n");
                }
                break;
            case 10:
                if (getInputWithEsc("Advance Payment (if any): ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%f", &advance) == 1 && advance >= 0) {
                    step++;
                } else {
                    printf("Invalid advance!\n");
                }
                break;
        }
    }

    float discountAmt = subtotal * (discount/100.0);
    float taxAmt = (subtotal - discountAmt) * (tax/100.0);
    finalAmount = subtotal - discountAmt + taxAmt;
    balance = finalAmount - advance;

    // Bill Output (screen + file)
    FILE *billf = NULL;
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

    // File output
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
