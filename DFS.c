#include <stdio.h>
#include <stdlib.h>

struct AdjacencyList{
	char vertex;
	struct AdjacencyList* next;
};

struct Stack
{
	char* vertex;
	int top;
	unsigned size;	

};


struct AdjacencyList* newNode(char child){
	struct AdjacencyList* temp = (struct AdjacencyList*)malloc(sizeof(struct AdjacencyList));
	temp->vertex = child;
	temp->next = NULL;

	return temp;
}

void insert(struct AdjacencyList* array[], int index, char child){

	struct AdjacencyList* temp = newNode(child);
	temp->next = array[index];
	array[index] = temp;

}


struct Stack* createStack(int size){
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));

	stack->size = size;
	stack->top = -1;
	stack->vertex = (char*)malloc(size * sizeof(char));

	return stack;
}

int isEmpty(struct Stack* stack){

	return (stack->top == -1);
}

void push(struct Stack* stack, char vertex){
	stack->top++;
	stack->vertex[stack->top] = vertex;

}

void pop(struct Stack* stack){

	if(isEmpty(stack)) return;

	stack->top--;
}

char top(struct Stack* stack){
	return stack->vertex[stack->top];
}

int SourceToIndex(char character){
	return (character-'A');
}

void DFS(struct AdjacencyList* array[], int size, char source, int* inDFSTree){

	struct Stack* stack = createStack(size);
	int index = SourceToIndex(source);


	push(stack, source);
	inDFSTree[index] = 1;

	while(!isEmpty(stack)){

		char parrent = top(stack);
		index = SourceToIndex(parrent);
		struct AdjacencyList* temp = array[index];

		while(temp->next != NULL){
			
			char child = temp->vertex;
			int tempIndex = SourceToIndex(child);

			if(inDFSTree[tempIndex] == 0){
				push(stack, child);
				inDFSTree[tempIndex] = 1;
				temp = array[tempIndex];
			}

			else temp = temp->next;
		}

		printf("%c->", top(stack));
		pop(stack);
	}
	printf("NULL\n");

}

int main(int argc, char const *argv[])
{

	int size=8;
	struct AdjacencyList* array[8] = {0};

	printf("Is is a directed Graph? 1/0? \n");
	int isDirected;
	scanf("%d", &isDirected);

	int choice = 1;

	while(choice == 1){
		printf("Enter the parrent and child(in upper Case): \n");
		char parrent, child;
		scanf(" %c %c", &parrent, &child);
		int index1 = parrent - 'A';
		insert(array, index1, child);

		if(!isDirected){
			int index2 = child - 'A';
			insert(array, index2, parrent);
		}
		
		printf("Want to continue:1/0 ? \n");
		scanf("%d", &choice);
	}

	printf("\nThe DFS Tree is: \n");
	int inBFSTree[8] = {0};

	printf("Enter the source: \n");

	char source;
	scanf(" %c", &source);
	DFS(array, size, source, inBFSTree);

	return 0;
}
