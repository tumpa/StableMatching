#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct hash *courseTable = NULL;
struct hash *slotTable = NULL;

int slot[]={0,0,0,0,0,0,0,0,0,0};
int course[]={0,0,0,0,0,0,0,0,0,0};
int teachers[]={0,0,0,0,0,0,0,0,0,0};
int ns = 10;
int nc = 6;
int arr [6][3];
int eleCount = 0;
struct node {
    int age;
    struct node *next;
};

struct hash {
    struct node *head;
    int count;
};
void initArr()
{
    for(int i = 0; i<nc;i++)
        for(int j=0; j<3;j++)
            arr[i][j]=0;
}
void stableClassSchedule(int nt)
{
    initArr();
    int c=0;
    int s=0;
    int trackArr = 0;
    int slotTemp = 0;
    int courseTemp = 0;
    for(int i = 0; i<nt; i++)
    {
        c=1,s=1;
        while(trackArr<nc)
        {
            if(teachers[i]==1)
                break;
            if(s > slotTable[i].count || c > courseTable[i].count){
                break;
            }
            slotTemp = traverseNode(i,s, slotTable);
            courseTemp = traverseNode(i,c , courseTable);
            if(slot[slotTemp]==0)
                if(course[courseTemp]==0){
                    arr[trackArr][0] = i+1;
                    arr[trackArr][1] = slotTemp;
                    arr[trackArr][2] = courseTemp;
                    slot[slotTemp] = 1;
                    course[courseTemp] = 1;
                    trackArr ++;
                    teachers[i] = teachers[i]+1;

                }
                else
                    c++;
            else
                s++;
        }
        if(trackArr>=nc)
            break;
    }

}



struct node * createNode(int age) {
    struct node *newnode;
    newnode = (struct node *) malloc(sizeof(struct node));
    newnode->age = age;
    newnode->next = NULL;
    return newnode;
}
int traverseNode(int i, int j, struct hash *hashTable){
    struct node *myNode = NULL;
    int count = 0;
    if (!hashTable[i].count == 0 && hashTable[i].count >= j){
        myNode = hashTable[i].head;
        count = 1;
        while(count != j){
                myNode = myNode->next;
                count ++;
            }
    }
    if (!myNode)
        return 0;
    else
        return myNode->age;
}

void insertToHash(int key, int age, struct hash *hashTable) {
    int hashIndex = key;
    struct node *newnode = createNode(age);
    if (!hashTable[hashIndex].head) {
        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count = 1;
        return;
    }
    struct node *temp;
    temp = hashTable[hashIndex].head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newnode;
    hashTable[hashIndex].count++;
    return;
}

void display(struct hash *hashTable) {
    struct node *myNode;
    int i;
    for (i = 0; i < eleCount; i++) {
        if (hashTable[i].count == 0)
            continue;
        myNode = hashTable[i].head;
        if (!myNode)
            continue;
        printf("\nData at index %d in Hash Table:\n", i);
        printf("Value\n");
        printf("---\n");
        while (myNode != NULL) {
            printf("%d\n", myNode->age);
            myNode = myNode->next;
        }
    }
    return;
}

void displayAssignment(){
    for(int i = 0 ; i<nc; i++){
        for(int j = 0 ; j<3; j++)
        {
               printf("%d\t", arr[i][j]);
        }
         printf("\n");
    }
}

int main() {
    int n, ch, key, age;
    printf("Enter the number of teachers:");
    scanf("%d", &n);
    eleCount = n;
    /* create hash table with "n" no of buckets */
    slotTable = (struct hash *) calloc(ns, sizeof(struct hash));
    courseTable = (struct hash *) calloc(nc, sizeof(struct hash));
    while (1) {
        printf("Enter course preference list of teachers");
        printf("\n1. Insertion\t4. Display\n5. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        if(ch ==1){
            printf("Enter the key value:");
            scanf("%d", &key);
            printf("Course code:");
            scanf("%d", &age);
            /*inserting new node to hash table */
            if(key >= n)
            {
                printf("Warning warning, enter a key between 0 to %d\n", n-1);
                printf("Enter the key value:");
                scanf("%d", &key);
            }
            insertToHash(key, age, courseTable);
        }
        else if(ch==4){
            display(courseTable);
        }
        else{
            break;
        }
    }

    while (1) {
        printf("Enter available time slot list of teachers");
        printf("\n1. Insertion\t4. Display\n5. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        if(ch==1){
            printf("Enter the key value:");
            scanf("%d", &key);
            printf("Slot number:");
            scanf("%d", &age);
            /*inserting new node to hash table */
            if(key >= n)
            {
                printf("Warning warning, enter a key between 0 to %d\n", n-1);
                printf("Enter the key value:");
                scanf("%d", &key);
            }

            insertToHash(key, age, slotTable);
        }
        else if(ch==4){
            display(slotTable);
        }
        else{
            break;
        }
    }
    stableClassSchedule(n);
    displayAssignment();
    return 0;
}
