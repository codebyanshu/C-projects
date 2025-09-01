#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_Book 100
#define MAX_ISSUED 100
struct book
{
    char book_id[10];
    char title[50];
    char author[30];
    int total_copies;
    int available_copies;
};
struct book books[MAX_Book];
int book_count = 0;

struct user
{

    char user_id[10];
    char name[20];
    char class[10];
};

struct issued_book
{

    char issue_id[12];
    char user_id[10];
    char book_id[10];
    char issue_date[10];
    char due_date[10];
    int return_status;
};
struct issued_book issuedBooks[MAX_ISSUED];
int issued_count = 0;

int is_only_letters(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!isalpha(str[i]))
        {
            return 0;
        }
    return 1;
}

int is_only_digit(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
        {
            return 0;
        }
    return 1;
}

void add_new_book();
void register_new_user();
void display_all_books();
void issue_book();
void return_book();
void view_issued_book();
void search_book();
void delete_book();

void library_menu()
{
    int Number;
    printf("\n ~~~~~  WELCOME TO LIBRARY MANAGMENT PAGE  ~~~~~ \n");
    printf("1. Add New Book \n");
    printf("2. Register New User\n");
    printf("3. Display All books\n");
    printf("4. Issue Book\n");
    printf("5. Return Book\n");
    printf("6. View Issued Books\n");
    printf("7. Search Book\n");
    printf("8. Delete Book\n");
    printf("9. Exit\n");
    printf("\n ~~~~~ PLEASE CHOOSE ANY ONE OPTION ~~~~~ \n");
    scanf("%d", &Number);

    switch (Number)
    {
    case 1:
        add_new_book();
        break;
    case 2:
        register_new_user();
        break;
    case 3:
        display_all_books();
        break;
    case 4:
        issue_book();
        break;
    case 5:
        return_book();
        break;
    case 6:
        view_issued_book();
        break;
        case 7:
            search_book();
        break;
        case 8:
        delete_book();
        break;
    case 9:
        printf("Exit");
        exit(0);
        break;
    default:
        printf("Invalid Input\n");
        break;
    }
}
int main(int argc, char const *argv[])
{
    while (1)
        library_menu();
    return 0;
}

// FUNCTION NO.1,Add New Books;

void add_new_book()
{
    struct book B;

    printf("\n ~~~~~ ADD NEW BOOK ~~~~~ \n");

    printf("Enter Book Id:->>\t");
    scanf("%s", &B.book_id);
    while (strlen(B.book_id) < 4)
    {
        printf("Your Book Id Must Be 4 Digits\n");
        scanf("%s", &B.book_id);
    }
    while (!is_only_digit(B.book_id))
    {
        printf("Enter Digits Only\n");
        printf("Enter Book Id:->>\t");
        scanf("%s", B.book_id);
    }

    printf("Enter Title:->>\t");
    scanf("%s", &B.title);
    while (strlen(B.title) < 5)
    {
        printf("Your Title Must Be 5 Letters\n");
        scanf("%s", &B.title);
    }

    while (!is_only_letters(B.title))
    {
        printf("Enter Characters Only\n");
        scanf("%s", &B.title);
    }

    printf("Enter Author:->>\t");
    scanf("%s", &B.author);
    while (strlen(B.author) < 5)
    {
        printf("Your Id Must Be 5 Letters\n");
        scanf("%s", &B.author);
    }
    while (!is_only_letters(B.author))
    {
        printf("Enter Characters Only\n");
        scanf("%s", &B.author);
    }

    printf("Total Copies:->>\t");
    scanf("%d", &B.total_copies);
    B.available_copies = B.total_copies;
    if (book_count < MAX_Book)
    {
        books[book_count++] = B;
        printf("Book added successfully!\n");
    }
    else
    {
        printf("Book limit reached.\n");
    }
}
// FUNCTION NO.2,Add New User;
void register_new_user()
{
    struct user C;

    printf("\n ~~~~~ REGISTER NEW USER ~~~~~ \n");
    while(1){
    printf("Enter User Id:->>\t");
    scanf("%s", C.user_id);
    if (strlen(C.user_id) < 4)
    {
        printf("Your User Id Must Be 4 Letters\n");
        continue;
    }
    if (!is_only_digit(C.user_id))
    {
        printf("Enter Digits Only\n");
        continue;
    }
    break;
}


    printf("Enter Your Name:->>\t");
    scanf("%s", &C.name);
    while (strlen(C.name) < 5)
    {
        printf("Your Id Must Be 5 Letters\n");
        scanf("%s", C.name);
    }
    while (!is_only_letters(C.name))
    {
        printf("Enter Characters Only\n");
        scanf("%s", C.name);
    }
    printf("Enter Your Class:->>\t");
    scanf("%s", &C.class);
}

// FUNCTION NO.3,Display All Books;
void display_all_books()
{

    if (book_count == 0)
    {
        printf("No Books are available in library\n");
        return;
    }
    printf("\n ~~~~~ ALL BOOKS IN LIBRARY ~~~~~ \n");
    printf("%10s %10s %10s %10s %10s \n", "Book Id", "Title", "Author", "Total", "Available");
    for (int i = 0; i < book_count; i++)
    {
        printf("%10s %10s %10s %10d %10d \n",
               books[i].book_id,
               books[i].title,
               books[i].author,
               books[i].total_copies,
               books[i].available_copies);
    }
}
// FUNCTION NO.4,issue book;
void issue_book()
{
    struct issued_book D;

    printf("\n ~~~~~ ISSUED BOOK ~~~~~ \n");
    while(1){
    printf("Enter Issue Id:->>\t");
    scanf("%s", D.issue_id);
    if (strlen(D.issue_id) < 4)
    {
        printf("Your Id Must Be 4 Letters \n");
       continue;
    }
    if (! is_only_digit(D.issue_id))
    {
        printf("Enter Digits Only. \n");
        continue;
    }
       break;
}
    while(1){
    printf("Enter User Id:->>\t");
    scanf("%s", D.user_id);
    if (strlen(D.user_id) < 4)
    {
        printf("Your Id Must Be 4 Letters \n");
        continue;
    }
    if (!is_only_digit(D.user_id))
    {
        printf("Enter Digits Only \n");
        continue;
    }
    break;
}
    while(1){
    printf("Enter Book Id:->>\t");
    scanf("%s", D.book_id);
    if (strlen(D.book_id) < 4)
    {
        printf("Your Id Must Be 4 Letters\n");
       continue;
    }
    if (!is_only_digit(D.book_id))
    {
        printf("Enter Digits Only");
        continue;
    }
    break;
}
    printf("Enter Issue Date(DD/MM/YYYY):->>\t");
    scanf("%d", &D.issue_date);

    printf("Enter Due Date(DD/MM/YYYY):->>\t");
    scanf("%d", &D.due_date);

    if (issued_count < MAX_ISSUED)
    {
        issuedBooks[issued_count++] = D;
        printf("Book issued successfully!\n");
    }
    else
    {
        printf("Cannot issue more books. Limit reached.\n");
    }
}
// FUNCTION NO.5,Return book;
void return_book()
{
    struct issued_book D;
    printf("\n ~~~~~ RETURN BOOK ~~~~~ \n ");
    while(1){
    printf("Enter Your Issued Id For Return:->> \n");
    scanf("%s", D.issue_id);
    if (strlen(D.issue_id) > 4)
    {
        printf("Your Id Must Be 4 Letters \n");
        continue;
    }
    if (!is_only_digit(D.issue_id))
    {
        printf("Enter Digits Only\n");
        continue;
    }
    break;
}
    printf("Book with Issue Id %s marked as returned.\n", D.issue_id);
    D.return_status = 1;
}

// FUNCTION NO.6,VIEW ISSUED BOOK:
void view_issued_book()
{
    if (issued_count == 0)
    {
        printf("No Any Book Issued\n");
        return;
    }
    printf("\n ~~~~~ ISSUED BOOK LIST ~~~~~ \n");
    printf("%12s %10s %10s %12s %12s %10s\n", "Issue Id", "User Id", "Book Id", "Issue Date", "Due Date", "Returned");
    for (int i = 0; i < issued_count; i++)
    {
        printf(" %12s %10s %10s %12s  %12s %10s \n",
               issuedBooks[i].issue_id,
               issuedBooks[i].user_id,
               issuedBooks[i].book_id,
               issuedBooks[i].issue_date,
               issuedBooks[i].due_date,
               issuedBooks[i].return_status ? "Yes" : "No");
    }
}
//FUNCTION NO.7,SEARCH BOOK;
void search_book()
{
    char search_book_id[10],search_title[10],search_author[10];
    int found =0;
    printf("\n ~~~~~ SEARCH BOOKS ~~~~~ \n");

    printf("Enter Book Id:->>\n");
    scanf("%s",&search_book_id);

    printf("Enter Title :->>\n");
    scanf("%s",&search_title);

    printf("Enter Author:->>a\n");
    scanf("%s",&search_author);

    printf("%10s %10s %10s %10s \n","Book Id","Title","Author","Total Copies");
    for (int i = 0; i < book_count; i++)
    {
    int match=1;
     if (strcmp(books[i].book_id, search_book_id) != 0)
            match = 0;
        if ( strcmp(books[i].title, search_title) != 0)
            match = 0;
        if (strcmp(books[i].author, search_author) != 0)
            match = 0;


    if (match)
    {
        printf("%10s %10s %10s %10d \n",
        books[i].book_id,
        books[i].title,
        books[i].author,
        books[i].total_copies);
    found =1;
    }
       
}
if (! found)
{
    printf("NO MATCHING BOOKS IN LIBRARY\n");
}
}

// FUNCTION NO.8,DELETE BOOK;
void delete_book()
{
    char delete_book_id[10];
    int found =0;
    printf("\n ~~~~~ DELETE BOOKS ~~~~~ \n");

    printf("Enter Book Id :->>\n");
    scanf("%s",&delete_book_id);

    
    printf("%10s \n","Book Id");
    for (int i = 0; i < book_count; i++)
    {
   
     if (strcmp(books[i].book_id, delete_book_id) != 0)
          found=1;
       
     printf("BOOK IS SUCCESSESFULLY DELETED With ID IS:->>");

    if (! found)
    {
        printf("%10s \n",
        books[i].book_id);
    found =1;
    }
       
}
if (! found)
{
    printf("NO MATCHING BOOKS IN LIBRARY\n");
}
}