                            //  Created by Mukul on 23/07/19.
                    //  Copyright © 2019 Mukul. All rights reserved.
                            //student database management system
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//function prototype declaration
int addstdnt(void);//for add student records
void prntstd(void);//for print student records
int modify(void);//for modifystudent records
void delstd(void);//for delete student records
int search(char[]);// for search student records
void filesort(void);// for sorting file
void prntstd1(void);//for print 1 record
void prntstd2(void);//for print all record
void sortname(void);// for sort record(by name)
void sortcgpa(void);//for sort record(by cgpa)
void delstud(void);//for delete record
//structure declaration
struct student
{char name[20];
    char rollno[20];
    float cgpa;
};
//main funct
int main()
{int i,j,n=0;
    for (j=0; n==0; j++) {
        printf("\t\t\t***welcome to ansal university***\n");
        printf("1.add student detail\n");
        printf("2.print student detail\n");
        printf("3.modify student detail\n");
        printf("4.delete student detail\n");
        printf("5.quit\n");
        scanf("%d",&i);
        switch (i) {
            case 1:
                addstdnt();
                break;
            case 2:
                prntstd();
                break;
            case 3:
                modify();
                break;
            case 4:
                delstud();
                break;
            case 5:
                n=1;
                break;
            default:
                printf("invalid choice!!!");
                break;
        }
    }
    return 0;
}
//add record funct
int addstdnt()
{
    struct student s[50];
    int i,n,flag;
    FILE *fp;
    fp = fopen("student.txt","a");
    if (fp==NULL) {
        printf("unable to create a file!!!");
        return 1;
    }
    printf("\nEnter no. of Students : ");
    scanf("%d",&n);
    printf("\nEnter the rollno,name,cgpa\n");
    for(i=0;i<n;i++){
        printf("roll no:");
        scanf("%s",s[i].rollno);
        printf("first name:");
        scanf("%s",s[i].name);
        printf("enter cgpa:");
        scanf("%f",&s[i].cgpa);
        flag=search(s[i].rollno);
        if (flag==1) {
            printf("!!!roll no already exist!!!");
            return -1;
        }
        fprintf(fp,"%s %s %f\n",s[i].rollno,s[i].name,s[i].cgpa);
    }
    fclose(fp);
    filesort();
    printf("\n\t\t\t***recods added successfully***\n");
    return 0;
}
//search record funct
int search(char rollno[])
{
    struct student s[50];
    int i=0;
    FILE *fp;
    fp=fopen("std.txt", "r");
    if (fp==NULL) {
        return -1;
    }
    while (!feof(fp)) {
        fscanf(fp,"%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
        if(strcmp(rollno,s[i].rollno)==0)
            return 1;
        else
            i=i+1;
    }
    fclose(fp);
    return 0;
}
//file sort function(by rollno)
void filesort()
{
    struct student s[50],temp[50],t;
    FILE *fp,*fm;
    int i=0,n,j;
    fp=fopen("student.txt", "r");
    fm=fopen("std.txt","w");
    while (!feof(fp)) {
        fscanf(fp,"%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
        temp[i]=s[i];
        i=i+1;
    }
    n=i;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(strcmp(temp[i].rollno,temp[j].rollno)>0)
            {
                t=temp[i];
                temp[i]=temp[j];
                temp[j]=t;
            }
        }
    }
    for (i=0; i<n; i++) {
        fprintf(fm, "%s %s %f\n",temp[i].rollno,temp[i].name,temp[i].cgpa);
    }
    fclose(fm);
    fclose(fp);
}
//print function
void prntstd()
{
    int i,n=0;
    for (i=0; n==0; i++) {
        printf("1.search student record\n");
        printf("2.print all records\n");
        printf("3.back to menu\n");
        scanf("%d",&i);
        switch (i) {
            case 1:
                prntstd1();
                break;
            case 2:
                prntstd2();
                break;
            case 3:
                n=1;
                break;
            default:
                printf("\t\t\t!!!invalid choice!!!\n");
                break;
        }
    }
    
}
//print all record funct
void prntstd2()
{
    struct student s[50];
    FILE *fm;
    int i=0,n;
    fm=fopen("std.txt", "r");
    if (fm==NULL) {
        printf("\t\t\t!!!roll no not found!!!\n");
    }
    while (!feof(fm)) {
        fscanf(fm,"%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
        printf("%s %s %f\n",s[i].rollno,s[i].name,s[i].cgpa);
        i=i+1;
    }
    printf("sort by:\n");
    printf("1.name\n");
    printf("2.cgpa\n");
    printf("3.previous menu\n");
    scanf("%d",&n);
    switch (n) {
        case 1:
            sortname();
            break;
        case 2:
            sortcgpa();
            break;
        default:
            break;
    }
}
//print 1 record funct
void prntstd1()
{
    struct student s[50];
    char rollno[20];
    int i=0,n=0;
    FILE *fp;
    fp=fopen("std.txt","r");
    printf("enter rollno:");
    scanf("%s",rollno);
    if (fp==NULL) {
        printf("\t\t\t!!!roll no not found!!!\n");
    }
    while (!feof(fp)) {
        fscanf(fp,"%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
        if(strcmp(rollno,s[i].rollno)==0){
            printf("%s %s %f\n",s[i].rollno,s[i].name,s[i].cgpa);
            n=0;
        }
        else{
            n=1;
            i=i+1;
         }
    }
    if (n==1) {
        printf("\t\t\t!!!roll no not found!!!\n");
    }
    fclose(fp);
}
//sort by name funct
void sortname()
{
    struct student s[50],temp[50],t;
    FILE *fp;
    int i=0,n,j;
    fp=fopen("std.txt", "r");
    while (!feof(fp)) {
        fscanf(fp,"%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
        temp[i]=s[i];
        i=i+1;
    }
    n=i;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(strcmp(temp[i].name,temp[j].name)>0)
            {
                t=temp[i];
                temp[i]=temp[j];
                temp[j]=t;
            }
        }
    }
    for (i=0; i<n; i++) {
        printf("%s %s %f\n",temp[i].rollno,temp[i].name,temp[i].cgpa);
    }
    fclose(fp);
}
//sort by cgpa funct
void sortcgpa()
{
    struct student s[50],temp[50],t;
    FILE *fp;
    int i=0,n,j;
    fp=fopen("std.txt", "r");
    while (!feof(fp)) {
        fscanf(fp,"%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
        temp[i]=s[i];
        i=i+1;
    }
    n=i;
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(temp[i].cgpa<temp[j].cgpa)
            {
                t=temp[i];
                temp[i]=temp[j];
                temp[j]=t;
            }
        }
    }
    for (i=0; i<n; i++) {
        printf("%s %s %f\n",temp[i].rollno,temp[i].name,temp[i].cgpa);
    }
    fclose(fp);
}
int modify()
{
    struct student s[50],t;
    char rollno[20];
    int i=0,n;
    FILE *fp,*fs;
    fp=fopen("student.txt","r");
    fs=fopen("std2.txt", "w");
    printf("enter rollno to modify student record:");
    scanf("%s",rollno);
    n=search(rollno);
    if (n!=1) {
        printf("\t\t\t!!!rollno not found!!!\n");
    }
    else{
        while (!feof(fp)) {
            fscanf(fp,"%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
            if(strcmp(rollno,s[i].rollno)==0){
                printf("%s %s %f\n",s[i].rollno,s[i].name,s[i].cgpa);
            }
            else
            fprintf(fs, "%s %s %f\n",s[i].rollno,s[i].name,s[i].cgpa);
            i=i+1;
        }
        printf("update record:\n");
        printf("rollno\tname\tcgpa\n");
        scanf("%s %s %f",t.rollno,t.name,&t.cgpa);
        fprintf(fs, "%s %s %f\n",t.rollno,t.name,t.cgpa);
        printf("\t\t\t***record updated***");
    }
    fclose(fs);
    fclose(fp);
    fs=fopen("std2.txt", "r");
    fp=fopen("student.txt", "w");
    while (!feof(fs)) {
        fscanf(fs, "%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
        fprintf(fp, "%s %s %f\n",s[i].rollno,s[i].name,s[i].cgpa);
        i=i+1;
    }
    fclose(fs);
    fclose(fp);
    filesort();
    return 0;
}
//delete record funct
void delstud()
{
    struct student s[50];
    char rollno[20];
    int i=0,n,a;
    FILE *fp,*fs;
    fp=fopen("student.txt","r");
    fs=fopen("std2.txt", "w");
    printf("enter rollno to delete record:");
    scanf("%s",rollno);
    n=search(rollno);
    if (n!=1) {
        printf("\t\t\t!!!rollno not found!!!\n");
    }
    else{
        printf("are you sure you want to del that record:\n1.yes\n2.no\n");
        scanf("%d",&a);
        if (a==2) {
            exit(0);
        }else{
        while (!feof(fp)) {
            fscanf(fp,"%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
            if(strcmp(rollno,s[i].rollno)!=0)
                fprintf(fs, "%s %s %f\n",s[i].rollno,s[i].name,s[i].cgpa);
                i=i+1;
            }
        }
        printf("\t\t\t***record deleted***");
    }
    fclose(fs);
    fclose(fp);
    fs=fopen("std2.txt", "r");
    fp=fopen("student.txt", "w");
    while (!feof(fs)) {
        fscanf(fs, "%s %s %f\n",s[i].rollno,s[i].name,&s[i].cgpa);
        fprintf(fp, "%s %s %f\n",s[i].rollno,s[i].name,s[i].cgpa);
        i=i+1;
    }
    fclose(fs);
    fclose(fp);
    filesort();
}




