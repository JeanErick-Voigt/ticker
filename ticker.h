
struct company {
	char symbol[6];
	size_t cents;
	char *name;
};

struct tree { 
	struct company *data;
	struct tree *left, *right;
};

void file_parse(FILE *fp);
struct tree *init_tree(struct company *company);
struct company *stock_create(char* symbol, char *name, double price);
void tree_insert(struct tree *root, struct company *compan);
void tree_search(struct tree *root, char word[], int price);
void inorder(struct tree *root);
void search_and_update(struct tree *root, char price_change[10], char symbol[6]);
int conversion(char price[]);