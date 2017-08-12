#include <stdio.h>
#include <stdlib.h>
#include "ticker.h"
#include <string.h>

int main(int argc, char ** argv)
{
	FILE *fp;
	fp = fopen(argv[1], "r");
	if(fp){
		printf("File opened\n");
		fclose(fp);
	}
	FILE *fp1;
	fp1 = fopen(argv[1], "r");
	file_parse(fp1);
	//inorder(root);
	fclose(fp1);
	return(0);
}

void file_parse(FILE *fp)
{
	char symbol[6], name[64], price_change[10];
	double price;
//	int ret;
	struct company *comp = NULL;
	struct tree *root = NULL;
	struct tree *current = NULL;
	struct tree *root_by_price = NULL;
//	struct tree *head = NULL;
	while(fscanf(fp, "%s %lf", symbol, &price) != EOF && fgets(name, 64, fp)){

		//fscanf(fp, "%s %lf %[^\n]", symbol, &dollar, name);

		//malloc for company
		comp  = stock_create(symbol, name, price);
//		head = init_tree(comp);
		
//		printf("This is stock\n");
//		printf("%s %lu %s\n", head->data->symbol, head->data->cents, head->data->name);
		if(root == NULL){
			root_by_price = current = root = init_tree(comp);
			//printf("this is root if statement\n");
		}
//		printf("This is root\n");
//		printf("%s %lu %s\n", root->data->symbol, root->data->cents, root->data->name);
		//malloc for tree
		//insert into tree
		//struct tree *head = NULL;
		//struct tree *t = NULL
		tree_insert(root, comp); 
		//printf("This is tree insert test\n");
		//printf("%s %lu %s\n", head->data->symbol, head->data->cents, head->data->name);
		//printf("This is test statement\n");
		//printf("RET = %d\n", ret);
		//printf(" SYMBOL: %s DOLLAR: %lf  NAME: %s\n", symbol, price, name); 

	}
	inorder(root);
//	while(fgets(buffer, 100, stdin)){
//		sscanf(buffer, "%s %s", symbol, price_change);
//	}
//	printf("last symbol and price_change  %s %s\n", symbol, price_change);
	
	search_and_update(root, price_change, symbol);
	
//	added lines of code
	tree_insert_by_price(root_by_price, current, root);
	printf("\n");
	inorder(root_by_price);
	//fclose(fp);
}


int conversion(char price[])
{
	char buffer[12];
	int buffer_i, i;
	int length;
	buffer_i = 0;
	length = strlen(price);
	for(i = 0; i <= length; i++){
		if(price[i] >= '0' && price[i] <= '9'){
			buffer[buffer_i++] = price[i];
		}
	}
	buffer[buffer_i] = '\0';
	int num;
	num = atoi(buffer);
	return(num);
}
void search_and_update(struct tree *root, char price_change[10], char symbol[6])
{
	char operand;
	int price;
	char buffer[20];
	while(fgets(buffer, 100, stdin)){
		sscanf(buffer, "%s %s", symbol, price_change);
		if(price_change[0] == '+' || price_change[0] == '-'){
			operand = price_change[0];
			printf("Operand %c\n", operand);
			//price = conversion(price_change[10]);
			//printf("%d\n", price);
		}
		price = conversion(price_change);
		price *= 100;
		printf("price %d \n", price);
		tree_search(root, symbol, price);
	}
	//price = conversion(price_change);
	//printf("price %d", price);
	//printf("%s %s\n", symbol, price_change);
	//int length = strlen(price_change);
	//buffer[0] = '\0';
	//int buffer_i = 0;
	//for(int i = 0; i <= length; i++){
	//	if(price_change[i] >= '0' &&  price_change[i] <= '9'){
	//		buffer[buffer_i++] = price_change[i];
	//		printf("buffer index value %c\n", buffer[i]);
	//	}
	//}
	//buffer[buffer_i] = '\0';
	//int num;
	//num = atoi(buffer);
	//printf("This is number buffer %d\n", num);
	//if(price_change[0] == '+')
	//	printf("%d\n", operand);
	//printf("String length of price_change is %d\n", strlen(price_change));
}
struct tree *copy_init_tree(struct tree *current)
{
	struct tree *t = NULL;
	t = malloc(sizeof(t));
	t->left = t->right  = NULL;
	t -> data = current->data;
	return(t);
}

struct tree *init_tree(struct company *company)
{
	struct tree *t = NULL;
	//t -> data = company;
	t = malloc(sizeof(t));
	t->left = t->right = NULL;
	t -> data = company;
	return(t);
}

struct company *stock_create(char *symbol, char *name, double price)
{
	struct company  *new_stock = malloc(sizeof(*new_stock));
	if(!new_stock){
		return NULL;
	}

	new_stock->name = strdup(name);
	if(!new_stock->name){
		free(new_stock);
		return NULL;
	}

	strncpy(new_stock->symbol, symbol, sizeof(new_stock->symbol)-1);
	new_stock->symbol[sizeof(new_stock->symbol)-1] = '\0';

	new_stock->cents = 100 * price;
	return new_stock;
}


void tree_search(struct tree *root, char word[], int price)
{
	int value;
	value = strcasecmp(word, root->data->symbol);
	if(value < 0){
		if(root->left != NULL){
			tree_search(root->left, word, price);
		}else{
			printf("word does not exist\n");
			return;
		}
	}else if(value > 0){
		if(root->right != NULL){
			tree_search(root->right, word, price);
		}else{
			printf("word does not exist\n");
			return;
		}
	}else{
		printf("before update %lu\n", root->data->cents);
		printf("This is price %d\n", price);
		root->data->cents = root->data->cents + price;
		printf("updated cents %lu", root->data->cents);
		
	}
}

void tranverse_tree(struct tree *root, struct tree *root_by_price, struct tree *current)
{
	if(current !=  NULL){
		tranverse_tree(root, root_by_price, current->left);
		tree_insert_by_price(root_by_price, current, root);
		tranverse_tree(root, root_by_price, current->right);
	}
}


void tree_insert_by_price(struct tree * root_by_price, struct tree *current, struct tree *root)
{
		
	if(root_by_price->data->cents < current->data->cents){
		if (root_by_price->left != NULL){
			tree_insert_by_price(root_by_price->left, current, root);
		}else{
			root_by_price->left = copy_init_tree(current);
		}
	}
	else if(root_by_price->data->cents > root->data->cents){
		if (root_by_price->right != NULL){
			tree_insert_by_price(root_by_price->left,current, root);
		}else{
			root_by_price->left = copy_init_tree(root);
		}
	}else{
		;
	}
}
//*/
void tree_insert(struct tree *root, struct company *compan)
{
	int value;
	value = strcasecmp(compan->symbol, root->data->symbol);
	if(value < 0){
		if(root->left != NULL){
			tree_insert(root->left, compan);
		}else{
			root->left = init_tree(compan);
//			printf("Print root %s and root->left %s\n", root->data->symbol, root->left->data->symbol);
		}
	}else if (value > 0){
		if(root->right != NULL) {
			tree_insert(root->right, compan);
		}else{
			root->right = init_tree(compan);
//			printf("Print root %s and root->right %s\n", root->data->symbol, root->right->data->symbol);
			//root->right;
		}
	}else{
		return;
	}
	
}

void inorder(struct tree *root)
{
	//printf("entering the print statement\n");
	if(root != NULL)
	{
		inorder(root->left);
		printf("%s %lu %s", root->data->symbol, root->data->cents, root->data->name);
		//inorder(root->left);
		inorder(root->right);
	}
	//printf("\n")
	//printf("%s %lu %s \n", root->data->symbol, root->data->cents, root->data->name);
}


