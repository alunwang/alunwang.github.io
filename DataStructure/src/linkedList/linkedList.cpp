#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

/*
 * 插入元素到表头
 */
void insert(struct Node** head, int data)
{
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));
    p->data = data;
    
    p->next = (*head);
    (*head) = p;
}

/*
 * 释放链表所有节点
 */
void freeLinkedList(struct Node* head)
{
    struct Node* p=head;
    while (p != NULL) {
        head = p->next;
        free(p);
        p = head;
    }
}

/*
 * 打印链表每一个节点中的值
 */
void printLinkedList(struct Node* head)
{
    if (head == NULL) return;

    struct Node* p=head;
    while (p != NULL) {
        printf("%d", p->data);
        p = p->next;
    }

    printf("\n");
}

/*
 * 反转链表
 */
void reverse(struct Node** head)    // 不能传struct Node* head，这是一个坑
{
    struct Node* prev = NULL;
    struct Node* cur = (*head);
    struct Node* ne = NULL;

    while (cur != NULL) {
        ne = cur->next; // Store next
        cur->next = prev;
        prev = cur;
        cur = ne;
    }

    *head = prev;
}

/*
 * 从给定单向链表摘取一个，插入新单向链表中
 */
void pickReverse(struct Node** head)
{
    struct Node* tmp = NULL;    // 指向新链表
    struct Node* p = *head;     // 摘第一个

    while (p != NULL) {
        *head = p->next;    // 保存下一个
        p->next = tmp;
        tmp = p;
        p = *head;
    }

    *head = tmp;
}

int main()
{
    struct Node* head = NULL;

    for (int i=0; i<10; ++i) {
        insert(&head, i);
    }
    printf("Sequence before reverse: ");
    printLinkedList(head);
    reverse(&head);
    printf("Sequence after reverse: ");
    printLinkedList(head);

    freeLinkedList(head);

    return 0;
}