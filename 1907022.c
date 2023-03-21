//tested by nihal!
#include<stdio.h>
#include<conio.h>    //For using system("cls") function
#include<stdlib.h>
#include<string.h>  //For using string functions such as strcpy,strcmp


//defining function prototype

int main();
void admin_panel();
void admin_account();
void teachers_account();
void teachers_information();
void assign_courses();
void students_account();
void students_information();

void teacher_panel();
void class_test_marks();
void finding_students();
void count_of_students();

int student_login();
void student_panel();



//Making admin ,teacher and student as user-defined structure type

typedef struct
{
    char username[20];
    char password[16];
    char name[25];
} admin;

typedef struct
{
    char username[20];
    char password[16];
    char name[25];
    char course[20][15];
} teacher;

typedef struct
{
    char username[20]; //As a string
    char password[16];
    char first_name[20];
    char last_name[20];
    char course[20][15];  //2D character type as an array of 20 strings
    int roll;
    int mark[20];  //As an array
} student;


//Declaring course as a global variable

char course[1][15]= {"Not Assigned"};



// Function to see student's profile that includes all the information of the student

void student_panel(int a) //student's roll number is received
{
    system("cls");  //To clear the display area of the console
    puts("\t\t ***** Student Profile ***** \n");
    student student_profile; //'student_profile' is declared as a structure type variable
    FILE *p;
    p=fopen("Students Information.txt","r"); //Opening the existing data file for reading only
    if(p==NULL) //If the data file does not exist NULL value is returned
    {
        fclose(p);
        puts("** Your profile has not been created yet !!\n");
        printf("To try again enter(y/Y) otherwise (n/N) : ");
        char c;
        scanf("%c",&c);
        getchar();
        if(c=='y'|| c=='Y')
            student_login();
        else
            main();
    }
    while(fread(&student_profile,sizeof(student_profile),1,p)>0) //Reading data from the data file and storing it in 'student_profile'
    {
        //if the data file is read then while loop is executed

        if(a==student_profile.roll) //matching the roll number
        {
            break; //If the roll number is matched then out of the loop
        }
    }
    fclose(p);  //Closing the data file
    if(a!=student_profile.roll)   //checking if the roll number is found or not
    {
        fclose(p);
        puts("** Your profile has not been created yet !!\n");
        printf("To try again enter(y/Y) otherwise (n/N) : ");
        char ch;
        scanf("%c",&ch);
        getchar();
        if(ch=='y'|| ch=='Y')
            student_login();
        else
            main();
    }
    printf("Full Name : %s %s\n",student_profile.first_name,student_profile.last_name);
    printf("\n* Roll : %d",student_profile.roll);
    int i;
    for(i=0; i<20; i++)
    {
        if(strcmp(student_profile.course[i],course[0])==0)
            continue; //If the condition is true then back to 'for' loop increment/decrement section
        printf("\nCourse : %s \t\t Mark : %d",student_profile.course[i],student_profile.mark[i]);
    }
    puts("\n\nNow what would you like to do ?\n");
    puts("1.Try login to another account");
    puts("2.Back to login section");
    puts("3.Exit");
X:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&i);
    getchar();
    if(i==1)
        student_login();
    else if(i==2)
        main();
    else if(i==3)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n* Invalid choice. Please try again.");
        goto X;
    }
}



//Function for student login

int student_login() //As the function returns an integer type value
{
X:
    system("cls"); //To clear the display area of the console
    puts("\t\t********** Student login Section **********\n\n");
    FILE *login;
    login=fopen("Students Information.txt","r"); //Opening the existing data file for reading only
    if(login==NULL) //If the data file does not exist NULL value is returned
    {
        fclose(login);
        puts("\t* Cannot login as student\n");
        puts("\t* Student account hasn't been created yet.\n");
        printf("Enter (y/Y) to go back to login section otherwise (n/N) : ");
        char c;
        scanf("%c",&c);
        getchar();
        if(c=='y'||c=='Y')
            main();
        else
        {
            puts("\n***** Thanks *****\n");
            exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
        }
    }
    student student_user,student_login; //'student_user' for getting input from the user and 'student_login' for storing data from the data file
    printf("Username : ");
    gets(student_user.username);
    printf("Password : ");
    gets(student_user.password);
    int a=1;
    while(fread(&student_login,sizeof(student_login),1,login)>0) //Reading data from the data file and storing it in 'student_login'
    {
        //if the data file is read then while loop is executed

        a=strcmp(student_login.username,student_user.username) || strcmp(student_login.password,student_user.password);

        //if the username and password are matched then 0 is returned and assigned to 'a'

        if(a==0)
        {
            fclose(login); //closing the data file
            student_panel(student_login.roll);  //passing the roll number to 'student_panel' function
        }
    }
    fclose(login); //Closing the data file
    if(a!=0) //Checking whether the username and password are matched or not
    {
        puts("\n* Username or Password Incorrect !\n");
        puts("\tOr Maybe the account has not been created yet !\n");
        printf("Enter (y/Y) to try again otherwise (n/N) : ");
        char ch;
        scanf("%c",&ch);
        getchar();
        if(ch=='y'||ch=='Y')
            goto X; //Back to the beginning of the 'student_login' function
        else
            main();
    }
}


//Function to count the number of total students

void count_of_students() //As the function does not return any value
{
    system("cls"); //To clear the console display area
    puts("\t\t********** Teacher Panel - Count of Students **********\n\n");
    student students;
    FILE *a;
    a=fopen("Students Information.txt","r"); //Opening the existing data file for reading only
    if(a==NULL) //If the data file does not exist NULL value is returned
    {
        fclose(a);
        puts("* No student account has been created yet !!\n");
        printf("Enter (y/Y) to go back to teacher panel otherwise (n/N) : ");
        char c;
        scanf("%c",&c);
        getchar();
        if(c=='y'||c=='Y')
            teacher_panel();
        else
            main();
    }
    puts("Roll,Course and Marks of the available students are given below->");
    int count=0,i;
    while(fread(&students,sizeof(students),1,a)>0) //Reading the data file and storing the read data in 'students'
    {
        //If the data file is read then while loop is executed

        printf("\n* Roll : %d",students.roll);
        for(i=0; i<20; i++)
        {
            if(strcmp(students.course[i],course[0])==0) //checking if the course is assigned or not
                continue; //If the course name is matched then the condition is true and back to for loop increment/decrement section
            printf("\nCourse : %s \t Mark : %d",students.course[i],students.mark[i]);
        }
        count++; //for each time while loop is executed the value of 'count' is increased by 1
    }
    fclose(a); //Closing the data file
    if(count==0) //Checking if any student is found
    {
        puts("* Either any students account has not been created yet!\n");
        puts("* Or You haven't provided any marks to the students yet.");
    }
    else
        printf("\n\n**Total number of students : %d\n",count);
    puts("\nNow what would you like to do ?\n");
    puts("1.Provide class test marks to the students");
    puts("2.Find the students using their first name");
    puts("3.Back to teacher panel");
    puts("4.Back to login section");
    puts("5.Exit");
Y:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&i);
    getchar();
    if(i==1)
        class_test_marks();
    else if(i==2)
        finding_students();
    else if(i==3)
        teacher_panel();
    else if(i==4)
        main();
    else if(i==5)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n* Invalid choice. Please try again.");
        goto Y;
    }
}


//Function to find a student using the first name

void finding_students()
{
X:
    system("cls");  //Clears the console display area
    puts("\t\t********** Teacher Panel - Finding Student **********\n\n");
    student students;
    char name[20];
    printf("Enter the first name of the student : ");
    gets(name);  //To get the student name with whitespaces
    FILE *n;
    n=fopen("Students Information.txt","r"); //Opening the existing data file for reading only
    if(n==NULL) //If the data file does not exist NULL value is returned
    {
        fclose(n);
        puts("\n* Students account has not been created yet.");
        printf("\nEnter (y/Y) to go back to teacher panel otherwise (n/N) : ");
        char c;
        scanf("%c",&c);
        getchar();
        if(c=='y'||c=='Y')
            teacher_panel();
        else
            main();
    }
    int a=1;
    while(fread(&students,sizeof(students),1,n)>0) //Reading the data file and storing the data in 'students'
    {
        //If the data file is read then while loop is executed

        if(strcmp(students.first_name,name)==0) /* If the name from the user input and data file is matched
                                                 then 0 is returned and the condition becomes true */
        {
            a=0;
            puts("\n* Student Found !");
            break; // Out of the loop
        }
    }
    fclose(n); //Closing the data file
    if(a!=0) //Checking if the name is matched
    {
        puts("\n** Invalid name or This student's account has not been created yet.");
        printf("Enter (y/Y) to try again otherwise (n/N) : ");
        char ch;
        scanf("%c",&ch);
        getchar();
        if(ch=='y'||ch=='Y')
            goto X; //Back to beginning at the 'finding_students' function
        else
            teacher_panel();
    }
    printf("\nStudent's full name : %s %s\n",students.first_name,students.last_name);
    printf("Roll no : %d\n",students.roll);
    int j;
    for(j=0; j<20; j++)
    {
        if(strcmp(students.course[j],course[0])==0) //checking if the course is assigned or not
            continue; //If the condition is true then back to 'for' loop increment/decrement section
        printf("Course : %s \t\t Mark: %d\n",students.course[j],students.mark[j]);
    }
    puts("\nNow what would you like to do ?\n");
    puts("1.Find another student using first name");
    puts("2.Provide class test marks to the students");
    puts("3.Count the students");
    puts("4.Back to teacher panel");
    puts("5.Back to login section");
    puts("6.Exit");
Y:
    printf("\nEnter a number as your choice : ");
    int i;
    scanf("%d",&i);
    getchar();
    if(i==1)
        finding_students();
    else if(i==2)
        class_test_marks();
    else if(i==3)
        count_of_students();
    else if(i==4)
        teacher_panel();
    else if(i==5)
        main();
    else if(i==6)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n* Invalid choice. Please try again.");
        goto Y;
    }
}


//Function to provide class test marks

void class_test_marks() //The function does not return any value
{
    system("cls"); //Clears the console display area
    puts("\t\t********** Teacher Panel - Provide Class Test Marks **********\n");
    student student_old,student_new;
    FILE *old;
    FILE *n;
    old=fopen("Students Information.txt","r"); //Opening the existing data file for reading only
    if(old==NULL) //If the file does not exist NULL value is returned
    {
        fclose(old);
        puts("\n** Student file has not been created yet !");
        printf("\n* To go back to teacher panel enter(y/Y) otherwise (n/N) :");
        char c;
        scanf("%c",&c);
        getchar();
        if(c=='y'||c=='Y')
            teacher_panel();
        else
            main();
    }
    n=fopen("Temp.txt","w+"); //Creates a new file for both reading and writing
    if(n==NULL) //If the file is not created then NULL value is returned
    {
        fclose(old);  //Closing the data file
        fclose(n);
        puts("\n** Cannot provide class test marks");
        printf("\n* To try again enter (y/Y) otherwise (n/N) : ");
        char ch;
        scanf("%c",&ch);
        getchar();
        if(ch=='y'||ch=='Y')
            class_test_marks();
        else
            teacher_panel();
    }
    char course_name[1][15]; // 1 string to get the input of course name from the user
    puts("* To provide class test marks enter the roll and course name\n");
    printf("Roll : ");
    scanf("%d",&student_new.roll);
    getchar();
    printf("Course : ");
    gets(course_name[0]);
    int i,j=20,b=1;
    while(fread(&student_old,sizeof(student_old),1,old)>0) //Reading the data file and storing the data in 'student_old'
    {
        //If the data file is read then while loop is executed

        if(student_new.roll==student_old.roll) //Checking if the roll number from the user input and the data file is matched
        {
            student_new=student_old; //Copying all the elements of 'student_old' to 'student_new'
            for(i=0; i<20; i++)
            {
                if(strcmp(student_new.course[i],course_name[0])==0) //Checking if the course name is matched
                {
                    puts("\n** Student found !!\n");
                    j=i; //assigning the index no (which course name is matched with the user input course name) to 'j'
                    b=0;
                    continue; //Back to the 'for' loop increment/decrement section
                }
            }
            continue; //Back to the 'while' loop condition
        }
        fwrite(&student_old,sizeof(student_old),1,n); /*writing all data (read from the 'Students Information.txt' named file)
                                                       except the one (which roll is matched) to a new file named 'Temp.txt'*/
    }
    if(b!=0) //Checking if the roll no and the course name are matched
    {
        fclose(old); //Closing the data file
        fclose(n); //Closing the data file
        remove("Temp.txt"); //Removes 'Temp.txt' file
        printf("\n* Roll %d hasn't taken the course %s\n",student_new.roll,course_name[0]);
        printf("\n* To try again enter (y/Y) otherwise (n/N) : ");
        char ch;
        scanf("%c",&ch);
        getchar();
        if(ch=='y'||ch=='Y')
            class_test_marks();
        else
            teacher_panel();
    }
    puts("\n\n\t**********\n");
    printf("Student's full name : %s %s\n",student_new.first_name,student_new.last_name);
    printf("Roll no : %d\n",student_new.roll);
    printf("Course : %s\n",student_new.course[j]);
    printf("Enter the mark : ");
    scanf("%d",&student_new.mark[j]); //Gets the 'mark' from the user and store it to the same index of the 'course'
    if(fwrite(&student_new,sizeof(student_new),1,n)<0) //Writing the new data into the new file named 'Temp.txt'
    {
        puts("\n\t* Couldn't provide the marks !!");
        goto X;
    }
    printf("\n* Student of Roll %d has been provided %d marks to course %s\n",student_new.roll,student_new.mark[j],student_new.course[j]);
X:
    fclose(old); //Closing the data file
    fclose(n);
    if(remove("Students Information.txt")!=0) //Remove the data file named 'Students Information.txt'
        puts("\n\t\t ** Error !!"); //If the operation is successful then 0 is returned
    if(rename("Temp.txt","Students Information.txt")!=0) //Rename the 'Temp.txt' data file as 'Students Information.txt'
        puts("\n\t\t ** Error !!"); //If the operation is successful then 0 is returned
    puts("\n\n\t**********\n");
    puts("\nNow what would you like to do ?\n");
    puts("1.Provide class test marks to another student");
    puts("2.Find students using their names");
    puts("3.Back to teacher panel");
    puts("4.Back to login section");
    puts("5.Exit");
Y:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&i);
    getchar();
    if(i==1)
        class_test_marks();
    else if(i==2)
        finding_students();
    else if(i==3)
        teacher_panel();
    else if(i==4)
        main();
    else if(i==5)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n* Invalid choice. Please try again.");
        goto Y;
    }
}


//Function to choose an operation as a teacher

void teacher_panel() //Function returns no value
{
    system("cls"); //Clears the console display area
    puts("\t\t********** Welcome to Teacher Panel **********\n");
    puts("* Which operation you want to do? (Enter the number to perform an operation)\n");
    puts("1.Provide class test marks to the students");
    puts("2.Find the students by the given first name");
    puts("3.Count the number of students provided class test marks");
    puts("4.Back to login section");
    puts("5.Exit");
    int a;
X:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1)
        class_test_marks();
    else if(a==2)
        finding_students();
    else if(a==3)
        count_of_students();
    else if(a==4)
        main();
    else if(a==5)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n* Invalid choice. Please try again.");
        goto X;
    }
}


//Function for teacher login

void teacher_login() //Function returns no value
{
X:
    system("cls"); //Clears the console display area
    puts("\t\t********** Teacher login Section **********\n\n");
    FILE *login;
    login=fopen("Teachers Information.txt","r"); //Opening the existing data file for reading only
    if(login==NULL) //If the file does not exist NULL value is returned
    {
        fclose(login);
        puts("\t* Cannot login as teacher\n");
        puts("\t* Teacher account hasn't been created yet.\n");
        printf("Enter (y/Y) to go back to login section otherwise (n/N) : ");
        char c;
        scanf("%c",&c);
        getchar();
        if(c=='y'||c=='Y')
            main();
        else
        {
            puts("\n***** Thanks *****\n");
            exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
        }
    }
    teacher teacher_user,teacher_login;
    printf("Username : ");
    gets(teacher_user.username);
    printf("Password : ");
    gets(teacher_user.password);
    int a=1;
    while(fread(&teacher_login,sizeof(teacher_login),1,login)>0) //Reading the data file and storing the data in 'teacher_login'
    {
        //If the data file is read then while loop is executed

        a=strcmp(teacher_login.username,teacher_user.username) || strcmp(teacher_login.password,teacher_user.password);

        //Checking if the username and password are matched.

        if(a==0) //If username and password are matched then 0 is returned
        {
            fclose(login); //Closing the data file
            teacher_panel();
        }
    }
    fclose(login); //Closes the data file
    if(a!=0) //If the username and password do not match then the condition becomes true
    {
        puts("\n* Username or Password Incorrect !\n");
        puts("\tOr Maybe the account has not been created yet !\n");
        printf("Enter (y/Y) to try again otherwise (n/N) : ");
        char ch;
        scanf("%c",&ch);
        getchar();
        if(ch=='y'||ch=='Y')
            goto X;
        else
            main();
    }
}


//Function to create student account

void students_account() //Function returns no value
{
    system("cls"); //Clears the console display area
    puts("\t********** Admin Panel - Create Student Account **********\n\n");
    puts("* To create students account enter the username and password");
    student student_login;
    printf("\nUsername : ");
    gets(student_login.username);
    printf("Password : ");
    gets(student_login.password);
    printf("Enter student's first name : ");
    gets(student_login.first_name);
    printf("Enter student's last name : ");
    gets(student_login.last_name);
    printf("Enter student's roll : ");
    scanf("%d",&student_login.roll);
    getchar();
    puts("\n\t**********\n");
    puts("Now Assign the courses to the student");
    printf("\nHow many courses ? ");
    int i,j;
    scanf("%d",&j); //User input for the number of courses
    getchar();
    printf("\n");
    for(i=0; i<j; i++) //Loop is executed  for the defined number of courses
    {
        printf("Enter the course name : ");
        gets(student_login.course[i]); //store the input of course name
        student_login.mark[i]=0; //assigning the marks 0 to the corresponded index of 'course'
    }
    for(i; i<20; i++) //Loop is executed for the remaining number of courses
    {
        strcpy(student_login.course[i],course[0]); //Copying the string 'Not Assigned' to the remaining courses
        student_login.mark[i]=0; //Assigning marks 0 to the corresponded index of the remaining course
    }
    system("cls"); //Clears the console display area
    puts("\t********** Admin Panel - Create Student Account **********\n\n");
    printf("* %d Courses have been assigned to %s %s\n",j,student_login.first_name,student_login.last_name);
    FILE *student_name;
    student_name=fopen("Students Information.txt","a+"); /*Opening the existing file for both reading and appending. The information is added at the end of the file.
                                                           If the file does not exist it will be created */
    if(fwrite(&student_login,sizeof(student_login),1,student_name)>0) //Reading the data file and storing the data in 'student_login'
        puts("\n* Students information has been stored successfully !!");
    else
        puts("\n* Students information storing failed !!");
    fclose(student_name); //Closing the data file
    puts("\nNow what would you like to do ?\n");
    puts("1.Create another student account");
    puts("2.Update student's information");
    puts("3.Back to admin panel");
    puts("4.Back to login section");
    puts("5.Exit");
    int a;
X:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1)
        students_account();
    else if(a==2)
        students_information();
    else if(a==3)
        admin_panel();
    else if(a==4)
        main();
    else if(a==5)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n* Invalid choice. Please try again.");
        goto X;
    }
}


//Function to update student information

void students_information() //Function returns no value
{
    system("cls"); //Clears the console display area
    puts("\t********** Admin Panel - Update Student Information **********\n\n");
    student student_new,student_old;
    FILE *old;
    old=fopen("Students Information.txt","r"); //Opening the existing data file for reading only
    if(old==NULL) //If the file does not exist NULL value is returned
    {
        fclose(old); //Closing the data file
        puts("* NO information has been included yet !\n");
        puts("* You have to assign courses along with creating an account.\n");
        char c;
        printf("Enter (y/Y) for creating an account otherwise (n/N) : ");
        scanf("%c",&c);
        getchar();
        if(c=='y' || c=='Y')
            students_account();
        else
            admin_panel();
    }
    FILE *n;
    n=fopen("Temp.txt","w+"); //Creates a new file for both reading and writing
    if(n==NULL) //If the file is not created then NULL value is returned
    {
        fclose(old); //Closing the data file
        fclose(n);
        puts("!! Can't upadte the information.");
        printf("\nTo try again enter (y/Y) otherwise (n/N : ");
        char ch;
        scanf("%c",&ch);
        getchar();
        if(ch=='y'||ch=='Y')
            students_information();
        else
            admin_panel();
    }
    int a=1;
    printf("** To update student's information *\n\nEnter student's existing roll no : ");
    scanf("%d",&student_new.roll);
    getchar();
    while(fread(&student_old,sizeof(student_old),1,old)>0) //Reading data from 'Students Information.txt' file and storing it in 'student_old'
    {
        //If the file is read then while loop is executed

        if(student_new.roll==student_old.roll) //Matching the roll no from user input with the roll no stored in data file
        {
            a=0;
            puts("\nStudent found !!\n");
            student_new=student_old; //Copying all the elements of 'student_old' to 'student_new'
            continue; //Back at the while loop condition
        }
        if(fwrite(&student_old,sizeof(student_old),1,n)<1) //writing the old data (read from 'Students Information.txt') to a new file named 'Temp.txt'
        {
            fclose(old); //Closing the data file
            fclose(n);
            puts("\n\n***** Sorry *****");
            puts("Cannot update !!");
            remove("Temp.txt"); //Removes 'Temp.txt' file
            goto A;
        }
    }
    fclose(old); //Closing the data file
    if(a!=0) //Checking if the roll number is matched
    {
        fclose(old);
        fclose(n); //Closing the data file
        remove("Temp.txt"); //Removes 'Temp.txt' file
        puts("* NO account has been created yet !\n");
        puts("* Create an account first.\n");
        char c;
        printf("Enter (y/Y) for creating an account otherwise (n/N) : ");
        scanf("%c",&c);
        getchar();
        if(c=='y' || c=='Y')
            students_account();
        else
            admin_panel();
    }
    puts("\t\t***** Student's Profile *****\n");
    printf("Full Name : %s %s\n",student_new.first_name,student_new.last_name);
    printf("Username : %s\n",student_new.username);
    printf("Password : %s\n",student_new.password);
    int i=0,j;
    while(strcmp(student_new.course[i],course[0])!=0) //Checking if the entered roll no has been assigned any courses
    {
        //If the strings are not matched then while loop is executed

        i++; //each time while loop is executed value of i is increased by 1
    }
    printf("\n\t * %s %s has been assigned %d courses already\n",student_new.first_name,student_new.last_name,i);
    puts("\nThe courses are ->");
    for(j=0; j<i; j++) //Loop is executed for the number of courses assigned
    {
        printf("\n%d.%s",j+1,student_new.course[j]);
    }
    puts("\n\n\t**********\n");
    puts("Enter the updated information");
    printf("\nEnter student's new first name : ");
    gets(student_new.first_name);
    printf("Enter student's new last name : ");
    gets(student_new.last_name);
    printf("Enter teacher's new login username : ");
    gets(student_new.username);
    printf("Enter teacher's new login password : ");
    gets(student_new.password);
    system("cls"); //Clears console display area
    puts("\t********** Admin Panel - Update Student Information **********\n\n");
    puts("** Do you want to\n\n1.Delete courses\n2.Add or Rename course\n3.Let the courses remain as before");
Y:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1) //Condition check for deleting courses
    {
        puts("\n\t**********");
        printf("\nHow many ? ");
        scanf("%d",&j);
        getchar();
        puts("\n* For deleting the courses enter the 'serial number'");
        puts("\n\t\tExample : '1' ");
        int x;
        while(j--) //Loop is executed for the defined number entered by the user
        {
            printf("-> ");
            scanf("%d",&i);
            getchar();
            x=i-1;
            for( ;x<19;x++)
            {
                strcpy(student_new.course[x],student_new.course[x+1]); //Copying the next string to the previous string
            }
        }
        goto X;
    }
    else if(a==2) //Condition check for rename or adding course
    {
        puts("\n\t**********");
        printf("\nHow many ? ");
        scanf("%d",&j);
        getchar();
        puts("\n* For adding or renaming the courses enter the 'serial number' and 'name'");
        puts("\n\t\tExample : '1 CSE 1201' ");
        while(j--) //loop is executed for the defined number
        {
            printf("-> ");
            scanf("%d",&i);
            getchar();
            gets(student_new.course[i-1]);
        }
        goto X;
    }
    else if(a==3)
        goto X;
    else
    {
        puts("\n* Invalid choice.Please try again.");
        goto Y;
    }
X:
    if(fwrite(&student_new,sizeof(student_new),1,n)>0) //Writing the new information into 'Temp.txt' file
        puts("\n***** Students information has been updated successfully *****\n");
    else
        puts("\n***** Students information update failed *****\n");
    fclose(n); //Closing the data file
    if(remove("Students Information.txt")!=0) //Remove the data file named 'Students Information.txt'
        puts("\n\t\t Error \n\n");
    if(rename("Temp.txt","Students Information.txt")!=0) //Rename the data file 'Temp.txt' as 'Students Information.txt'
        puts("\n\t\t Error \n\n");
A:
    puts("\t*****\n\nNow what would you like to do ?");
    puts("\n1.Update another student's information");
    puts("2.Back to admin panel");
    puts("3.Back to login section");
    puts("4.Exit");
Z:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1)
        students_information();
    else if(a==2)
        admin_panel();
    else if(a==3)
        main();
    else if(a==4)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n\n** Invalid choice.Please try again.");
        goto Z;
    }
}


//Function to assign the courses to the teacher

void assign_courses()
{
    system("cls"); //Clears console display area
    puts("\t********** Admin Panel - Assign Courses to Teacher **********\n\n");
    teacher teacher_new;
    admin teacher_old;
    int a=1;
    FILE *old;
    old=fopen("Login Information.txt","r"); //Opens existing data file for reading only
    if(old==NULL) //If the data file does not exist NULL value is returned
    {
        fclose(old); //Closes the data file
        puts("* NO account has been created yet !\n");
        puts("* Create an account first.\n");
        char c;
        printf("Enter (y/Y) for creating an account otherwise (n/N) : ");
        scanf("%c",&c);
        getchar();
        if(c=='y' || c=='Y')
            teachers_account();
        else
            admin_panel();
    }
    printf("To assign the courses enter teacher's existing full name : ");
    gets(teacher_new.name);
    while(fread(&teacher_old,sizeof(teacher_old),1,old)>0) //Reads from data file and stores the data in 'teacher_old'
    {
        //if the data file is read 'while' loop is executed

        a=strcmp(teacher_new.name,teacher_old.name); //Matching teacher's name from user input with the name read from data file
        if(a==0) //If teacher's name is matched then 0 is returned
        {
            fclose(old); //Closes the data file
            puts("\nTeacher found !!");
            strcpy(teacher_new.username,teacher_old.username);  //Copying teacher's username read from data file to 'teacher_new'
            strcpy(teacher_new.password,teacher_old.password);  //Copying teacher's password read from data file to 'teacher_new'
            puts("\n\t\t***** Teacher's Profile *****\n");
            printf("Name : %s\n",teacher_new.name);
            printf("Userame : %s\n",teacher_new.username);
            printf("Password : %s\n",teacher_new.password);
            break; //Out of the loop
        }
    }
    if(a!=0) //Checking if the teacher name is matched
    {
        fclose(old); //Closes the data file
        puts("* NO account has been created yet or Wrong Name !\n");
        puts("* Create an account first or Enter the correct name.\n");
        char c;
        printf("Enter (y/Y) for creating an account(or try again) otherwise (n/N) : ");
        scanf("%c",&c);
        getchar();
        if(c=='y' || c=='Y')
            teachers_account();
        else
            admin_panel();
    }
    puts("\n\t**********\n");
    puts("Now Assign the courses to the teacher");
    printf("\nHow many courses ? ");
    int i,j;
    scanf("%d",&j);
    getchar();
    printf("\n");
    for(i=0; i<j; i++) //Loop is executed for defined number of courses entered by user
    {
        printf("Enter the course name : ");
        gets(teacher_new.course[i]);
    }
    for(i; i<20; i++) //Loop is executed for the remaining number of the courses
    {
        strcpy(teacher_new.course[i],course[0]); //Copying the sting 'Not Assigned' to the remaining courses
    }
    system("cls"); //Clears console display area
    puts("\t********** Admin Panel - Assign Courses to Teacher **********\n\n");
    printf("* %d Courses have been assigned to %s\n",j,teacher_new.name);
    FILE *teacher_name;
    teacher_name=fopen("Teachers Information.txt","a+"); /*Opening the existing data file for both reading and appending. New information is added at the end of file.
                               If the file does not exist a new file will be created */
    if(fwrite(&teacher_new,sizeof(teacher_new),1,teacher_name)>0) //Writing the new information to 'Teachers Information.txt' file
        puts("\n* Teachers information has been stored successfully !!");
    else
        puts("\n* Teachers information storing failed !!");
    fclose(teacher_name); //Closes the data file
    puts("\nNow what would you like to do ?\n");
    puts("1.Assign courses to another teacher.");
    puts("2.Create another teacher account");
    puts("3.Update teacher's information");
    puts("4.Back to admin panel");
    puts("5.Back to login section");
    puts("6.Exit");
X:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1)
        assign_courses();
    if(a==2)
        teachers_account();
    else if(a==3)
        teachers_information();
    else if(a==4)
        admin_panel();
    else if(a==5)
        main();
    else if(a==6)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n* Invalid choice. Please try again.");
        goto X;
    }

}


//Function to update teacher information

void teachers_information() //Function returns no value
{
    system("cls"); //Clears console display area
    puts("\t********** Admin Panel - Update Teacher information **********\n\n");
    teacher teacher_new,teacher_old;
    FILE *old;
    old=fopen("Teachers Information.txt","r"); //Opens existing data file for reading only
    if(old==NULL) //If the data file does not exist NULL value is returned
    {
        fclose(old); //Closes the data file
        puts("* NO information has been included yet !\n");
        puts("* You have to assign courses along with creating an account.\n");
        char c;
        printf("Enter (y/Y) for creating an account otherwise (n/N) : ");
        scanf("%c",&c);
        getchar();
        if(c=='y' || c=='Y')
            teachers_account();
        else
            admin_panel();
    }
    FILE *n;
    n=fopen("Temp.txt","w+"); //Creates a new file for both reading and writing
    if(n==NULL)  //If the data file is not created NULL value is returned
    {
        fclose(old); //Closes the data file
        fclose(n);
        puts("!! Can't upadte the information.");
        printf("\nTo try again enter (y/Y) otherwise (n/N : ");
        char ch;
        scanf("%c",&ch);
        getchar();
        if(ch=='y'||ch=='Y')
            teachers_information();
        else
            admin_panel();
    }
    int a,b=1;
    printf("* To update teacher's information *\n\nEnter teacher's existing full name : ");
    gets(teacher_new.name);
    while(fread(&teacher_old,sizeof(teacher_old),1,old)>0) //Reads from data file and store the data in 'teacher_old'
    {
        //If the data file is read then 'while' loop is executed

        a=strcmp(teacher_new.name,teacher_old.name); //Matching user input teacher name with the teacher name read from the data file
        if(a==0) //If teacher name is matched then 0 is returned
        {
            b=a; //Assigning 0 to 'b'
            puts("\nTeacher found !!\n");
            teacher_new=teacher_old; //Copying all the elements of 'teacher_old' to 'teacher_new'
            continue; //Back at the 'while' loop condition
        }
        if(fwrite(&teacher_old,sizeof(teacher_old),1,n)<1) /*Writing all data (read from 'Teachers Information.txt')
                                                        except one (that is matched) to 'Temp.txt' file  */
        {
            fclose(old); //Closes the data file
            fclose(n);
            puts("\n\n***** Sorry *****");
            puts("Cannot update !!");
            remove("Temp.txt"); //Removes 'Temp.txt' file
            goto A;
        }
    }
    fclose(old); //Closes the data file
    if(b!=0) //Checking if the teacher name is matched
    {
        fclose(old);
        fclose(n);  //Closes the data file
        remove("Temp.txt"); //Removes 'Temp.txt' file
        puts("* NO account has been created or No course has been assigned yet!\n");
        puts("* Create an account along with assigning courses first.\n");
        char c;
        printf("Enter (y/Y) for creating an account otherwise (n/N) : ");
        scanf("%c",&c);
        getchar();
        if(c=='y' || c=='Y')
            teachers_account();
        else
            admin_panel();
    }
    puts("\t\t***** Teacher's Profile *****\n");
    printf("Name : %s\n",teacher_new.name);
    printf("Username : %s\n",teacher_new.username);
    printf("Password : %s\n",teacher_new.password);
    int i=0,j;
    while(strcmp(teacher_new.course[i],course[0])!=0) //Checking if the entered roll no has been assigned any courses
    {
        //If the string is not matched then 'while' loop is executed

        i++; //each time 'while' loop is executed the value of 'i' is increased by 1
    }
    printf("\n\t * %s has been assigned %d courses already\n",teacher_new.name,i);
    puts("\nThe courses are ->");
    for(j=0; j<i; j++)
    {
        printf("\n%d.%s",j+1,teacher_new.course[j]);
    }
    puts("\n\n\t**********\n");
    puts("Enter the updated information");
    printf("\nEnter teacher's new full name : ");
    gets(teacher_new.name);
    printf("Enter teacher's new login username : ");
    gets(teacher_new.username);
    printf("Enter teacher's new login password : ");
    gets(teacher_new.password);
    system("cls"); //Clears console display area
    puts("\t********** Admin Panel - Update Teacher Information **********\n\n");
    puts("** Do you want to\n\n1.Delete courses\n2.Add or Rename course\n3.Let the courses remain as before");
Y:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1) //Condition check for deleting courses
    {
        puts("\n\t**********");
        printf("\nHow many ? ");
        scanf("%d",&j);
        getchar();
        puts("\n* For deleting the courses enter the 'serial number'");
        puts("\n\t\tExample : '1' ");
        int x;
        while(j--)  //Loop is executed for the defined number entered by the user
        {
            printf("-> ");
            scanf("%d",&i);
            getchar();
            x=i-1;
            for( ;x<19;x++)
            {
                strcpy(teacher_new.course[x],teacher_new.course[x+1]); //Copying the next string to the previous string
            }
        }
        goto X;
    }
    else if(a==2) //Condition check for rename or adding courses
    {
        puts("\n\t**********");
        printf("\nHow many ? ");
        scanf("%d",&j);
        getchar();
        puts("\n* For adding or renaming the courses enter the 'serial number' and 'name'");
        puts("\n\t\tExample : '1 CSE 1201' ");
        while(j--) //Loop is executed for the defined number entered by the user
        {
            scanf("%d",&i);
            getchar();
            gets(teacher_new.course[i-1]);
        }
        goto X;
    }
    else if(a==3)
        goto X;
    else
    {
        puts("\n* Invalid choice.Please try again.");
        goto Y;
    }
X:
    if(fwrite(&teacher_new,sizeof(teacher_new),1,n)>0) //Writing new information to 'Temp.txt' file
        puts("\n***** Teachers information has been updated successfully *****\n");
    fclose(n); //Closes the data file
    if(remove("Teachers Information.txt")!=0) //Removes the file 'Teachers Information.txt'
        puts("\n\t\t Error \n\n");
    if(rename("Temp.txt","Teachers Information.txt")!=0) //Rename the file 'Temp.txt' as 'Teachers Information.txt'
        puts("\n\t\t Error \n\n");
A:
    puts("\t*****\n\nNow what would you like to do ?");
    puts("\n1.Update another teacher's information");
    puts("2.Back to admin panel");
    puts("3.Back to login section");
    puts("4.Exit");
Z:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1)
        teachers_information();
    else if(a==2)
        admin_panel();
    else if(a==3)
        main();
    else if(a==4)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\n\n** Invalid choice.Please try again.");
        goto Z;
    }
}


//Function to create teacher account

void teachers_account() //Function returns no value
{
    system("cls"); //Clears console display area
    puts("\t********** Admin Panel - Create Teacher Account **********\n\n");
    puts("* To create teachers account enter the username and password *");
    int i=1,a;
    admin teacher_login;
    printf("\nUsername : ");
    gets(teacher_login.username);
    printf("Password : ");
    gets(teacher_login.password);
    printf("Enter teacher's full name : ");
    gets(teacher_login.name);
    printf("\nYou have tried to create %d teachers account\n",i);
    FILE *teacher_info;
    teacher_info=fopen("Login Information.txt","a+"); /*Opens existing data file for both reading and appending. If the data file exists
                               The new information will be added at the end of the file otherwise a new data file will be created*/
    if(fwrite(&teacher_login,sizeof(teacher_login),1,teacher_info)>0)  //Writing new information to the data file
        printf("\n* Teacher's account has been created successfully !!\n");
    else
        printf("\n* Teacher account could not be created !!\n");
    fclose(teacher_info);  //Closes the data file
    puts("\n\t**********\n");
    puts("Now what would you like to do ?\n");
    puts("1.Create another teacher account");
    puts("2.Assign courses");
    puts("3.Update existing teacher's information");
    puts("4.Back to admin panel");
    puts("5.Back to login section");
    puts("6.Exit");
X:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1)
        teachers_account();
    else if(a==2)
        assign_courses();
    else if(a==3)
        teachers_information();
    else if(a==4)
        admin_panel();
    else if(a==5)
        main();
    else if(a==6)
    {
        puts("\n***** Thanks *****\n");
        exit(0);
    }
    else
    {
        puts("\n* Invalid choice. Please try again.");
        goto X; //Terminates the program after closing all the opened file and buffer area if those are still open
    }
}


//Function to choose an operation as admin

void admin_panel() //Function returns no value
{
    system("cls"); //Clears console display area
    puts("!! Login Successful !!\n");
    puts("\t********** Welcome to Admin Panel **********\n\n");
    puts("Which operation you want to do? (Enter the number to perform an operation)\n");
    puts("1.Create new teacher and student account");
    puts("2.Update existing teacher and student information");
    puts("3.Assign courses to teacher");
    puts("4.Change username and password for admin login");
    puts("5.Back to login section");
    puts("6.Exit");
    int a,b;
X:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1)
    {
        puts("\n\t **********\n\n");
        puts("Which account you want to create ?");
        puts("\n1.Teachers account\n2.Students account with assigning courses");
        printf("\nEnter a number as your choice : ");
        scanf("%d",&b);
        getchar();
        if(b==1)
            teachers_account();
        else
            students_account();
    }
    else if(a==2)
    {
        puts("\n\t **********\n\n");
        puts("Which information you want to update ?");
        puts("\n1.Teachers information\n2.Students information");
        printf("\nEnter a number as your choice : ");
        scanf("%d",&b);
        getchar();
        if(b==1)
            teachers_information();
        else
            students_information();
    }
    else if(a==3)
        assign_courses();
    else if(a==4)
        admin_account();
    else if (a==5)
        main();
    else if(a==6)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\nInvalid choice.Try again.");
        goto X;
    }
}


//Function for admin login

void admin_login() //Function returns no value
{
X:
    system("cls"); //Clears console display area
    admin admin_login,admin_user;
    FILE *login;
    login=fopen("Login Information.txt","r"); //Opens existing data file for reading only
    if(login==NULL) //If the file does not exist NULL value is returned
    {
        fclose(login); //Closes the data file
        puts("* Admin account hasn't been created yet.");
        puts("\nDo you want to create admin account by yourself ?");
        printf("If Yes enter (y/Y) otherwise (n/N) : ");
        char c;
        c=getchar();
        getchar();
        if(c=='y' || c=='Y')
            admin_account();
        else
            main();
    }
    puts("\t********** Admin Login Section **********\n");
    printf("\nUsername : ");
    gets(admin_user.username);
    printf("Password : ");
    gets(admin_user.password);
    int a=1;
    while(fread(&admin_login,sizeof(admin_login),1,login)>0) //Reads from the data file and store data in 'admin_login'
    {
        a=strcmp(admin_login.username,admin_user.username) || strcmp(admin_login.password,admin_user.password);
        //Matching the username and password
        if(a==0) //If the username and password are matched 0 is returned
        {
            fclose(login); //Closes the data file
            admin_panel();
        }
    }
    if(a!=0) //Checking if the the username and password are matched
    {
        fclose(login); //Closes the data file
        puts("\nUsername or Password Incorrect.Please try again.\n");
        printf("\nIf you want to try again enter (y/Y) otherwise (n/N) : ");
        char c;
        scanf("%c",&c);
        getchar();
        if(c=='y' || c=='Y')
            goto X;
        else
            main();
    }
}


//Function to change admin login username and password

void admin_account() //Function returns no value
{
    system("cls"); //Clears console display area
    puts("\t********** Admin Panel - Change Admin Login Information **********\n\n");
    admin admin_old,admin_new;
    FILE *a;
    FILE *b;
Z:
    b=fopen("Temp.txt","w+"); //Creates a new file for both reading and writing
    if(b==NULL) //If the file is not created NULL value is returned
    {
        fclose(a); //Closes the data file
        fclose(b);
        puts("Cannot change username and password.");
        admin_panel();
    }
    a=fopen("Login Information.txt","r"); //Opens existing data file for reading only
    if(a==NULL) //If the file does not exist NULL value is returned
    {
        puts("Admin account has not been created yet.");
        puts("Create admin account using username and password");
        goto X;
    }
    printf("\nPrevious username : ");
    gets(admin_new.username);
    printf("Previous password : ");
    gets(admin_new.password);
    int x,y=2;
    while(fread(&admin_old,sizeof(admin_old),1,a)>0) //Reads from the data file and store the data in 'admin_old'
    {
        //If the file is read 'while' loop is executed

        x=strcmp(admin_new.username,admin_old.username) || strcmp(admin_new.password,admin_old.password);

        //Matching the username and password
        if(x==0) //If username and password are matched then 0 is returned
        {
            y=x; //Assigning 0 to y
            continue; //Back to 'while' loop condition
        }
        fwrite(&admin_old,sizeof(admin_old),1,b); /*Writing all data (read from 'Login Information.txt' file) except one that is matched with the user input data
                                                    to 'Temp.txt' named file */
        y=1;
    }
    fclose(a); //Closes the data file
    if(y==1) //Checking  if the username and password are matched
    {
        fclose(a); //Closes the data file
        fclose(b);
        remove("Temp.txt"); //Removes 'Temp.txt' file
        puts("\n***** Wrong username and password *****\n");
        printf("\nIf you want to try again enter (y/Y) otherwise (n/N) : ");
        char c;
        scanf("%c",&c);
        getchar();
        if(c=='y' || c=='Y')
            goto Z;
        else
            admin_panel();
    }
X:
    fclose(a); //Closes the data file
    if(remove("Login Information.txt")!=0) //Removes 'Login Information.txt' file
        puts("\n***** Error !! *****\n");
    puts("\n\n*************\n");
    puts("\nEnter new username and password\n");
    printf("New Username : ");
    gets(admin_new.username);
    printf("New Password : ");
    gets(admin_new.password);
    fwrite(&admin_new,sizeof(admin_new),1,b); //Writing the new information to 'Temp.txt' file
    fclose(b);
    if(rename("Temp.txt","Login Information.txt")!=0) //Rename 'Login Information.txt' file as 'Temp.txt'
    {
        puts("\n\nThe uername and password update failed.\n\n");
        goto A;
    }
    puts("\n ******Username and password were changed successfully***** \n\n");
A:
    puts("Now what would you like to do ?\n");
    puts("1.Back to admin panel");
    puts("2.Back to login section");
    puts("3.Exit");
Y:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&x);
    getchar();
    if(x==1)
        admin_panel();
    else if(x==2)
        main();
    else if(x==3)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\nInvalid choice.Try again.");
        goto Y;
    }
}


//Function to create admin login information

void admin_login_info() //Function returns no value
{
    admin admin_login= {"admin1289@gmail.com","temp1289","Admin"};
    FILE *login;
    login=fopen("Login Information.txt","w"); //Opens a new file for writing only each time the function is called
    if(login==NULL) //If the file is not created then NULL value is returned
        printf("Login information hasn't been provided yet.");
    fwrite(&admin_login,sizeof(admin_login),1,login); //Writing the admin login information to the data file
    fclose(login); //Closing the data file
}


//Main function as Login section

int main()
{
    system("cls"); //Clears console display area
    FILE *p;
    p=fopen("Login Information.txt","r"); //Opening the existing file for reading only
    if(p==NULL) //If the file does not exist NULL value is returned
    {
        fclose(p); //Closing the data file
        admin_login_info();
    }
    fclose(p); //Closing the data file
    int a=0;
    char b;
    puts("\t********** Welcome to University Management System **********\n\n");
    puts("How do you want to login ?");
    puts("\n-> As \t 1.Admin \t 2.Teacher\t 3.Student \t 4.Exit");
X:
    printf("\nEnter a number as your choice : ");
    scanf("%d",&a);
    getchar();
    if(a==1)
        admin_login();
    else if(a==2)
        teacher_login();
    else if(a==3)
        student_login();
    else if(a==4)
    {
        puts("\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
    else
    {
        puts("\nInvalid choice.Please try again.\n");
        printf("* If you want to try again enter (y/Y) otherwise (n/N) : ");
        b=getchar();
        getchar();
        if(b=='y'|| b=='Y')
            goto X;
        puts("\n\n***** Thanks *****\n");
        exit(0); //Terminates the program after closing all the opened file and buffer area if those are still open
    }
}

