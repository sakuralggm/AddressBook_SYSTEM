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
    printf("欢迎使用通讯录管理系统，该系统有以下功能：\n");
    printf("1 添加联系人\n");
    printf("2 删除联系人(支持姓名搜索，可先使用查询功能了解要删除的联系人姓名)\n");
    printf("3 修改联系人信息(支持姓名搜索，可先使用查询功能了解要修改的联系人姓名)\n");
    printf("4 查询联系人(支持姓名、电话、邮箱、地址搜索)\n");
    printf("5 按名字排序\n");
    printf("0 保存修改并退出");
    printf("\n----------------------------------------------------------------------\n");
    printf("请输入功能对应的数字：");
}

void printlist(PERSON *list, int isarrray)
{
    printf("\n%-10s%20s%20s%15s\n\n","姓名","电话","邮箱","地址");
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
    if(fp==NULL) printf("\n加载数据库错误\n");

    int res=-1;
    while(!feof(fp))
    {
        res=fscanf(fp,"%s %s %s %s",list[N].name, list[N].phone, list[N].email, list[N].address);
        if(res<4) break;
        else
        {
            if(N>=MAX) printf("\n通讯录已满\n");
            else N++;
        }
    }
    fclose(fp);

    printf("\n已加载完成，打印通讯录信息如下：\n\n");
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
    printf("\n欢迎使用添加联系人功能，直接回车退出\n\n");
    char input[100]={'\0'};
    PERSON toadd={0};
    int flag=0, idx=-1,res=-1;

    while(1)
    {
        printf("（输入格式：姓名 电话 邮箱 地址）（一次输入一个，每项之间用空格隔开！！！）\n");
        printf("请输入：");
        fflush(stdin);
        memset(input,0,sizeof(input));
        memset(&toadd,0,sizeof(PERSON));
        flag=0, idx=-1, res=-1;

        gets(input);
        if(strcmp(input,"")==0)
        {
            printf("\n已退出添加联系人功能\n");
            break;
        }
        else if(N>=MAX)
        {
            printf("\n通讯录已满\n");
            return;
        }
        res=sscanf(input,"%s %s %s %s",toadd.name, toadd.phone, toadd.email, toadd.address);
        if(res<4) printf("\n输入错误，请重新输入：");
        else
        {
            idx=unique(list,toadd);
            if(idx==-1) list[N++]=toadd;
            else
            {
                if(list[idx].isdelete==0)
                {
                    int cover=0;
                    printf("\n有同名联系人，是否覆盖？（覆盖输入1，放弃添加输入0）\n");
                    printf("请输入：");
                    scanf("%d",&cover);
                    fflush(stdin);
                    if(cover) list[idx]=toadd, printf("\n添加成功\n\n");
                    else printf("\n已放弃添加联系人，可回车退出选择修改联系人信息功能\n");
                }
                else list[idx]=toadd, printf("\n添加成功\n\n");
            }

        }
    }

}

void sub()
{
    printf("\n欢迎使用删除联系人功能，直接回车退出\n\n");
    char input[100]={'\0'};
    PERSON tosub={0};
    int flag=0, idx=-1,res=-1;

    while(1)
    {
        printf("\n输入格式：姓名（一次输入一个！！！）\n");
        printf("请输入：");
        fflush(stdin);
        memset(input,0,sizeof(input));
        memset(&tosub,0,sizeof(PERSON));
        flag=0, idx=-1, res=-1;

        gets(input);
        if(strcmp(input,"")==0)
        {
            printf("\n已退出删除联系人功能\n");
            break;
        }
        res=sscanf(input,"%s",tosub.name);
        if(res!=1) printf("\n输入错误，请重新输入：");
        else
        {
            idx=unique(list,tosub);
            if(idx==-1||list[idx].isdelete==1) printf("\n查无此人\n");
            else list[idx].isdelete=1;
        }
        printf("\n删除成功\n\n");
    }
}

void modify()
{
    printf("\n欢迎使用修改联系人信息功能，直接回车退出\n\n");
    char input[100]={'\0'};
    PERSON tomodify={0};
    int flag=0, idx=-1,res=-1;

    while(1)
    {
        printf("（输入格式：姓名 电话 邮箱 地址）（一次输入一个，每项之间用空格隔开，不需要修改的信息用*代替）\n");
        printf("请输入：");
        fflush(stdin);
        memset(input,0,sizeof(input));
        memset(&tomodify,0,sizeof(PERSON));
        flag=0, idx=-1, res=-1;

        gets(input);
        if(strcmp(input,"")==0)
        {
            printf("\n已退出修改联系人信息功能\n");
            break;
        }
        res=sscanf(input,"%s %s %s %s",tomodify.name, tomodify.phone, tomodify.email, tomodify.address);
        if(res!=4) printf("\n输入错误，请重新输入：");
        else
        {
            idx=unique(list,tomodify);
            if(idx==-1||list[idx].isdelete==1) printf("\n查无此人\n");
            else
            {
                if(strcmp(tomodify.phone, "*")!=0) strcpy(list[idx].phone, tomodify.phone);
                if(strcmp(tomodify.email, "*")!=0) strcpy(list[idx].email, tomodify.email);
                if(strcmp(tomodify.address, "*")!=0) strcpy(list[idx].address, tomodify.address);
            }
             printf("\n修改成功\n\n");
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
    printf("欢迎使用查询功能，输入0并回车退出\n");
    printf("可根据以下项目查询：\n");
    printf("1 姓名\n");
    printf("2 电话\n");
    printf("3 邮箱\n");
    printf("4 地址\n");
    printf("0 退出查询功能\n");
    printf("****************************\n\n");
    printf("请输入选项对应的数字：");
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
            printf("\n已退出查询功能\n");
            break;
        }
        printf("\n请输入查询信息：");
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
            if(idx==-1) printf("\n查无此人\n");
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
            if(idx==-1) printf("\n查无此人\n");
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
            if(idx==-1) printf("\n查无此人\n");
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
                    if(firstone==0) printf("\n%-10s%20s%20s%15s\n\n","姓名","电话","邮箱","地址"), firstone=1;
                    printf("%-10s%20s%20s%15s\n\n",list[i].name, list[i].phone, list[i].email, list[i].address), idx=i;
                }
            }
            if(idx==-1) printf("\n查无此人\n");
        }
    }
}

void save()
{
    FILE *fp;
    fp=fopen("data.txt","w");
    if(fp==NULL) printf("\n保存通讯录失败\n");

    for(int i=0; i<N; i++)
    {
        if(list[i].isdelete==1) continue;
        fprintf(fp,"%s %s %s %s\n", list[i].name, list[i].phone, list[i].email, list[i].address);
    }
    printf("\n保存成功\n");
    fclose(fp);
}

int main()
{
    printf("通讯录系统载入中…………\n");
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
            case 5: sort(0,N-1); printf("\n已按姓名排序，结果如下：\n\n"); printlist(list,1); break;
            case 0: save(); printf("\n已安全退出\n"); return 0;
            default: printf("\n输入错误，请重新输入!\n");
        }
        system("cls");
    }
    return 0;
}
