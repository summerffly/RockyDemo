
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>   // POSIX SysCall (Unix,Linux,masOS)
#include <stdlib.h>   // standard library of C
#include <stdio.h>

#define MAXSIZE   1000000s

using namespace std;


typedef struct Node
{
    int data;
    struct Node *next;
}LNode;
typedef struct Node *LinkList;

void CreateListHead(LinkList *, int);
void TraverseList(LinkList);
void ReverseList(LinkList);

int main(int argc, char **argv, char *env[])
{
    LinkList lla = NULL;

    CreateListHead(&lla, 10);
    TraverseList(lla);
    ReverseList(lla);
    TraverseList(lla);
    
    return 0;
}

void CreateListHead(LinkList *LL, int length)
{
    struct Node *rNode;
    *LL = (LinkList)malloc(sizeof(LNode));
    rNode = *LL;

    struct Node *tmpNode;
    for(int i=1; i<=length; i++)
    {
        tmpNode = (struct Node *)malloc(sizeof(LNode));
        tmpNode->data = i;
        rNode->next = tmpNode;
        rNode = tmpNode;
    }
    rNode->next = NULL;
}

void TraverseList(LinkList LL)
{
    struct Node *tmpNode = LL->next;

    while( 1 )
    {        
        printf("Node %d \n", tmpNode->data);
        if(tmpNode->next == NULL)
            break;
        tmpNode = tmpNode->next;
    }
    printf("\n");
}

void ReverseList(LinkList LL)
{
    if(LL == NULL || LL->next == NULL || LL->next->next == NULL)
        return;
    
    struct Node *curNode = LL->next;
    struct Node *nextNode = LL->next->next;
    struct Node *tmpNode = NULL;

    curNode->next = NULL;
    while( nextNode != NULL )
    {
        tmpNode = nextNode->next;
        nextNode->next = curNode;
        curNode = nextNode;
        nextNode = tmpNode;
    }
    LL->next = curNode;
}

//------------------------------//
//   River flows in summer
//------------------------------//
