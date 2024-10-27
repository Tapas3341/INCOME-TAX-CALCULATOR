#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>

struct records {
	char name[20];
	int income, id;
	float tax, income_after_tax;
}rec[100];

int end = 0;

//MAKING FILE POINTER
FILE *fp, *fp1;

//FUNCTION DECLARATION TO LOGIN
void password();

//ADDING RECORDS ENTERED BY THE USER
void add_record() {
	int n, s, id;
	printf("\nEnter number of records you want to insert: ");
	scanf("%d", &n);
	fflush(stdin);
	if (n>=0 && n<=100) {
		for (int i=0; i<n; i++) {
			printf("\n----------------------------");
			while (1) {
				s = 0;
				printf("\nEnter Id of tax Payer:");
				scanf("%d", &id);
				fflush(stdin);
				fp = fopen("records.txt", "r");
				while(fscanf(fp, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax)!=EOF) {
					if (rec[i].id == id) s++;
				}
				if (s) printf("Duplicate ID found!");
				else {
					rec[i].id = id;
					break;
				}
			}
			fclose(fp);                                                         
			printf("Enter Tax Payer's username: (firstname_lastname): ");
			gets(rec[i].name);
			fflush(stdin);
			while (1) {
				printf("Enter Salary: ");                            
				scanf("%d", &rec[i].income);
				fflush(stdin);
				if (rec[i].income>0) break;
				else printf("Wrong input!\n"); 
			}
			printf("----------------------------");
			if (rec[i].income <= 250000) {
        		rec[i].tax = 0;
    		} else if (rec[i].income <= 500000) {
        		rec[i].tax = (rec[i].income - 250000) * 0.05;
    		} else if (rec[i].income <= 1000000) {
        		rec[i].tax = 12500 + (rec[i].income - 500000) * 0.2;
    		} else {
        		rec[i].tax = 112500 + (rec[i].income - 1000000) * 0.3;
    		}
    		rec[i].income_after_tax = rec[i].income - rec[i].tax;
			//WRITING OR INSERTING RECORDS INTO FILE
    		fp = fopen("Records.txt","a");
    		fprintf(fp, "%d %s %d %.2f %.2f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
    		fclose(fp);
		}
	} else { 
		printf("\nInvalid Number\n");
		printf("\n----------------------------------");
	}
}

//DISPLAYING TAX PAYER RECORDS
void list_of_tax_payers() {
	system("cls");
	int i=0, number_of_records;
	fp = fopen("records.txt", "r");
	fseek(fp, 0, SEEK_END);
	number_of_records = ftell(fp) / sizeof(records);
	fclose(fp);
	fp = fopen("records.txt", "r");
	if (number_of_records > 0) {                                                        
		printf("\n------------List of Tax Payers:------------");
		//READING RECORDS FROM FILE
		while(fscanf(fp, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax)!=EOF) {
			printf("\nID of the tax payer:         %d", rec[i].id);
			printf("\nName of the tax payer:       %s", rec[i].name);
			printf("\nIncome of tax payer:         %d", rec[i].income);
			printf("\nTax to be paid:              %.2f", rec[i].tax);
			printf("\nIncome after applying tax:   %.2f", rec[i].income_after_tax);
			printf("\n----------------------------------------");
			i++;
		}
	}
	else { 
		printf("\nEmpty File! No records found...\n");
		printf("\n--------------------------------------------");
	}	
}


//SEARCHING FOR A RECORD
void search_record() {
	int check_id, s=0;
	printf("\nID of Tax payer:");
	scanf("%d", &check_id);
	fflush(stdin);
	//SEARCHING FOR A RECORD IN FILE
	fp = fopen("records.txt", "r");
	if (fp == NULL)  {
		printf("\nError opening file for checking, Please check again later!");
		exit(1);
	}
	int i=0;
	while (fscanf(fp, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax) != EOF) {
		if (rec[i].id == check_id) {
			printf("----------------------------------------");
			printf("\nID of the tax payer: %d", rec[i].id);
			printf("\nName of the tax payer: %s", rec[i].name);
			printf("\nIncome of tax payer: %d", rec[i].income);
			printf("\nTax to be paid: %.2f", rec[i].tax);
			printf("\nIncome after applying tax: %.2f", rec[i].income_after_tax);
			printf("\n----------------------------------------");
			s=1;
		}
		i++;
	}
	if (s==0) {
		printf("\nTax payer with ID %d is not found", check_id);
		printf("\n----------------------------------------------");
	}
}

//EDITING A RECORD
void edit_record() {
	int edit_id, s = 0, i=0;
	printf("\nEnter id whose record you want to update: ");
	scanf("%d", &edit_id);
	fflush(stdin);
	fp = fopen("records.txt", "r+");
	if (!feof(fp)) {
		int i =0, n = 0;
		while (fscanf(fp, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax) != EOF) {
		if (rec[i].id == edit_id) {
			s++;
		}
		i++;
		}
		fclose(fp);
		if (s>0) {
			int choices;
			printf("\n1.NAME OF TAX PAYER:");
			printf("\n2.INCOME OF TAX PAYER:");
			printf("\nSelect choice from above you want to edit the record: ");
			scanf("%d", &choices);
			fflush(stdin);
			switch(choices) {
				case 1: printf("\n\n##############################################\n");
						printf("#YOU SELECTED TO CHANGE THE NAME OF TAX PAYER#\n");
						printf("##############################################\n");
						char change_name[20];
						printf("\nEnter Name: ");
						gets(change_name);
						fflush(stdin);
						fp = fopen("records.txt", "r");
						fp1 = fopen("records1.txt", "w");
						if (fp == NULL) {
							printf("\nError opening file!");
							exit(1);
						}
						
						while (fscanf(fp, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax) != EOF) {
							if (rec[i].id == edit_id) {
								strcpy(rec[i].name, change_name);
								fprintf(fp1, "%d %s %d %.2f %.2f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
							}
							else  {
									fprintf(fp1, "%d %s %d %.2f %.2f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
							}
						i++;
						}
						fclose(fp);
						fclose(fp1);
						fp = fopen("records.txt", "w");
						fp1 = fopen("records1.txt", "r");
						while (fscanf(fp1, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax) != EOF) {
							fprintf(fp, "%d %s %d %f %f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
						}
						fclose(fp);
						fclose(fp1);
						printf("Successfully Updated!");
						break;
						
				case 2: printf("\n\n############################################\n");
						printf("#YOU SELECTED TO UPDATE INCOME OF TAX PAYER#\n");
						printf("############################################\n");
						int change_income, tax, changed_income;
						printf("\nEnter updated income: ");
						scanf("%d", &change_income);
						fflush(stdin);
						if (change_income <= 250000) {
        					tax = 0;
    					} else if (change_income <= 500000) {
        					tax = (change_income - 250000) * 0.05;
    					} else if (change_income <= 1000000) {
        					tax = 12500 + (change_income - 500000) * 0.2;
    					} else {
        					tax = 112500 + (change_income - 1000000) * 0.3;
    					}
    					changed_income = change_income - tax;
    					fp = fopen("records.txt", "r");
						fp1 = fopen("records1.txt", "w");
						if (fp == NULL) {
							printf("\nError opening file!");
							exit(1);
						}
						i = 0;
						while (fscanf(fp, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax) != EOF) {
							if (rec[i].id == edit_id) {
								rec[i].income = change_income;
								rec[i].tax = tax;
								rec[i].income_after_tax = changed_income;
								fprintf(fp1, "%d %s %d %.2f %.2f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
							}
							else  {
									fprintf(fp1, "%d %s %d %.2f %.2f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
							}
						i++;
						}
						fclose(fp);
						fclose(fp1);
						fp = fopen("records.txt", "w");
						fp1 = fopen("records1.txt", "r");
						while (fscanf(fp1, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax) != EOF) {
							fprintf(fp, "%d %s %d %f %f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
						}
						fclose(fp);
						fclose(fp1);
    					
    					printf("Successfully Updated!");
    					break;
    			default: printf("\nWrong Choice");
    					 break;
			}
		}
		else {
			printf("\nRecord not found!");
		}	
	}
}




//DELETING A RECORD
void delete_record() {
	int delete_id, s = 0, i = 0;
	printf("\nEnter ID of the tax payer whose record you want to Delete: ");
	scanf("%d", &delete_id);
	fflush(stdin);
	FILE *fp1, *fp2;
	fp1 = fopen("records.txt", "r");
	fp2 = fopen("records1.txt", "w");
	if (fp1 ==NULL || fp2==NULL) {
		printf("\nError opening file to delete a record!");
			exit(1);	
	}
	while (fscanf(fp1, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax) != EOF) {
		fprintf(fp2, "%d %s %d %f %f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
	}
	fclose(fp1);
	fclose(fp2);
	
	fp1=fopen("records.txt","w");
	fp2=fopen("records1.txt","r");
	while (fscanf(fp2, "%d %s %d %f %f\n", &rec[i].id, rec[i].name, &rec[i].income, &rec[i].tax, &rec[i].income_after_tax) != EOF) {
		if (rec[i].id != delete_id) {
			fprintf(fp1, "%d %s %d %f %f\n", rec[i].id, rec[i].name, rec[i].income, rec[i].tax, rec[i].income_after_tax);
		}
		else {s++;}
	}
	fclose(fp1);
	fclose(fp2);
	if (s==0) printf("\nID doesn't exists");
	else { 
		printf("\nRecord successfully deleted!\n");
	}
}


//CHOICES TO PERFORM OPERATIONS
void choices () {
	int choice;
	while (1) {
		system("cls");
		printf("\n------------------------------------------------------\n");
		printf("\n####################");
		printf("\n#SELECT AN OPTION: #");
		printf("\n####################\n\n");
		printf("1.Add New Record.\n");
		printf("2.List All Tax Payer along with income tax to be paid.\n");
		printf("3.Search a record.\n");
		printf("4.Edit a record.\n");
		printf("5.Delete a record.\n");
		printf("6.Exit.\n");
		printf("Enter a choice from given above: ");
		scanf("%d", &choice);
		fflush(stdin);
		switch (choice) {
			case 1: system("cls");
					printf("\n#######################################");
					printf("\n#YOU HAVE SELECTED TO ADD A NEW RECORD#");
					printf("\n#######################################\n");
					add_record();
					break;
			case 2: list_of_tax_payers();
					break;
			case 3: system("cls");
					printf("\n#####################");
					printf("\n#SEARCH FOR A RECORD#");
					printf("\n#####################\n");
					search_record();
					break;
			case 4: system("cls");
					printf("\n#############################");
					printf("\n#YOU SELECT TO EDIT A RECORD#");
					printf("\n#############################\n");
					edit_record();
					break;
			case 5: system("cls");
					printf("\n#############################");
					printf("\n#YOU SELECT TO DELETE A RECORD#");
					printf("\n#############################\n");
					delete_record();
					break;
			case 6:	break;
			default: printf("Wrong Choice");
		}
		char ans[5];
		char check[5] = "yes";
		char show[100] = "\n\n\t\t\t======================THANK YOU======================\n\n\t\t\tSee you soon........\n\n";
		printf("\n----------------------------------------------------");
		printf("\nDo you want to perfrom more operations? (yes/no): ");
		gets(ans);
		fflush(stdin);
		if (strcmp(ans, check) != 0) {
			printf("\n---------------------------------------------------------");
			system("cls");
			for (int i=0; i<strlen(show); i++) {
				printf("%c", show[i]);
				usleep(100 * 1000);
			}
			end = 1;
			break;
		}                                                                                  
	}
}

//MAIN FUNCTION
main() {
	printf("================================== INCOME TAX CALCULATOR ==================================\n\n");
	password();
}

//FUNCTION DEFINITION TO LOGIN
void password() {
	char pwd[10], r, pwd_check[10] = "abc123";
	int index = 0;
	while (end!=1) {
		printf("\nEnter password to login: ");
		while((r = getch()) != 13) {
			putch('*');
			pwd[index] = r;
			index++;
		}
		pwd[index]='\0';
		if (strcmp(pwd,pwd_check)==0) {
			printf("\nLogin Successful\n");
			choices();
		} 
		else { 
			printf("\nInvalid password\n");
			index=0;
			printf("Please enter password again !\n\n"); 
		}
	}
}





















