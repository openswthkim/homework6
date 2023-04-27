/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node { // 구조체 선언
	int key; // 정수형 변수 선언
	struct Node* link; // 구조체 변수 node에 대한 포인터 선언
} listNode;

typedef struct Head { // 구조체 선언
	struct Node* first; // 구조체 변수 node에 대한 포인터 선언
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); // headNode에 메모리를 할당하여 초기화하는 함수
int freeList(headNode* h); // 할당된 메모리를 해제함

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command; // 문자형 변수 선언
	int key; // 정수형 변수 선언
	headNode* headnode=NULL; // headnode에 대한 포인터 선언 하고 초기화
		printf("[----- [Taehyung Kim] [2020039024] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 명령 입력받기

		switch(command) {
		case 'z': case 'Z': // z를 입력 받을 경우
			headnode = initialize(headnode); // initialize 함수 리턴 값 대입
			break;
		case 'p': case 'P': // p를 입력 받을 경우
			printList(headnode); // headnode 함수를 출력 함
			break;
		case 'i': case 'I': // i를 입력 받을 경우
			printf("Your Key = ");
			scanf("%d", &key); // 정수형 변수 입력 받음
			insertNode(headnode, key); // insertNode 함수 호출
			break;
		case 'd': case 'D': // d를 입력 받을 경우
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); // deleteNode 함수 호출
			break;
		case 'n': case 'N': // n을 입력 받을 경우
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // insertLast 함수 호출
			break;
		case 'e': case 'E': // e를 입력 받을 경우
			deleteLast(headnode); // deleteLast 함수 호출
			break;
		case 'f': case 'F': // f를 입력 받을 경우
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); // insertFirst 함수 호출
			break;
		case 't': case 'T': // t를 입력 받을 경우
			deleteFirst(headnode); // deleteFirst 함수 호출
			break;
		case 'r': case 'R': // r을 입력 받을 경우
			invertList(headnode); // invertList 함수 호출
			break;
		case 'q': case 'Q': // q를 입력 받을 경우
			freeList(headnode); // 함수 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q가 입력되지 않는 동안 반복함

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL) // headNode가 NULL이 아니면
		freeList(h); // 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode의 크기만큼 temp 변수에 저장한다
	temp->first = NULL; // temp의 first에 NULL을 저장
	return temp; //temp값 반환
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // 포인터 변수 p를 선언하고 h를 옹해 노드에 연결하고 p에 저장

	listNode* prev = NULL; // 포인터 변수 prev 선언하고 초기화
	while(p != NULL) { //p가 NULL이 아닐때까지 반복
		prev = p; // prev에 p 대입
		p = p->link; // p의 link를 p에 저장
		free(prev); // prev 메모리 해제
	}
	free(h); // h 메모리 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listnode의 포인터 변수 node에 listnode 크기의 메모리 할당
	node->key = key; // node의 key에 key 값 저장
	node->link = NULL; // node의 link에 NULL 값 저장

	if (h->first == NULL) // h의 first가 NULL 이라면
	{
		h->first = node; // first에 node값 대입
		return 0;
	}

	listNode* n = h->first; // 포인터 n에 h의 first값 저장
	listNode* trail = h->first; // 포인터 trail에 h의 first값 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { // n이 NULL이 아닐 동안 반복
		if(n->key >= key) { // n의 key가 입력 받은 값보다 클 때
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { // n이 첫번째 노드인 경우
				h->first = node; // first에 node 저장
				node->link = n; // node의 link에 n값 저장
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n; // node의 link에 n값 저장
				trail->link = node; // trail의 link에 node 저장
			}
			return 0;
		}

		trail = n; // trail에 n값 저장
		n = n->link; // n의 link를 n에 저장장
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node; // trail의 링크를 node에 저장
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 listnode 크기 만큼 메모리 할당
	node->key = key; // node의 key에 key값 저장
	node->link = NULL; // node에 link에 NULL값 저장

	if (h->first == NULL) // h의 first가 NULL이면
	{
		h->first = node; // h의 first에 node 저장
		return 0;
	}

	listNode* n = h->first; // 포인터 변수 n에 h의 first 저장
	while(n->link != NULL) { // n의 link가 NULL이 아닐 동안 반복
		n = n->link; // n에 n의 link값 저장
	}
	n->link = node; // n의 link 값을 node에 저장
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node에 listnode 크기만큼의 메모리 할당
	node->key = key; // node의 key를 key에 저장

	node->link = h->first; // node의 link에 h의 first값 저장
	h->first = node; // h의 first값에 node값 저장

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // h의 first가 NULL이면
	{
		printf("nothing to delete.\n"); // 출력
		return 0;
	}

	listNode* n = h->first; // n에 h의 first 저장
	listNode* trail = NULL; // 포인터 traill에 NULL 저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { // n이 NULL이 아닐 동안 반복한다
		if(n->key == key) { // n의 key가 key이면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { // n이 h의 first와 같으면
				h->first = n->link; // h의 first에 n의 link 대입
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; // 아니면 trail의 link에 n의 link 대입
			}
			free(n); // n의 메모리 해제
			return 0;
		}

		trail = n; // trail에 n 저장
		n = n->link; // n에 n의 link 저장
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // h의 first가 NULL이면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // n에 h의 first 저장
	listNode* trail = NULL; // 포인터 변수 traill에 NULL 저장

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { // n의 link가 NULL이면
		h->first = NULL; // h의 first에 NULL 저장
		free(n); // n의 메모리 초기화
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) { // n의 link가 NULL이 아닐 동안 반복
		trail = n; // trail에 n저장
		n = n->link; // n에 n의 link 저장
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; // trail의 link에 NULL 저장
	free(n); // n의 메모리 해제
 
	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // h의 frst가 NULL이면
	{
		printf("nothing to delete.\n"); // 출력
		return 0;
	}
	listNode* n = h->first; // 포인터 변수 n에 h의 first 저장

	h->first = n->link; // h의 first에 n의 link 저장
	free(n); // n에 할당된 메모리 해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { // h의 first가 NULL이면
		printf("nothing to invert...\n"); // 출력
		return 0;
	}
	listNode *n = h->first; // n에 h의 first 저장
	listNode *trail = NULL; // trail에 NULL 저장
	listNode *middle = NULL; // middle에 NULL 저장

	while(n != NULL){ // n이 NULL이 아닐때까지 반복
		trail = middle; // trail에 middle값 저장
		middle = n; // middle에 n저장
		n = n->link; // n에 n의 link 저장
		middle->link = trail; // middle의 link에 trail 저장
	}

	h->first = middle; // h의 first에 middle 저장

	return 0;
}


void printList(headNode* h) {
	int i = 0; // 정수형 변수 선언
	listNode* p; // 포인터 변수 선언

	printf("\n---PRINT\n");

	if(h == NULL) { // h가 NULL이라면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // p에 h의 first 저장

	while(p != NULL) { // p가 NULL이 아닌동안 반복
		printf("[ [%d]=%d ] ", i, p->key); // i의 p 출력
		p = p->link; // p에 p의 link 저장
		i++; // i값 증가
	}

	printf("  items = %d\n", i);
}