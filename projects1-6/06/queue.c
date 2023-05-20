#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//使用queue建立symbol table 
struct Qnode{
	int val;
	char* symbol;
	struct Qnode* next;
};

struct Queue{
	struct Qnode *front;
	struct Qnode *rear;
};

struct Qnode *createNode(int k, char* s){
	struct Qnode *n=(struct Qnode*)malloc(sizeof(struct Qnode));
	n->val=k;
	n->symbol=s;
	n->next=NULL;
	return n;
}

struct Queue *createQueue(){
	struct Queue *q=(struct Queue*)malloc(sizeof(struct Queue));
	q->front=q->rear=NULL;
	return q;
}

void enqueue(struct Queue *q, int k, char* s){
	struct Qnode *n=createNode(k,s);
	if (q->rear==NULL){
		q->front=q->rear=n;
		return;
	}
	q->rear->next=n;
	q->rear=n; 
}

struct Queue * create_predefined(){
	struct Queue *q=createQueue();
	enqueue(q,0,"R0");
	enqueue(q,1,"R1");
	enqueue(q,2,"R2");
	enqueue(q,3,"R3");
	enqueue(q,4,"R4");
	enqueue(q,5,"R5");
	enqueue(q,6,"R6");
	enqueue(q,7,"R7");
	enqueue(q,8,"R8");
	enqueue(q,9,"R9");
	enqueue(q,10,"R10");
	enqueue(q,11,"R11");
	enqueue(q,12,"R12");
	enqueue(q,13,"R13");
	enqueue(q,14,"R14");
	enqueue(q,15,"R15");
	enqueue(q,16384,"SCREEN");
	enqueue(q,24576,"KBD");
	enqueue(q,0,"SP");
	enqueue(q,1,"LCL");
	enqueue(q,2,"ARG");
	enqueue(q,3,"THIS");
	enqueue(q,4,"THAT");
	return q;
}

void show_queue(struct Queue *q){
	struct Qnode *current=q->front;
	while(current){
		printf("symbol=%s, val=%d\n",current->symbol,current->val);
		current=current->next;
	}
	printf("\n");
}
//檢查queue是否資料已存在 
int check_queue(struct Queue *q, char *str){
	struct Qnode *current=q->front;
	while(current){
		if(strcmp(current->symbol,str)==0){
			return current->val;
		}
		current=current->next;
	}
	return -1;
}
