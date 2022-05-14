#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
	char name[50];
	char usn[10];
	char dept[20];
	int sem;
	char phno[20];
}stu;

struct node {
	struct student stu;
	struct node *link;
};
typedef struct node nd;


void add_student();
void search_student();
void display();
void delete_student();
void mod_student();

nd *head,*curr;
FILE *fp,*temp;


void main()  
{
	int choice;
	system("clear");
	for(;;)
	{
		printf("The Task that you want to perform\n");
		printf("1. Add the Student Details\n");
		printf("2. Find the Student Details\n");
	        printf("3. Display all the students\n");
	        printf("4. Delete the Student Details\n");
	        printf("5. Update the Student Details\n");
	        printf("6. Exit\n");
	        printf("Enter your choice to perform the task\n");
	        scanf("%d", &choice);
	        switch (choice) {
		        case 1:
		            add_student();
		            break;
		        case 2:
		            search_student();
		            break;
		        case 3:
		            display();
		            break;
		        case 4:
		            delete_student();
		            break;
		        case 5:
		            mod_student();
		            break;
		        case 6:
		            exit(0);
		            break;
		        default:
		            printf("INVALID INPUT!!! Try again......\n");
	        }
	    }
}

void add_student()
{
	fp=fopen("database.txt","ab+");
	nd *t;	
	t=(nd*)malloc(sizeof(nd));
	printf("Add the Students Details\n");
	printf("-------------------------\n");
	printf("USN : ");
	scanf("%s",t->stu.usn);
	while(fread(&stu, sizeof(stu), 1, fp) == 1)
	{
		if(strcmp(t->stu.usn,stu.usn) == 0)
		{
			printf("\nRecord already exists\n");
			return;
		}
	}
	printf("Name : ");
	scanf("%s",t->stu.name);
	printf("Dept. : ");
	scanf("%s",t->stu.dept);
	printf("SEM : ");
	scanf("%d",&(t->stu.sem));
	printf("phno : ");
	scanf("%s",t->stu.phno);
	t->link=NULL;
	if(head==NULL){
		head=t;
		curr=t;
	}
    	else{
        	curr->link=t;
        	curr=t;
    	}
	fwrite(&curr->stu,sizeof(curr->stu),1,fp);
	fclose(fp);
    
}

void search_student(){
	char s_usn[20];
	int isFound = 0;
	printf("Enter USN to Search: ");
	scanf("%s",s_usn);
	fp = fopen("database.txt","rb");
	while(fread(&stu, sizeof(stu), 1, fp) == 1)
	{  
		if(strcmp(s_usn,stu.usn) == 0){
			isFound = 1;
			break;
		}
	}
	if(isFound == 1){
		printf("The record is Found\n");	
		printf("USN: %s\n",stu.usn);
        	printf("Name: %s\n",stu.name);
        	printf("Dept: %s\n",stu.dept);
        	printf("Sem: %d\n",stu.sem);
        	printf("Phone No: %s\n",stu.phno);
    	}
	else
	{
	        printf("Sorry, No record found in the database\n");
    	}
	fclose(fp);
	return;
}

void delete_student()
{
	char s_usn[20];
	int isFound = 0,flag=0;
    	printf("Enter USN to delete: ");
    	scanf("%s",s_usn);
    	fp = fopen("database.txt","rb");
    	temp = fopen("temp.txt", "wb");
    	while(fread(&stu, sizeof(stu), 1, fp) == 1)
    	{
		if(strcmp(s_usn,stu.usn) == 0)
        	{
        	    flag=1;
            	    printf("\nRecord Deleted for");
		    printf("\t%s\t%s\t%d\t%s\n",stu.name,stu.dept,stu.sem,stu.phno);
            	    continue;
		}
        	fwrite(&stu, sizeof(stu), 1, temp);
    	}
	fclose(fp);
	fclose(temp);
	remove("database.txt");
	rename("temp.txt","database.txt");
	if(flag==0)
		printf("No record found\n");
    	return;
}

void mod_student(){
	char s_usn[20];
	int isFound = 0;
	printf("Enter USN to Modify: ");
	scanf("%s",s_usn);
	fp = fopen("database.txt","rb+");
	while(fread(&stu, sizeof(stu),1,fp) == 1)
    	{
        	if(strcmp(s_usn, stu.usn) == 0)
		{
		    printf("USN: ");scanf("%s",stu.usn);
        	    printf("Name: ");scanf("%s",stu.name);
        	    printf("dept: ");scanf("%s",stu.dept);
        	    printf("Sem: ");scanf("%d",&(stu.sem));
        	    printf("Phone Number: ");scanf("%s",stu.phno);
        	    fseek(fp,-sizeof(stu), SEEK_CUR);
        	    fwrite(&stu,sizeof(stu), 1, fp);
        	    isFound = 1;
        	    break;
        	}
    	}
    	if(!isFound){
        	printf("No Record Found");
    	}
    	else
        	printf("Record modified\n");
    	fclose(fp);
   	return;
}

void display()
{
	printf("USN\tNAME\tDEPARTMENT\tSEM\tPHONE NO\n");
	printf("--------------------------------------------------------------------\n");
	fp = fopen("database.txt","rb");
	while((fread(&stu,sizeof(stu),1,fp))==1)
	{
		printf("%s\t%s\t%s\t\t%d\t%s\n",stu.usn,stu.name,stu.dept,stu.sem,stu.phno);
	}
	fclose(fp);
	return;
}


