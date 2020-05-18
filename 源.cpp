#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode* HuffmanTree;
struct TreeNode {
	int weight;
	char Data;
	HuffmanTree Left, Right;
};
typedef struct hNode* Minheap;
struct hNode {
	int size;//当前的元素个数
	struct TreeNode *A;//元素数组
	int capacity;//堆的最大容量
};
Minheap creatheap(int maxsize) {
	Minheap h= (Minheap)malloc(sizeof(struct hNode));
	h->A = (HuffmanTree)malloc((maxsize + 1) * sizeof(struct TreeNode));
	h->size =h->capacity = maxsize;
	h->A[0].weight= -1;//定义哨兵为数组元素不可能取到的值 
	return h;
}
bool isFull(Minheap h) {
	return h->size == h->capacity;
}
bool isEmpty(Minheap h) {
	return h->size == 0;
}
bool Insert(Minheap h,struct TreeNode x) {
	int i;
	if (isFull(h))return false;//最小堆已满
	i = ++h->size;
	for (; h->A[i / 2].weight > x.weight; i /= 2) {
		h->A[i]= h->A[i / 2];
	}
	h->A[i] = x;
	return true;
}
struct TreeNode DeleteMin(Minheap h) {
	int parent, child;
	struct TreeNode Minitem, x;
	struct TreeNode error;
	error.weight = -1;
	if (isEmpty(h))return error;
	Minitem = h->A[1];
	x = h->A[h->size--];
	for (parent = 1; parent * 2 <= h->size; parent = child) {
		child = parent * 2;
		if (child != h->size && h->A[child].weight > h->A[child+1].weight)child++;
		if (h->A[child].weight < x.weight) {
			h->A[parent] = h->A[child];
		}
		else break;
	}
	h->A[parent] = x;
	return Minitem;
}
void percdown(Minheap h,int i) {
	int parent, child;
	struct TreeNode x= h->A[i];
	for (parent = i; parent * 2 <= h->size; parent = child) {
		child = parent * 2;
		if (child != h->size && h->A[child].weight > h->A[child + 1].weight)child++;
		if (h->A[child].weight < x.weight)h->A[parent] = h->A[child];
		else break;
	}
	h->A[parent] = x;
}
void buildheap(Minheap h) {
	
	for (int i = 1; i <= h->capacity; i++) {
		scanf_s("%d", &h->A[i].weight);
	}
	getchar();
	for (int i = 1; i <= h->capacity; i++) {
		scanf_s("%c", &h->A[i].Data);
	}
	for (int i = h->size / 2; i >= 1; i--) {
		percdown(h,i);
	}
}
HuffmanTree Huffman(Minheap H) {
	int i;
	HuffmanTree T;
	for (i = 1; i < H->capacity; i++) {
		T = (HuffmanTree)malloc(sizeof(struct TreeNode));
		T->Left = &DeleteMin(H);
		T->Right = &DeleteMin(H);
		T->weight = T->Left->weight + T->Right->weight;
	    Insert(H, *T);
	}
	
	T = &DeleteMin(H);
	return T;
}
int main() {
	int n;
	scanf_s("%d", &n);
	Minheap h = creatheap(n);
	buildheap(h);
	HuffmanTree T =Huffman(h);
		printf("%d\n", T->Left->Right->weight);
    
}