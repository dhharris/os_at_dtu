typedef struct node {
        int value;
        struct node *next;
} node_t;


typedef struct {
        node_t *head, *tail;
        int counter;
} Collection;

void clear_list(node_t *head);
void print_list(node_t *head);
void reset(Collection *col);
void eval_a(Collection *col);
void eval_b(Collection *col);
void eval_c(Collection *col);

