typedef struct {
        int *contents;
        int top;
        int size;
} Stack;

void spush(Stack *s, int val);
int spop(Stack *s);
int sisempty(Stack *s);
Stack *sinit();
void sdestroy(Stack *s);
