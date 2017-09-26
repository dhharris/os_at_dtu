typedef struct {
        int *contents;
        int top;
        int size;
} Stack;

void spush(Stack *s, int val);
int spop(Stack *s);
int sisempty(Stack *s);
void sinit(Stack *s, int size);
void sdestroy(Stack *s);
