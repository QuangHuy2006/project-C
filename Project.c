#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sex;

int amountstudent=0;

int amountteacher=0;

int amountclass=0;

struct Date
{
	int month, day, year;
};

struct Student
{
	int studentID;
	int classroomID;
	char name[20];
	struct Date dateofbirth;
	bool gender;
	char email[30];
	char phone[20];
	char password[20];
};
struct Student sv[100];

struct Classroom
{
	int classroomID;
	int teacherID;
	char classroomName[10];
	struct Student students[];
};
struct Classroom cr[100];

struct Teacher
{
	int teacherID;
	int classroomID;
	char name[20];
	struct Date dateofbirth;
	bool gender;
	char email[30];
	char phone[20];
	char password[20];
	struct Classroom classrooms[];
};
struct Teacher tc[100];

int max(int a,int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

void loadstudent(){
		FILE *file;
		file=fopen("student.bin", "rb");
		if(file){
			amountstudent=fread(sv,sizeof(sv[0]), 100,file);
			fclose(file);	
		}else{
			printf("Error : Student File Empty !");
		}
}

void loadteacher(){
		FILE *file;
		file=fopen("teacher.bin", "rb");
		if(file){
			amountteacher=fread(tc,sizeof(tc[0]), 100,file);
			fclose(file);	
		}else{
			printf("Error : Teacher File Empty !");
		}
}

void exiting(){
	char decision[10];
	while(1){
			printf("\nGo back(b)? or Exit(0)?:\n");
			fflush(stdin);
			gets(decision);
			if(strcmp(decision,"0")==0){
				return;
			}
			if(strcmp(decision,"b")==0){
				break;
			}
		}
}
void loadclass(){
		FILE *file;
		file=fopen("class.bin", "rb");
		if(file){
			amountclass=fread(cr,sizeof(cr[0]), 100,file);
			fclose(file);	
		}else{
			printf("Error : Class File Empty !");
		}
}

void savestudent(){
		FILE *file;
		file=fopen("student.bin", "wb");
		if(file){
			fwrite(sv,sizeof(sv[0]),amountstudent, file);	
			fclose(file);
		}else{
			printf("Error : Can't read file");
		}	
}

void saveteacher(){
		FILE *file;
		file=fopen("teacher.bin", "wb");
		if(file){
			fwrite(tc,sizeof(tc[0]),amountteacher, file);	
			fclose(file);
		}else{
			printf("Error : Can't read file");
		}	
}

void saveclass(){
		FILE *file;
		file=fopen("class.bin", "wb");
		if(file){
			fwrite(cr,sizeof(cr[0]),amountclass, file);	
			fclose(file);
		}else{
			printf("Error : Can't read file");
		}	
}

void AddStudent(){
	
	loadstudent();
	int cntwrongchar=1;
	printf("\t\t***Add Student***\t\t\n");
	int findstudent;
	int check=0;
	struct Student sv1;
	char email[20]="@gmail.com";
		while(check!=1){
			check = 0;
			printf("Enter the ID : ");
			scanf("%d", &findstudent);
			for (int i = 0; i <= amountstudent; i++) {
    			if (findstudent == sv[i].studentID) {
        			check = 0; 
       				 break; 
    			} else {
        			check = 1; 
        			
    			}
			}

			if (check) {
    			printf("ID VALID!\n");
   			sv1.studentID = findstudent; 
			} else {
   				 printf("ID UNVALID!\n");
			}
		}
		
		check=0;
		while(check!=1){
			check=0;
			fflush(stdin);
			printf("Enter classroom ID : ");
			scanf("%d", &sv1.classroomID);
				for(int i=0;i<amountclass;i++){
					if(sv1.classroomID==cr[i].classroomID){
						check=1;
						break;
					}
				}
				if(check){
					printf("Class Valid !\n");
				}else {
					printf("Class unvalid !\n");
				}
	
				
		}
		
		
		
		
		check=0;
		while(check!=1){
		fflush(stdin);
		cntwrongchar=1;
		printf("Enter name : ");
		fgets(sv1.name, sizeof(sv1.name), stdin);
		sv1.name[strcspn(sv1.name,"\n")]='\0';	
		if(strlen(sv1.name)==0){
			check=0;
			continue;
		}else{
		for(int i=0;i<strlen(sv1.name);i++){
					if(!isalpha(sv1.name[i]) && sv1.name[i] != ' '){
						cntwrongchar=0;
						break;
					}
			}
			
			if(cntwrongchar){
				printf("Name correct format !\n");
				if(amountstudent>=1){
					printf("Duplicate check !\n");
						for(int i = 0; i < amountstudent; i++){
							if(strcmp(sv1.name,sv[i].name)==0){
								printf("Name duplicated !\n");
								break;
							}else {
								check=1;	
							}
						}
				}else{
				check=1;	
				}
			}else {
				printf("Name improper format !\n");
				continue;
			}
				
		}
			
		}
			
		check=0;
		while(check!=1){
			int cntcheck=0;
			printf("Enter month of birth : ");
			scanf("%d", &sv1.dateofbirth.month);
				if(sv1.dateofbirth.month > 0 && sv1.dateofbirth.month <= 12){
					printf("MONTH VALID !\n");	
					cntcheck++;
				}else{
					printf("MONTH UNVALID !\n");
					continue;
				}
			printf("Enter day of birth : ");
				scanf("%d", &sv1.dateofbirth.day);
				if(sv1.dateofbirth.month == 1 || sv1.dateofbirth.month == 3 || sv1.dateofbirth.month == 5 || sv1.dateofbirth.month == 7 || sv1.dateofbirth.month == 8 || sv1.dateofbirth.month == 10 || sv1.dateofbirth.month == 12){
					if(sv1.dateofbirth.day > 0 && sv1.dateofbirth.day <= 31){	
						printf("DAY VALID !\n");
						cntcheck++;
					}else{
						printf("DAY UNVALID !\n");
						continue;
					}
				}
					if(sv1.dateofbirth.month == 4 || sv1.dateofbirth.month == 6 || sv1.dateofbirth.month == 9 || sv1.dateofbirth.month == 11){
						if(sv1.dateofbirth.day > 0 && sv1.dateofbirth.day <= 30){
							printf("DAY VALID !\n");
							cntcheck++;
						}else{
							printf("DAY UNVALID !\n");
							continue;
						}	
					}
						if(sv1.dateofbirth.month ==2){
							if(sv1.dateofbirth.day > 0 && sv1.dateofbirth.month <= 28){
								printf("DAY VALID !\n");
								cntcheck++;
							}else{
								printf("DAY UNVALID !\n");
								continue;
							}	
						}
							printf("Enter year of birth : ");
							scanf("%d", &sv1.dateofbirth.year);
								if(sv1.dateofbirth.year > 1900 && sv1.dateofbirth.year < 2025){
									printf("YEAR VALID !\n");
									cntcheck++;
								}else{
								printf("YEAR UNVALID !\n");
								continue;
								}
									if(cntcheck>=3){
										check=1;
									}else{
										printf("DATE OF BIRTH UNVALID !\n");
									}
		}
		
		check=0;
		while(check!=1){
		printf("Enter student gender(enter 0 for male, 1 for female) : ");
		scanf("%d", &sex);
			if(sex == 0 || sex==1){
				check=1;
			}else{
				printf("GENDER UNVALID\n");
			}
		}
		
		check=0;
		while(check!=1){
		fflush(stdin);
		printf("Enter email : ");
		fgets(sv1.email,sizeof(sv1.email),stdin);
		sv1.email[strcspn(sv1.email,"\n")]='\0';
		if(strlen(sv1.email)==0){
			check=0;
			continue;
		}else{
		if(strstr(sv1.email,email)==NULL){
			printf("Email improper format !\n");
		}else{
			printf("Email correct format !\n");
			if(amountstudent>=1){
				printf("Duplicate check !\n");
				for(int i = 0; i < amountstudent; i++){	
					if(strcmp(sv1.email,sv[i].email)==0){
						printf("Email duplicated !\n");
					}else {
						check=1;
						break;	
					}
				}
			}else{
				break;
			}
		}	
		}
		
		}
		
		check=0;
		int cntwrongdigit=1;
		while(check!=1){
			fflush(stdin);
			printf("Enter phonenumber : ");
			fgets(sv1.phone,sizeof(sv1.phone),stdin);
			sv1.phone[strcspn(sv1.phone,"\n")]='\0';
			if(strlen(sv1.phone)==0){
				check=0;
				continue;
			}else{
				for(int i=0;i<strlen(sv1.phone);i++){
					if(!isdigit(sv1.phone[i]) && sv1.phone[i] == ' '){
						cntwrongdigit=0;
						break;
					}
			}
			
			if(cntwrongdigit){
				printf("Phone correct format !\n");
				if(amountstudent>=1){
					printf("Duplicate check !\n");
						for(int i = 0; i < amountstudent; i++){
							if(strcmp(sv1.phone,sv[i].phone)==0){
								printf("Phone duplicated !\n");
							}else {
								check=1;	
							}
						}
				}else{
				check=1;	
				}
			}else {
				printf("Phone improper format !\n");
				continue;
			}
			
			}
				
		}
		
		sv[amountstudent]=sv1;
		amountstudent++;
		savestudent();		
	}
	
void PrintStudent(){	
	loadstudent();
	char exit[2]="0";
	char back[2]="b";
	char printchoice[10];
	
	int length=amountstudent;
	
	printf("\t\t***All Student***\t\n");
	printf("|===============|======================|============================|===================|==================|");
	printf("\n|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");
	printf("\n|===============|======================|============================|===================|==================|");
		for(int i = 0; i < length; i++){
				printf("\n|	%d	|%-22s|%-28s|%-17s	|	%s	   |", sv[i].studentID, sv[i].name, sv[i].email, sv[i].phone, cr[sv[i].classroomID-1].classroomName);
				printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");	
			}
				
	while(1){
		
	printf("\nGo back(b)? or Exit(0)?:\n");
	fflush(stdin);
	gets(printchoice);
	
		if(strcmp(printchoice,exit)==0){
			return;
		}
		
		if(strcmp(printchoice,back)==0){
			break;
		}
		
	}
}

void FindStudent(){
	
	loadstudent;
	char exit[2]="0";
	char back[2]="b";
	char findchoice[10];
	char findstudent[20];
	
	int check=0;
	int findpos;
	
	struct Student sv1;
	
	sv1=sv[amountstudent-1];
		fflush(stdin);
		
		while(check!=1){
			check=0;
			printf("\nOne Student Found For Name : ");
			gets(findstudent);
			printf("Student Informations\n");
			printf("---------------------\n");	
			printf("|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");	
			for(int i=0;i<amountstudent;i++){
				if(strstr(sv[i].name, findstudent)){
					check=1;
					printf("\n|===============|======================|============================|===================|==================|");
					printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", i+1, sv[i].name, sv[i].email, sv[i].phone, sv[i].classroomID);
				}
			}
		}
			if(check) {
				printf("\nFOUND !\n");
			}else{
				printf("\nUnvalid !, please enter another Name\n");	
			}

			while(1){
				
				printf("\nGo back(b)? or Exit(0)?:\n");
				fflush(stdin);
				gets(findchoice);
				
					if(strcmp(findchoice,exit)==0){
						return;
					}
					
						if(strcmp(findchoice,back)==0){
							break;
						}
						
		}
	}

void EditStudent(){
	
	loadstudent;
	struct Student sv1;
	struct Student sv2;
	
	char email[20]="@gmail.com";
	char exit[2]="0";
	char back[2]="b";
	
	int cntwrongchar=1;
	printf("\t\t***Edit A Student***\t\t\n");
	char editchoice[10];
	
	int findstudent;
	int check=0;
	
	
		fflush(stdin);
		
		while(check!=1){
			
		printf("Enter Student's ID : ");
			scanf("%d", &findstudent);	
			for(int i=0;i<amountstudent;i++){
					if(findstudent < 0 || findstudent > amountstudent+1 || findstudent != sv[i].studentID ) {
						check=0;
					}else {
						check++;
						break;
					}
							
			}
			
			if(check){
				printf("FOUND !\n");
				sv2=sv[findstudent-1];
				findstudent--;
				break;
			}else{
				printf("Unvalid !, please enter another ID\n");	
			}
		}
			printf("Student Informations\n");
			printf("---------------------\n");	
			printf("|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");	
			printf("\n|===============|======================|============================|===================|==================|");
			printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", sv[findstudent].studentID, sv[findstudent].name, sv[findstudent].email, sv[findstudent].phone, cr[sv[findstudent].classroomID-1].classroomID);
			printf("\n");
			fflush(stdin);
			printf("Enter classroom ID (enter 0 to skip) : ");
			scanf("%d", &sv1.classroomID);
			if(sv1.classroomID == 0){
				printf("information unchanged !\n");
				sv1.classroomID==sv2.classroomID;
			}
		
		check=0;
		while(check!=1){
			check=0;
			fflush(stdin);
			cntwrongchar=1;
			printf("Enter name (enter 0 to skip) : ");
			fgets(sv1.name,sizeof(sv1.name),stdin);
			sv1.name[strcspn(sv1.name,"\n")]='\0';
			if(strlen(sv1.name)==0){
			check=0;
			continue;	
			}else{
				if(strcmp(sv1.name,exit)==0){
						printf("information unchanged !\n");
						strcpy(sv1.name,sv2.name);
						check=1;
						continue;
					}else{
						for(int i=0;i<strlen(sv1.name);i++){
							if(!isalpha(sv1.name[i]) && sv1.name[i] != ' '){
								cntwrongchar=0;
								break;
							}
						}
				
					if(cntwrongchar){
						printf("Name correct format !\n");
						if(amountstudent>=1){
							printf("Duplicate check !");
								for(int i = 0; i < amountstudent; i++){
									if(strcmp(sv1.name,sv[i].name)==0){
										printf("Name duplicated !\n");
									}else {
									check=1;	
									}
								}
						}else{
							check=1;	
						}
					}else {
						printf("Name improper format !\n");
						continue;
					}
				}	
			}
				
		}
		
		
		
		check=0;
		while(check!=1){
			check=0;
			fflush(stdin);
			printf("Enter email (enter 0 to skip) : ");
			fgets(sv1.email,sizeof(sv1.email),stdin);
			sv1.email[strcspn(sv1.email,"\n")]='\0';
			if(strlen(sv1.email)==0){
				check=0;
				continue;
			}else{
				if(strcmp(sv1.email,exit)==0){
					printf("information unchanged !\n");
					strcpy(sv1.email,sv2.email);
					check=1;
					continue;
				}else{
					if(strstr(sv1.email,email)==NULL){
						printf("Email improper format !\n");
					}else{
						printf("Email correct format !\n");
						if(amountstudent>=1){
							printf("Duplicate check !\n");
							for(int i = 0; i < amountstudent; i++){	
								if(strcmp(sv1.email,sv[i].email)==0){
									printf("\nEmail duplicated !");
								}else {
									check=1;
									break;	
								}
							}
						}else{
							break;
						}	
					}	
				}	
			}	
		}
		
		check=0;
		while(check!=1){
			fflush(stdin);
			printf("Enter phonenumber (enter 0 to skip) : ");
			fgets(sv1.phone,sizeof(sv1.phone),stdin);
			if(strlen(sv1.phone)==0){
				check=0;
				continue;
			}else{
				sv1.phone[strcspn(sv1.phone,"\n")]='\0';
					if(strcmp(sv1.phone,exit)==0){
						printf("information unchanged !\n");
						strcpy(sv1.phone,sv2.phone);
						check=1;
						continue;
					}else{
						for(int i=0;i<strlen(sv1.phone);i++){
							if(isdigit(sv1.phone[i]) && strlen(sv1.phone)==10){
								printf("Phone correct format !");
								check=1;
								break;
							}else{
								printf("Phone improper format !");
								break;
							}
						}	
					}	
			}
		}
		
		
		sv[findstudent-1]=sv1;
		savestudent();
		while(1){
			printf("\nGo back(b)? or Exit(0)?:\n");
			fflush(stdin);
			gets(editchoice);
			if(strcmp(editchoice,exit)==0){
				return;
			}
			if(strcmp(editchoice,back)==0){
				break;
			}
		}
		
}

void DeleteStudent(){

	loadstudent();
	char deletechoice[10];
	char exit[2]="0";
	char back[2]="b";
	
	printf("\t\t***Delete A Student***\t\t\n");
	int findstudent;
	int check=0;
	
		fflush(stdin);
		while(check!=1){	
		printf("Enter Student's ID : ");
			scanf("%d", &findstudent);	
			if(findstudent < 0 || findstudent > amountstudent+1){
				printf("Unvalid !, please enter another ID\n");	
				check=0;
			}
			for(int i=0;i<amountstudent;i++){
					 if(findstudent == sv[i].studentID){
						check++;
					}	
			}
			if(check){
				printf("FOUND !\n");
				break;
			}
		}
		
		findstudent--;
		
			printf("Student Informations\n");
			printf("---------------------\n");	
			printf("\n|===============|======================|============================|===================|==================|");
			printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", findstudent+1, sv[findstudent].name, sv[findstudent].email, sv[findstudent].phone, sv[findstudent].classroomID);
			printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");
			printf("\nAre you sure want to delete this student? (Y/N) : ");
			fflush(stdin);
			gets(deletechoice);
			if(strcmp(deletechoice,"Y")==0){
				for(int i=findstudent;i<amountstudent-1;i++){
					strcpy(sv[i].name,sv[i+1].name);
					sv[i].studentID=sv[i+1].studentID;
					strcpy(sv[i].email,sv[i+1].email);
					strcpy(sv[i].phone,sv[i+1].phone);
					sv[i].classroomID=sv[i+1].classroomID;	
				}
				printf("\nStudent Was Deleted !");
				amountstudent--;
				savestudent();
			}
			if(strcmp(deletechoice,"N")==0){
				printf("Student was not deleted !");
			}
			
		while(1){
			printf("\nGo back(b)? or Exit(0)?:\n");
			fflush(stdin);
			gets(deletechoice);
			if(strcmp(deletechoice,exit)==0){
				return;
			}
			if(strcmp(deletechoice,back)==0){
				break;
			}
		}
}

void ArrangeStudentIncrease(){
	char temp[100];
	loadstudent();
	
	int m;
	int pos1;
	int pos2;
	for(int i=0;i<amountstudent;i++){
		for(int j=0;j<strlen(sv[i].name);j++){
			if(sv[i].name[j]==' '){
				pos1=j;
				pos2=j;
			}	
		}
			m = max(pos2,pos1);
}
for(int i=0;i<amountstudent-1;i++){
		int minpos=i;
		for(int j=i+1;j<amountstudent;j++){
			if(sv[minpos].name[m+1]>sv[j].name[m+1]){
				minpos=j;
			}
		}
		if(minpos!=i){
		strcpy(temp,sv[i].name);
		strcpy(sv[i].name,sv[minpos].name);
		strcpy(sv[minpos].name,temp);		
		}
	}
	
	printf("\n\t\t***All Students***\t\n");
	printf("|===============|======================|============================|===================|==================|");
	printf("\n|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");
	printf("\n|===============|======================|============================|===================|==================|");
	for(int i = 0; i < amountstudent; i++){
			printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", sv[i].studentID, sv[i].name, sv[i].email, sv[i].phone, sv[i].classroomID);
			printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");	
	}
	
}


void ArrangeStudentDecrease(){
	loadstudent();
	
	int m;
	int pos1;
	int pos2;
	
	for(int i=0;i<amountstudent;i++){
		for(int j=0;j<strlen(sv[i].name);j++){
			if(sv[i].name[j]==' '){
				pos1=j;
				pos2=j;
			}	
		}
			m=max(pos2,pos1);
	}
for(int i=0;i<amountstudent-1;i++){
		int minpos=i;
		for(int j=i+1;j<amountstudent;j++){
			if(sv[minpos].name[m+1]<sv[j].name[m+1]){
				minpos=j;
			}
		}
		if(sv[minpos].name[m+1]!=sv[i].name[m+1]){
			char temp[100];
			strcpy(temp,sv[i].name);
			strcpy(sv[i].name,sv[minpos].name);
			strcpy(sv[minpos].name,temp);		
		}
	}
	
	printf("\n\t\t***All Students***\t\n");
	printf("|===============|======================|============================|===================|==================|");
	printf("\n|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");
	printf("\n|===============|======================|============================|===================|==================|");
	for(int i = 0; i < amountstudent; i++){
			printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", sv[i].studentID, sv[i].name, sv[i].email, sv[i].phone, sv[i].classroomID);
			printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");	
	}
	
}

void AddTeacher(){
	
	loadteacher();
	int cntwrongchar=1;
	
	printf("\t\t***Add Teacher***\t\t\n");
	int findteacher;
	
	int check=0;
	struct Teacher sv1;
	
	char email[20]="@gmail.com";
			check=0;
			while(check!=1){
			check = 0;
			printf("Enter the ID : ");
			scanf("%d", &findteacher);
			for (int i = 0; i <= amountteacher; i++) {
    			if (findteacher == tc[i].teacherID) {
        			check = 0; 
    			} else {
        			check = 1; 
        			break; 
    			}
			}

			if (check) {
    			printf("ID VALID!\n");
    			sv1.teacherID = findteacher; 
			} else {
   				 printf("ID UNVALID!\n");
			}

		}
		
		check=0;
		while(check!=1){
			check=0;
			fflush(stdin);
			printf("Enter classroom ID : ");
			scanf("%d", &sv1.classroomID);
				for(int i=0;i<amountclass;i++){
					if(sv1.classroomID==cr[i].classroomID){
						check=1;
						break;
					}
				}
				if(check){
					printf("Class Valid !\n");
				}else {
					printf("Class unvalid !\n");
				}	
			}	
		
		
				
		check=0;
		while(check!=1){
		check=0;	
		fflush(stdin);
		cntwrongchar=1;
		printf("Enter name : ");
		fgets(sv1.name, sizeof(sv1.name), stdin);
		sv1.name[strcspn(sv1.name,"\n")]='\0';	
			if(strlen(sv1.name)==0){
			check=0;
			continue;
		}else{
			for(int i=0;i<strlen(sv1.name);i++){
					if(!isalpha(sv1.name[i]) && sv1.name[i] != ' '){
						cntwrongchar=0;
						break;
					}
			}
			
			if(cntwrongchar){
				printf("Name correct format !\n");
				if(amountteacher>=1){
					printf("Duplicate check !\n");
						for(int i = 0; i < amountteacher; i++){
							if(strcmp(sv1.name,tc[i].name)==0){
								printf("Name duplicated !\n");
							}else {
								check=1;	
							}
						}
				}else{
				check=1;	
				}
			}else {
				printf("Name improper format !\n");
				continue;
			}
		}
		}
			
		check=0;
		while(check!=1){
			check=0;
			int cntcheck=0;
			printf("Enter month of birth : ");
			scanf("%d", &sv1.dateofbirth.month);
				if(sv1.dateofbirth.month > 0 && sv1.dateofbirth.month <= 12){
					printf("MONTH VALID !\n");	
					cntcheck++;
				}else{
					printf("MONTH UNVALID !\n");
					continue;
				}
			printf("Enter day of birth : ");
				scanf("%d", &sv1.dateofbirth.day);
				if(sv1.dateofbirth.month == 1 || sv1.dateofbirth.month == 3 || sv1.dateofbirth.month == 5 || sv1.dateofbirth.month == 7 || sv1.dateofbirth.month == 8 || sv1.dateofbirth.month == 10 || sv1.dateofbirth.month == 12){
					if(sv1.dateofbirth.day > 0 && sv1.dateofbirth.day <= 31){	
						printf("DAY VALID !\n");
						cntcheck++;
					}else{
						printf("DAY UNVALID !\n");
						continue;
					}
				}
					if(sv1.dateofbirth.month == 4 || sv1.dateofbirth.month == 6 || sv1.dateofbirth.month == 9 || sv1.dateofbirth.month == 11){
						if(sv1.dateofbirth.day > 0 && sv1.dateofbirth.day <= 30){
							printf("DAY VALID !\n");
							cntcheck++;
						}else{
							printf("DAY UNVALID !\n");
							continue;
						}	
					}
						if(sv1.dateofbirth.month ==2){
							if(sv1.dateofbirth.day > 0 && sv1.dateofbirth.month <= 28){
								printf("DAY VALID !\n");
								cntcheck++;
							}else{
								printf("DAY UNVALID !\n");
								continue;
							}	
						}
							printf("Enter year of birth : ");
							scanf("%d", &sv1.dateofbirth.year);
								if(sv1.dateofbirth.year > 1900 && sv1.dateofbirth.year < 2025){
									printf("YEAR VALID !\n");
									cntcheck++;
								}else{
								printf("YEAR UNVALID !\n");
								continue;
								}
									if(cntcheck>=3){
										check=1;
									}else{
										printf("DATE OF BIRTH UNVALID !\n");
									}
		}
		
		check=0;
		while(check!=1){
		check=0;	
		printf("Enter teacher gender(enter 0 for male, 1 for female) : ");
		scanf("%d", &sex);
			if(sex == 0 || sex == 1){
				
				check = 1;
				
			}else{
				
				printf("\nGENDER UNVALID !");
				
			}
		}
		
		check=0;
		while(check!=1){
		check=0;	
		fflush(stdin);
		printf("Enter email : ");
		fgets(sv1.email,sizeof(sv1.email),stdin);
		sv1.email[strcspn(sv1.email,"\n")]='\0';
		if(strlen(sv1.email)==0){
			check=0;
			continue;
		}else{
		if(strstr(sv1.email,email)==NULL){
			printf("Email improper format !\n");
		}else{
			printf("Email correct format !\n");
				if(amountteacher>=1){
					printf("Duplicate check !\n");
						for(int i = 0; i < amountteacher; i++){	
							if(strcmp(sv1.email,tc[i].email)==0){
								printf("\nEmail duplicated !");
							}else {
								check=1;
								break;	
							}
						}
				}else{
					break;
				}
			}
		}
	}
		
		check=0;
		int cntwrongdigit=1;
		while(check!=1){
		check=0;	
			fflush(stdin);
			printf("Enter phonenumber : ");
			fgets(sv1.phone,sizeof(sv1.phone),stdin);
			sv1.phone[strcspn(sv1.phone,"\n")]='\0';
			if(strlen(sv1.phone)==0){
				check=0;
				continue;
			}else{
				for(int i=0;i<strlen(sv1.phone);i++){
					if(!isdigit(sv1.phone[i]) && sv1.phone[i] == ' '){
						cntwrongdigit=0;
						break;
					}
			}
			
			if(cntwrongdigit){
				printf("Phone correct format !\n");
					if(amountteacher>=1){
						printf("Duplicate check !\n");
							for(int i = 0; i < amountteacher; i++){
								if(strcmp(sv1.phone,tc[i].phone)==0){
									printf("\nPhone duplicated !");
								}else {
									check=1;	
								}
							}
					}else{
						check=1;	
					}
			}else {
				printf("Phone improper format !\n");
				continue;
			}
			}
		}
		
		tc[amountteacher]=sv1;
		amountteacher++;
		saveteacher();
		printf("Teacher Added Successfully !");
	}

void AddClassToStudent(){
	loadclass();
	char choice[2];
	char exit[2]="0";
	char back[2]="b";
	char findchoice[10];
	char findclass[20];
	
	int check=0;
	int findpos;
	int findclass2;
	
	struct Classroom cr1;
	
	cr1=cr[amountclass-1];
		fflush(stdin);
		
		while(check!=1){
			
			printf("One Class Found For Name : ");
			gets(findclass);
			for(int i=0;i<amountclass;i++){
				if(strcmp(findclass, cr[i].classroomName)==0){
					check++;
					findpos = i;
				}
			}
			if(check) {
				printf("FOUND !\n");
			}else{
				printf("Unvalid !, please enter another Name\n");	
			}
		}
			
			printf("Class Informations\n");
			printf("|	ID	|ClassName           |	Student ID      |   Teacher ID     |\n");
			printf("|---------------|--------------------|------------------|------------------|");	
			printf("\n|	%d	|%-20s| %d                | %d                |", cr[findpos].classroomID, cr[findpos].classroomName, cr[findpos].students[findpos].studentID, cr[findpos].teacherID);
			printf("\n|---------------|--------------------|------------------|------------------|");
			check=0;
			while(check!=1){
			check = 0;
			printf("\nEnter the student ID : ");
			scanf("%d", &cr1.students[findpos].studentID);
			for (int i = 0; i < amountstudent; i++) {
    			if (cr1.students[findpos].studentID == sv[i].studentID) {
        			check = 1; 
       				 break; 
    			} else {
        			check = 0; 
    			}
			}

			if (check) {
    			printf("ID VALID !\n");
			} else {
   				 printf("ID UNVALID !\n");
			}	
		}
		printf("Student Informations\n");
			printf("---------------------\n");	
			printf("|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");	
			printf("\n|===============|======================|============================|===================|==================|");
			printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", sv[findpos].studentID, sv[findpos].name, sv[findpos].email, sv[findpos].phone, sv[findpos].classroomID);
			printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");
			printf("\nYou sure want to input this student to class(Y/N) : ");
			fflush(stdin);
			gets(choice);
			if(strcmp(choice,"Y")==0){
				cr[findpos].students[findpos].studentID=cr1.students[findpos].studentID;
				savestudent();	
				saveclass();
				printf("Student was added to class !");
			}
			if(strcmp(choice,"N")==0){
				printf("Student wasn't added to class !");	
				cr[findpos].students[findpos].studentID = 0;			
			}
	}
	
void AddClassToTeacher(){
	loadclass();
	char exit[2]="0";
	char back[2]="b";
	char findchoice[10];
	char findclass[20];
	char choice[20];
	
	int check=0;
	int findpos;
	
	struct Classroom cr1;
	
	cr1=cr[amountclass-1];
		fflush(stdin);
		
		while(check!=1){
			
			printf("One Class Found For Name : ");
			gets(findclass);
			for(int i=0;i<amountclass;i++){
				if(strcmp(findclass, cr[i].classroomName)==0){
					check++;
					findpos = i;
				}
			}
		}
			if(check) {
				printf("FOUND !\n");
			}else{
				printf("Unvalid !, please enter another Name\n");	
			}

			printf("Class Informations\n");
			printf("|	ID	|ClassName           |	Student ID      |   Teacher ID     |\n");
			printf("|---------------|--------------------|------------------|------------------|");	
			printf("\n|	%d	|%-20s| %d                | %d                |", cr[findpos].classroomID, cr[findpos].classroomName, cr[findpos].students[findpos].studentID, cr[findpos].teacherID);
			printf("\n|---------------|--------------------|------------------|------------------|");
			
			check=0;
			int found=0;
			while(check!=1){
			check=0;
			fflush(stdin);
			printf("\nEnter teacher's ID To Add To Class : ");
			scanf("%d", &cr1.teacherID);
			for(int i=0;i<amountteacher;i++){
					if(cr1.teacherID==tc[i].teacherID){
						found++;
					}
			}
				if(found){
					printf("TEACHERID VALID !\n");
					check=1;
					printf("Student Informations\n");
			printf("---------------------\n");	
			printf("|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");	
			printf("\n|===============|======================|============================|===================|==================|");
			printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", findpos+1, tc[findpos].name, tc[findpos].email, tc[findpos].phone, tc[findpos].classroomID);
			printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");
				}else{
					printf("TEACHERID UNVALID !\n");
				}	
			}
			printf("\nYou sure want to input this teacher to class(Y/N) : ");
			while(1){		
			fflush(stdin);
			gets(choice);
			if(strcmp(choice,"Y")==0){
				cr[findpos].teacherID=cr1.teacherID;
				
				saveteacher();
				saveclass();	
				printf("Teacher was added to class !");
				break;
			}
			if(strcmp(choice,"N")==0){
				printf("Teacher wasn't added to class !");	
				cr[findpos].teacherID= 0;	
				break;		
			}
						
		}
	}

void PrintTeacher(){	
	loadteacher();
	char exit[2]="0";
	char back[2]="b";
	char printchoice[10];
	
	int length=amountteacher;

	printf("\t\t***All TEACHERS***\t\n");
	printf("|===============|======================|============================|===================|==================|");
	printf("\n|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");
	printf("\n|===============|======================|============================|===================|==================|");
	
		for(int i = 0; i < length; i++){
				printf("\n|	%d	|%-22s|%-28s|%-17s	|	%s	   |", tc[i].teacherID, tc[i].name, tc[i].email, tc[i].phone, cr[tc[i].classroomID-1].classroomName);
				printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");	
			}
		saveteacher();		
	while(1){
		
	printf("\nGo back(b)? or Exit(0)?:\n");
	fflush(stdin);
	gets(printchoice);
	
		if(strcmp(printchoice,exit)==0){
			return;
		}
		
		if(strcmp(printchoice,back)==0){
			break;
		}
		
	}
}

void FindTeacher(){
	
	loadteacher();
	char exit[2]="0";
	char back[2]="b";
	char findchoice[10];
	char findteacher[20];
	
	int check=0;
	int findpos;
	
	struct Teacher sv1;
	
	sv1=tc[amountteacher-1];
		fflush(stdin);
		
	while(check!=1){
			check=0;
			printf("\nOne Teacher Found For Name : ");
			gets(findteacher);
			printf("Teacher Informations\n");
			printf("---------------------\n");	
			printf("|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");	
			for(int i=0;i<amountteacher;i++){
				if(strstr(tc[i].name, findteacher)){
					check=1;
					printf("\n|===============|======================|============================|===================|==================|");
					printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", i+1, tc[i].name, tc[i].email, tc[i].phone, tc[i].classroomID);
				}
			}
		}
			if(check) {
				printf("\nFOUND !\n");
			}else{
				printf("\nUnvalid !, please enter another Name\n");	
			}
			while(1){
				
				printf("\nGo back(b)? or Exit(0)?:\n");
				fflush(stdin);
				gets(findchoice);
				
					if(strcmp(findchoice,exit)==0){
						return;
					}
					
						if(strcmp(findchoice,back)==0){
							break;
						}
						
		}
	}

void EditTeacher(){
	
	loadteacher();
	int cntwrongchar=1;
	
	struct Teacher sv1;
	struct Teacher sv2;
	
	char exit[2]="0";
	char back[2]="b";
	char email[20]="@gmail.com";
	
	printf("\t\t***Edit A Teacher***\t\t\n");
	char editchoice[10];
	
	int findteacher;
	int check=0;
	
	
		fflush(stdin);
		
		while(check!=1){
			
		printf("Enter Teacher's ID : ");
			scanf("%d", &findteacher);	
			for(int i=0;i<amountteacher;i++){			
					if(findteacher < 0 || findteacher > amountteacher+1 || findteacher != sv1.teacherID ) {
						check=0;
					}else {
						check++;
					}
							
			}
			
			if(check){
				printf("FOUND !\n");
				sv2=tc[findteacher-1];
				break;
			}else{
				printf("Unvalid !, please enter another ID\n");	
			}
			
		}

		check=0;
		while(check!=1){
			check=0;
			fflush(stdin);
			cntwrongchar=1;
			printf("Enter name (enter 0 to skip) : ");
			fgets(sv1.name,sizeof(sv1.name),stdin);
			sv1.name[strcspn(sv1.name,"\n")]='\0';
				if(strlen(sv1.name)==0){
					printf("Name Unvalid !");
				}else{	
					if(strcmp(sv1.name,exit)==0){
						printf("information unchanged !\n");
						strcpy(sv1.name,sv2.name);
						check=1;
						continue;
					}else{
						for(int i=0;i<strlen(sv1.name);i++){
							if(!isalpha(sv1.name[i]) && sv1.name[i] != ' '){
								cntwrongchar=0;
								break;
							}
						}
			
						if(cntwrongchar){
							printf("Name correct format !\n");
							if(amountteacher>=1){
								printf("Duplicate check !\n");
								for(int i = 0; i < amountteacher; i++){
									if(strcmp(sv1.name,tc[i].name)==0){
										printf("Name duplicated !\n");
									}else {
										check=1;	
									}
								}
							}else{
								check=1;	
							}
						}else {
							printf("Name improper format !\n");
							continue;
						}
					}
				}
		}
		
		check=0;
		while(check!=1){
			check=0;
			fflush(stdin);
			printf("Enter email (enter 0 to skip) : ");
			fgets(sv1.email,sizeof(sv1.email),stdin);
			sv1.email[strcspn(sv1.email,"\n")]='\0';
			if(strcmp(sv1.email,exit)==0){
				printf("information unchanged !\n");
				strcpy(sv1.email,sv2.email);
				check=1;
				continue;
			}else{
				if(strstr(sv1.email,email)==NULL){
					printf("Email improper format !\n");
				}else{
					printf("Email correct format !\n");
					if(amountteacher>=1){
						printf("Duplicate check !\n");
						for(int i = 0; i < amountteacher; i++){	
							if(strcmp(sv1.email,tc[i].email)==0){
								printf("Email duplicated !\n");
							}else {
								check=1;
								break;	
							}
						}
					}else{
						break;
					}	
				}	
			}
		}
		
		check=0;
		while(check!=1){
		check=0;	
		fflush(stdin);
		printf("Enter phonenumber (enter 0 to skip) : ");
		fgets(sv1.phone,sizeof(sv1.phone),stdin);
		sv1.phone[strcspn(sv1.phone,"\n")]='\0';
			if(strlen(sv1.phone)==0){
				check=0;
				continue;
			}else{
				if(strcmp(sv1.phone,exit)==0){
					printf("information unchanged !\n");
					strcpy(sv1.phone,sv2.phone);
					check=1;
					continue;
				}else{
					for(int i=0;i<strlen(sv1.phone);i++){
						if(isdigit(sv1.phone[i]) && strlen(sv1.phone)==10){
							printf("Phone correct format !\n");
							check=1;
							break;
						}else{
							printf("Phone improper format !\n");
							break;
						}	
					}
				}
			}
		}
		
		tc[findteacher-1]=sv1;
		saveteacher();
		
		while(1){
			printf("\nGo back(b)? or Exit(0)?:\n");
			fflush(stdin);
			gets(editchoice);
			if(strcmp(editchoice,exit)==0){
				return;
			}
			if(strcmp(editchoice,back)==0){
				break;
			}
		}
		
}

void DeleteTeacher(){

	loadteacher();
	char deletechoice[10];
	char exit[2]="0";
	char back[2]="b";
	
	printf("\t\t***Delete A Teacher***\t\t\n");
	int findteacher;
	int check=0;
	
		fflush(stdin);
		while(check!=1){	
		printf("Enter Teacher's ID : ");
			scanf("%d", &findteacher);	
			if(findteacher < 0 || findteacher > amountteacher + 1){
				printf("Unvalid !, please enter another ID\n");	
				check=0;
			}
			for(int i=0;i<amountteacher;i++){
					 if(findteacher == tc[i].teacherID){
						check++;
					}	
			}
			if(check){
				printf("FOUND !\n");
				break;
			}
		}
		
		findteacher--;
		
			printf("Teacher Informations\n");
			printf("---------------------\n");	
			printf("\n|===============|======================|============================|===================|==================|");
			printf("\n|	%d	|%-22s|%-28s|%-17s	|	%d	   |", findteacher+1, tc[findteacher].name, tc[findteacher].email, tc[findteacher].phone, cr[tc[findteacher-1].classroomID].classroomName);
			printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");
			printf("\nAre you sure want to delete this teacher? (Y/N) : ");
			fflush(stdin);
			gets(deletechoice);
			if(strcmp(deletechoice,"Y")==0){
				for(int i=findteacher;i<amountteacher-1;i++){
					strcpy(tc[i].name,tc[i+1].name);
					tc[i].teacherID=tc[i+1].teacherID;
					strcpy(tc[i].email, tc[i+1].email);
					strcpy(tc[i].phone, tc[i+1].phone);
					tc[i].classroomID = tc[i+1].classroomID;	
				}
				printf("\nTeacher Was Deleted !");
				amountteacher--;
				saveteacher();
			}
			if(strcmp(deletechoice,"N")==0){
				printf("\nTeacher was not deleted !");
			}
			saveteacher();
			
		while(1){
			printf("\nGo back(b)? or Exit(0)?:\n");
			fflush(stdin);
			gets(deletechoice);
			if(strcmp(deletechoice,exit)==0){
				return;
			}
			if(strcmp(deletechoice,back)==0){
				break;
			}
		}
}

void AddClass(){
	loadclass();
	int cntwrongchar=1;
	printf("\t\t***Add Class***\t\t\n");
	struct Classroom cr1;
	int findclass;
	int check=0;
			while(check!=1){
			check = 0;
			printf("Enter the ID : ");
			scanf("%d", &findclass);
			for(int i=0;i<= amountclass;i++){
    			if (findclass == cr[i].classroomID) {
        			check = 0; 
       				 break; 
    			} else {
        			check = 1; 
    			}
    		}

			if (check) {
    			printf("ID VALID!\n");
    			cr1.classroomID = findclass; 
			} else {
   				 printf("ID UNVALID!\n");
			}

		}
		
		check=0;
		while(check!=1){
			check=0;
			fflush(stdin);
			printf("Enter class name : ");
			fgets(cr1.classroomName,sizeof(cr1.classroomName),stdin);
			cr1.classroomName[strcspn(cr1.classroomName,"\n")]='\0';
			if(strlen(cr1.classroomName)==0){
				check=0;
				continue;
			}else{
				for(int i=0;i<amountclass;i++){
					if(strcmp(cr1.classroomName, cr[i].classroomName)==0){
					check=0;
					printf("Classroom Name Duplicated !");
					break;
					}else{
						check=1;
						break;	
					}
				}
			}
		}
		
		if(amountteacher > 0){
		check=0;
		int found=0;
		while(check!=1){
		fflush(stdin);
		cntwrongchar=1;
		printf("Enter teacher's ID To Add To Class : ");
		scanf("%d", &cr1.teacherID);
			for(int i=0;i<=amountteacher;i++){
					if(cr[i].teacherID==tc[i].teacherID){
						found++;
					}
			}
				if(found){
					printf("TEACHERID VALID !\n");
					check=1;
				}else{
					printf("TEACHERID UNVALID !\n");
				}	
		}	
		}
		
		if(amountstudent > 0){
			check=0;
			while(check!=1){
				check = 0;
				printf("Enter the student ID : ");
				scanf("%d", &cr1.students[findclass].studentID);
				for (int i = 0; i < amountstudent; i++) {
    				if (cr1.students[findclass].studentID == sv[i].studentID) {
        				check = 1; 
       					 break; 
    				} else {
        				check = 0; 
    				}
				}

				if (check) {
    				printf("ID VALID !\n");
				} else {
   					 printf("ID UNVALID !\n");
				}

			}
		}
			
		cr[amountclass]=cr1;
		amountclass++;
		saveclass();
		printf("Class added successfully !");
}
	
void PrintClass(){
	loadclass();
	char exit[2]="0";
	char back[2]="b";
	char printchoice[10];
	int length = amountclass;
	printf("\t\t***All Class***\t\n");
	printf("|===============|====================|==========================|==========================|");
	printf("\n|	ID	|ClassName           |	Student Name            |   Teacher Name           |");
	printf("\n|===============|====================|==========================|==========================|");
	
		for(int i = 0; i < length; i++){
			printf("\n|	%d	|%-20s| %-25s| %-25s|", cr[i].classroomID, cr[i].classroomName, sv[cr[i].students[i].studentID-1].name, tc[cr[i].teacherID-1].name);
			printf("\n|---------------|--------------------|--------------------------|--------------------------|");
		}
		saveclass();
	while(1){
		
	printf("\nGo back(b)? or Exit(0)?:\n");
	fflush(stdin);
	gets(printchoice);
	
		if(strcmp(printchoice,exit)==0){
			return;
		}
		
		if(strcmp(printchoice,back)==0){
			break;
		}
		
	}
}

void FindClass(){
	
	loadclass();
	char exit[2]="0";
	char back[2]="b";
	char findchoice[10];
	int findclass;
	
	int check=0;
	int findpos;
	
	struct Classroom cr1;
	
	cr1=cr[amountclass-1];
		fflush(stdin);
		
		while(check!=1){
			check=0;
			printf("\nOne Class Found For ID : ");
			scanf("%d", &findclass);
			printf("Class Informations\n");
			printf("---------------------\n");
			printf("|	ID	|ClassName           |	Student ID      |   Teacher ID     |\n");	
			findclass--;
			for(int i=0;i<=amountclass;i++){
				if(findclass==cr[i].classroomID){
					check=1;
				printf("|===============|====================|==================|==================|");
				printf("\n|	%d	|%-20s| %d                | %d                |", cr[findclass].classroomID, cr[findclass].classroomName, cr[findclass].students[findclass].studentID, cr[findclass].teacherID);
			}
		}
			if(check) {
				printf("\nFOUND !\n");
			}else{
				printf("\nUnvalid !, please enter another \n");	
			}
		}
			while(1){
				
				printf("\nGo back(b)? or Exit(0)?:\n");
				fflush(stdin);
				gets(findchoice);
				
					if(strcmp(findchoice,exit)==0){
						return;
					}
					
						if(strcmp(findchoice,back)==0){
							break;
						}
						
		}
	}

void EditClass(){
	
	loadclass();
	struct Classroom cr1;
	struct Classroom cr2;
	
	char exit[2]="0";
	char back[2]="b";
	char editchoice[10];
	
	
	printf("\t\t***Edit Class***\t\t\n");
	int findclass;
	int check=0;
			while(check!=1){
			check = 0;
			printf("Enter the ID (enter 0 to skip) : ");
			scanf("%d", &findclass);
			findclass--;
			
			for(int i=0;i<=amountclass;i++){
    			if (findclass != cr[i].classroomID) {
        			check = 0; 
       				 
    			} else {
        			check = 1; 
        			break; 
    			}
    		}

			if (check) {
    			printf("ID VALID!\n");
    			cr2=cr[findclass-1];
			} else {
   				 printf("ID UNVALID!\n");
			}

		}
		
		check=0;
		while(check!=1){
			check=0;
			fflush(stdin);
			printf("Enter class name (enter 0 to skip): ");
			if(strcmp(cr1.classroomName,"0")==0){
				printf("Information Unchanged");
				strcpy(cr1.classroomName,cr2.classroomName);
			}else{
			fgets(cr1.classroomName,sizeof(cr1.classroomName),stdin);
			cr1.classroomName[strcspn(cr1.classroomName,"\n")]='\0';
			if(strlen(cr1.classroomName)==0){
				check=0;
				continue;
			}else{
				check=1;
			}	
			}	
		}
		
		
		check=0;
		int found=0;
		while(check!=1){
		fflush(stdin);
		printf("Enter teacher's ID To Add To Class (if number teacher only 1 auto skip) : ");
		if(amountteacher <= 1){
			cr[findclass].teacherID==cr2.teacherID;
			printf("SKipped !!\n");
			check=1;
			continue;
		}else{
			found=0;
		scanf("%d", &cr1.teacherID);
			for(int i=0;i<=amountteacher;i++){
					if(cr[i].teacherID==tc[i].teacherID){
						found++;
					}
			}
				if(found){
					printf("TEACHERID VALID !\n");
					check=1;
				}else{
					printf("TEACHERID UNVALID !\n");
				}	
		}
			
		}
			check = 0;
			while(check!=1){
			check = 0;
			printf("Enter student's ID To Add To Class (if number student only 1 auto skip) : ");
		if(amountstudent <= 1){
			cr[findclass].students[findclass].studentID==cr2.students[findclass].studentID;
			printf("SKipped !!\n");
			check=1;
			continue;
		}else{
			scanf("%d", &cr1.students[findclass].studentID);
			for (int i = 0; i < amountstudent; i++) {
    			if (cr1.students[findclass].studentID == sv[i].studentID) {
        			check = 1; 
       				 break; 
    			} else {
        			check = 0; 
    			}
			}

			if (check) {
    			printf("ID VALID !\n");
			} else {
   				 printf("ID UNVALID !\n");
			}

		}
	}
	cr[findclass-1]=cr1;
		saveclass();
		while(1){
			printf("\nGo back(b)? or Exit(0)?:\n");
			fflush(stdin);
			gets(editchoice);
			if(strcmp(editchoice,exit)==0){
				return;
			}
			if(strcmp(editchoice,back)==0){
				break;
			}
		}
}

void DeleteClass(){

	loadclass();
	char deletechoice[10];
	char exit[2]="0";
	char back[2]="b";
	
	printf("\t\t***Delete Class***\t\t\n");
	int findclass;
	int check=0;
	
		fflush(stdin);
		while(check!=1){
			check = 0;
			printf("Enter the ID : ");
			scanf("%d", &findclass);
			for(int i=0;i<=amountclass;i++){
    			if (findclass != cr[i].classroomID) {
        			check = 0; 
       				 
    			} else {
        			check = 1; 
        			break; 
    			}
    		}

			if (check) {
    			printf("ID VALID!\n");
			} else {
   				 printf("ID UNVALID!\n");
			}

		}
		
		findclass--;
		
			printf("Class Informations\n");
			printf("|---------------|--------------------|------------------|------------------|");
			printf("\n|	%d	|%-20s| %d                | %d                |", cr[findclass].classroomID, cr[findclass].classroomName, cr[findclass].students[findclass].studentID, cr[findclass].teacherID);
			printf("\n|---------------|--------------------|------------------|------------------|");
			printf("\nAre you sure want to delete this class? (Y/N) : ");
			fflush(stdin);
			gets(deletechoice);
			if(strcmp(deletechoice,"Y")==0){
				for(int i=findclass;i<amountclass-1;i++){
					strcpy(cr[i].classroomName,cr[i+1].classroomName);
					cr[i].teacherID = cr[i+1].teacherID;
					cr[i].classroomID = cr[i+1].classroomID;
					cr[i].students[i].studentID	= cr[i+1].students[i+1].studentID;
				}
				printf("\nClass Was Deleted !");
				amountclass--;
				saveclass();
			}
			if(strcmp(deletechoice,"N")==0){
				printf("\nClass was not deleted !");
			}
			
		saveclass();
		while(1){
			printf("\nGo back(b)? or Exit(0)?:\n");
			fflush(stdin);
			gets(deletechoice);
			if(strcmp(deletechoice,exit)==0){
				return;
			}
			if(strcmp(deletechoice,back)==0){
				break;
			}
		}
}

int main(){
	loadstudent();
	loadteacher();
	loadclass();	
	int choice;
	
	int adminchoice;
	
	int admin;
	
	int check=0;
	
	FILE *file;
	file=fopen("account.txt", "w");
	char username[15]="quanghuy";
	
	char password[15]="quanghuy123";
	
	fprintf(file,"Username : %s", username);
	
	fprintf(file,"\nPassword : %s", password);
	
	fclose(file);
	
	char login[15];
	
	char passwordlogin[15];
	
	int cnt=0;
	
	char decision[2];
	
	do
	{
		printf("\n***Student Management System Using C***\n");
		
		printf("\t    CHOOSE YOUR ROLE\n");
		
		printf("\t========================\n");
		
		printf("\t[1] Admin.\n");
		
		printf("\t[2] Student.\n");
		
		printf("\t[3] Teacher.\n");
		
		printf("\t[0] Exit The Program.\n");
		
		printf("\t========================\n");
		
		printf("\tENTER YOUR CHOICE : ");
		
		scanf("%d", &choice);
		
		if(choice==0){
			printf("!!!EXIT THE PROGRAM!!!");
			break;
		}
		
			if(choice == 1){
			while(1){	
				cnt=0; 
				printf("\t***Student Management System***\n");
				printf("\n\tLogin\n");
				printf("\t===================\n");
				fflush(stdin);
				printf("\tUsername : ");
				fgets(login,100,stdin);
				login[strcspn(login,"\n")]='\0';
	
				fflush(stdin);
				printf("\tPassword : ");
				fgets(passwordlogin,100,stdin);
				passwordlogin[strcspn(passwordlogin,"\n")]='\0';
				if(strcmp(passwordlogin,password)==0 && strcmp(login,username)==0){
					cnt=1;
					
				}
				printf("\t===================\n");
				if(cnt==1){
					check=1;
					break;
				}else{
					printf("\tUsername or password incorrect !\n");	
				}
			}
		}
		
		if(choice==2){
			printf("\t\t***All Student***\t\n");
			printf("|===============|======================|============================|===================|==================|");
			printf("\n|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");
			printf("\n|===============|======================|============================|===================|==================|");
				for(int i = 0; i < amountstudent; i++){
					printf("\n|	%d	|%-22s|%-28s|%-17s	|	%s	   |", sv[i].studentID, sv[i].name, sv[i].email, sv[i].phone, cr[sv[i].classroomID-1].classroomName);
					printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");	
				}
		while(1){
			char choice2[10];	
				printf("\nGo back(b)? or Exit(0)?:\n");
				fflush(stdin);
				gets(choice2);
				
					if(strcmp(choice2,"0")==0){
						exit(0);
					}
					
						if(strcmp(choice2,"b")==0){
							break;
						}
						
		}	
		}
		if(choice==3){
			printf("\t\t***All TEACHERS***\t\n");
			printf("|===============|======================|============================|===================|==================|");
			printf("\n|	ID	|	Name	       |	Email	            |	Phone	        |   NO.Course      |");
			printf("\n|===============|======================|============================|===================|==================|");
				for(int i = 0; i < amountteacher; i++){
					printf("\n|	%d	|%-22s|%-28s|%-17s	|	%s	   |", tc[i].teacherID, tc[i].name, tc[i].email, tc[i].phone, cr[tc[i].classroomID-1].classroomName);
					printf("\n|---------------|----------------------|----------------------------|-------------------|------------------|");	
				}
		while(1){
				char choice2[10];
				printf("\nGo back(b)? or Exit(0)?:\n");
				fflush(stdin);
				gets(choice2);
				
					if(strcmp(choice2,"0")==0){
						exit(0);
					}
					
						if(strcmp(choice2,"b")==0){
							break;
						}
						
		}	
		}
			if(check){
				while(1){
			
				printf("\n\t***Admin Management System***\t\n");
			
				printf("\t=========================\n");
			
				printf("\t[1] : Student Management.\n");
			
				printf("\t[2] : Teacher Management.\n");
			
				printf("\t[3] : User Guildline.\n");
			
				printf("\t[4] : About us.\n");
			
				printf("\t[0] : Exit Program.\n");
			
				printf("\t=========================\n");
			
				printf("\tEnter your choice : ");
			
				scanf("%d", &adminchoice);
					if(adminchoice == 0){
						break;
					}
				
				if(adminchoice == 3) {
					
				printf("\n\t\t***User Guildline***\t\n");
				
				printf("\t\t============================\n");
				
				printf("\tEnter the number inside the box to play that section ([1] Add student) !\n");
				
				printf("\tAt the end of every section you have two decision(enter b to go back, enter 0 for exit) !\n");
				
				printf("\t\t============================\n");
				
				
			}
			
			if(adminchoice==4){
				printf("\n\t\t\t\t\t***About Us***\t\n");
				
				printf("\t\t==========================================================\n\n");
				
				printf("\t\tDeveloper : Ton Pham Quang Huy \n\n");
				
				printf("\tA Student Management System (SMS) is a software application designed to streamline and manage various \n\tadministrative, academic, and operational tasks related to students in educational institutions. It simplifies \n\tprocesses for administrators, teachers, students, and parents by centralizing information and providing tools \n\tfor efficient management.!\n");
				
				printf("\n\t\t==========================================================\n");
				
				
			}
			if(adminchoice == 2){
			
					while(1){
			
					int teacherchoice;
			
					printf("\n***Teacher Management System Using C***\n");
			
					printf("\t    Teacher MENU\n");
			
					printf("\t========================\n");
			
					printf("\t[1] Add a new teacher.\n");
						
					printf("\t[2] Show all teachers\n");
						
					printf("\t[3] Search a teacher.\n");
						
					printf("\t[4] Edit a teacher.\n");
						
					printf("\t[5] Delete a teacher.\n");
					
					printf("\t[6] Classrooms Management.\n");
					
					printf("\t[7] Add teacher to class.\n");
						
					printf("\t[0] Exit the program.\n");
						
					printf("\t========================\n");
						
					printf("\tENTER YOUR CHOICE : ");
						
					scanf("%d", &teacherchoice);
							
						if(teacherchoice==0){
					
								break;
					
							}
								if(teacherchoice == 1){
								
									AddTeacher();	
									
								}
					
									if(teacherchoice == 2){
										
										PrintTeacher();
										
									}
						
										if(teacherchoice == 3){
											
											FindTeacher();
										
										}
							
											if(teacherchoice == 4){
											
												EditTeacher();
												
											}
								
												if(teacherchoice == 5){
													
													DeleteTeacher();
													
												}
												
													if(teacherchoice==6){
															while(1){
			
			int classchoice;
			
			printf("\n***Class Management System Using C***\n");
			
			printf("\t    Class MENU\n");
			
			printf("\t========================\n");
			
			printf("\t[1] Add a new class.\n");
			
			printf("\t[2] Show all classes\n");
			
			printf("\t[3] Search a class.\n");
			
			printf("\t[4] Edit a class.\n");
			
			printf("\t[5] Delete a class.\n");
			
			printf("\t[0] Exit the program.\n");
			
			printf("\t========================\n");
			
			printf("\tENTER YOUR CHOICE : ");
			
			scanf("%d", &classchoice);
			
			if(classchoice==0){
				
				break;
				
			}
				if(classchoice==1){
					
					AddClass();
					
				}
					if(classchoice==2){
						
						PrintClass();
						
					}
							if(classchoice == 3){
								
								FindClass();
								
							}
								if(classchoice==4){
									
									EditClass();
										
								}
									if(classchoice==5){
										
										DeleteClass();
										
									}
		}	
	}
										if(teacherchoice==7){
											
											AddClassToTeacher();
											
										}	
						}
					}
					if(adminchoice == 1) {
						
						while(1){

						int studentchoice;
			
						printf("\n***Student Management System Using C***\n");
			
						printf("\t    STUDENT MENU\n");
			
						printf("\t========================\n");
						
						printf("\t[1] Add a new student.\n");
						
						printf("\t[2] Show all students\n");
						
						printf("\t[3] Search a student.\n");
						
						printf("\t[4] Edit a student.\n");
						
						printf("\t[5] Delete a student.\n");
						
						printf("\t[6] Arrange student.\n");
						
						printf("\t[7] Add class to student.\n");
						
						printf("\t[0] Exit the program.\n");
						
						printf("\t========================\n");
						
						printf("\tENTER YOUR CHOICE : ");
						
						scanf("%d", &studentchoice);
			
						if(studentchoice==0){
					
							break;
					
						}
						if(studentchoice == 1){
						
							AddStudent();	
						
						}
					
						if(studentchoice == 2){
						
							PrintStudent();
						
						}
						
						if(studentchoice == 3){
						
							FindStudent();
						
						}
							
						if(studentchoice == 4){
							
							EditStudent();
			
						}
								
						if(studentchoice == 5){	
						
							DeleteStudent();
											
						}
									
						if(studentchoice == 6){
							int studentchoice2;
							printf("\t***Student Management***\t\n");
							printf("[1] Increase.\n");
							printf("[2] Decrease.\n");
							printf("[0] Exit the program.\n");
							printf("----------------------\n");
							printf("Your Choice : ");
							scanf("%d", &studentchoice2);
											
							if(studentchoice2==0){
												
								continue;				
												
											}
												if(studentchoice2==1){
													
													ArrangeStudentIncrease();	
													
												}
													if(studentchoice2==2){
														
														ArrangeStudentDecrease();
														
													}
											
										}
										
										if(studentchoice==7){
											
											AddClassToStudent();
											
										}
										
				}
			}
		}	
	}
	
	}while(choice != 0);
	
	return 0;
	
}