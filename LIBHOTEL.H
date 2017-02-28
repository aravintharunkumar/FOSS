// FILE NAME :- libhotel.h
// VERSION :- 0.0.1
// AUTHOR :- Rittwick Banerjee
// COPYRIGHT :- Copyright (c) 2008 by Rittwick Banerjee

// This file contains the main structures, file handler
// & some const variable along with all the function prototypes
// that will be used in the main application

// Structure for date
struct date
{
	int dd;
	int mm;
	int yy;
};
struct define_idx
{
	char id[16];
	long pos;
}idx;
// Structure for a customer
struct define_customer
{
	char id[16];
	char name[101];
	char sex[2];
	char add[101];
	char ph[15];
	char mail[50];
}cust;
// Structure for an Item
struct item
{
	char id[16];
	char name[101];
	float itemprice;
	int qty;
	float totamount;
	float vat;
}item;
// Structure for room
struct define_room
{
	char id[16];
	char cust_name[101];
	char cust_id[15];
	char type[10];
	struct date checkin;
	struct date checkout;
	float charge;
	int flag; // 0 = this room is booked, 1 = this room available
}room;
// Structure for an employee
struct define_employee
{
	char empid[16];
	char name[101];
	char age[3];
	char sex[2];
	struct date dob; // Date of Birth
	char post[16];
	struct date doj; // Date of Joining
	struct date dor; // Date of Retire
	float bas; // Employee's basic pay
	float da; // Employee's DA
}emp;
// Structure for Billing System
struct define_bill
{
	char bno[16];
	char cust_name[101];
	struct date d;
	struct item i[25];
	int nitem;
	float totamount;
}bill;
// The Main user structure that will hold the user name & password
struct define_user
{
	char user[11];
	char passwd[17];
}user;
// The Following constant variable will hold the size of structures
// This value will hold the % value of VAT & this should not be changed
int vat = 4,n;
const long rsize = sizeof(room);
const long csize = sizeof(cust);
const long empsize = sizeof(emp);
const long billsize = sizeof(bill);
const long usersize = sizeof(user);
const long idxsize = sizeof(idx);
const char login_file[] = "login.dat";
const char login_idx[] = "login.idx";
const char emp_file[] = "emp.dat";
const char emp_tmp[] = "emp_tmp.dat";
const char emp_idx[] = "emp.idx";
const char bill_file[] = "bill.dat";
const char bill_tmp[] = "bill_tmp.dat";
const char tmp_bill[] = "tmp_bill.dat";
const char bill_idx[] = "bill.idx";
const char room_file[] = "room.dat";
const char room_tmp[] = "room_tmp.dat";
const char room_idx[] = "room.idx";
const char cust_file[] = "cust.dat";
const char cust_tmp[] = "cust_tmp.dat";
const char cust_idx[] = "cust.idx";

// Function Prototypes
int main(void);
// 1 This function will convert a string into its corosponding ascii value
int convert(char s, int mode);
// 1 This function will create an index file with the given parameters
int idx_create(char id[], const char file[], long fpos);
//int idx_create(char id[], const char file, long fpos)
// 1 This function will create an room entry
void create_room(void);
// 1 This function will show the info about the room
void show_room(void);
// 1 This function will show the information about a room which is not availble
void booked_room(void);
// 1 We will use This function to book a room
void book_room(void);
// This function will clear room
void clear_room(void);
// This function will calculate & store the food charges
void food_sevice(void);
// 1 By using this function we can create an employee
void create_employee(void);
// 1 Using this function we can delete an employee
void del_employee(void);
// 1 Using this function we can edit an employee
void edit_employee(void);
// 1 To show information about an employee
void show_employee(void);
// 1 This function will show all the EMP code of all employee
void show_empcode(void);
// 1 This function will create a new entry of customer
// info in customer databaase
void create_customer(void);
// To edit the information about a customer
void edit_customer(void);
// To delete the information about a customer
void del_customer(void);
// This function will show the info about an customer
void show_customer(void);
// 1 By Using this function we make bill for our customer
void create_bill(void);
// 1 By using this function we can make change to a bill
void edit_bill(void);
// 1 By using this function we can delete a bill
void del_bill(void);
// 1 This function will show the info about a bill
void show_bill(void);
// 1 This function will print the bill
void print_bill(char s[]);
// 1 This function will asks the user for user name & password
int login(void);
// 1 This function will create an user account
void create_login(void);
// 1 This function creates new user name & password
// On condition that at least one user name & password is exsist
void create_new_login(void);
// 1 This function will back up the database
int backup_restore_database(const char source[], const char des[]);
// 1 This function will create the database
// if the database has not been created yet...
int createdatabase(const char filename[]); // 1
// This is the list of menu functions
// 1 This function will show the main menu
void main_menu(void);
// 1 The employee menu
void emp_menu(void);
// 1 The Billing Menu
void bill_menu(void);
// The Room Booking menu
void room_menu(void);
// 1 The Customer Menu
void cust_menu(void);

// Global Variable used for some global operations
FILE *db; // A pointer type variable used for main database
FILE *r; // A pointer type variable used for room database
FILE *c; // A pointer type variable used for customer database
FILE *e; // A pointer type variable used for employee database
FILE *b; // A pointer type variable used for billing database
FILE *u; // A pointer type variable used for user information
FILE *id; // A pointer for IDX file operation