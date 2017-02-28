// Hotel Management System (HMS)
// By Avishek Mukherjee & Rittwick Banerjee

// Including Header file...
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "libhotel.h"

// void convert(char s, int mode)
int convert(char s, int mode)
{
	int x;
	if (mode == 0)
	{
		x = s;
	}
	else if (mode == 1)
	{
		x = ("%d",s);
	}
	return x;
}
// int idx_create(char id, const char file, long fpos)
// This function will append an IDX file against the given parameters
// & it will return 0 if the process is successful else return 1 on faliure
// This function will char id as a unique id to be written in the file
// const char file as filename where to write the data
// long fpos as the position of the ID in the original database
int idx_create(char id[], const char file[], long fpos)
{
	int i,f=0;
	fflush(stdin);
	id = fopen(file,"a+");
	rewind(id);
	while(fread(&idx,idxsize,1,id) == 1)
	{
		if (strcmp(idx.id,id) == 0)
		{
			f = 1;
			break;
		}
		else
		{
			f = 0;
		}
	}
	if (f == 0)
	{
		strcpy(idx.id,id);
		idx.pos = fpos;
		fseek(id,1,SEEK_END);
		fwrite(&idx,idxsize,1,id);
		i = 0;
	}
	else
	{
		i = 1;
	}
	rewind(id);
	fclose(id);
	return i;
}
// int backup_database(const char source[], const char des[])
// This function will make a copy of the original file
// to protect it from being deleted accidentaly
int backup_restore_database(const char source[], const char des[])
{
	FILE *ba1, *ba2;
	int r;
	fflush(stdin);
	ba1 = fopen(source,"rb+");
	ba2 = fopen(des,"wb+");
	if ((ba1 == NULL) || (ba2 == NULL))
	{
		r = 1;
	}
	else
	{

		rewind(ba1);
		rewind(ba2);
		while (!feof(ba1))
		{
			fputc(fgetc(ba1), ba2);
		}
		fclose(ba1);
		fclose(ba2);
		r = 0;
	}
	return r;
}
// int createdatabase(const char filename[])
// This file will create the supplied file
// This function will return 0 if the operation is successful
// else return 1
int createdatabase(const char filename[])
{
	FILE *cd;
	int r;
	fflush(stdin);
	cd = fopen(filename,"w");
	if (cd == NULL)
	{
		r = 1;
	}
	else
	{
		fclose(cd);
		r = 0;
	}
	return r;
}
// This function will create an user account
// See function prototype for more details
void create_new_login(void)
{
	char u1[11],p1[17],c;
	int i,r;
	fflush(stdin);
	user.user[0] = '\0';
	user.passwd[0] = '\0';
	u1[0]='\0';
	p1[0] = '\0';
	u = fopen(login_file,"a+");
	_setcursortype(_SOLIDCURSOR);
	rewind(u);
	printf("\n\t\tEnter New User Name -> ");
	fflush(stdin);
	gets(u1);
	printf("\n\t\tEnter New Password ->");
	for(i=0;i<=15;i++)
	{
		c = getch();
		if(c == 13)
			break;
		p1[i] = c;
		printf("*");
	}
	p1[i] = '\0';
	while(fread(&user,usersize,1,u) == 1)
	{
		if (strcmp(user.user,u1) == 0)
		{
			r = 1;
			break;
		}
		else
		{
			r = 0;
		}
	}
	if (r == 0)
	{
		for(i=0;u1[i] !='\0';i++)
		{
			user.user[i] = u1[i];
		}
		user.user[i] = '\0';
		fflush(stdin);
		for (i=0;p1[i]!='\0';i++)
		{
			user.passwd[i] = p1[i];
		}
		user.passwd[i] = '\0';
		fseek(u,1,SEEK_END);
		fwrite(&user,usersize,1,u);
		fclose(u);
	}
	else
	{
		printf("\n\t\t\tPlease enter a different user name ...");
		getch();
	}
}
// This function will create an user account
void create_login(void)
{
	int i,c;
	fflush(stdin);
	user.user[0] = '\0';
	user.passwd[0] = '\0';
	u = fopen(login_file,"a+");
	_setcursortype(_SOLIDCURSOR);
	printf("\n\t\tEnter New User Name -> ");
	fflush(stdin);
	gets(user.user);
	printf("\n\t\tEnter New Password ->");
	for(i=0;i<=15;i++)
	{
		c = getch();
		if(c == 13)
			break;
		user.passwd[i] = c;
		printf("*");
	}
	user.passwd[i] = '\0';
	fseek(u,1,SEEK_END);
	fwrite(&user,usersize,1,u);
	fflush(stdin);
	fclose(u);
	printf("\n\t\t\tUser account created...\n");
	printf("\n\t\t\tPress any key to login ...");
	getch();
	main();
}
// On a successful login this function will return 0
int login(void)
{
	int i,result,r;
	char u1[11],p1[17],c;
	u1[0]='\0';
	p1[0]='\0';
	user.user[0] = '\0';
	user.passwd[0] = '\0';
	fflush(stdin);
	u = fopen(login_file,"r");
	if (u == NULL)
	{
		result = createdatabase(login_file);
		if (result == 0) // 0 = the login file has been created
		{
			create_login();
		}
		else if (result == 1)
		{
			printf("\n\t\tThe Database can't be created ...");
			printf("\n\t\tPlease contact your vendor ...");
			getch();
			exit(0);
		}

	}
	else
	{
		printf("\n\n\t\t\t***************************");
		printf("\n\t\t\t*                         *");
		printf("\n\t\t\t* HOTEL MANAGEMENT SYSTEM *");
		printf("\n\t\t\t*                         *");
		printf("\n\t\t\t***************************");
		printf("\n\n");
		printf("\t\t\t\tLOGIN SYSTEM\n");
		printf("\t\t\t\t************\n");
		_setcursortype(_SOLIDCURSOR);
		printf("\n\n\t\tEnter User Name :- ");
		gets(u1);
		printf("\n\t\tPress 'ESC' to exit ...");
		printf("\n\n\t\tEnter Password :- ");
		fflush(stdin);
		for(i=0;i<=15;i++)
		{

			c = getch();
			if (c == 13)
			{
				break;
			}
			else if (c == 27)
			{
				exit(0);
			}
			p1[i] = c;
			printf("*");
		}

		p1[i] = '\0';
		rewind(u);
		// This while loop has to be modified ...
		while(fread(&user,usersize,1,u) == 1)
		{
			if (((strcmp(user.user,u1)) == 0) && ((strcmp(user.passwd,p1)) == 0))
			{
				r = 0; // if the application finds an user name
				// then it will break the loop
				break;
			}
			else
			{
				r = 1;
			}
		}
		fflush(stdin);
		fclose(u);
	}
	return r;
}

// Main menu for the Application
void main_menu(void)
{
	int m;
	char choice,x;
	//const char emp_back_file[] = "emp_back.dat";
	clrscr();
	_setcursortype(_NOCURSOR);
	printf("\n\n\t\t\t***************************");
	printf("\n\t\t\t*                         *");
	printf("\n\t\t\t* HOTEL MANAGEMENT SYSTEM *");
	printf("\n\t\t\t*                         *");
	printf("\n\t\t\t***************************");
	printf("\n");
	printf("\n\t\t    1.) Rooms\t\t2.) Manage Bills\n");
	printf("\n\t\t    3.) Employee\t4.) Customer\n");
	printf("\n\t\t    5.) Options\t\t6.) Exit\n");
	printf("\n\t\tEnter your choice :- ");
	fflush(stdin);
	choice = getch();
	switch(choice)
	{
		case '1':
		case 'r':
		case 'R':
		{
			/*fflush(stdin);
			create_new_login();
			printf("\n\t\tDo you want to create another account (y/n) ->");
			c1 = getch();
			if ((c1 == 'y') || (c1 == 'Y') || (c1 == 13))
			{
				fflush(stdin); // This function will clear the buffer
				create_new_login();
			}
			else
			{
				main_menu();
			}
			main_menu();*/
			room_menu();
			break;
		}
		case '2':
		case 'b':
		case 'B':
		{
			bill_menu();
			break;
		}
		case '3':
		case 'e':
		case 'E':
		{
			emp_menu();
			break;
		}
		case '4':
		case 'c':
		case 'C':
		{
			cust_menu();
			break;
		}
		case '5':
		case 'h':
		case 'H':
		{
			/*fflush(stdin);
			fclose(u);
			u = fopen(login_file,"r");
			while(fread(&user,usersize,1,u) == 1)
			{
				puts(user.user);
				printf("\n\t");
				puts(user.passwd);
			}
			printf("\n\t\tContinue ...");*/
			_setcursortype(_SOLIDCURSOR);
			printf("\n\t\tEnter String ->");
			scanf("%c", &x);
			m = convert(x,1);
			printf("\t%c%d",m,m);
			getch();
			break;
		}
		case '6':
		case 'x':
		case 'X':
		{
			printf("\n\n\tThank you for using this software");
			printf("\n\tDeveloped & Copyright (c) 2008 By Rittwick Banerjee");
			printf("\n\n\tPress any key to exit ...");
			getch();
			exit(0);
			break;
		}
		default:
		{
			printf("\n\t\t\tYou gave an Invalid choice ...");
			getch();
			main_menu();
			break;
		}
	}
}

// The Main Menu for employee
void emp_menu()
{
	char choice;
	emp.name[0] = '\0';
	emp.empid[0] = '\0';
	emp.sex[0] = '\0';
	emp.post[0] = '\0';
	_setcursortype(_NOCURSOR);
	fflush(stdin);
	clrscr();
	printf("\n\n");
	printf("\t\t\t***************************");
	printf("\n\t\t\t*                         *");
	printf("\n\t\t\t* HOTEL MANAGEMENT SYSTEM *");
	printf("\n\t\t\t*                         *");
	printf("\n\t\t\t***************************");
	printf("\n");
	printf("\n\t\t    1.) Create EMP\t2.) Edit EMP\n");
	printf("\n\t\t    3.) Delete EMP\t4.) Show Info EMP\n");
	printf("\n\t\t    5.) Show EMP_CODE\t6.) Back\n");
	printf("\n\t\tEnter your choice :- ");
	choice = getch();
	switch(choice)
	{
		case '1':
		case 'c':
		case 'C':
		{
			create_employee();
			break;
		}
		case '2':
		case 'e':
		case 'E':
		{
			edit_employee();
			break;
		}
		case '3':
		case 'd':
		case 'D':
		{
			del_employee();
			break;
		}
		case '4':
		case 's':
		case 'S':
		{
			show_employee();
			break;
		}
		case '5':
		case 'h':
		case 'H':
		{
			show_empcode();
			break;
		}
		case '6':
		case 'b':
		case 'B':
		{
			main_menu();
			break;
		}
		default:
		{
			printf("\n\t\t\tYou gave an Invalid choice ...");
			getch();
			emp_menu();
			break;
		}
	}
}
// void create_employee(void) function will create an employee
void create_employee()
{
	char ch,id[16];
	int r, flag;
	clrscr();
	fflush(stdin);
	_setcursortype(_SOLIDCURSOR);
	e = fopen(emp_file,"a+");
	if (e == NULL)
	{
		r = createdatabase(emp_file);
		if (r == 0) // OK
		{
			fclose(e);
			fflush(stdin);
			create_employee();
		}
		else
		{
			printf("\n\t\tThe Database can't be created ...");
			printf("\n\t\tPlease contact your vendor ...");
			getch();
			exit(0);
		}
	}
	else
	{
		fflush(stdin);
		rewind(e);
		printf("\n\t\t\t   Create New Employee");
		printf("\n\t\t\t   ===================\n");
		printf("\n\t\tEmployee Id :- ");
		fflush(stdin);
		gets(id);
		while(fread(&emp,empsize,1,e) == 1)
		{
			if (strcmp(emp.empid,id) == 0)
			{
				flag = 1;
				break;
			}
			else
			{
				flag = 0;
			}
		}
		if (flag == 0)
		{
			strcpy(emp.empid,id);
			printf("\n\t\tEmployee Name :- ");
			fflush(stdin);
			gets(emp.name);
			printf("\n\t\tEmployee Age :- ");
			fflush(stdin);
			gets(emp.age);
			printf("\n\t\tEmployee Sex :- ");
			fflush(stdin);
			gets(emp.sex);
			printf("\n\t\tEmployee DOB (dd/mm/yyyy):- ");
			fflush(stdin);
			scanf("%d%d%d",&emp.dob.dd,&emp.dob.mm,&emp.dob.yy);
			printf("\n\t\tEmployee Post :- ");
			fflush(stdin);
			gets(emp.post);
			printf("\n\t\tEmployee DOJ (dd/mm/yyyy):- ");
			scanf("%d%d%d",&emp.doj.dd,&emp.doj.mm,&emp.doj.yy);
			printf("\n\t\tEmployee DOR (dd/mm/yyyy):- ");
			fflush(stdin);
			scanf("%d%d%d",&emp.dor.dd,&emp.dor.mm,&emp.dor.yy);
			printf("\n\t\tEmployee Basic :- ");
			fflush(stdin);
			scanf("%f",&emp.bas);
			printf("\n\t\tEmployee Da :- ");
			fflush(stdin);
			scanf("%f",&emp.da);
			fflush(stdin);
			fseek(e,1,SEEK_END);
			fwrite(&emp,empsize,1,e);
		}
		else
		{
			printf("\n\t\tThis EMP ID is already in the database ...");
			getch();
		}
	}
	fclose(e);
	fflush(stdin);
	printf("\n\t\tDo you want to continue (y/n) -> ");
	ch = getch();
	if ((ch == 'y') || (ch == 'Y') || (ch == 13))
	{
		fflush(stdin);
		create_employee();
	}
	else
	{
		fflush(stdin);
		emp_menu();
	}
}

// edit_employee will edit an exsisting employee information
void edit_employee(void)
{
	int result;
	char id[16],ch;
	fflush(stdin);
	_setcursortype(_SOLIDCURSOR);
	e = fopen(emp_file,"r+");
	if (e == NULL)
	{
		result = createdatabase(emp_file);
		if (result == 0) // OK
		{
			create_employee();
		}
		else
		{
			printf("\n\t\tThe Database can't be created ...");
			printf("\n\t\tPlease contact your vendor ...");
			getch();
			exit(0);
		}
	}
	else
	{

		rewind(e);
		printf("\n\t\tEmployee ID :- ");
		gets(id);
		while(fread(&emp,empsize,1,e) == 1)
		{
			if (strcmp(emp.empid,id) == 0)
			{
				printf("\n\t\tFile position 1 :- %ld",ftell(e));
				printf("\n\t\tEmployee Id :- ");
				fflush(stdin);
				gets(emp.empid);
				printf("\n\t\tEmployee Name :- ");
				fflush(stdin);
				gets(emp.name);
				printf("\n\t\tEmployee Age :- ");
				fflush(stdin);
				gets(emp.age);
				printf("\n\t\tEmployee Sex :- ");
				fflush(stdin);
				gets(emp.sex);
				printf("\n\t\tEmployee DOB :- ");
				fflush(stdin);
				scanf("%d%d%d",&emp.dob.dd,&emp.dob.mm,&emp.dob.yy);
				printf("\n\t\tEmployee Post :- ");
				fflush(stdin);
				gets(emp.post);
				printf("\n\t\tEmployee DOJ :- ");
				fflush(stdin);
				scanf("%d%d%d",&emp.doj.dd,&emp.doj.mm,&emp.doj.yy);
				printf("\n\t\tEmployee DOR :- ");
				fflush(stdin);
				scanf("%d%d%d",&emp.dor.dd,&emp.dor.mm,&emp.dor.yy);
				printf("\n\t\tEmployee Basic :- ");
				fflush(stdin);
				scanf("%f",&emp.bas);
				printf("\n\t\tEmployee Da :- ");
				fflush(stdin);
				scanf("%f",&emp.da);
				fseek(e,-empsize,SEEK_CUR);
				printf("\n\t\tFile position 1 :- %ld",ftell(e));
				fwrite(&emp,empsize,1,e);
				getch();
				emp_menu();
				break;
			}
		}
		fclose(e);
		printf("\n\t\t\tWant to continue (Y/N) ->");
		ch = getch();
		if ((ch == 'y') || (ch == 'Y') || (ch == 13))
		{
			fflush(stdin);
			edit_employee();
		}
		else
		{
			emp_menu();
		}

	}
}
// del_employee() will delete an employee from the database
void del_employee(void)
{
	int a; // this variable will hold the return value of createdatabase()
	char id[16],c;
	FILE *tmp; // Temp file pointer
	fflush(stdin);
	id[0] = '\0';
	emp.empid[0] = '\0';
	_setcursortype(_SOLIDCURSOR);
	e = fopen(emp_file,"r");
	if (e == NULL)
	{
		a = createdatabase(emp_file);
		if (a == 0)
		{
			fclose(e);
			del_employee();
		}
		else
		{
			printf("\n\t\tThe Database can't be created ...");
			printf("\n\t\tPlease contact your vendor ...");
			getch();
			exit(0);
		}
	}
	else
	{
		printf("\n\t\tEmployee Id :- ");
		gets(id);
		rewind(e);
		while(fread(&emp,empsize,1,u) == 1)
		{
			if (strcmp(emp.empid,id) == 0)
			{
				printf("\n\t\tAre you sure that you want to delete (y/n) :- ");
				c = getch();
				if ((c == 'y') || (c == 'Y') || (c == 13))
				{
					tmp = fopen(emp_tmp,"a+");
					rewind(e);
					while (fread(&emp,empsize,1,e) == 1)
					{
						if (strcmp(emp.empid,id) != 0)
						{
							fwrite(&emp,empsize,1,tmp);
						}
					}
					fclose(tmp);
					fclose(e);
					remove(emp_file);
					if(rename(emp_tmp,emp_file) == 0)
					{
						printf("\n\t\t\tData deleted successfully ...");
						break;
					}
					else
					{
						perror("FILE UPDATE -> ");
						getch();
						break;
					}
				}
			}
		}
		fclose(e);
		printf("\n\t\tWant to continue (y/n) ->");
		c = getch();
		if ((c == 'y') || (c == 'Y') || (c == 13))
		{
			fflush(stdin);
			del_employee();
		}
		else
		{
			emp_menu();
		}
	}
}
// void show_employee function will show the info about an EMP
void show_employee(void)
{
	char id[16],c;
	clrscr();
	fflush(stdin);
	_setcursortype(_SOLIDCURSOR);
	id[0] = '\0';
	emp.empid[0] = '\0';
	fflush(stdin);
	e = fopen(emp_file, "r");
	if (e == NULL)
	{
		printf("\n\t\tEmployee Database not found ...");
		printf("\n\t\tCreate some Employee's entry first ...");
		getch();
		emp_menu();
	}
	else
	{
		printf("\n\t\tEnter Employee ID :- ");
		gets(id);
		while(fread(&emp,empsize,1,e) == 1)
		{
			if (strcmp(emp.empid,id) == 0)
			{
				clrscr();
				printf("\n\t\t\t\tEMPLOYEE INFO");
				printf("\n\t\t\t\t*************");
				printf("\n\tEmployee Name :-  ");
				puts(emp.name);
				printf("\n\tEmployee Age :-  ");
				puts(emp.age);
				printf("\n\tEmployee Sex :-  ");
				puts(emp.sex);
				printf("\n\tEmployee DOB (mm/dd/yyyy) :-  ");
				printf("%d/%d/%d\n",emp.dob.dd,emp.dob.mm,emp.dob.yy);
				printf("\n\tEmployee DOR (''/''/'''') :-  ");
				printf("%d/%d/%d\n",emp.dor.dd,emp.dor.mm,emp.dor.yy);
				printf("\n\tEmployee DOJ (''/''/'''') :-  ");
				printf("%d/%d/%d\n",emp.doj.dd,emp.doj.mm,emp.doj.yy);
				printf("\n\tEmployee Post :-  ");
				puts(emp.post);
				printf("\n\tEmployee Basic :-  ");
				printf("%.2f\n", emp.bas);
				printf("\n\tEmployee Da :-  ");
				printf("%.2f\n", emp.da);
				break;
			}
		}
		fclose(e);
		printf("\n\t\tWant to continue (Y/N) :- ");
		c = getch();
		if ((c == 'y') || (c == 'Y') || (c == 13))
		{
			show_employee();
		}
		else
		{
			emp_menu();
		}
	}
}
// void show_empcode(void) function will show all the emp code of all employee
void show_empcode(void)
{
	int i=0;
	fflush(stdin);
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	fflush(stdin);
	emp.empid[0] = '\0';
	fflush(stdin);
	e = fopen(emp_file, "r");
	if (e == NULL)
	{
		printf("\n\t\tEmployee Database not found ...");
		printf("\n\t\tCreate some Employee's entry first ...");
		getch();
		emp_menu();
	}
	else
	{
		printf("\n\t\t\tEmployee's EMP CODE List");
		printf("\n\t\t\t************************\n");
		printf("\n\t    -: EMP CODE :-\t\t   -: NAME :-");
		printf("\n\t    **************\t\t   **********");
		while(fread(&emp,empsize,1,e) == 1)
		{
			printf("\n\t\t");
			printf(" %s",emp.empid);
			printf("\t\t\t");
			printf("%s",emp.name);
			i++;
		}
		printf("\n\n\t\tTotal Employee found :- %d",i);
		printf("\n\t\tPress any key to continue ...");
		getch();
		fclose(e);
		emp_menu();
	}
}
// void bill_menu(void) function contains the menu for bill
void bill_menu(void)
{
	char c;
	clrscr();
	_setcursortype(_NOCURSOR);
	printf("\n\n\t\t\t***************************");
	printf("\n\t\t\t*                         *");
	printf("\n\t\t\t* HOTEL MANAGEMENT SYSTEM *");
	printf("\n\t\t\t*                         *");
	printf("\n\t\t\t***************************");
	printf("\n");
	printf("\n\t\t\t1.) Create Bill\t\t2.) Show Bill\n");
	printf("\n\t\t\t3.) Edit Bill\t\t4.) Del Bill\n");
	printf("\n\t\t\t5.) Help\t\t6.) Back\n");
	printf("\n\t\tEnter your choice :- ");
	fflush(stdin);
	c = getch();
	switch(c)
	{
		case '1':
		case 'b':
		case 'B':
		{
			create_bill();
			break;
		}
		case '2':
		case 's':
		case 'S':
		{
			show_bill();
			break;
		}
		case '3':
		case 'e':
		case 'E':
		{
			edit_bill();
			break;
		}
		case '4':
		case 'd':
		case 'D':
		{
			del_bill();
			break;
		}
		case '6':
		case 'm':
		case 'M':
		{
			main_menu();
			break;
		}
		default:
		{
			printf("\n\t\t\tYou gave an Invalid choice ...");
			getch();
			bill_menu();
			break;
		}
	}
}
// void create_bill(void)
void create_bill(void)
{
	int r,flag=0,m;
	char ch,bno[16],bno1[16];
	bno[0] = '\0';
	bno1[0] = '\0';
	bill.cust_name[0] = '\0';
	bill.bno[0] = '\0';
	fflush(stdin);
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	b = fopen(bill_file,"a+");
	if (b == NULL)
	{
		r = createdatabase(bill_file);
		if (r == 0)
		{
			fclose(b);
			fflush(stdin);
			create_bill();
		}
		else
		{
			printf("\n\t\tBilling Database can't be created ...");
			getch();
			bill_menu();
		}
	}
	else
	{
		fflush(stdin);
		rewind(b);
		while(fread(&bill,billsize,1,b) == 1)
		{
			bno1[0] = '\0';
			strcpy(bno1,bill.bno);
		}
		rewind(b);
		printf("\n\t\t\tLast Bill Number -> %s",bno1);
		printf("\n\t\tEnter Bill Number ->");
		gets(bno);
		while(fread(&bill,billsize,1,b) == 1)
		{
			if (strcmp(bill.bno,bno) == 0)
			{
				flag = 1;
				break;
			}
			else
			{
				flag = 0;

			}
		}
		if (flag == 0)
		{
			bill.totamount = 0;
			strcpy(bill.bno,bno);
			printf("\n\tCustomer Name ->");
			gets(bill.cust_name);
			printf("\n\t\tBill Date (dd/mm/yyyy) ->");
			fflush(stdin);
			scanf("%d%d%d",&bill.d.dd,&bill.d.mm,&bill.d.yy);
			printf("\n\t\tEnter no. of items (MAX 25) ->");
			fflush(stdin);
			scanf("%d",&n);

			for(m=0;m<=(n-1);m++)
			{
				if (m > (n-1))
					break;
				printf("\n\tItem Code for product %d ->",m);
				fflush(stdin);
				gets(bill.i[m].id);
				printf("\n\tItem Name for product %d ->",m);
				fflush(stdin);
				gets(bill.i[m].name);
				printf("\n\tItem Price for product %d ->",m);
				fflush(stdin);
				scanf("%f",&bill.i[m].itemprice);
				printf("\n\tItem Quantity ->");
				fflush(stdin);
				scanf("%d",&bill.i[m].qty);
				bill.i[m].totamount = bill.i[m].itemprice * bill.i[m].qty;
				bill.i[m].vat = (bill.i[m].itemprice * bill.i[m].qty * 4) / 100;
				bill.totamount = bill.totamount + bill.i[m].totamount +bill.i[m].vat ;
				bill.nitem = n;
			}
			fflush(stdin);
			fseek(b,1,SEEK_END);
			fwrite(&bill,billsize,1,b);
			printf("\n\tPlease check the customer name in customer database ...\n");
		}
		else
		{
			printf("\n\t\tThis Bill ID is already in the database ...");
			getch();
			create_bill();
		}
		fclose(b);
		printf("\n\t\tDo you want to continue (y/n) ->");
		ch = getch();
		if ((ch == 'y') || (ch == 'Y'))
		{
			fflush(stdin);
			fclose(b);
			create_bill();
		}
		else
		{
			fflush(stdin);
			fclose(b);
			bill_menu();
		}
	}
}
// This Function will edit a billing information
void edit_bill(void)
{
	int r,i,flag,n,m;
	char bno[16],ch;
	bno[0] = '\0';
	fflush(stdin);
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	b = fopen(bill_file,"r+");
	if (b == NULL)
	{
		r = createdatabase(bill_file);
		if (r == 0)
		{
			fclose(b);
			create_bill();
		}
		else
		{
			printf("\n\t\tBilling Database can't be created ...");
			getch();
			bill_menu();
		}
	}
	else
	{
		fflush(stdin);
		printf("\n\t\tEnter Bill No :- ");
		gets(bno);
		rewind(b);
		while(fread(&bill,billsize,1,b) == 1)
		{
			if (strcmp(bill.bno,bno) == 0)
			{
				flag = 0;
				break;
			}
			else
			{
				flag = 1;
			}
		}
		if (flag == 0)
		{
			n = bill.nitem;
			printf("\n\t\tBill No ->");
			puts(bill.bno);
			printf("\n\t\tBill Date ->");
			printf("%d/%d/%d",bill.d.dd,bill.d.mm,bill.d.yy);
			printf("\n\t\tCustomer Name -> %20s",bill.cust_name);
			printf("\n\tSerial\tName\tQuantity\tPrice\tTotal\n\n");
			for(i=0;i<=(n-1);i++)
			{
				printf("\t%2s\t%s\t%3d\t\t%.2f\t%.2f\n",bill.i[i].id,bill.i[i].name,bill.i[i].qty,bill.i[i].itemprice,bill.i[i].totamount);
				fflush(stdin);
			}
			printf("\n\t\t=======================================");
			printf("\n\t\tTotal Bill Amount for %d Items ->Rs. %.2f",i,bill.totamount);
			printf("\n\t\t=======================================");
			printf("\n\t\tVAT -> 4%% of Toatl amount ->Rs. %.2f",((bill.totamount * 4) /100));
			printf("\n\t\tDo you want to edit this bill (Y/N) ->");
			ch = getch();
			if ((ch == 'y') || (ch == 'Y') || (ch == 13))
			{
				strcpy(bill.bno,bno);
				printf("\n\tCustomer Name ->");
				gets(bill.cust_name);
				printf("\n\t\tBill Date (dd/mm/yyyy) ->");
				fflush(stdin);
				scanf("%d%d%d",&bill.d.dd,&bill.d.mm,&bill.d.yy);
				bill.totamount = 0;
				for(m=0;m<=(n-1);m++)
				{
					if (m > (n-1))
						break;
					printf("\n\tItem Code for product %d ->",m);
					fflush(stdin);
					gets(bill.i[m].id);
					printf("\n\tItem Name for product %d ->",m);
					fflush(stdin);
					gets(bill.i[m].name);
					printf("\n\tItem Price for product %d ->",m);
					fflush(stdin);
					scanf("%f",&bill.i[m].itemprice);
					printf("\n\tItem Quantity ->");
					fflush(stdin);
					scanf("%d",&bill.i[m].qty);
					bill.i[m].totamount = bill.i[m].itemprice * bill.i[m].qty;
					bill.i[m].vat = (bill.i[m].itemprice * bill.i[m].qty * 4) / 100;
					bill.totamount = bill.totamount + bill.i[m].totamount + bill.i[m].vat ;
				}
				fflush(stdin);
				fseek(b,-billsize,SEEK_CUR);
				fwrite(&bill,billsize,1,b);
				fclose(b);
				printf("\n\t\t\tDo you want to continue (Y/N) ->");
				fflush(stdin);
				ch = getch();
				if ((ch == 'y') || (ch == 'Y') || (ch == 13))
				{
					edit_bill();
				}
				else
				{
					bill_menu();
				}
			}
			else
			{
				fflush(stdin);
				fclose(b);
				bill_menu();
			}
		}
		else
		{
			printf("\n\t\tThis bill id is not in database ...");
			getch();
			fflush(stdin);
			fclose(b);
			bill_menu();
		}
	}
}
// This Function will delete an entry from billing database
void del_bill(void)
{
	int r;
	char bno[16],ch;
	FILE *tmp;
	bno[0] = '\0';
	fflush(stdin);
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	b = fopen(bill_file,"r");
	if (b == NULL)
	{
		r = createdatabase(bill_file);
		if (r == 0)
		{
			fclose(b);
			create_bill();
		}
		else
		{
			printf("\n\t\tBilling Database can't be created ...");
			getch();
			bill_menu();
		}
	}
	else
	{
		fflush(stdin);
		printf("\n\t\tEnter Bill No :- ");
		gets(bno);
		rewind(b);
		while(fread(&bill,billsize,1,b) == 1)
		{
			if (strcmp(bill.bno,bno) == 0)
			{
				printf("\n\t\tAre you sure that you want to delete (y/n) :- ");
				ch = getch();
				if ((ch == 'y') || (ch == 'Y') || (ch == 13))
				{
					tmp = fopen(bill_tmp,"a+");
					rewind(b);
					while (fread(&bill,billsize,1,b) == 1)
					{
						if (strcmp(bill.bno,bno) != 0)
						{
							fwrite(&bill,billsize,1,tmp);
						}
					}
					fclose(tmp);
					fclose(b);
					remove(bill_file);
					if(rename(bill_tmp,bill_file) == 0)
					{
						printf("\n\t\t\tData deleted successfully ...");
						break;
					}
					else
					{
						perror("FILE UPDATE -> ");
						getch();
						break;
					}
				}
			}
		}
		fclose(b);
		fflush(stdin);
		printf("\n\t\tWant to continue (y/n) ->");
		ch = getch();
		if ((ch == 'y') || (ch == 'Y') || (ch == 13))
		{
			fflush(stdin);
			del_bill();
		}
		else
		{
			bill_menu();
		}
	}
}

// Function will show the billing information
void show_bill(void)
{
	int r,i; // r for creating file, i for a for() loop
	char bno[16],ch;
	bno[0] = '\0';
	bill.bno[0] ='\0';
	fflush(stdin);
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	b = fopen(bill_file,"r");
	if (b == NULL)
	{
		r = createdatabase(bill_file);
		if (r == 0)
		{
			fclose(b);
			create_bill();
		}
		else
		{
			printf("\n\t\tBilling Database can't be created ...");
			getch();
			bill_menu();
		}
	}
	else
	{
		fflush(stdin);
		printf("\n\t\tEnter Bill No :- ");
		gets(bno);
		rewind(b);
		while(fread(&bill,billsize,1,b) == 1)
		{
			if (strcmp(bill.bno,bno) == 0)
			{
				n = bill.nitem;
				printf("\n\t\tBill No ->");
				puts(bill.bno);
				printf("\n\t\tBill Date ->");
				printf("%d/%d/%d",bill.d.dd,bill.d.mm,bill.d.yy);
				printf("\n\t\tCustomer Name -> %s",bill.cust_name);
				printf("\n\tSerial    Name\t\tQuantity    Price\tTotal\n\n");
				for(i=0;i<=(n-1);i++)
				{
					printf("\t%2s      %s\t\t%3d    %10.2f\t%.2f\n",bill.i[i].id,bill.i[i].name,bill.i[i].qty,bill.i[i].itemprice,bill.i[i].totamount);
					fflush(stdin);
				}
				printf("\n\t\t=======================================");
				printf("\n\t\tTotal Bill Amount for %d Items ->Rs. %.2f",i,bill.totamount);
				printf("\n\t\t=======================================");
				printf("\n\t\tVAT -> 4%% of Toatl amount ->Rs. %.2f",((bill.totamount * 4) /100));
				break;
			}
		}
		fflush(stdin);
		printf("\n\t\t\tDo you want to print this bill (Y/N) ->");
		ch = getch();
		if ((ch == 'y') || (ch == 'Y') || (ch == 13))
		{
			print_bill(bno);
		}
		fflush(stdin);
		printf("\n\t\t\tWant to continue (Y/N) ->");
		ch = getch();
		if ((ch == 'y') || (ch == 'Y') || (ch == 13))
		{
			fflush(stdin);
			fclose(b);
			show_bill();
		}
		else
		{
			fflush(stdin);
			fclose(b);
			bill_menu();
		}
	}

}
void print_bill(char s[])
{
	int r,i;
	char bno[16],ch;
	FILE *fp;
	bno[0] = '\0';
	strcpy(bno,s);
	fflush(stdin);
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	printf("\n\n\t\t");
	puts(bno);
	getch();
	b = fopen(bill_file,"r");
	if (b == NULL)
	{
		r = createdatabase(bill_file);
		if (r == 0)
		{
			fclose(b);
			create_bill();
		}
		else
		{
			printf("\n\t\tBilling Database can't be created ...");
			getch();
			bill_menu();
		}
	}
	else
	{
		fflush(stdin);
		rewind(b);
		while(fread(&bill,billsize,1,b) == 1)
		{
			if (strcmp(bill.bno,bno) == 0)
			{
				n = bill.nitem;
				printf("\n\t\tBill No ->");
				puts(bno);
				printf("\n\t\tBill Date ->");
				printf("%d/%d/%d",bill.d.dd,bill.d.mm,bill.d.yy);
				printf("\n\tSerial\tName\tQuantity\tPrice\tTotal\n\n");
				for(i=0;i<=(n-1);i++)
				{
					printf("\t%2s\t%s\t%3d\t\t%.2f\t%.2f\n",bill.i[i].id,bill.i[i].name,bill.i[i].qty,bill.i[i].itemprice,bill.i[i].totamount);
					fflush(stdin);
				}
				printf("\n\t\t=======================================");
				printf("\n\t\tTotal Bill Amount for %d Items ->Rs. %.2f",i,bill.totamount);
				printf("\n\t\t=======================================");
				printf("\n\t\tVAT -> 4%% of Toatl amount ->Rs. %.2f",((bill.totamount * 4) /100));
				break;
			}
		}
		fp = fopen("bill_print.txt","a+");
		fprintf(fp,"\n\t\t\t   **********************");
		fprintf(fp,"\n\t\t\t   * HMS BILLING SYSTEM *");
		fprintf(fp,"\n\t\t\t   **********************");
		fprintf(fp,"\nBill No ->%s",bno);
		fprintf(fp,"\nBill Date ->%d/%d/%d",bill.d.dd,bill.d.mm,bill.d.yy);
		fprintf(fp,"\nCustomer Name -> %s",bill.cust_name);
		fprintf(fp,"\n\n  Serial\tName\t\tQuantity\t\tPrice\tTotal\n\n");
		for(i=0;i<=(n-1);i++)
		{
			fprintf(fp,"  %4s\t\t%s\t\t%3d\t\t\t%.2f\t%.2f\n",bill.i[i].id,bill.i[i].name,bill.i[i].qty,bill.i[i].itemprice,bill.i[i].totamount);
			fflush(stdin);
		}
		fprintf(fp,"\n\t\t=======================================");
		fprintf(fp,"\n\t\tTotal Bill Amount for %d Items ->Rs. %.2f",i,bill.totamount);
		fprintf(fp,"\n\t\t=======================================");
		fprintf(fp,"\n\t\tVAT -> 4%% of Toatl amount ->Rs. %.2f",((bill.totamount * 4) /100));
		fprintf(fp,"\n\n\t\t\t\tEND OF BILL");
		fclose(fp);
		printf("\n\t\t\tPrint completed ...");
		printf("\n\t\t\tPlease \"bill_pri.txt\" for more details ...");
		getch();
		printf("\n\t\t\tWant to continue (Y/N) ->");
		ch = getch();
		if ((ch == 'y') || (ch == 'Y') || (ch == 13))
		{
			fflush(stdin);
			fclose(b);
			show_bill();
		}
		else
		{
			fflush(stdin);
			fclose(b);
			bill_menu();
		}
	}

}
// Customer's Main menu
void cust_menu(void)
{
	char ch;
	fflush(stdin);
	clrscr();
	_setcursortype(_NOCURSOR);
	printf("\n\n\t\t\t***************************");
	printf("\n\t\t\t*                         *");
	printf("\n\t\t\t* HOTEL MANAGEMENT SYSTEM *");
	printf("\n\t\t\t*                         *");
	printf("\n\t\t\t***************************");
	printf("\n\n");
	printf("\t\t\t\tCUSTOMER\n");
	printf("\t\t\t\t********\n");
	printf("\n\t\t1.) Create Customer\t2.) Show Customer\n");
	printf("\n\t\t3.) Edit Customer\t4.) Del Customer\n");
	printf("\n\t\t5.) Help\t\t6.) Back\n");
	printf("\n\t\tEnter your choice :- ");
	fflush(stdin);
	ch = getch();
	switch(ch)
	{
		case '1':
		case 'c':
		case 'C':
		{
			create_customer();
			break;
		}
		case '2':
		case 's':
		case 'S':
		{
			show_customer();
			break;
		}
		case '3':
		case 'e':
		case 'E':
		{
			edit_customer();
			break;
		}
		case '4':
		case 'd':
		case 'D':
		{
			del_customer();
			break;
		}
		case '6':
		case 'm':
		case 'M':
		{
			main_menu();
			break;
		}
		default:
		{
			printf("\n\t\t\tYou gave an Invalid choice ...");
			getch();
			cust_menu();
			break;
		}
	}
}
// void create_customer(void)
// This function will create an entry for a customer
void create_customer(void)
{
	int r,flag=0;
	char cuid[16];
	fflush(stdin);
	_setcursortype(_SOLIDCURSOR);
	c = fopen(cust_file,"a+");
	cust.id[0] = '\0';
	cuid[0] = '\0';
	if (c == NULL)
	{
		r = createdatabase(cust_file);
		if (r == 0)
		{
			fflush(stdin);
			fclose(c);
			create_customer();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		fflush(stdin);
		printf("\n\t\tCustomer ID ->");
		fflush(stdin);
		gets(cuid);
		while(fread(&cust,csize,1,c) == 1)
		{
			if(strcmp(cust.id,cuid) == 0)
			{
				flag = 1;
				break;
			}
			else
			{
				flag = 0;
			}
		}
		if (flag == 0)
		{
			printf("\n\t\t\t   CREATE CUSTOMER");
			printf("\n\t\t\t   ***************");
			strcpy(cust.id,cuid);
			printf("\n\t\tCustomer Name ->");
			fflush(stdin);
			gets(cust.name);
			printf("\n\t\tCustomer Sex ->");
			fflush(stdin);
			gets(cust.sex);
			printf("\n\t\tCustomer Address ->");
			fflush(stdin);
			gets(cust.add);
			printf("\n\t\tCustomer Phone ->");
			fflush(stdin);
			gets(cust.ph);
			printf("\n\t\tCustomer e-mail ->");
			fflush(stdin);
			gets(cust.mail);
			fflush(stdin);
			fseek(c,1,SEEK_END);
			fwrite(&cust,csize,1,c);
			printf("\n\t\tCustomer created ...");
			fclose(c);
			getch();
			cust_menu();
		}
		else
		{
			printf("\n\t\tData is already in the list ...");
			getch();
			create_customer();
		}
	}
}
// This function will edit an entry for a customer
void edit_customer(void)
{
	int r,flag;
	char ch, id[16];
	fflush(stdin);
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	c = fopen(cust_file,"r+");
	cust.id[0] = '\0';
	id[0] = '\0';
	if (c == NULL)
	{
		r = createdatabase(cust_file);
		if (r == 0)
		{
			fflush(stdin);
			fclose(c);
			create_customer();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		rewind(c);
		fflush(stdin);
		printf("\n\t\tCustomer ID ->");
		gets(id);
		while(fread(&cust,csize,1,c) == 1)
		{
			if(strcmp(cust.id,id) == 0)
			{
				flag = 0;
				break;
			}
			else
			{
				flag = 1;
			}
		}
		if (flag == 0)
		{
			printf("\n\t\t\t   EDIT CUSTOMER");
			printf("\n\t\t\t   *************");
			printf("\n\t\tCustomer ID -> ");
			puts(cust.id);
			printf("\n\t\tCustomer Name ->");
			puts(cust.name);
			printf("\n\t\tCustomer Sex ->");
			puts(cust.sex);
			printf("\n\t\tCustomer Address ->");
			puts(cust.add);
			printf("\n\t\tCustomer Phone ->");
			puts(cust.ph);
			printf("\n\t\tCustomer e-mail ->");
			puts(cust.mail);
			fflush(stdin);
			printf("\n\t\tDo you want to Edit This (Y/N) ->");
			ch = getch();
			if ((ch == 'y') || (ch == 'Y') || (ch == 13))
			{
				strcpy(cust.id,id);
				printf("\n\t\tCustomer Name ->");
				fflush(stdin);
				gets(cust.name);
				printf("\n\t\tCustomer Sex ->");
				fflush(stdin);
				gets(cust.sex);
				printf("\n\t\tCustomer Address ->");
				fflush(stdin);
				gets(cust.add);
				printf("\n\t\tCustomer Phone ->");
				fflush(stdin);
				gets(cust.ph);
				printf("\n\t\tCustomer e-mail ->");
				fflush(stdin);
				gets(cust.mail);
				fflush(stdin);
				fseek(c,-csize,SEEK_CUR);
				fwrite(&cust,csize,1,c);
				printf("\n\t\tDo want to continue (Y/N) ->");
				ch = getch();
				if ((ch == 'y') || (ch == 'Y') || (ch == 13))
				{
					fclose(c);
					fflush(stdin);
					edit_customer();
				}
				else
				{
					fclose(c);
					fflush(stdin);
					cust_menu();
				}
			}
			else
			{
				fclose(c);
				fflush(stdin);
				cust_menu();
			}


		}
		else
		{
			printf("\n\t\tData not found in the database ...");
			getch();
			printf("\n\t\tDo you want to try again (Y/N) ->");
			ch = getch();
			if ((ch == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(c);
				fflush(stdin);
				edit_customer();
			}
			else
			{
				fclose(c);
				fflush(stdin);
				cust_menu();
			}
		}
	}
}
// This function will delete an entry from customer database
void del_customer(void)
{
	int r,flag=1;
	char id[16],ch;
	FILE *tmp;
	fflush(stdin);
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	c = fopen(cust_file,"r");
	cust.id[0] = '\0';
	id[0] = '\0';
	if (c == NULL)
	{
		r = createdatabase(cust_file);
		if (r == 0)
		{
			fflush(stdin);
			fclose(c);
			create_customer();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		rewind(c);
		fflush(stdin);
		printf("\n\t\tCustomer ID ->");
		gets(id);
		while(fread(&cust,csize,1,c) == 1)
		{
			if(strcmp(cust.id,id) == 0)
			{
				flag = 0;
				break;
			}
			else
			{
				flag = 1;
			}
		}
		if (flag == 0)
		{
			printf("\n\t\t\t   DELETE CUSTOMER");
			printf("\n\t\t\t   ***************");
			printf("\n\t\tCustomer ID -> ");
			puts(cust.id);
			printf("\n\t\tCustomer Name ->");
			puts(cust.name);
			printf("\n\t\tCustomer Sex ->");
			puts(cust.sex);
			printf("\n\t\tCustomer Address ->");
			puts(cust.add);
			printf("\n\t\tCustomer Phone ->");
			puts(cust.ph);
			printf("\n\t\tCustomer e-mail ->");
			puts(cust.mail);
			fflush(stdin);
			printf("\n\t\tDo you want to Delete This (Y/N) ->");
			ch = getch();
			if ((ch == 'y') || (ch == 'Y') || (ch == 13))
			{
				rewind(c);
				tmp = fopen(cust_tmp,"a+");
				while (fread(&cust,csize,1,c) == 1)
				{
					if (strcmp(cust.id,id) != 0)
					{
						fwrite(&cust,csize,1,tmp);
					}
				}
				fclose(tmp);
				fclose(c);
				remove(cust_file);
				if(rename(cust_tmp,cust_file) == 0)
				{
					printf("\n\t\t\tData deleted successfully ...");
				}
				else
				{
					perror("FILE UPDATE -> ");
					getch();
				}
			}
			printf("\n\t\tDo want to continue (Y/N) ->");
			ch = getch();
			if ((ch == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(c);
				fflush(stdin);
				del_customer();
			}
			else
			{
				fclose(c);
				fflush(stdin);
				cust_menu();
			}
		}
		else
		{
			printf("\n\t\tID not found in the database ...");
			printf("\n\t\tDo want to try again (Y/N) ->");
			fflush(stdin);
			ch = getch();
			if ((ch == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(c);
				fflush(stdin);
				del_customer();
			}
			else
			{
				fflush(stdin);
				fclose(c);
				cust_menu();
			}
		}
	}
}
// This function will show an coustomer entry
void show_customer(void)
{
	int r,flag;
	char id[16],ch;
	id[0] = '\0';
	clrscr();
	fflush(stdin);
	_setcursortype(_SOLIDCURSOR);
	c = fopen(cust_file,"r");
	cust.id[0] = '\0';
	if (c == NULL)
	{
		r = createdatabase(cust_file);
		if (r == 0)
		{
			fflush(stdin);
			fclose(c);
			create_customer();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		rewind(c);
		printf("\n\t\tCustomer ID ->");
		fflush(stdin);
		gets(id);
		while(fread(&cust,csize,1,c) == 1)
		{
			if(strcmp(cust.id,id) == 0)
			{
				flag = 0;
				break;
			}
			else
			{
				flag = 1;
			}
		}
		if (flag == 0)
		{
			printf("\n\t\t\t\tSHOW CUSTOMER");
			printf("\n\t\t\t\t*************");
			printf("\n\t\tCustomer ID -> ");
			puts(cust.id);
			printf("\n\t\tCustomer Name ->");
			puts(cust.name);
			printf("\n\t\tCustomer Sex ->");
			puts(cust.sex);
			printf("\n\t\tCustomer Address ->");
			puts(cust.add);
			printf("\n\t\tCustomer Phone ->");
			puts(cust.ph);
			printf("\n\t\tCustomer e-mail ->");
			puts(cust.mail);
			fflush(stdin);
			printf("\n\t\tDo you want to continue (Y/N) ->");
			ch = getch();
			if ((ch == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(c);
				fflush(stdin);
				show_customer();
			}
			else
			{
				fclose(c);
				fflush(stdin);
				cust_menu();
			}
		}
		else
		{
			printf("\n\t\tThis Customer ID not found in the database ...");
			getch();
			printf("\n\t\tDo you want to try again (Y/N) ->");
			ch = getch();
			if ((ch == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(c);
				fflush(stdin);
				show_customer();
			}
			else
			{
				fclose(c);
				fflush(stdin);
				cust_menu();
			}
		}
	}
}
void room_menu(void)
{
	char ch;
	fflush(stdin);
	clrscr();
	_setcursortype(_NOCURSOR);
	printf("\n\n");
	printf("\t\t\t        ROOM SERVICE\n");
	printf("\t\t\t        ************\n");
	printf("\n\n\t\t1.) Book Room");
	printf("\t\t2.) Clear Room");
	printf("\n\n\t\t3.) Create Room");
	printf("\t\t4.) Availble Room(s)");
	printf("\n\n\t\t5.) Booked Room");
	printf("\t\t6.) Back");
	printf("\n\n\t\tEnter your choice ->");
	ch = getch();
	switch(ch)
	{
		case '1':
		case 'r':
		case 'R':
		{
			fflush(stdin);
			book_room();
			break;
		}
		case '2':
		case 'c':
		case 'C':
		{
			fflush(stdin);
			clear_room();
			break;
		}
		case '3':
		case 'h':
		case 'H':
		{
			fflush(stdin);
			//room_help();
			create_room();
			break;
		}
		case '4':
		case 'a':
		case 'A':
		{
			fflush(stdin);
			show_room();
			break;
		}
		case '5':
		case 'b':
		case 'B':
		{
			fflush(stdin);
			booked_room();
			break;
		}
		case '6':
		case 'm':
		case 'M':
		{
			fflush(stdin);
			main_menu();
			break;
		}
		default:
		{
			printf("\n\t\tYou gave an invalid choice ...");
			getch();
			room_menu();
			break;
		}
	}
}
// This function will create an room entry
void create_room(void)
{
	int i,f=0;
	char id[16],id1[16],ch;
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	id[0] = '\0';
	room.id[0] = '\0';
	room.flag = 1; // This means that the room is now available
	r = fopen(room_file,"a+");
	if (r == NULL)
	{
		i = createdatabase(room_file);
		if (i == 0)
		{
			fflush(stdin);
			fclose(c);
			create_room();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		rewind(r);
		while(fread(&room,rsize,1,r) == 1)
		{
			id1[0] = '\0';
			strcpy(id1,room.id);
		}
		rewind(r);
		room.id[0] = '\0';
		printf("\n\n\t\t\tLast Room Id -> %s",id1);
		printf("\n\n\t\t\tRoom ID ->");
		fflush(stdin);
		gets(id);
		while(fread(&room,rsize,1,r) == 1)
		{
			if(strcmp(room.id,id) == 0)
			{
				f = 1;
				break;
			}
			else
			{
				f = 0;
			}
		}
		if (f == 0)
		{
			printf("\n\n");
			printf("\t\t\tCREATE NEW ROOM\n");
			printf("\t\t\t***************\n");
			fflush(stdin);
			strcpy(room.id,id);
			printf("\n\n\t\tRoom Type ->");
			fflush(stdin);
			gets(room.type);
			printf("\n\t\tRoom Charge ->");
			fflush(stdin);
			scanf("%f",&room.charge);
			room.flag = 1;
			room.checkin.dd = 0;
			room.checkin.mm = 0;
			room.checkin.yy = 0;
			room.checkout.dd = 0;
			room.checkout.mm = 0;
			room.checkout.yy = 0;
			room.cust_name[0] ='\0';
			fseek(r,1,SEEK_END);
			fwrite(&room,rsize,1,r);
			printf("\n\t\tDo you want to continue (Y/N) ->");
			fflush(stdin);
			ch = getch();
			if ((ch  == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(r);
				fflush(stdin);
				create_room();
			}
			else
			{
				fclose(r);
				fflush(stdin);
				room_menu();
			}
		}
		else
		{
			printf("\n\n\t\t");
			printf("This Room already exsist, Please use another Room ID ...");
			getch();
			printf("\n\t\tDo you want to try again (Y/N) ->");
			fflush(stdin);
			ch = getch();
			if ((ch  == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(r);
				fflush(stdin);
				create_room();
			}
			else
			{
				fclose(r);
				fflush(stdin);
				room_menu();
			}
		}
	}
}
// This function will book a room for an customer
void book_room(void)
{
	int i,f,f1=1;
	char id[16],ch,cid[16];
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	room.id[0] = '\0';
	r = fopen(room_file,"r+");
	c = fopen(cust_file,"r");
	if (r == NULL)
	{
		i = createdatabase(room_file);
		if (i == 0)
		{
			fflush(stdin);
			fclose(c);
			create_room();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		rewind(r);
		printf("\n\n");
		printf("\t\t\t\t  BOOK ROOM\n");
		printf("\t\t\t\t  *********\n");
		printf("\n\n");
		printf("\n\n\t\t\tEnter Room ID ->");
		fflush(stdin);
		gets(id);
		while(fread(&room,rsize,1,r) == 1)
		{
			if(strcmp(room.id,id) == 0)
			{
				f = 0;
				break;
			}
			else
			{
				f = 1;
				//break;
			}
		}
		if (f == 0)
		{
			printf("\t\tRoom ID -> %s",room.id);
			printf("\n\t\tRoom Type -> %s",room.type);
			printf("\n\t\tRoom Charge -> Rs. %.2f",room.charge);
			printf("\n\t\tEnter Customer Name ->");
			gets(room.cust_name);
			rewind(c);
			while(fread(&cust,csize,1,c) == 1)
			{
				if(strcmp(cust.name,room.cust_name) == 0)
				{
					f1 = 0;
					break;
				}
				else
				{
					f1 = 1;
				}
			}
			if (f1 == 1)
			{
				fclose(c);
				printf("\n\tYou have to create the customer first ...");
				getch();
				create_customer();
				printf("\n\t\tEnter Check IN (dd/mm/yyyy) ->");
				scanf("%d%d%d",&room.checkin.dd,&room.checkin.mm,&room.checkin.yy);
				printf("\n\t\tEnter Check OUT (dd/mm/yyyy) ->");
				scanf("%d%d%d",&room.checkout.dd,&room.checkout.mm,&room.checkout.yy);
				room.flag = 0;
				fseek(r,-rsize,SEEK_CUR);
				fwrite(&room,rsize,1,r);
				printf("\n\t\tDo you want to continue (Y/N) ->");
				fflush(stdin);
				ch = getch();
				if ((ch  == 'y') || (ch == 'Y') || (ch == 13))
				{
					fclose(r);
					fflush(stdin);
					create_room();
				}
				else
				{
					fclose(r);
					fflush(stdin);
					room_menu();
				}
			}
			else
			{
				strcpy(room.cust_id,cust.id);
				printf("\n\t\tEnter Check IN (dd/mm/yyyy) ->");
				scanf("%d%d%d",&room.checkin.dd,&room.checkin.mm,&room.checkin.yy);
				printf("\n\t\tEnter Check OUT (dd/mm/yyyy) ->");
				scanf("%d%d%d",&room.checkout.dd,&room.checkout.mm,&room.checkout.yy);
				room.flag = 0;
				fseek(r,-rsize,SEEK_CUR);
				fwrite(&room,rsize,1,r);
				printf("\n\t\tDo you want to continue (Y/N) ->");
				fflush(stdin);
				ch = getch();
				if ((ch  == 'y') || (ch == 'Y') || (ch == 13))
				{
					fclose(r);
					fflush(stdin);
					create_room();
				}
				else
				{
					fclose(r);
					fflush(stdin);
					room_menu();
				}
			}
		}
		else
		{
			printf("\n\n\t\t");
			printf("This Room does not exsist, Please use another Room ID ...");
			getch();
			printf("\n\t\tDo you want to try again (Y/N) ->");
			fflush(stdin);
			ch = getch();
			if ((ch  == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(r);
				fflush(stdin);
				create_room();
			}
			else
			{
				fclose(r);
				fflush(stdin);
				room_menu();
			}
		}
	}
}
// This function will show the information about a room which is availble
void show_room(void)
{
	int i,f=1,r1=0;
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	r = fopen(room_file,"r");
	if (r == NULL)
	{
		i = createdatabase(room_file);
		if (i == 0)
		{
			fflush(stdin);
			fclose(c);
			create_room();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		rewind(r);
		printf("\n\n");
		printf("\t\t\t     ROOM IMFORMATION\n");
		printf("\t\t\t     ****************\n");
		printf("\n");
		rewind(c);
		printf("\n\t\tROOM ID\t\tType\tCharge(Rs.)\n");
		printf("\t\t*******\t\t****\t***********\n\n");
		while(fread(&room,rsize,1,r) == 1)
		{
			if (room.flag == f)
			{
				printf("\t\t%s\t\t%s\t%.2f\n",room.id,room.type,room.charge);
				r1++;
			}
		}
		printf("\n\n\t\tTotal Room(s) Availble -> %d",r1);
		getch();
		fflush(stdin);
		fclose(r);
		room_menu();
	}
}
// This function will show the information about a room which is availble
void booked_room(void)
{
	int i,f=0,r1=0;
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	r = fopen(room_file,"r");
	if (r == NULL)
	{
		i = createdatabase(room_file);
		if (i == 0)
		{
			fflush(stdin);
			fclose(c);
			create_room();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		rewind(r);
		printf("\n\n");
		printf("\t\t\t     ROOM IMFORMATION\n");
		printf("\t\t\t     ****************\n");
		printf("\n");
		rewind(c);
		printf("\n\t\tROOM ID\t\tType\tCharge(Rs.)\n");
		printf("\t\t*******\t\t****\t***********\n\n");
		while(fread(&room,rsize,1,r) == 1)
		{
			if (room.flag == f)
			{
				printf("\t\t%s\t\t%s\t%.2f\n",room.id,room.type,room.charge);
				r1++;
			}
			printf("\n\tCustomer Name -> %s",room.cust_name);
			printf("\n\tCustomer ID -> %s",room.cust_id);
		}
		printf("\n\n\t\tTotal Room(s) Availble -> %d",r1);
		getch();
		fflush(stdin);
		fclose(r);
		room_menu();
	}
}

// This function will clear the room
void clear_room(void)
{
	int i,f,f1,f2;
	char id[16],ch;
	clrscr();
	_setcursortype(_SOLIDCURSOR);
	room.id[0] = '\0';
	r = fopen(room_file,"r+");
	b = fopen(bill_file,"r");
	if (r == NULL)
	{
		i = createdatabase(room_file);
		if (i == 0)
		{
			fflush(stdin);
			fclose(c);
			create_room();
		}
		else
		{
			printf("\n\t\t\tThe Database can't created ...\n");
			printf("\t\t\tPlease contact your vendor ...");
			getch();
			cust_menu();
		}
	}
	else
	{
		rewind(r);
		printf("\n\n");
		printf("\t\t\t\t  CLEAR ROOM\n");
		printf("\t\t\t\t  **********\n");
		printf("\n\n");
		printf("\n\n\t\t\tEnter Room ID ->");
		fflush(stdin);
		gets(id);
		while(fread(&room,rsize,1,r) == 1)
		{
			if(room.flag == 0)
			{
				f2 = 0;
				break;
			}
			else
			{
				f2 = 1;
				//break;
			}
		}
		rewind(r);
		while(fread(&room,rsize,1,r) == 1)
		{
			if(strcmp(room.id,id) == 0)
			{
				f = 0;
				break;
			}
			else
			{
				f = 1;
				//break;
			}
		}
		if ((f == 0) && (f2 == 0))
		{
			while(fread(&bill,billsize,1,b) == 1)
			{
				if(strcmp(bill.cust_name,room.cust_name) == 0)
				{
					f1 = 0;
					break;
				}
				else
				{
					f1 = 1;
				}
			}
			if (f1 == 0)
			{
				fflush(stdin);
				fclose(b);
				room.flag = 1;
				room.cust_name[0] = '\0';
				room.cust_id[0] = '\0';
				room.checkin.dd = 0;
				room.checkin.mm = 0;
				room.checkin.yy = 0;
				room.checkout.dd = 0;
				room.checkout.mm = 0;
				room.checkout.yy = 0;
				fseek(r,-rsize,SEEK_CUR);
				fwrite(&room,rsize,1,r);
				printf("\n\t\tOr Edit the bill for this customer ...");
				getch();
			}
			else
			{
				fflush(stdin);
				fclose(b);
				printf("\n\t\tCreate Bill for this customer now ...");
			}
			printf("\n\t\tDo you want to continue (Y/N) ->");
			fflush(stdin);
			ch = getch();
			if ((ch  == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(r);
				fflush(stdin);
				clear_room();
			}
			else
			{
				fclose(r);
				fflush(stdin);
				room_menu();
			}
		}
		else
		{
			printf("\n\tEither The Room Is Not Booked or The Room ID Not Found ...");
			getch();
			printf("\n\t\tDo you want to continue (Y/N) ->");
			fflush(stdin);
			ch = getch();
			if ((ch  == 'y') || (ch == 'Y') || (ch == 13))
			{
				fclose(r);
				fflush(stdin);
				clear_room();
			}
			else
			{
				fclose(r);
				fflush(stdin);
				room_menu();
			}
		}
	}
}
// From the void main the programme execution will start
int main(void)
{
	int r1;
	char ch;
	fflush(stdin);
	clrscr();
	r1 = login();
	if (r1 == 0)
	{
		main_menu();
	}
	else if (r1 == 1)
	{
		printf("\n\t\tYou entered wrong USER ID or PASSWORD ...");
		printf("\n\t\tDo you want to try again (Y/N) ->");
		fflush(stdin);
		ch = getch();
		if ((ch  == 'y') || (ch == 'Y') || (ch == 13))
		{
			fflush(stdin);
			main();
		}
		else
		{
			exit(0);
		}

	}
	return 0;
}