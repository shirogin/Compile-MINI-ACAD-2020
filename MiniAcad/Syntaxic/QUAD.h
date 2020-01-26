typedef struct qdr{
    char *oper;
    char *op1;
    char *op2;
    char *res;

    struct qdr *next;
}qdr;

int len_qdr(qdr *head)
{
    int count = 0;
    qdr *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void push_qdr(qdr **head, char oper[], char op1[], char op2[], char res[])
{
    qdr *new_node = (qdr *)malloc(sizeof(qdr));
    qdr *last = *head;

    new_node->oper = adapt(oper);
    new_node->op1 = adapt(op1);
    new_node->op2 = adapt(op2);
    new_node->res = adapt(res);

    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}
void append_qdr(qdr **head, char oper[], char op1[], char op2[], char res[])
{
    qdr *new_node = (qdr *)malloc(sizeof(qdr));
    qdr *last = *head;

    new_node->oper = adapt(oper);
    new_node->op1 = adapt(op1);
    new_node->op2 = adapt(op2);
    new_node->res = adapt(res);

    new_node->next = *head;
    *head = new_node;
}

qdr* getNth_qdr(qdr *head, int position)
{
    if (position > len_qdr(head) || position < 0){
        printf("Qdr out of range\n");
        return NULL;
    }
    
    qdr *current = head;
    while(current != NULL && position--)
        current = current->next;
        
    return current;
}

void print_qdr(qdr *head)
{
    qdr *current = head;
    int i=1;
    while(current != NULL){
        printf("%d- (%s, %s, %s, %s) \n", i, current->oper, current->op1, current->op2, current->res);
        current = current->next;
        i++;
    }
}