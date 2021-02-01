#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

int N, S;

typedef struct __node
{
    char data[16];
    struct __node *next;
} Node;

Node *head_ptr = NULL;

int push(Node *new_node, Node *barrier[], int stack_n, int nums[])
{
    int total = nums[0];
    int i;
    for (i = 1; i < N; i++)
        total += nums[i];

    if (total >= S)
        return -1;

    ++nums[stack_n - 1];
    if (head_ptr == NULL)
    {
        new_node->next = NULL;
        head_ptr = barrier[0] = barrier[stack_n] = new_node;
    }
    else if (nums[stack_n - 1] != 1)
    {
        Node *next_node = barrier[stack_n];
        new_node->next = next_node->next;
        next_node->next = new_node;
        barrier[stack_n] = new_node;
    }
    else
    {
        int l;
        for (l = stack_n - 1; l >= 0; l--)
        {
            if (!l && barrier[l] == NULL)
                continue;

            if (!l)
            {
                new_node->next = head_ptr;
                head_ptr = new_node;
                barrier[0] = new_node;
            }
            else
            {
                Node *t = barrier[l];
                new_node->next = (stack_n == N) ? NULL : t->next;
                t->next = new_node;
            }
            barrier[stack_n] = new_node;
            return 0;
        }
    }
    return 0;
}

int pop(Node *barrier[], int stack_n, int nums[])
{
    Node *delNode = head_ptr;
    int size = stack_n - 1;
    if (nums[stack_n - 1] <= 0)
        return -1;

    if (nums[stack_n - 1] >= 2)
    {
        int i = 0;
        for (i = size; i >= 0; i--)
        {
            if (i > 0 && barrier[i] == NULL)
                continue;

            int count = 0;
            Node *prev;
            if (!i)
            {
                prev = head_ptr;
                while (prev->next != NULL && count++ < nums[size] - 2)
                    prev = prev->next;
            }
            else
            {
                prev = barrier[i];
                while (prev->next != NULL && count++ < nums[size] - 1)
                    prev = prev->next;
            }
            --nums[size];
            delNode = barrier[stack_n];
            prev->next = delNode->next;
            barrier[stack_n] = prev;
            free(delNode);
            return 0;
        }
    }
    else
    {
        int l;
        for (l = size; l >= 0; l--)
        {
            if (l > 0 && barrier[l] == NULL)
                continue;

            if (l <= 0)
            {
                delNode = barrier[stack_n];
                head_ptr = barrier[stack_n]->next;
                barrier[0] = head_ptr;
            }
            else
            {
                Node *prev = barrier[l];
                delNode = barrier[stack_n];
                prev->next = delNode->next;
            }
            --nums[size];
            barrier[stack_n] = NULL;
            free(delNode);
            return 0;
        }
    }
    return 0;
}

int get_rand(int from, int to)
{
    return (rand() % (to - from + 1)) + from;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Program expected 2 arguments, but got %d arguments", argc - 1);
        exit(0);
    }

    N = atoi(argv[1]);
    S = atoi(argv[2]);
    srand(time(NULL));

    head_ptr = NULL;
    Node *barrier[N + 1];
    int i = 0;
    for (i = 0; i <= N; i++)
        barrier[i] = NULL;

    int nums[N];
    memset(nums, 0, sizeof(nums));
    int l = 0;
    for (l = 0; l < 3 * S; ++l)
    {
        int rand_stack_n = get_rand(1, N);
        printf("-------------[%d]-------------\n", l + 1);
        if (get_rand(1, 2) == 1)
        {
            printf("operation: push(st%d_%d)", rand_stack_n, nums[rand_stack_n - 1] + 1);
            Node *new = (Node *)malloc(sizeof(Node));
            sprintf(new->data, "st%d_%d", rand_stack_n, nums[rand_stack_n - 1] + 1);
            new->next = NULL;
            char result = push(new, barrier, rand_stack_n, nums);
            printf("result: ");
            printf(result == 0 ? "ok" : "stack_overflow");
        }
        else
        {
            printf("operation: pop(st%d)\n", rand_stack_n);
            char result = pop(barrier, rand_stack_n, nums);
            printf("result: ");
            printf(result == 0 ? "ok" : "stack_underflow");
        }
        printf("\n");

        Node *cur = head_ptr;
        while (cur)
        {
            printf("Node(%s) -> ", cur->data);
            cur = cur->next;
        }
        printf("\n");
    }

    return 0;
}