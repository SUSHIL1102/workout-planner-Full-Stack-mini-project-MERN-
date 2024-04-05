#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node* prev;
    int data;
    struct node* next;
}NODE;

NODE* createnode();
NODE* createlist(NODE* head, NODE** tail, int n);
void display(NODE* head); 
NODE* insert_first(NODE* head, NODE* tail);
NODE* insert_end(NODE* head, NODE* tail);
NODE* delete_first(NODE* head,NODE* tail);
NODE* delete_last(NODE* head,NODE* tail);
NODE* insert_at_pos(NODE* head,NODE* tail,int pos,int n);
NODE* delete_at_pos(NODE* head,NODE* tail, int pos);
void freelist(NODE* head);


int main(){
    NODE* head,*tail;
    head=NULL;
    tail=NULL;
    int n,pos;

    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    if(n<0){
        printf("Enter a valid number!");
    }else if(n==0){
        printf("The List is empty");
    }else{
        head=createlist(head,&tail,n);
    }

    printf("Before: ");
    display(head);
    printf("\n\n");

    
    head=insert_first(head,tail);
    printf("After inserting node at front: ");
    display(head);
    printf("\n\n");
    
    tail=insert_end(head,tail);
    printf("After inserting node at back: ");
    display(head);
    printf("\n\n");
    
    head=delete_first(head,tail);
    printf("After deleting node at front: ");
    display(head);
    printf("\n\n");
    
    tail=delete_last(head,tail);
    printf("After deleting node at back: ");
    display(head);
    printf("\n\n");
    

    printf("Enter position of node to be inserted: ");
    scanf("%d",&pos);
    if(pos<=0){
        printf("Invalid position!!\n");
    }else if(pos>n+1){
        printf("Insertion at position %d failed-There are only %d nodes!!\n",pos,n);
    }else{
        head=insert_at_pos(head,tail,pos,n);
        printf("After inserting node at position %d: ",pos);
        display(head);
        printf("\n\n");
    }
    

    printf("Enter position of node to be deleted: ");
    scanf("%d",&pos);
    if(pos<=0){
        printf("Invalid position!!\n");
    }
    else if(pos>n+1){
        printf("Deletion at position %d failed-There are only %d nodes!!\n",pos,n);
    }else{
        head=delete_at_pos(head,tail,pos);
        printf("After deleting node at position %d: ",pos);
        display(head);
        printf("\n");
    }
    

    freelist(head);
    return 0;
}

NODE* createnode(){
    NODE* new=(NODE*)malloc(sizeof(NODE));
    printf("Enter data for new node: ");
    scanf("%d",&new->data);
    new->prev=NULL;
    new->next=NULL;
    return new;
}

NODE* createlist(NODE* head,NODE** tail, int n){
    head=(NODE*)malloc(sizeof(NODE));
    printf("Enter the data 1: ");
    scanf("%d",&head->data);
    head->prev=*tail;
    head->next=head;
    *tail=head;
    NODE* temp=head;

    for(int i=2;i<=n;i++){
        NODE *new;
        new=(NODE*)malloc(sizeof(NODE));
        printf("Enter the data %d: ",i);
        scanf("%d",&new->data);
        temp->next=new;
        new->prev=temp;
        new->next=head;
        head->prev=new;
        *tail=new;
        temp=temp->next;
    }
    return head;
}

void display(NODE* head){
    if(head==NULL){
        printf("The List is empty!");
    }
    NODE* temp=head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
}

NODE* insert_first(NODE* head,NODE* tail){
    NODE* temp=createnode();
    temp->next=head;
    head->prev=temp;
    head=temp;
    tail->next=head;
    head->prev=tail;
    return head;
}

NODE* insert_end(NODE* head,NODE* tail){
    NODE* temp=createnode();
    tail->next=temp;
    temp->prev=tail;
    tail=temp;
    tail->next=head;
    head->prev=tail;
    return tail;
}

NODE* delete_first(NODE *head,NODE* tail){
    NODE* temp=head;
    head=head->next;
    free(temp);
    head->prev=tail;
    tail->next=head;
    return head;
}

NODE* delete_last(NODE *head,NODE *tail){
    NODE* temp=tail;
    tail=tail->prev;
    free(temp);
    tail->next=head;
    head->prev=tail;
    return tail;
}

NODE* insert_at_pos(NODE* head,NODE* tail,int pos,int n){
    if(pos==1){
        head=insert_first(head,tail);
        return head;
    }
    NODE* temp=head;
    NODE* nxt=head->next;
    NODE* new=(NODE*)malloc(sizeof(NODE));
    printf("Enter data for new node:");
    scanf("%d",&new->data);
    new->next=NULL;
    new->prev=NULL;
    int count=0;
    do{
        if(count==pos-2){
            new->prev=temp;
            temp->next=new;
            new->next=nxt;
            nxt->prev=new;
            return head;
        }
        temp=temp->next;
        count++;        
        nxt=nxt->next;
    }while(temp!=head);
}

NODE* delete_at_pos(NODE* head,NODE* tail, int pos){
    NODE* temp=head; 
    NODE* back=head;
    NODE* nxt=head;

    if(pos==1){
        head=delete_first(head,tail);
        return head;
    }
    for(int i=1;i<pos;i++){
        temp=temp->next;
    }
    if(temp->next==head){
        tail=delete_last(head,tail);
        return head;
    }
    back=temp->prev;
    nxt=temp->next;
    back->next=nxt;
    nxt->prev=back;
    free(temp);
    return head;
}

void freelist(NODE* head){
    NODE* current = head;
    do{
        NODE* temp = current;
        current = current->next;
        free(temp);
    }while (current != head);
}