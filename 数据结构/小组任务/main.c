#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 2000
#include<time.h>
typedef struct ND
{
	double stunum;char stuname[100];
	int serialnum;int attendance[50];
	int total;int score;int works[50];int homeworks[50];
	struct ND *next;
}node;
int klass=0,tests=0,homeworks=0;
int midterm,finalterm;
void calculate(node *head,int number)
{
    unsigned int seed;
    int n,i;
    float sum;
    node *p=head;
    srand(seed);
    for(i=0;i<number;i++)
            p=p->next;
    for(i=0;i<10;i++)
    {
        n=rand()%klass;
        sum+=p->attendance[n-1];
    }
    for(i=0;i<4;i++)
    {
        n=rand()%homeworks;
        sum+=p->homeworks[n-1]*5;
    }
    p->score=sum;
    printf("Student number %d :%.0f",number,sum);
    printf("What are the test numbers of midterm&final tests?\n");
    scanf("%d %d",&midterm,&finalterm);
    sum+=(p->works[midterm]*3+p->works[finalterm]*5+sum*3)/10;
    printf("Final score:%.0f",sum);

}
node *createlinkedlist(int n)
{
	node *p,*head,*prep;int i;
	p=(node*)malloc(sizeof(node));
	head=p;
	printf("Enter the name,studentnumber,serialnumber of the target person.\n");
	{
		getchar();
	  gets(p->stuname);
	scanf("%d %lf",&p->serialnum,&p->stunum);}
	prep=p;
	for(i=1;i<n;i++)
	{
		p=(node*)malloc(sizeof(node));
		prep->next=p;
		printf("Enter the name,studentnumber,serialnumber of the target person.\n");getchar();
		gets(p->stuname);
	    scanf("%d %lf",&p->serialnum,&p->stunum);
	    prep=p;
	}
	p->next=NULL;
	return head;
}
int createfile(node *head,int n,int klass,int tests,int homeworks)
{
	FILE *stream;node *p=head;
	int i=0,j;
	if((stream=fopen("C:\\Users\\ASUS\\Desktop\\student.txt","w+"))==NULL) {printf("Invalid file.\n");exit(0);}
	fprintf(stream,"%d ",klass);
	fprintf(stream,"%d ",tests);
	fprintf(stream,"%d  ",homeworks);
	while(p!=NULL||i<n)
	{
		fprintf(stream,"%d %.0f %s ",p->serialnum,p->stunum,p->stuname);
		for(j=0;j<klass;j++)
	{
	fprintf(stream,"%d ",p->attendance[j]);
	}
	for(j=0;j<tests;j++)
	{
		fprintf(stream,"%d ",p->works[j]);
	}
	for(j=0;j<homeworks;j++)
	{
		fprintf(stream,"%d ",p->homeworks[j]);
	}
		p=p->next;
		i++;
	}
	fclose(stream);
	printf("File creation complete.\n");
	return 0;
}
node *extractfile(int m)
{
	FILE *stream;node *p,*prep;int i=0,j;
	node *head;
	if((stream=fopen("C:\\Users\\ASUS\\Desktop\\student.txt","r"))==NULL) {printf("Invalid file.\n");exit(0);}
	p=(node*)malloc(sizeof(node));head=p;
	fscanf(stream,"%d",&klass);
	fscanf(stream,"%d",&tests);
	fscanf(stream,"%d",&homeworks);
		fscanf(stream,"%d",&p->serialnum);
		fscanf(stream,"%lf",&p->stunum);
		fscanf(stream,"%s",p->stuname);
		while(i<klass)
		{
			fscanf(stream,"%d",&p->attendance[i]);
			i++;
		}
		i=0;
		while(i<tests)
		{
			fscanf(stream,"%d",&p->works[i]);
			i++;
		}
		i=0;
		while(i<homeworks)
		{
			fscanf(stream,"%d",&p->homeworks[i]);
			i++;
		}
		i=0;
		prep=p;
	for(j=1;j<m;j++)
	{
		p=(node*)malloc(sizeof(node));
		prep->next=p;
		fscanf(stream,"%d",&p->serialnum);
		fscanf(stream,"%lf",&p->stunum);
		fscanf(stream,"%s",p->stuname);
		while(i<klass)
		{
			fscanf(stream,"%d",&p->attendance[i]);
			i++;
		}
		i=0;
		while(i<tests)
		{
			fscanf(stream,"%d",&p->works[i]);
			i++;
		}
		i=0;
		while(i<homeworks)
		{
			fscanf(stream,"%d",&p->homeworks[i]);
			i++;
		}
		i=0;
		prep=p;
	}
	p->next=NULL;
	return head;

}
int addingattendancestats(int n,int klass,node *head)
{
	node *p;
	p=head;
	while(p!=NULL)
	{
		printf("Is student %d here in class?",p->serialnum);
		scanf("%d",&p->attendance[klass-1]);
		p=p->next;
	}
}
int addingtestsstats(int n,node *head,int tests)
{
   node *p;
	p=head;
	while(p!=NULL)
	{
		printf("The test grade of student %d was:",p->serialnum);
		scanf("%d",&p->works[tests-1]);
		p=p->next;
	}
}

int addinghomeworkstats(int n,node *head,int homeworks)
{
	node *p;
	p=head;
	while(p!=NULL)
	{
		printf("Have student %d finished his/her homework?(0 for not finished,1 for finished)",p->serialnum);
		scanf("%d",&p->homeworks[homeworks-1]);
		p=p->next;
	}
}

node *insertstudent(node *head)
{
	node *p;int i;
	node *p1=head;
	p=(node*)malloc(sizeof(node));
	printf("Please input information of the newin.\n");
		scanf("%d %lf %s",&p->serialnum,&p->stunum,p->stuname);
		memset(p->attendance,0,sizeof(p->attendance));
		memset(p->works,0,sizeof(p->works));
		memset(p->homeworks,0,sizeof(p->homeworks));
		while(p1->next!=NULL)
		{
			p1=p1->next;
		}
		p1->next=p;p->next=NULL;
	return head;
}

node *deletestudent(int n,node *head)
{
    node *p;int i;
	node *p1=head;
	node *prep;
	for(i=1;i<n;i++)
	{
		p1=p1->next;
		if(i==(n-2)) prep=p1;
	}
	prep->next=p1->next;
	free(p1);
	return head;
}

int main()
{
	node *head,*p;
	int n,option=1,i;
	printf("Total amount of students.\n");
	scanf("%d",&n);
	while(option!=0)
	{
	printf("1.Input students` list.\n2.Print all informations.\n3.Sign for attendance stat data.\n4.Search for one certain student.\n5.Sign for homework stat data.\n6.Calculate scores.\n7.Student joining class.\n8.Students expelling from class.\n9.Sign for testgrades.\n");
	getchar();scanf("%d",&option);
	if(option==1)
	{
	head=createlinkedlist(n);
	createfile(head,n,0,0,0);
	}
	else if(option==3)
	{
	head=extractfile(n);
	klass++;
	addingattendancestats(n,klass,head);
	createfile(head,n,klass,tests,homeworks);
    }
    else if(option==9)
    {
    	head=extractfile(n);
    	tests++;
    	addingtestsstats(n,head,tests);
    	createfile(head,n,klass,tests,homeworks);
	}
	else if(option==5)
	{
		head=extractfile(n);
		homeworks++;
		addinghomeworkstats(n,head,homeworks);
		createfile(head,n,klass,tests,homeworks);
	}
	else if(option==12)
    {
        head=extractfile(n);
        printf("%d %d %d\n",klass,tests,homeworks);
    }
	else if(option==2)
    {
        int j;
        head=extractfile(n);
        while(head!=NULL)
        {
            printf("%d %.0f %-9s",head->serialnum,head->stunum,head->stuname);
            printf(" Class attendances:");
		for(j=0;j<klass;j++)
	{
	printf("%d ",head->attendance[j]);
	}
	printf("Test stats:");
	for(j=0;j<tests;j++)
	{
		printf("%d ",head->works[j]);
	}
	printf("Homework stats:");
	for(j=0;j<homeworks;j++)
	{
		printf("%d ",head->homeworks[j]);
	}
		head=head->next;
		printf("\n");
	}
    }
    else if(option==7)
    {
        int number;
        printf("How many students joining in?");
        scanf("%d",&number);
        head=extractfile(n);
        while(number>0)
        {head=insertstudent(head);n++;number--;}
        createfile(head,n,klass,tests,homeworks);
    }
    else if(option==8)
    {
        int m;int number;
        head=extractfile(n);
        printf("How many students being expelled?\n");
        scanf("%d",&number);
        while(number>0)
        {
            printf("Please enter the serial number of the student being expelled.\n");
            scanf("%d",&m);
            head=deletestudent(m,head);
            n--;
            number--;
    }
    createfile(head,n,klass,tests,homeworks);
    }
    else if(option==6)
    {
        int number,k,i,b;
        head=extractfile(n);
        printf("Do you want to calculate for all?(1 for yes,0 for No)");
        scanf("%d",&k);
        if(k==1)
        {
            for(i=0;i<n;i++)
            {
                calculate(head,i);
            }
        }
        else
        {
            printf("Please tell us how many students you are going to calculate for.");
            scanf("%d",&number);
            for(i=0;i<number;i++)
            {
                printf("The student you want to calculate for:");
                scanf("%d",&b);
                calculate(head,b);
            }
        }

    }
    else if(option==4)
    {
        int number,i;
        head=extractfile(n);
        printf("Please enter the student you want to search:");
        scanf("%d",&number);
        for(i=0;i<number;i++)
            head=head->next;
        if(head==NULL) printf("Not found!\n");
        else
        {
            printf("%d %.0f %s ",head->serialnum,head->stunum,head->stuname);
            for(i=0;i<klass;i++)
            {
                printf("%d ",head->attendance[i]);
            }
            for(i=0;i<tests;i++)
            {

                printf("%d ",head->works[i]);
            }
            for(i=0;i<homeworks;i++)
            {
                printf("%d ",head->homeworks[i]);
            }

        }
    }
	}

	return 0;
}
