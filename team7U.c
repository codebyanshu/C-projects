#include<stdio.h>
#include<stdlib.h>

struct accountcreate {
    char name[50];
    char father_name[50];
    char mobile_no[15];
    char email[50];
    char date_of_birth [50];
    char id[10];
};
void account();
void view();

 //function no 1, create account.
 void account()
 { 
     struct accountcreate user;   
    printf("Welcome To Account Managment Page \n");
    printf("Enter your Name:-");
    scanf("%s",&user.name);
     printf("Enter your Father Name:-");
    scanf("%s",&user.father_name);
     printf("Enter your Mobile Number:-");
    scanf("%s",&user.mobile_no);
     printf("Enter your Email:-");
    scanf("%s",&user.email);
     printf("Enter your Date Of Birth:-");
    scanf("%s",&user.date_of_birth);
    printf("Enter your id:-");
    scanf("%s",&user.id);
    FILE*fptr=fopen("login1.txt","a");

 if (fptr==NULL)
 {
   printf ("error in file opening \n");
    return;
 }
 fprintf(fptr,"Full 1Name :- %s\n",user.name);
 fprintf(fptr,"Father Name :- %s\n",user.father_name);
fprintf(fptr,"Email :- %s\n",user.email);
fprintf(fptr,"Mobile No :- %s\n",user.mobile_no);
fprintf(fptr,"Date Of Birth :- %s\n",user.date_of_birth);
fprintf(fptr,"Id :- %s\n",user.id);
 fclose(fptr);
 printf("Your Account Is Successfully Created");

}
void account_menu(){
   int Number;
    printf(" Welcome To Account Managment Page  \n\n");
    printf("Options:- \n");
    printf("1.Create Account \n");
    printf("2.view \n");
    printf("3.Modify \n");
    printf("4.Delete\n");
    printf("5.Exit\n");
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
 FILE*fptr=fopen("login1.txt","r");

 if (fptr==NULL)
 {
   printf ("error in file opening \n");
    return;
 }
    
   char line[300];
   while (fgets(line,sizeof(line),fptr))
   {
printf("%s",line);   
   }
}





