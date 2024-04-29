#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct Waitlist
{
    int x;
    int y;
    int lastpointx;
    int lastpointy;
    int cost;
    struct Waitlist *next;
}waitlist;
typedef struct path
{
    int x;
    int y;
    struct path *next;
}path;
waitlist* head=NULL;
waitlist* tmp=NULL;
waitlist* new_node=NULL;
waitlist* tail=NULL;
path *path_head=NULL;
path *path_tmp=NULL;
path *path_new_node=NULL;
path *path_DFShead=NULL;
int m=0,n=0,startx=0,starty=0,currentx,currenty,currentcost=0,setpointx[3],setpointy[3],a=0,totalcost=2147483647,tmpmap[40000],tmpvisited[1000][1000],displaycost=0;
int main()
{
    FILE *in;
    in=fopen("input7.txt","r");
    int b=0;
    while(fscanf(in,"%c",&tmpmap[m])!=EOF)
    {
        if(tmpmap[m]=='\n'&&b==0)
        {
            n=m;
            b=1;
        }
        if(tmpmap[m]!='\n')
        {
            m++;
        }
    }
    printf("%d %d\n",m/n,n);
    //Sleep(1000);
    m=m/n;
    m=m+2;
    n=n+2;
    b=0;
    char map[m][n];
    for(int i=0;i<n;i++)
    {
        map[0][i]='0';
    }
    for(int i=1;i<m-1;i++)
    {
        map[i][0]='0';
        for(int j=1;j<n-1;j++)
        {
            map[i][j]=tmpmap[b];
            /*while((map[i][j]<'0')||(map[i][j]>'3'))
            {
                b++;
                map[i][j]=tmpmap[b];
            }*/
            if(map[i][j]=='2')//record the car-spot
            {
                startx=startx+j;
                starty=starty+i;
                printf("(%d %d)\n",j,i);
            }
            if(map[i][j]=='3')
            {
                setpointx[a]=j;
                setpointy[a]=i;
                a++;
            }
            b++;
        }
        map[i][n-1]='0';
    }
    for(int i=0;i<n;i++)
    {
        map[m-1][i]='0';
    }
    /*for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }*/

    startx=startx/3;
    starty=starty/3;

    currentx=startx;
    currenty=starty;

    if(a==0)//all steps
    {
        printf("%d %d",currentx,currenty);
        path *path_start=NULL;
        path *path_tmp2=NULL;
        path *path_tmp3=NULL;
        path_start=DFS(currentx,currenty,map);
        printf("yes");
        path_tmp=path_start;
        printf(" %d",(path_tmp->next)->x);
        while(((path_tmp->next)->x)!=-2)
        {
            if((abs((path_tmp->x)-(path_tmp->next)->x)+abs((path_tmp->y)-(path_tmp->next)->y))<=2)
            {
                path_tmp=path_tmp->next;
            }
            else
            {
                path_tmp2=shortest_path(path_tmp->x,path_tmp->y,(path_tmp->next)->x,(path_tmp->next)->y,map,1);
                path_tmp3=path_tmp2;
                while((path_tmp3->next)->x!=-1)
                {
                    path_tmp3=path_tmp3->next;
                }
                path_tmp3->next=path_tmp->next;
                path_tmp->next=path_tmp2->next;
                path_tmp=path_tmp3;
            }
        }
        display(map,path_start);
    }
    else//mission spot
    {
        printf("start caculating\n");
        int b=1,c=0,orderlist[6][3]={0,1,2, 1,0,2, 0,2,1, 2,0,1, 2,1,0, 1,2,0},tmpcost=0;
        for(int i=1;i<=a;i++)
        {
            b=b*i;
            if(shortest_path(startx,starty,setpointx[i-1],setpointy[i-1],map,0)==-1)
            {
                printf("cant reach point(%d,%d)\n",setpointx[i-1],setpointy[i-1]);
                setpointx[i-1]=-1;
            }
        }
        //Sleep(10000);
        currentx=startx;
        currenty=starty;
        for(int i=0;i<b;i++)
        {
            tmpcost=0;
            for(int j=0;j<a;j++)
            {
                if(setpointx[orderlist[i][j]]!=-1)
                {
                    shortest_path(currentx,currenty,setpointx[orderlist[i][j]],setpointy[orderlist[i][j]],map,0);
                    tmpcost=tmpcost+currentcost;
                }
            }
            for(int j=0;j<a;j++)
            {
                printf("%d ",orderlist[i][j]);
            }
            printf("%d\n",tmpcost);
            if(tmpcost<totalcost)
            {
                totalcost=tmpcost;
                c=i;
            }
            currentx=startx;
            currenty=starty;
        }
        printf("finished");
        //Sleep(1500);
        int finalpath;
        for(int i=0;i<a;i++)
        {
            if(setpointx[orderlist[c][i]]!=-1)
            {
                finalpath=shortest_path(currentx,currenty,setpointx[orderlist[c][i]],setpointy[orderlist[c][i]],map,0);
                if(finalpath!=-1)
                {
                    //display(map,finalpath);
                }
            }
        }
        int d=0;
        printf("\n");
        for(int i=0;i<a;i++)
        {
            if(setpointx[orderlist[c][i]]!=-1)
            {
                if(d!=0)
                {
                    printf("->");
                }
                printf("(%d,%d)",setpointx[orderlist[c][i]],setpointy[orderlist[c][i]]);
                d=1;
            }
        }
        //printf("\ncost:%d",totalcost);
    }
    return 0;
}
//===================================================================================================
void display(char map[m][n],path* path_tmp)
{
    int lx=path_tmp->x,ly=path_tmp->y;
    while(!(path_tmp->x==-1||path_tmp->x==-2))
    {
        int tmpx=path_tmp->x,tmpy=path_tmp->y;
        //system("CLS");
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(tmpx%2==1)//vertical
                {
                    if(i>=tmpy/2-1 && i<=tmpy/2+1 && j>=tmpx/2 && j<=tmpx/2+1)
                    {
                        printf("@");
                        map[i][j]='-';
                    }
                    else
                    {
                        if(map[i][j]!='0' && map[i][j]!='3' && map[i][j]!='-')
                        {
                            printf(" ");
                        }
                        else
                        {
                            printf("%c",map[i][j]);
                        }
                    }
                }
                else//horizonal
                {
                    if(i>=tmpy/2 && i<=tmpy/2+1 && j>=tmpx/2-1 && j<=tmpx/2+1)
                    {
                        printf("@");
                        map[i][j]='-';
                    }
                    else
                    {
                        if(map[i][j]!='0' && map[i][j]!='3' && map[i][j]!='-')
                        {
                            printf(" ");
                        }
                        else
                        {
                            printf("%c",map[i][j]);
                        }
                    }
                }
            }
            printf("\n");
        }
        if(tmpx%2==1)
        {
            if(abs(tmpx-lx)==2)
            {
                displaycost=displaycost+2;
            }
            if(abs(tmpy-ly)==2)
            {
                displaycost=displaycost+1;
            }
        }
        else
        {
            if(abs(tmpx-lx)==2)
            {
                displaycost=displaycost+1;
            }
            if(abs(tmpy-ly)==2)
            {
                displaycost=displaycost+2;
            }
        }
        if(abs(tmpx-lx)==1&&abs(tmpy-ly)==1)
        {
            displaycost=displaycost+5;
        }
        printf("cost:%d",displaycost);
        lx=tmpx;
        ly=tmpy;
        path_tmp=path_tmp->next;
        Sleep(50);
    }
}
//================================================================================================
int shortest_path(int ax,int ay,int bx,int by,char map[m][n],int mode)// 0:map point 1:car point
{
    int visited[m*2][n*2],directionx[m*2][n*2],directiony[m*2][n*2],check=0,check2=0;
    for(int i=0;i<m*2;i++)
    {
        for(int j=0;j<n*2;j++)
        {
            visited[i][j]=0;
            directionx[i][j]=0;
            directiony[i][j]=0;
            tmpvisited[i][j]=2147483647;
        }
    }
    head=(waitlist*)malloc(sizeof(waitlist));
    new_node=(waitlist*)malloc(sizeof(waitlist));
    tail=(waitlist*)malloc(sizeof(waitlist));
    head->cost=-1;
    new_node->x=ax;
    new_node->y=ay;
    new_node->cost=0;
    tail->cost=2147483647;
    head->next=new_node;//
    new_node->next=tail;
    while((head->next)->cost!=2147483647)
    {
        currentx=(head->next)->x;
        currenty=(head->next)->y;
        currentcost=(head->next)->cost;
        if(visited[currenty][currentx]==0)
        {
            directionx[currenty][currentx]=(head->next)->lastpointx;
            directiony[currenty][currentx]=(head->next)->lastpointy;
        }
        head->next=(head->next)->next;
        visited[currenty][currentx]=1;
        if(currentx%2==1)//vertical
        {
            for(int i=currenty/2-1;i<=currenty/2+1;i++)
            {
                for(int j=currentx/2;j<=currentx/2+1;j++)
                {
                    if(i==by&&j==bx)
                    {
                        check=-10;
                    }
                }
            }
            if(check<0&&mode==0)
            {
                check2=-1;
                break;
            }
            if(currentx==bx&&currenty==by&&mode==1)
            {
                check2=-1;
                break;
            }
            //=================================================================================================================================
            if(!((map[(currenty/2)+1][currentx/2+2])=='0'||(map[(currenty/2)][currentx/2+2]=='0')||(map[(currenty/2)-1][currentx/2+2])=='0'))
            {
                if(visited[currenty][currentx+2]==0)
                {
                    pushsort(currentx+2,currenty,currentcost+2);
                    //printf("right ");
                }
                if(visited[currenty-1][currentx+1]==0)
                {
                    pushsort(currentx+1,currenty-1,currentcost+5);
                    //printf("counterclock ");
                }
                if(visited[currenty+1][currentx+1]==0)
                {
                    pushsort(currentx+1,currenty+1,currentcost+5);
                    //printf("anticounterclock ");
                }
            }
            //---------------------------------------------------------------------------------------------------------------------------------------
            if(visited[currenty-2][currentx]==0)
            {
                if(!(map[(currenty/2)-2][currentx/2]=='0'||(map[(currenty/2)-2][currentx/2+1]=='0')))
                {
                    pushsort(currentx,currenty-2,currentcost+1);
                    //printf("up ");
                }
            }
            //=========================================================================================================================================
            if(!((map[(currenty/2)+1][currentx/2-1])=='0'||(map[(currenty/2)][currentx/2-1])=='0'||(map[(currenty/2)-1][currentx/2-1])=='0'))
            {
                if(visited[currenty][currentx-2]==0)
                {
                    pushsort(currentx-2,currenty,currentcost+2);
                    //printf("left ");
                }
                if(visited[currenty+1][currentx-1]==0)
                {
                    pushsort(currentx-1,currenty+1,currentcost+5);
                    //printf("counterclock ");
                }
                if(visited[currenty-1][currentx-1]==0)
                {
                    pushsort(currentx-1,currenty-1,currentcost+5);
                    //printf("anticounterclock ");
                }
            }
            //------------------------------------------------------------------------------------------------------------------------------------
            if(visited[currenty+2][currentx]==0)
            {
                if(!((map[(currenty/2)+2][currentx/2])=='0'||(map[(currenty/2)+2][currentx/2+1]=='0')))
                {
                    pushsort(currentx,currenty+2,currentcost+1);
                    //printf("down ");
                }
            }
        }
        else//horizontal
        {
            for(int i=currenty/2;i<=currenty/2+1;i++)
            {
                for(int j=currentx/2-1;j<=currentx/2+1;j++)
                {
                    if(i==by&&j==bx)
                    {
                        check=-10;
                    }
                }
            }
            if(check<0&&mode==0)
            {
                check2=-1;
                break;
            }
            if(currentx==bx&&currenty==by&&mode==1)
            {
                check2=-1;
                break;
            }
            //===================================================================================================================================
            if(!((map[(currenty/2)-1][currentx/2-1])=='0'||(map[(currenty/2-1)][currentx/2])=='0'||(map[(currenty/2)-1][currentx/2+1])=='0'))
            {
                if(visited[currenty-2][currentx]==0)
                {
                    pushsort(currentx,currenty-2,currentcost+2);
                    //printf("up ");
                }
                if(visited[currenty-1][currentx-1]==0)
                {
                    pushsort(currentx-1,currenty-1,currentcost+5);
                    //printf("counterclock ");
                }
                if(visited[currenty-1][currentx+1]==0)
                {
                    pushsort(currentx+1,currenty-1,currentcost+5);
                    //printf("anticounterclock ");
                }
            }
            //-------------------------------------------------------------------------------------------------------------------------------
            if(visited[currenty][currentx+2]==0)
            {
                if(!((map[(currenty/2)+1][currentx/2+2])=='0'||(map[(currenty/2)][currentx/2+2]=='0')))
                {
                    pushsort(currentx+2,currenty,currentcost+1);
                    //printf("right ");
                }
            }
            //================================================================================================================================
            if(!((map[(currenty/2)+2][currentx/2-1])=='0'||(map[(currenty/2)+2][currentx/2])=='0'||(map[(currenty/2)+2][currentx/2+1])=='0'))
            {
                if(visited[currenty+2][currentx]==0)
                {
                    pushsort(currentx,currenty+2,currentcost+2);
                    //printf("down ");
                }
                if(visited[currenty+1][currentx+1]==0)
                {
                    pushsort(currentx+1,currenty+1,currentcost+5);
                    //printf("counterclock ");
                }
                if(visited[currenty+1][currentx-1]==0)
                {
                    pushsort(currentx-1,currenty+1,currentcost+5);
                    //printf("anticounterclock ");
                }
            }
            //----------------------------------------------------------------------------------------------------------------------------------
            if(visited[currenty][currentx-2]==0)
            {
                if(!((map[(currenty/2)][currentx/2-2])=='0'||(map[(currenty/2)+1][currentx/2-2]=='0')))
                {
                    pushsort(currentx-2,currenty,currentcost+1);
                    //printf("left ");
                }
            }
        }
        /*waitlist *tmp6=NULL;
        tmp6=head->next;
        printf("(%d,%d) %d\n",currentx,currenty);
        printf("(%d,%d) %d\n",tmp6->x,tmp6->y,tmp6->cost);
        //Sleep(2000);
        system("CLS");*/
        check=0;
    }
    if((head->next)->cost==2147483647&&check2==0)
    {
        return -1;
    }
    int tmpx,tmpy,tmp2x,tmp2y;
    path_head=(path*)malloc(sizeof(path));
    path_head->x=-1;
    path_new_node=(path*)malloc(sizeof(path));
    path_new_node->x=currentx;
    path_new_node->y=currenty;
    path_new_node->next=path_head;
    path_head=path_new_node;
    tmpx=currentx;
    tmpy=currenty;
    while(tmpx!=ax||tmpy!=ay)
    {
        path_new_node=(path*)malloc(sizeof(path));
        path_new_node->x=directionx[tmpy][tmpx];
        path_new_node->y=directiony[tmpy][tmpx];
        path_new_node->next=path_head;
        path_head=path_new_node;
        tmp2x=tmpx;
        tmp2y=tmpy;
        tmpx=directionx[tmp2y][tmp2x];
        tmpy=directiony[tmp2y][tmp2x];
    }
    return path_head;
}
//================================================================================================
void pushsort(int a,int b,int cost)
{
    if(tmpvisited[b][a]>cost)
    {
        tmpvisited[b][a]=cost;
        new_node=(waitlist*)malloc(sizeof(waitlist));
        new_node->x=a;
        new_node->y=b;
        new_node->cost=cost;
        new_node->lastpointx=currentx;
        new_node->lastpointy=currenty;
        tmp=head;
        while(!(cost>=(tmp->cost)&&cost<=(tmp->next)->cost))
        {
            tmp=tmp->next;
        }
        new_node->next=tmp->next;
        tmp->next=new_node;
    }
}
//===================================================================================================
int DFS(int ax,int ay,char map[m][n])// ax=5 ay=28 map[17][17]
{
    int visited[m*2][n*2],check=0;
    for(int i=0;i<m*2;i++)
    {
        for(int j=0;j<n*2;j++)
        {
            visited[i][j]=0;//34*34
        }
    }
    head=(waitlist*)malloc(sizeof(waitlist));//initialize
    tail=(waitlist*)malloc(sizeof(waitlist));
    head->x=ax;
    head->y=ay;
    tail->x=-1;//stop
    head->next=tail;
    path_DFShead=(path*)malloc(sizeof(path));
    path_DFShead->x=-2;
    path_tmp=path_DFShead;
    while(head->x!=-1)
    {
        currentx=head->x;
        currenty=head->y;
        head=head->next;
        visited[currenty][currentx]=1;//
        if(currentx%2==1)//vertical
        {
            for(int i=currenty/2-1;i<=currenty/2+1;i++)
            {
                for(int j=currentx/2;j<=currentx/2+1;j++)
                {
                    if(map[i][j]=='@')
                    {
                        check++;
                    }
                    else
                    {
                        map[i][j]='@';
                    }
                }
            }
            //==============================================================================================================================
            if(!((map[(currenty/2)+1][currentx/2+2])=='0'||(map[(currenty/2)][currentx/2+2]=='0')||(map[(currenty/2)-1][currentx/2+2])=='0'))
            {
                if(visited[currenty-1][currentx+1]==0)
                {
                    push(currentx+1,currenty-1);
                    printf("counterclock \n");
                }
                if(visited[currenty+1][currentx+1]==0)
                {
                    push(currentx+1,currenty+1);
                    printf("anticounterclock \n");
                }
                if(visited[currenty][currentx+2]==0)
                {
                    push(currentx+2,currenty);
                    printf("right \n");
                }
            }
            //-----------------------------------------------------------------------------------------------------------------------------
            if(visited[currenty-2][currentx]==0)
            {
                if(!(map[(currenty/2)-2][currentx/2]=='0'||(map[(currenty/2)-2][currentx/2+1]=='0')))
                {
                    push(currentx,currenty-2);
                    printf("up \n");
                }
            }
            //=============================================================================================================================
            if(!((map[(currenty/2)+1][currentx/2-1])=='0'||(map[(currenty/2)][currentx/2-1])=='0'||(map[(currenty/2)-1][currentx/2-1])=='0'))
            {
                if(visited[currenty+1][currentx-1]==0)
                {
                    pushsort(currentx-1,currenty+1,currentcost+5);
                    printf("counterclock \n");
                }
                if(visited[currenty-1][currentx-1]==0)
                {
                    pushsort(currentx-1,currenty-1,currentcost+5);
                    printf("anticounterclock \n");
                }
                if(visited[currenty][currentx-2]==0)
                {
                    push(currentx-2,currenty);
                    printf("left \n");
                }
            }
            //---------------------------------------------------------------------------------------------------------------------------------
            if(visited[currenty+2][currentx]==0)
            {
                if(!((map[(currenty/2)+2][currentx/2])=='0'||(map[(currenty/2)+2][currentx/2+1]=='0')))
                {
                    push(currentx,currenty+2);
                    printf("down \n");
                }
            }
        }
        else//horizontal
        {
            for(int i=currenty/2;i<=currenty/2+1;i++)
            {
                for(int j=currentx/2-1;j<=currentx/2+1;j++)
                {
                    if(map[i][j]=='@')
                    {
                        check++;
                    }
                    else
                    {
                        map[i][j]='@';
                    }
                }
            }
            //================================================================================================================================
            if(!((map[(currenty/2)-1][currentx/2-1])=='0'||(map[(currenty/2-1)][currentx/2])=='0'||(map[(currenty/2)-1][currentx/2+1])=='0'))
            {
                if(visited[currenty-1][currentx-1]==0)
                {
                    push(currentx-1,currenty-1);
                    printf("h counterclock \n");
                }
                if(visited[currenty-1][currentx+1]==0)
                {
                    push(currentx+1,currenty-1);
                    printf("h anticounterclock \n");
                }
                if(visited[currenty-2][currentx]==0)
                {
                    push(currentx,currenty-2);
                    printf("h up \n");
                }
            }
            //----------------------------------------------------------------------------------------------------------------------------------
            if(visited[currenty][currentx+2]==0)
            {
                if(!((map[(currenty/2)+1][currentx/2+2])=='0'||(map[(currenty/2)][currentx/2+2]=='0')))
                {
                    push(currentx+2,currenty);
                    printf("h right \n");
                }
            }
            //===============================================================================================================================
            if(!((map[(currenty/2)+2][currentx/2-1])=='0'||(map[(currenty/2)+2][currentx/2])=='0'||(map[(currenty/2)+2][currentx/2+1])=='0'))
            {
                if(visited[currenty+1][currentx+1]==0)
                {
                    push(currentx+1,currenty+1,currentcost+5);
                    printf("h counterclock \n");
                }
                if(visited[currenty+1][currentx-1]==0)
                {
                    push(currentx-1,currenty+1,currentcost+5);
                    printf("h anticounterclock \n");
                }
                if(visited[currenty+2][currentx]==0)
                {
                    push(currentx,currenty+2);
                    printf("h down \n");
                }
            }
            //-----------------------------------------------------------------------------------------------------------------------------------
            if(visited[currenty][currentx-2]==0)
            {
                if(!((map[(currenty/2)][currentx/2-2])=='0'||(map[(currenty/2)+1][currentx/2-2]=='0')))
                {
                    push(currentx-2,currenty);
                    printf("h left \n");
                }
            }
        }
        if(check!=6)
        {
            path_tmp->x=currentx;
            path_tmp->y=currenty;
            path_new_node=(path*)malloc(sizeof(path));
            path_tmp->next=path_new_node;
            path_tmp=path_new_node;
            path_new_node->x=-2;
        }
        check=0;
    }
    return(path_DFShead);
}
//==================================================================================================
void push(int a,int b)
{
    new_node=(waitlist*)malloc(sizeof(waitlist));
    new_node->x=a;
    new_node->y=b;
    new_node->next=head;
    head=new_node;
}
