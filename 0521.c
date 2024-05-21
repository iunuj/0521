#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct listNode {
	element data;
	struct listNode* link;
} ListNode;

ListNode* insert_first(ListNode* h, element value) {

	ListNode* p = (ListNode*)malloc(sizeof(ListNode));

	p->data = value;
	p->link = h;
	h = p;
	return h;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));

	if (pre == (ListNode*)NULL) {
		fprintf(stderr, "Insert parameter error in pre == NULL");
		return;
	}
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}


ListNode* delete_first(ListNode* h) {

	if (h == NULL) return NULL;
	ListNode* remove = h;

	h = remove->link;
	free(remove);
	return h;
}

ListNode* delete(ListNode* h, ListNode* pre) {
	ListNode* remove = pre->link;

	pre->link = remove->link;
	free(remove);

	return h;
}

void print_list(ListNode* h) {
	while (h != (ListNode*)NULL) {
		printf("[%d] ", h->data);
		h = h->link;
	}
	printf("\n");
}

ListNode* search_list(ListNode* h, element x) {
	ListNode* p = h;

	while (p != NULL) {
		if (p->data == x) break;
		p = p->link;
	}
	return p;
}

ListNode* reverse(ListNode* h) {
	ListNode* r, * q, * p;

	q = NULL;
	p = h;
	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

ListNode* insert_last(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;
	if (head == NULL) {
		head = p;
	}
	else {
		ListNode* q = head;
		while (q->link != NULL) {
			q = q->link;
		}
		q->link = p;
	}
	return head;
}

ListNode* insert_node(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	if (head == NULL) {
		head = p;
	}
	else {
		ListNode* q = head;
		while (q->link != NULL) {
			q = q->link;
		}
		q->link = p;
	}
	return head;
}

ListNode* delete_node(ListNode* head, element value, ListNode** deleted_head) {
	ListNode* p = head;
	ListNode* pre = NULL;

	while (p != NULL && p->data != value) {
		pre = p;
		p = p->link;
	}

	if (p == NULL) {
		printf("%d not found\n", value);
		return head;
	}

	if (pre != NULL) {
		pre->link = p->link;
	}
	else {
		*deleted_head = p;
	}

	free(p);
	return head;
}
int main() {
	ListNode* head = NULL;
	ListNode* deleted_head = NULL;
	char* initial_fruits[] = { "Mango", "Orange", "Apple", "Grape", "Cherry", "Plum", "Guava", "Raspberry", "Banana", "Peach" };
	int initial_count = sizeof(initial_fruits) / sizeof(initial_fruits[0]);

	for (int i = 0; i < initial_count; i++) {
		head = insert_last(head, initial_fruits[i]);
	}

	int choice;
	char fruit[30];

	while (1) {
		printf("1. 리스트의 매 마지막에 새로운 과일 추가\n");
		printf("2. 리스트에 있는 과일을 삭제\n");
		printf("3. 삭제된 과일 목록 출력\n");
		printf("4. 종료\n");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("추가할 과일을 입력하세요 : ");
			scanf("%s", fruit);
			if (search_list(head, fruit) == NULL) {
				head = insert_last(head, _strdup(fruit));
			}
			else {
				printf("%s은 이미 존재합니다\n", fruit);
			}
			break;
		case 2:
			printf("삭제할 과일을 입력하세요 : ");
			scanf("%s", fruit);
			if (search_list(head, fruit) != NULL) {
				head = delete_node(head, fruit, &deleted_head);
				printf("%s을 삭제했습니다\n", fruit);
			}
			else {
				printf("%s은 존재하지 않습니다\n", fruit);
			}
			break;
		case 3:
			printf("삭제된 과일 목록 : ");
			print_list(deleted_head);
			break;
		case 4:
			printf("프로그램 종료");
			return 0;
		default:
			printf("유효하지 않은 선택입니다 ! \n");
		}
	}
	return 0;
}