#include<stdio.h>


struct accountcreate {
    char name[50];
    char Father_name[50];
    char mobile_no[15];
    char email[50];
    char Date_Of_Birth [50];
};
void account();
void view();

 
 void account ()
 { 
      char Name[50], Father_Name[50], Date_Of_Birth[50], Mobile_Number[15], Email[50];
    printf("Welcome To Account Managment Page \n");
    printf("Enter your Name:-");
    scanf("%s",&Name);
     printf("Enter your Father Name:-");
    scanf("%s",&Father_Name);
     printf("Enter your Mobile Number:-");
    scanf("%s",&Mobile_Number);
     printf("Enter your Email:-");
    scanf("%s",&Email);
     printf("Enter your Date Of Birth:-");
    scanf("%s",&Date_Of_Birth);
}
void account_menu(){
   int Number;
    printf(" Welcome To Account Managment Page  \n\n");
    printf("Options:- \n");
    printf("1.Create Account \n");
    printf("2.Modify \n");
    printf("3.Delete\n");
    printf("4.Exit\n");
    printf("Please Select Any Option:-");
    scanf("%d",&Number);
    switch (Number)
    {
    case 1:
    account();
    break;
  case 2:
//     Modify();
     break;
     case 3:
//     Delete();
     break;
     case 4:
//     Exit;
     break;
    default:
    printf("invalid input");
   
         break;
    }
    
}
int main() {
    account_menu();
    return 0;
}

void view()
{
 struct accountcreate user ;
 FILE*fptr=fopen("login1.txt","a");

 if (fptr==NULL)
 {
    ("error in file opening \n");
 }
    
   printf("\t\t\t~~Welcome To Account Detail Page~~\t\t\t");
   printf("Full Name");
   scanf("%[^\n]",user.name);
 /*printf("Father Name :- \t ");
 scanf("%s", user.Father_name);
 printf("Mobile number :- \t ");
 scanf("%s", user.mobile_no);
 printf("Email :- \t ");
 scanf("%s", user.email);
 printf("Date Of Birth :- \t ");
 scanf("%s", user.Date_Of_Birth);*/

   fprintf(fptr,"Name :- %s\n",user.name);
   fprintf(fptr," Father Name :- %s\n",user.Father_name);
   fprintf(fptr,"Mobile No :- %s\n",user.mobile_no);
   fprintf(fptr,"Email :- %s\n",user.email);
   fprintf(fptr,"Date Of Birth :- %s\n",user.Date_Of_Birth);
}




