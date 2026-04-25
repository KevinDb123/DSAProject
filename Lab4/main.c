#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_input_line(const char *line, int values[], int max_count)
{
    int count = 0;
    const char *cursor = line;
    char *endptr;
    long value;

    while (*cursor != '\0')
    {
        while (*cursor == ' ' || *cursor == '\t' || *cursor == '\n' || *cursor == '\r')
        {
            ++cursor;
        }

        if (*cursor == '\0')
        {
            break;
        }

        value = strtol(cursor, &endptr, 10);
        if (cursor == endptr)
        {
            return -1;
        }

        if (count >= max_count)
        {
            return -2;
        }

        values[count++] = (int)value;
        cursor = endptr;
    }

    return count;
}

static void print_menu_tip(void)
{
    printf("===== Lab4 AVL Tree =====\n");
    printf("Enter integers separated by spaces.\n");
    printf("Example: 10 20 30 40 50 25\n");
    printf("Duplicate values will be ignored.\n");
    printf("Input: ");
}

int main(void)
{
    char line[1024];
    int values[MAX_INPUT_COUNT];
    int count;
    int i;
    AVLNode *root = NULL;
    int inserted_count = 0;

    print_menu_tip();

    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        printf("Input failed.\n");
        return 1;
    }

    count = parse_input_line(line, values, MAX_INPUT_COUNT);
    if (count == -1)
    {
        printf("Input contains non-integer data.\n");
        return 1;
    }
    if (count == -2)
    {
        printf("Too many numbers. At most %d integers are supported.\n", MAX_INPUT_COUNT);
        return 1;
    }
    if (count == 0)
    {
        printf("No valid data was entered.\n");
        return 1;
    }

    for (i = 0; i < count; ++i)
    {
        root = avl_insert(root, values[i]);
        if (root != NULL)
        {
            ++inserted_count;
        }
    }

    if (inserted_count == 0)
    {
        printf("\nAVL insert is not implemented yet.\n");
        printf("Please complete the TODOs in avl.c and try again.\n");
        return 0;
    }

    printf("\nAVL tree (sideways display):\n");
    avl_print_sideways(root, 0);

    printf("\nPreorder: ");
    avl_preorder(root);
    printf("\n");

    printf("Inorder: ");
    avl_inorder(root);
    printf("\n");

    printf("Postorder: ");
    avl_postorder(root);
    printf("\n");

    avl_destroy(root);
    return 0;
}
