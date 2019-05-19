#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>//for pow function
typedef struct node {
	char info;
	struct  node *next;
}Node, *Nodeptr;
typedef struct evonode {
	//for evoluation statement
	int info;
	struct evonode *next;
}evo, *evoptr;
char que[100];//global for took result of the infix to postfix. its working like a buffer system!!!!!!!!
Nodeptr get_node(void) {
	return ((Nodeptr)malloc(sizeof(Node)));
}
void free_node(Nodeptr *p) {
	if (p != NULL)
		free(p);
}
Nodeptr push(Nodeptr *p, char item) {
	Nodeptr q;
	q = get_node();
	q->info = item;
	if (*p == NULL) {
		q->next = NULL;
		*p = q;
	}



	else {
		q->next = *p;
		*p = q;
	}
}
char pop(Nodeptr *p) {
	char item;
	Nodeptr q;
	q = get_node();
	q = *p;
	item = q->info;
	if ((*p)->next == NULL)
		*p = NULL;
	else
		*p = q->next;
	free_node(q);
	if (item == '(' || item == ')')
		return '\0';// if elemet is   '('  or ')'   return space 
	return item;
}
void traverse(Nodeptr p) {
	while (p != NULL) {
		printf(" -> %d", p->info);
		p = p->next;
	}
	printf(" -> null (x)");
	return;
}


int top_of(Nodeptr *p) {
	return (*p)->info;
}
int priority(char x) { // check priority  of operator !!
	if (x == '$')
		return 3;
	else if (x == '*' || x == '/')
		return 2;
	else if (x == '+' || x == '-')
		return 1;
	return 0;
}
int check(char x) {
	return ((x > 47 && x < 58) || (x > 64 && x < 91) || (x > 96 && x < 123));
}
void delete_space(char infix[100]) {
	int i, j = 0;
	for (i = 0; infix[i] != '\0'; ++i)
		if (infix[i] != ' ')
			infix[j++] = infix[i];
	infix[j] = '\0';
	//x.erase(std::remove(x.begin(),x.end(),' '),x.end());
}
evoptr get_node_evo(void) {
	return ((evoptr)malloc(sizeof(evo)));
}
void free_node_evo(evoptr *p) {
	if (p != NULL)
		free(p);
}


evoptr push_evo(evoptr *p, int item) {
	evoptr q;
	q = get_node_evo();
	q->info = item;
	if (*p == NULL) {
		q->next = NULL;
		*p = q;
	}
	else {
		q->next = *p;
		*p = q;
	}
	//	free_node(q);
}
int pop_evo(evoptr *p) {
	int item;
	evoptr q;
	q = get_node_evo();
	if (*p == NULL) {
		//printf("Error");
		return 0;
	}
	q = *p;
	item = q->info;
	if ((*p)->next == NULL)
		*p = NULL;
	else
		*p = q->next;
	free_node_evo(q);
	return item;
}

void convert(char *a) {

	int i = 0;
	int j = 0;
	char b[50];
	while (a[i] != '\0' || a[i] != '\n') {
		if ((a[i] == '+'&&a[i + 1] == '-') || (a[i] == '-'&&a[i + 1] == '+')) {

			b[j] = '-';
			j++;
			i += 2;
		}
		else if ((a[i] == '-'&&a[i + 1] == '-')) {
			b[j] = '+';
			j++;
			i += 2;
		}
		else {
			b[j] = a[i];
			i++;
			j++;
		}
		//i++;
	}
	b[j] = '\0';
	strcpy(a, b);

}


void infix_to_postfix(Nodeptr *s, char *infix) {
	//delete_space(infix);
	//convert(infix);
	int i = 0;
	int j = 0;
	while (infix[i] != NULL) {
		int c = 0;
		if (check(infix[i])) {
			que[j++] = ' ';
			while (check(infix[i])) {
				que[j++] = infix[i++];
			}
			i--;
		}
		else if (infix[i] == '(')
			push(s, infix[i]);
		else if (!check(infix[i])) {  // if infix is operator :
			int timer = 0;
			do {
				timer = 0;
				//c = 0;
				//c = 0;
				if (*s == NULL) {
					push(s, infix[i]);
					timer = 1;
				}
				else if ((*s)->info == '(') {
					if (c) {
						que[j++] = ' ';
						pop(s);
						timer = 1;
						break;
					}
					timer = 1;
					push(s, infix[i]);
				}
				else if (priority(infix[i]) > priority((*s)->info)) {
					push(s, infix[i]);
					timer = 1;
				}
				else {
					if (infix[i] == ')')
						c = 1;
					que[j++] = ' ';
					que[j++] = pop(s);

				}
			} while (!timer);//TIMER FOR else part if infix[i]=')' has to pop all of them!!
		}
		else {
			while ((*s)->info != '(') {
				que[j++] = ' ';
				que[j++] = pop(s);
			}
			que[j++] = ' ';
			// que[j++]=pop(s);
			pop(s);
		}
		i++;
	}
	i = 0;
	if ((*s)->info != NULL) {
		while ((*s)->next != NULL) {
			// when input is finish !!
			//printf(" %c ",pop(s));
			que[j++] = ' ';
			que[j++] = pop(s);
		}	
	}
	que[j++] = pop(s);
	que[++j] = '\0';
}
int postfix_evoliton(char *x) {
	evoptr list = NULL;
	int i = 0;
	for (i = 0; x[i] != '\0'; i++) {
		if (x[i] == ' ') {
			//i++;
			continue;//for understand when is space its two digit number goto next one;
		}
		else if (x[i] == '\n')//if not use this one not read to last space. ask to Ferhun Hoca....
			continue;
		else if (isdigit(x[i])) {
			int number = 0;
			while (isdigit(x[i])) {
				number = number * 10 + (int)x[i] - '0';//this one for multiple number;
				i++;
			}
			i--;
			push_evo(&list, number);
		}
		else {
			int value1 = pop_evo(&list);
			int value2 = pop_evo(&list);
			switch (x[i]) {
			case '+':
				push_evo(&list, value2 + value1);
				break;
			case '-':
				push_evo(&list, value2 - value1);
				break;
			case '*':
				push_evo(&list, value2*value1);
				break;
			case '/':
				push_evo(&list, value2 / value1);
				break;
			case '$':
				push_evo(&list, pow(value2, value1));
				break;
			}
		}
	}
	return pop_evo(&list);
}
void menu() {
	int i = 1;
	while (i) {
		system("cls");
		printf("--------------------------INFIX-TO-POSTFIX & POSTFIX EVALUATION SYSTEM--------------------------------------------------\n\n\n\n");
		Nodeptr list;
		list = NULL;
		char infix[80];
		printf("enter your infix expression = \t");
		fgets(infix, 80, stdin);
		infix_to_postfix(&list, infix);
		printf("infix to postfix  = %s", que);
		printf(" Evaluation of postfix = %d", postfix_evoliton(que));
		printf("\n press 0 for finish  or any number for continue.... ");
		scanf_s("%d", &i);
		fflush(stdin);
		list = NULL;
	}
	printf("Good Bye !!!!!");
	exit(1);
}

int main() {
	menu();	//cal menu function
/*	printf("--------------------------INFIX-TO-POSTFIX & POSTFIX EVALUATION SYSTEM--------------------------------------------------\n\n\n\n");
	Nodeptr list;
	list = NULL;
	char infix[50];
	printf("enter your infix expression = \t");
	fgets(infix, 50, stdin);
	infix_to_postfix(&list, infix);
	printf("infix to postfix  = %s", que);
	
	printf(" Evaluation of postfix = %d", postfix_evoliton(que));
	*/
	system("pause");
	return 0;
}