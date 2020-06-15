#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#define D_CRT_NONSTDC_NO_WARNINGS
#define N 50
#define B 30
#define MAX 100
#pragma warning(disable : 4996)

struct books { unsigned long long int isbn; char author[N]; char title[N]; int all; int ava; };
struct books book[MAX];

struct students { char num[8]; char name[B]; char sname[B]; char otch[B]; char fak[4];  char napr[N]; };
struct students student[MAX];

struct users { char login[20]; char pass[20]; int stud; int book; };
struct users user[MAX];

struct sb { unsigned long long int isbn; char num[8]; char date[12]; };
struct sb stud[MAX];

int BookFileOpen();
int StudentFileOpen();
int UserFileOpen();
int StudentBooksFileOpen();

int UserAccess(char* login, char* pass, int usercount);

void StudentAdd(int studcount);
void StudentDelete(int studcount, int studbook);
void BookAdd(int strcount);
void BookDelete(int strcount, int studbook);

void Recovery(int strcount, int q);
void Backup(int strcount, int q);

char* settime(struct tm* u);
char* settm(struct tm* u);
void SeacrhByAuthor(int strcount);
void SearchBySurname(int studcount);

int BookDelCheck(int studbook, unsigned long long int isbn);
int StudentDelCheck(int studbook, char* num);
void CheckInfoStud(int studbook, int strcount, int studcount);
void CheckInfoBook(int studbook, int strcount, int studcount);

void Bookgive(int studbook, int strcount, int studcount);
void Booktake(int studbook, int strcount, int studcount);
int StrInt(char* tmp, char* newtmp);

void log(char* login, char* men);

FILE* file;


void Valid(int q)
{
    if (q == 1)
    {
        if ((file = fopen("users.csv", "r")) == NULL)
        {
            printf("Can't open users.csv");
            exit(1);
        }
    }
    if (q == 2)
    {
        if ((file = fopen("books.csv", "r")) == NULL)
        {
            printf("Can't open books.csv");
            exit(1);
        }
    }
    if (q == 3)
    {
        if ((file = fopen("students.csv", "r")) == NULL)
        {
            printf("Can't open students.csv");
            exit(1);
        }
    }
    if (q == 4)
    {
        if ((file = fopen("student_books.csv", "r")) == NULL)
        {
            printf("Can't open student_books.csv");
            exit(1);
        }
    }
}



int main()
{
    
    int usercoun = UserFileOpen();

    int num, status, tr = 0;
    char pass[20], login[20];

    for (; tr == 0; )
    {
        printf("Login: "); scanf("%s", login);
        printf("Password: "); scanf("%s", pass);
        status = UserAccess(login, pass, usercoun);
        if (status != 0) tr = 1;
    }
    bool Adm = false;
    system("cls");

    for (;;)
    {
        tr = 0;
        if (status == 1)
        {
            Adm = true;
            printf("Admin menu:\n 1.book \n 2.Student \n 3.Exit \n");
            scanf("%d", &status);
            for (; tr == 0;)
            {
                if (status == 2) tr = 1;
                else if (status == 3) exit(0);
                else if (status == 1) { tr = 1; status = 3; }
                else printf("wrong number");
            }
            system("cls");
        }
        if ((status == 2) && (Adm == true))
            printf("\nmenu:\n 0.Back \n 1.Add student \n 2.Delete student \n 3.Do backup student \n 4.Recovery student \n 5.Search student \n 6.Student Book Information \n 7.Exit \n");

        if ((status == 2) && (Adm == false))
            printf("\nmenu:\n 1.Add student \n 2.Delete student \n 3.Do backup student \n 4.Recovery student \n 5.Search student \n 6.Student Book Information \n 7.Exit \n");

        if ((status == 3) && (Adm == true))
            printf("\nmenu:\n 0.Back \n 1.Add book \n 2.Delete book \n 3.Do backup book \n 4.Recovery \n 5.Find book by Author \n 6.Student Book Information \n 7.Give Book \n 8.Take Book \n 9.Exit \n");

        if ((status == 3) && (Adm == false))
            printf("\nmenu:\n 1.Add book \n 2.Delete book \n 3.Do backup book \n 4.Recovery \n 5.Find book by Author \n 6.Student Book Information \n 7.Give Book \n 8.Take Book \n 9.Exit \n");
        
        int strcoun = BookFileOpen();
        int studcoun = StudentFileOpen();
        int studbook = StudentBooksFileOpen();

        scanf("%d", &num);
        if (status == 2)
        {
            system("cls");
           if ((num == 0) && (Adm == 1))
                status = 1;
            else if (num == 1)
            {
                char a[18] = {"Student Add"}; log(login, a);
                StudentAdd(studcoun);
            }
            else if (num == 2)
            {
                char a[18] = { "Student Delete" }; log(login, a);
                StudentDelete(studcoun, studbook); 
            }
            else if (num == 3)
            {
                char a[18] = { "Backup Stud" }; log(login, a);
                Backup(studcoun, 2);
            }
            else if (num == 4)
            {
                char a[18] = { "Recovery Stud" }; log(login, a);
                Recovery(studcoun, 2);
            }
            else if (num == 5)
            {
                char a[18] = { "Search Surname" }; log(login, a);
                SearchBySurname(studcoun);
            }
            else if (num == 6)
            {
                char a[18] = { "Check Info Stud" }; log(login, a);
                CheckInfoStud(studbook, strcoun, studcoun);
            }
            else if (num == 7)
            {
                char a[18] = { "Exit" }; log(login, a);
                break;
            }
            else { printf("wrong num\n"); }
        }
        if (status == 3)
        {
            system("cls");
            if ((num == 0) && (Adm == 1))
                status = 1;
            else if (num == 1)
            {
                char a[18] = { "Book Add" }; log(login, a);
                BookAdd(strcoun);
            }
            else if (num == 2)
            {
                char a[18] = { "Book Delete" }; log(login, a);
                BookDelete(strcoun, studbook);
            }
            else if (num == 3)
            {
                char a[18] = { "Backup Book" }; log(login, a);
                Backup(strcoun, 1);
            }
            else if (num == 4)
            {
                char a[18] = { "Recovery Book" }; log(login, a);
                Recovery(strcoun, 1);
            }
            else if (num == 5)
            {
                char a[18] = { "Search Author" }; log(login, a);
                SeacrhByAuthor(strcoun);
            }
            else if (num == 6)
            {
                char a[18] = { "Check Info" }; log(login, a);
                CheckInfoBook(studbook, strcoun, studcoun);
            }
            else if (num == 7)
            {
                char a[18] = { "Book Give" }; log(login, a);
                Bookgive(studbook, strcoun, studcoun);
            }
            else if (num == 8)
            {
                char a[18] = { "Book Take" }; log(login, a);
                Booktake(studbook, strcoun, studcoun);
            }
            else if (num == 9)
            {
                char a[18] = { "Exit" }; log(login, a);
                break;
            }
            else { printf("wrong num\n"); }
        }
    }
    return 0;
}

int UserAccess(char* login, char* pass, int usercount)
{
   int i = 0;
    for (int y = 0; y < usercount; y++)
    {
        if ((strcmp(login, user[y].login) == 0) && (strcmp(pass, user[y].pass) == 0))
        {
            if ((user[y].stud == 1) && (user[y].book == 1))
                i = 1;
            if ((user[y].stud == 1) && (user[y].book == 0))
                i = 2;
            if ((user[y].stud == 0) && (user[y].book == 1))
                i = 3;
                break;
        }
    }
    if (i == 0)
        printf("Wrong login/pass\ntry again\n");
    return i;
}


int StudentBooksFileOpen()
{
    Valid(4);

    int i;
    for (i = 0; !feof(file); i++)
    {
        fscanf(file, "%lld", &stud[i].isbn);
        getc(file);
        fscanf(file, "%[^;]%*c", stud[i].num);
        fscanf(file, "%[^'\n']%*c", stud[i].date);
    }
    fclose(file);
    return i;
}


int UserFileOpen()
{
    Valid(1);

    int i;
    for (i = 0; !feof(file); i++)
    {
        fscanf(file, "%[^;]%*c", user[i].login);
        fscanf(file, "%[^;]%*c", user[i].pass);
        fscanf(file, "%d", &user[i].stud);
        getc(file);
        fscanf(file, "%d", &user[i].book);
        getc(file);
    }
    fclose(file);
    return i;
}

int BookFileOpen()
{
    Valid(2);
    int i;
    for (i = 0; !feof(file); i++)
    {
        fscanf(file, "%lld", &book[i].isbn);
        getc(file);
        fscanf(file, "%[^;]%*c", book[i].author);
        fscanf(file, "%[^;]%*c", book[i].title);
        fscanf(file, "%d", &book[i].all);
        getc(file);
        fscanf(file, "%d", &book[i].ava);
        getc(file);
    }
    fclose(file);
    return i;
}




void BookAdd(int strcount)
{
    unsigned long long int isbn;
    char author[N], title[N];
    int all, ava;
    int q = 0;

    
    Valid(2);
    fclose(file);

    file = fopen("books.csv", "a+");

    printf("ISBN knigi, kotoruy nado dobavit': ");
    scanf("%lld", &isbn);

    for (int y = 0; y < strcount; y++)
    {
        if (isbn == book[y].isbn)
        {
            printf("Uzhe sush."); 
            exit(2);                                        
        }
    }

    printf("Author: ");   scanf("%s", author);
    printf("title: ");
    char c = getchar();
    while ((c = getchar()) != '\n')
    {
        title[q] = c; q++;
    }
    title[q] = '\0';

    printf("Total books: ");      scanf("%d", &all);
    printf("available: ");        scanf("%d", &ava);

    fprintf(file, "\n%lld;%s;%s;%d;%d", isbn, author, title, all, ava);
    fclose(file);
    printf("\nBook added\n");
}




int BookDelCheck(int studbook, unsigned long long int isbn)
{
    int error = 0;
    for (int i = 0; i < studbook; i++)
    {
        if (stud[i].isbn == isbn)
            error = 1;
    }
    return error;
}

void BookDelete(int strcount, int studbook)
{
    unsigned long long int isbn;

    Valid(2);
    fclose(file);

    printf("ISBN knigi, kotoruy nado udalit': ");
    scanf("%lld", &isbn);

    int error = BookDelCheck(studbook, isbn);

    if (error == 0)
    {
        file = fopen("books.csv", "r");
        char* a = (char*)malloc(strcount * (sizeof(struct books)));
        int w = 0;

        for (int y = 0; y < strcount; y++)
        {
            if (isbn != book[y].isbn)
            {
                a[w] = getc(file);
                while ((a[w] != '\n') && (!feof(file)))
                {
                    w++;
                    a[w] = getc(file);
                }
                a[w] = '\n'; w++;
            }
            if (isbn == book[y].isbn)
            {
                while ((getc(file) != '\n') && (!feof(file)))
                {
                    ;
                }
            }
        }
        a[w - 1] = '\0';
        fclose(file);

        file = fopen("books.csv", "w");

        for (int n = 0; a[n] != '\0'; n++)
            fprintf(file, "%c", a[n]);

        fclose(file);
        printf("\nBook deleted\n");
    }
    else
    {
        printf("\nEta kniga est' u studenta\n");
    }
}



void SeacrhByAuthor(int strcount)
{
    
    int i = 0;
    printf("Author surname: ");
    char c = getchar();
    c = getchar();
    char surname[N];
    while (c != '\n')
    {
        surname[i] = c;
        i++;
        c = getchar();
    }
    surname[i] = '\0';

    for (int y = 0; y < strcount; y++)
    {
        if (strcmp(surname, book[y].author) == 0)
        {
            printf("ISBN: %lld \t ", book[y].isbn);
            printf("Author: %s \t", book[y].author);
            printf("Title: %s \t", book[y].title);
            printf("Total books: %d \t", book[y].all);
            printf("available: %d\n", book[y].ava);
        }
    }
    printf("\n");
}





int StudentFileOpen()
{
    Valid(3);
    int i;
    for (i = 0; !feof(file); i++)
    {
        fscanf(file, "%[^;]%*c", student[i].num);
        fscanf(file, "%[^;]%*c", student[i].sname);
        fscanf(file, "%[^;]%*c", student[i].name);
        fscanf(file, "%[^;]%*c", student[i].otch);
        fscanf(file, "%[^;]%*c", student[i].fak);
        fscanf(file, "%[^'\n']%*c", student[i].napr);

    }
    fclose(file);
    return i;
}





void StudentAdd(int studcount)
{
    char num[8];
    char name[B];
    char sname[B];
    char otch[B]; 
    char fak[4]; 
    char napr[N];
   
    Valid(3);
    fclose(file);

    file = fopen("students.csv", "a+");

    printf("Zachetka studenta dlya dobavleniya: ");
    scanf("%s", num);

    int y;
    for (y = 0; y < studcount; y++)
    {
        if (strcmp(num, student[y].num) == 0)
        {
            printf("Uzhe sush.");
            exit(2);
        }
    }
    
    printf("Surname: "); scanf("%s", sname);
    printf("Name: ");  scanf("%s", name);
    printf("Patronymic: "); scanf("%s", otch);
    printf("Facultet: "); scanf("%s", fak);
    printf("Napravlenie: ");  
    int q = 0;
    char c = getchar();
    while ((c = getchar()) != '\n')
    {
        napr[q] = c; q++;
    }
    napr[q] = '\0';
    
    fprintf(file, "\n%s;", num);
    fprintf(file, "%s;", sname);
    fprintf(file, "%s;", name);
    fprintf(file, "%s;", otch);
    fprintf(file, "%s;", fak);
    fprintf(file, "%s", napr);

    fclose(file);
    printf("\nStudent added\n");
}




int StudentDelCheck(int studbook, char* num)
{
    int error = 0;
    for (int i = 0; i < studbook; i++)
    {
        if (strcmp(num, stud[i].num) == 0)
            error = 1;
    }
    return error;
}

void StudentDelete(int studcount, int studbook)
{
    char num[8];
    int w = 0;

    
    Valid(3);
    fclose(file);

    printf("Zachetka studenta dlya udaleniya: ");
    scanf("%s", num);

    int error = StudentDelCheck(studbook, num);
    if (error == 0)
    {
        file = fopen("students.csv", "r");
        char* a = (char*)malloc(studcount*(sizeof(struct students)));

        for (int y = 0; y < studcount; y++)
        {
            if (strcmp(num, student[y].num) == 0)
            {
                while ((getc(file) != '\n') && (!feof(file)))
                {
                    ;
                }
            }
            if (strcmp(num, student[y].num) != 0)
            {
                a[w] = getc(file);
                while ((a[w] != '\n') && (!feof(file)))
                {
                    w++;
                    a[w] = getc(file);
                }
                a[w] = '\n'; w++;
            }
        }
        a[w - 1] = '\0';
        fclose(file);

        file = fopen("students.csv", "w");

        for (int n = 0; a[n] != '\0'; n++)
            fprintf(file, "%c", a[n]);

        fclose(file);
        printf("Student deleted\n");
    }
    else
    {
        printf("\nU studenta est' kniga\n");
    }
}




void SearchBySurname(int studcount)
{
   
    char surname[N];
    printf("Student's surname: ");
    scanf("%s", surname);

    for (int y = 0; y < studcount; y++)
    {
        if (strcmp(surname, student[y].sname) == 0)
        {
            printf("Zachetka: %s \t ", student[y].num);
            printf("Surname: %s \t", student[y].sname);
            printf("Name: %s \t", student[y].name);
            printf("Patronymic: %s \t", student[y].otch);
            printf("Facultet: %s\t", student[y].fak);
            printf("Napravlenie: %s\n", student[y].napr);
        }
    }
    printf("\n");
}





void Recovery(int strcount,int q)
{
    int y;
    char name[MAX];
    int b = 0;
   
    if (q == 1)
        printf("File name <<books_DD.MM.YYYY HH.MM.csv>>: ");
    if (q == 2)
        printf("File name <<students_DD.MM.YYYY HH.MM.csv>>: ");

    char c = getchar();
    c = getchar();
    while (c != '\n')
    {
        name[b] = c;
        b++;
        c = getchar();
    }
    name[b] = '\0';

    fclose(file);

    file = fopen(name, "r");

    char* a = (char*)malloc((sizeof(char)));
    int n = 0;

    for (y = 0; !feof(file); y++)
    {
        a = (char*)realloc(a, (y + 1) * (sizeof(char)));
        a[y] = getc(file);
    }
    a[y - 1] = '\0';

    fclose(file);

    if (q == 1)
    {
        file = fopen("books.csv", "w");
    }
    if (q == 2)
        file = fopen("students.csv", "w");

    for (int e = 0; (a[e] != '\0'); e++)
        fprintf(file, "%c", a[e]);

    fclose(file);

    printf("File vos. iz %s", name);
    printf("\n");
}





char* settime(struct tm* u)
{
    char s[20];
    char* tmp;
    for (int i = 0; i < 20; i++) s[i] = 0;
    int length = strftime(s, 20, "%d.%m.%Y %H.%M", u);
    tmp = (char*)malloc(sizeof(s));
    strcpy(tmp, s);
    return(tmp);
    free(tmp);
    free(s);
}

void Backup(int strcount, int q)
{
    int y;
    struct tm* u;
    char* stri;
    const time_t timer = time(NULL);
    u = localtime(&timer);
    stri = settime(u);

    char* a = 0;
    char name[31];
    if (q == 1)
    {
        Valid(2);
        a = (char*)malloc(strcount * (sizeof(struct books)));
        name[0] = 'b'; name[1] = 'o'; name[2] = 'o'; name[3] = 'k'; name[4] = 's'; name[5] = '_';
        for (int lon = 6; stri[lon - 6] != '\0'; lon++)
        {
            name[lon] = stri[lon - 6];
        }
        name[19] = '.'; name[22] = '.'; name[23] = 'c'; name[24] = 's'; name[25] = 'v'; name[26] = '\0';
    }
    if (q == 2)
    {
        Valid(3);
        a = (char*)malloc(strcount * (sizeof(struct students)));
        name[0] = 's'; name[1] = 't'; name[2] = 'u'; name[3] = 'd'; name[4] = 'e'; name[5] = 'n';
        name[6] = 't'; name[7] = 's'; name[8] = '_';

        for (int lon = 9; stri[lon - 9] != '\0'; lon++)
        {
            name[lon] = stri[lon - 9];
        }
        name[22] = '.'; name[25] = '.'; name[26] = 'c'; name[27] = 's'; name[28] = 'v'; name[29] = '\0';
    }

    for (y = 0; !feof(file); y++)
    {
        a[y] = getc(file);
    }
    a[y - 1] = '\0';

    file = fopen(name, "w");

    for (int e = 0; (a[e] != '\0'); e++)
        fprintf(file, "%c", a[e]);

    fclose(file);

    if ((file = fopen(name, "r")) != NULL)
    {
        printf("Success\n");
        printf("Created %s", name);
    }
    else printf("\nerror");
    printf("\n");
}





void CheckInfoStud(int studbook, int strcount, int studcount)
{
    
    Valid(2);
    fclose(file);
    Valid(4);
    fclose(file);
    char zachnum[8];
    bool t = false;
    bool f = false;

    printf("Zachetka:");
    scanf("%s", zachnum);

    for (int i = 0; i < studcount; i++)
    {
        if (strcmp(zachnum, student[i].num) == 0)
        {
            t = true;
        }
    }

    if (t == true)
    {
        for (int i = 0; i < studbook; i++)
        {
            if (strcmp(zachnum, stud[i].num) == 0)
            {
                f = true;
                printf("Date: %s \n ", stud[i].date);
                for (int j = 0; j < strcount; j++)
                {
                    if (stud[i].isbn == book[j].isbn)
                    {
                        printf("ISBN: %lld \t ", book[j].isbn);
                        printf("Author: %s \t", book[j].author);
                        printf("Title: %s \t", book[j].title);
                       
                    }
                }
                printf("\n");
            }
        }
        if (f == false)
            printf("\nU studenta net knig\n");
    }
    if (t == false)
        printf("\nStudenta ne sush.\n");
}

void CheckInfoBook(int studbook, int strcount, int studcount)
{
    
    Valid(2);
    fclose(file);
    Valid(4);
    fclose(file);
    unsigned long long int isbn;
    bool t = false;
    bool f = false;

    printf("ISBN:");
    scanf("%lld", &isbn);

    for (int i = 0; i < strcount; i++)
    {
        if (isbn == book[i].isbn)
        {
            t = true;
        }
    }
    
    if (t == true)
    {
        for (int j = 0; j < studbook; j++)
        {
            if (isbn == stud[j].isbn)
            {
                f = true;
                printf("\nDate: %s\n", stud[j].date);

                for (int i = 0; i < studcount; i++)
                {
                    if (strcmp(stud[j].num, student[i].num) == 0)
                    {
                        printf("Zachetka: %s \t ", student[i].num);
                        printf("Surname: %s \t", student[i].sname);
                        printf("Name: %s \t", student[i].name);
                        printf("Patronymic: %s \t", student[i].otch);
                        printf("Facultet: %s\t", student[i].fak);
                        printf("Napravlenie: %s\n", student[i].napr);
                    }
                }
            printf("\n");
            }
        }
    if (f == false)
        printf("\nKnigu ne brali\n");
    }
    if (t == false)
        printf("\nKniga ne naydena\n");
}




void Bookgive(int studbook, int strcount,int studcount)
{
   
    unsigned long long int isbn;
    char num[8];
    int checkbook = 0;
    bool dat = false;
    int checkstudent = 0;
    int i;
    int checkdate;

    printf("ISBN: ");
    scanf("%lld", &isbn);
    Valid(2);
    for (i = 0; i < strcount; i++)
    {
        if (isbn == book[i].isbn)
        {
            checkbook = 1;
            if (book[i].ava > 0)
            {
                checkbook = 2;
                break;
            }
        }
    }

    fclose(file);

    if (checkbook == 0) printf("Kniga ne naydena");

    if (checkbook == 1)
    {
        printf("Knig net\n");
        char* date = 0;
        for (i = 0; i < studbook; i++)
        {
            if ((isbn == stud[i].isbn)&&(dat == false))
            {
                date = stud[i].date;
                dat = true;
                i++;
            }
            if ((isbn == stud[i].isbn) && (dat == true))
            {
               checkdate = StrInt(stud[i].date, date);
               if (checkdate == 2)
                   date = stud[i].date;
            }
        }
        checkstudent = 1;
        printf("Data sdachi: %s\n", date);
    }
    
    if (checkbook == 2)
    {
        printf("Zachetka: ");
        scanf("%s", num);

        Valid(3);
        for (i = 0; i < studcount; i++)
        {
            if (strcmp(num, student[i].num) == 0)
            {
                checkstudent = 2;
            }
        }
        fclose(file);
    }
    
    if (checkstudent == 0)
        printf("student ne nayden\n");

    if ((checkstudent == 2) && (checkbook == 2))
    {
        for (int i = 0; i < strcount; i++)
        {
            if (isbn == book[i].isbn)
                book[i].ava--;
        }
        file = fopen("books.csv", "w");
        for (int i = 0; i < strcount; i++)
        {
            fprintf(file, "%lld;", book[i].isbn);
            fprintf(file, "%s;", book[i].author);
            fprintf(file, "%s;", book[i].title);
            fprintf(file, "%d;", book[i].all);
            if (i == (strcount - 1))
                fprintf(file, "%d", book[i].ava);
            else
                fprintf(file, "%d\n", book[i].ava);
        }
        fclose(file);

        file = fopen("student_books.csv", "a");
        
        struct tm* u;
        char* stri;
        time_t timer = time(NULL);
        timer += 604800;
        u = localtime(&timer);
        stri = settime(u);

        char givedate[11];
        for (i = 0; i < 10; i++)
        {
            givedate[i] = stri[i];
        }
        givedate[10] = '\0';

            fprintf(file, "\n%lld;", isbn);
            fprintf(file, "%s;", num);
            fprintf(file, "%s", givedate);
        
        fclose(file);
        printf("kniga vidana\n");
    }
}

int StrInt(char* newtmp, char* tmp)
{
    int day = 0;
    int month = 0;
    int year = 0;
    int nday = 0;
    int nmonth = 0;
    int nyear = 0;

    day = (tmp[0] - '0') * 10;
    day += (tmp[1] - '0');

    month = (tmp[3] - '0') * 10;
    month += (tmp[4] - '0');

    year = (tmp[6] - '0') * 10;
    year += (tmp[7] - '0');
    year *= 10;
    year += (tmp[8] - '0');
    year *= 10;
    year += (tmp[9] - '0');

    nday = (newtmp[0] - '0') * 10;
    nday += (newtmp[1] - '0');

    nmonth = (newtmp[3] - '0') * 10;
    nmonth += (newtmp[4] - '0');

    nyear = (newtmp[6] - '0') * 10;
    nyear += (newtmp[7] - '0');
    nyear *= 10;
    nyear += (newtmp[8] - '0');
    nyear *= 10;
    nyear += (newtmp[9] - '0');

    if (nyear == year)
    {
        if (nmonth == month)
        {
            if (nday == day)
            {
                return 1;
            }
            if (nday < day)
            {
                return 2;
            }
            else return 3;
        }
        if (nmonth < month)
        {
            return 2;
        }
        else return 3;
    }
    if (nyear < year)
    {
        return 2;
    }
    else return 3;
}


void Booktake(int studbook, int strcount, int studcount)
{
    
    unsigned long long int isbn;
    char num[8];
    int checkbook = 0;
    bool dat = false;
    int checkstudent = 0;
    int i;
    int checkdate;
    int w = 0;

    printf("ISBN: ");
    scanf("%lld", &isbn);
    Valid(2);
    for (i = 0; i < strcount; i++)
    {
        if (isbn == book[i].isbn)
        {
            checkbook = 1;
            if (book[i].ava < book[i].all)
            {
                checkbook = 2;
                break;
            }
        }
    }

    fclose(file);

    if (checkbook == 0) printf("Kniga ne naydena");

    if (checkbook == 1)
    {
        printf("Vse knige v biblioteke\n");   
        checkstudent = 1;
    }

    if (checkbook == 2)
    {
        printf("Zachetka: ");
        scanf("%s", num);

        Valid(3);
        for (i = 0; i < studcount; i++)
        {
            if (strcmp(num, student[i].num) == 0)
            {
                checkstudent = 2;
            }
        }
        fclose(file);
    }

    if (checkstudent == 0)
        printf("student ne nayden\n");

    if ((checkstudent == 2) && (checkbook == 2))
    {
        for (int i = 0; i < strcount; i++)
        {
            if (isbn == book[i].isbn)
                book[i].ava++;
        }

        Valid(4);
        char* a = (char*)malloc(studbook*(sizeof(struct sb)));

        for (int y = 0; y < studbook; y++)
        {
            if ((strcmp(num, stud[y].num) == 0) && (isbn == stud[y].isbn))
            {
                while ((getc(file) != '\n') && (!feof(file)))
                {
                    ;
                }
            }
            else
            {
                a[w] = getc(file);
                while ((a[w] != '\n') && (!feof(file)))
                {
                    w++;
                    a[w] = getc(file);
                }
                a[w] = '\n'; w++;
            }
        }
        a[w - 1] = '\0';
        fclose(file);

        file = fopen("student_books.csv", "w");
        for (int n = 0; a[n] != '\0'; n++)
            fprintf(file, "%c", a[n]);

        fclose(file);
        
        file = fopen("books.csv", "w");
        for (int i = 0; i < strcount; i++)
        {
            fprintf(file, "%lld;", book[i].isbn);
            fprintf(file, "%s;", book[i].author);
            fprintf(file, "%s;", book[i].title);
            fprintf(file, "%d;", book[i].all);
            if (i == (strcount - 1))
                fprintf(file, "%d", book[i].ava);
            else
                fprintf(file, "%d\n", book[i].ava);
        }
        fclose(file);
        printf("Kniga prinyata\n");
    }
}



char* settm(struct tm* u)
{
    char s[20];
    char* tmp;
    for (int i = 0; i < 20; i++) s[i] = 0;
    int length = strftime(s, 20, "%d.%m.%Y %H:%M:%S", u);
    tmp = (char*)malloc(sizeof(s));
    strcpy(tmp, s);
    return(tmp);
    free(tmp);
    free(s);
}


void log(char* login, char* men)
{
    struct tm* u;
    char* stri;
    const time_t timer = time(NULL);
    u = localtime(&timer);
    stri = settm(u);

    file = fopen("library.log", "a");
    fprintf(file, "%s;", stri);
    fprintf(file, "%s;", login);
    fprintf(file, "%s\n", men);
    fclose(file);
}
