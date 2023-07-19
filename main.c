#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 100

typedef struct person
{
    char name[50];
    char phone[20];
    char email[30];
    char address[50];
    int isdelete;
}PERSON;

int N;
PERSON list[MAX];

void main_menu()
{
    printf("\n\n---------------------------------------------------------------------\n");
    printf("��ӭʹ��ͨѶ¼����ϵͳ����ϵͳ�����¹��ܣ�\n");
    printf("1 �����ϵ��\n");
    printf("2 ɾ����ϵ��(֧����������������ʹ�ò�ѯ�����˽�Ҫɾ������ϵ������)\n");
    printf("3 �޸���ϵ����Ϣ(֧����������������ʹ�ò�ѯ�����˽�Ҫ�޸ĵ���ϵ������)\n");
    printf("4 ��ѯ��ϵ��(֧���������绰�����䡢��ַ����)\n");
    printf("5 ����������\n");
    printf("0 �����޸Ĳ��˳�");
    printf("\n----------------------------------------------------------------------\n");
    printf("�����빦�ܶ�Ӧ�����֣�");
}

void printlist(PERSON *list, int isarrray)
{
    printf("\n%-10s%20s%20s%15s\n\n","����","�绰","����","��ַ");
    if(isarrray)
    {
        for(int i=0; i<N; i++)
            if(list[i].isdelete==0) printf("%-10s%20s%20s%15s\n\n",list[i].name, list[i].phone, list[i].email, list[i].address);
    }
    else printf("%-10s%20s%20s%15s\n\n",list->name, list->phone, list->email, list->address);
}

void load()
{
    FILE *fp;
    fp=fopen("data.txt","r");
    if(fp==NULL) printf("\n�������ݿ����\n");

    int res=-1;
    while(!feof(fp))
    {
        res=fscanf(fp,"%s %s %s %s",list[N].name, list[N].phone, list[N].email, list[N].address);
        if(res<4) break;
        else
        {
            if(N>=MAX) printf("\nͨѶ¼����\n");
            else N++;
        }
    }
    fclose(fp);

    printf("\n�Ѽ�����ɣ���ӡͨѶ¼��Ϣ���£�\n\n");
    printlist(list, 1);
}

int unique(PERSON *list, PERSON toadd)
{
    int idx=-1;
    for(int i=0; i<N; i++)
    {
        if(strcmp(list[i].name, toadd.name)==0)
        {
            idx=i;
            break;
        }
    }
    return idx;
}

void add()
{
    printf("\n��ӭʹ�������ϵ�˹��ܣ�ֱ�ӻس��˳�\n\n");
    char input[100]={'\0'};
    PERSON toadd={0};
    int flag=0, idx=-1,res=-1;

    while(1)
    {
        printf("�������ʽ������ �绰 ���� ��ַ����һ������һ����ÿ��֮���ÿո������������\n");
        printf("�����룺");
        fflush(stdin);
        memset(input,0,sizeof(input));
        memset(&toadd,0,sizeof(PERSON));
        flag=0, idx=-1, res=-1;

        gets(input);
        if(strcmp(input,"")==0)
        {
            printf("\n���˳������ϵ�˹���\n");
            break;
        }
        else if(N>=MAX)
        {
            printf("\nͨѶ¼����\n");
            return;
        }
        res=sscanf(input,"%s %s %s %s",toadd.name, toadd.phone, toadd.email, toadd.address);
        if(res<4) printf("\n����������������룺");
        else
        {
            idx=unique(list,toadd);
            if(idx==-1) list[N++]=toadd;
            else
            {
                if(list[idx].isdelete==0)
                {
                    int cover=0;
                    printf("\n��ͬ����ϵ�ˣ��Ƿ񸲸ǣ�����������1�������������0��\n");
                    printf("�����룺");
                    scanf("%d",&cover);
                    fflush(stdin);
                    if(cover) list[idx]=toadd, printf("\n��ӳɹ�\n\n");
                    else printf("\n�ѷ��������ϵ�ˣ��ɻس��˳�ѡ���޸���ϵ����Ϣ����\n");
                }
                else list[idx]=toadd, printf("\n��ӳɹ�\n\n");
            }

        }
    }

}

void sub()
{
    printf("\n��ӭʹ��ɾ����ϵ�˹��ܣ�ֱ�ӻس��˳�\n\n");
    char input[100]={'\0'};
    PERSON tosub={0};
    int flag=0, idx=-1,res=-1;

    while(1)
    {
        printf("\n�����ʽ��������һ������һ����������\n");
        printf("�����룺");
        fflush(stdin);
        memset(input,0,sizeof(input));
        memset(&tosub,0,sizeof(PERSON));
        flag=0, idx=-1, res=-1;

        gets(input);
        if(strcmp(input,"")==0)
        {
            printf("\n���˳�ɾ����ϵ�˹���\n");
            break;
        }
        res=sscanf(input,"%s",tosub.name);
        if(res!=1) printf("\n����������������룺");
        else
        {
            idx=unique(list,tosub);
            if(idx==-1||list[idx].isdelete==1) printf("\n���޴���\n");
            else list[idx].isdelete=1;
        }
        printf("\nɾ���ɹ�\n\n");
    }
}

void modify()
{
    printf("\n��ӭʹ���޸���ϵ����Ϣ���ܣ�ֱ�ӻس��˳�\n\n");
    char input[100]={'\0'};
    PERSON tomodify={0};
    int flag=0, idx=-1,res=-1;

    while(1)
    {
        printf("�������ʽ������ �绰 ���� ��ַ����һ������һ����ÿ��֮���ÿո����������Ҫ�޸ĵ���Ϣ��*���棩\n");
        printf("�����룺");
        fflush(stdin);
        memset(input,0,sizeof(input));
        memset(&tomodify,0,sizeof(PERSON));
        flag=0, idx=-1, res=-1;

        gets(input);
        if(strcmp(input,"")==0)
        {
            printf("\n���˳��޸���ϵ����Ϣ����\n");
            break;
        }
        res=sscanf(input,"%s %s %s %s",tomodify.name, tomodify.phone, tomodify.email, tomodify.address);
        if(res!=4) printf("\n����������������룺");
        else
        {
            idx=unique(list,tomodify);
            if(idx==-1||list[idx].isdelete==1) printf("\n���޴���\n");
            else
            {
                if(strcmp(tomodify.phone, "*")!=0) strcpy(list[idx].phone, tomodify.phone);
                if(strcmp(tomodify.email, "*")!=0) strcpy(list[idx].email, tomodify.email);
                if(strcmp(tomodify.address, "*")!=0) strcpy(list[idx].address, tomodify.address);
            }
             printf("\n�޸ĳɹ�\n\n");
        }
    }
}

void sort(int l, int r)
{
    if(l>=r) return;
    int i=l-1, j=r+1;
    PERSON flag=list[l+r>>1];
    while(i<j)
    {
        do i++; while(strcmp(list[i].name, flag.name)<0);
        do j--; while(strcmp(list[j].name, flag.name)>0);
        if(i<j)
        {
            PERSON t=list[i];
            list[i]=list[j];
            list[j]=t;
        }
    }
    sort(l,j), sort(j+1,r);
}

void search_menu()
{
    printf("\n****************************\n");
    printf("��ӭʹ�ò�ѯ���ܣ�����0���س��˳�\n");
    printf("�ɸ���������Ŀ��ѯ��\n");
    printf("1 ����\n");
    printf("2 �绰\n");
    printf("3 ����\n");
    printf("4 ��ַ\n");
    printf("0 �˳���ѯ����\n");
    printf("****************************\n\n");
    printf("������ѡ���Ӧ�����֣�");
}

void search()
{
    char tosearch[100]={'\0'};
    int idx=-1, flag=0, res=-1, select=-1;

    while(1)
    {
        fflush(stdin);
        memset(tosearch,0,sizeof(tosearch));
        idx=-1, select=0;

        search_menu();
        scanf("%d",&select);
        fflush(stdin);
        if(select==0)
        {
            printf("\n���˳���ѯ����\n");
            break;
        }
        printf("\n�������ѯ��Ϣ��");
        gets(tosearch);

        if(select==1)
        {
            for(int i=0; i<N; i++)
            {
                if(list[i].isdelete) continue;
                if(strcmp(list[i].name, tosearch)==0)
                {
                    idx=i;
                    break;
                }
            }
            if(idx==-1) printf("\n���޴���\n");
            else printlist(&list[idx],0);
        }
        else if(select==2)
        {
            for(int i=0; i<N; i++)
            {
                if(list[i].isdelete) continue;
                if(strcmp(list[i].phone, tosearch)==0)
                {
                    idx=i;
                    break;
                }
            }
            if(idx==-1) printf("\n���޴���\n");
            else printlist(&list[idx],0);
        }
        else if(select==3)
        {
            for(int i=0; i<N; i++)
            {
                if(list[i].isdelete) continue;
                if(strcmp(list[i].email, tosearch)==0)
                {
                    idx=i;
                    break;
                }
            }
            if(idx==-1) printf("\n���޴���\n");
            else printlist(&list[idx],0);
        }
        else if(select==4)
        {
            int firstone=0;
            for(int i=0; i<N; i++)
            {
                if(list[i].isdelete) continue;
                if(strcmp(list[i].address, tosearch)==0)
                {
                    if(firstone==0) printf("\n%-10s%20s%20s%15s\n\n","����","�绰","����","��ַ"), firstone=1;
                    printf("%-10s%20s%20s%15s\n\n",list[i].name, list[i].phone, list[i].email, list[i].address), idx=i;
                }
            }
            if(idx==-1) printf("\n���޴���\n");
        }
    }
}

void save()
{
    FILE *fp;
    fp=fopen("data.txt","w");
    if(fp==NULL) printf("\n����ͨѶ¼ʧ��\n");

    for(int i=0; i<N; i++)
    {
        if(list[i].isdelete==1) continue;
        fprintf(fp,"%s %s %s %s\n", list[i].name, list[i].phone, list[i].email, list[i].address);
    }
    printf("\n����ɹ�\n");
    fclose(fp);
}

int main()
{
    printf("ͨѶ¼ϵͳ�����С�������\n");
    load();

    int select=0;
    while(1)
    {
        main_menu();
        scanf("%d",&select);
        fflush(stdin);
        switch(select)
        {
            case 1: add(); break;
            case 2: sub(); break;
            case 3: modify(); break;
            case 4: search(); break;
            case 5: sort(0,N-1); printf("\n�Ѱ��������򣬽�����£�\n\n"); printlist(list,1); break;
            case 0: save(); printf("\n�Ѱ�ȫ�˳�\n"); return 0;
            default: printf("\n�����������������!\n");
        }
        system("cls");
    }
    return 0;
}
