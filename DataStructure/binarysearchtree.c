#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    char *key;
    struct node *left;
    struct node *right;
} treenode;

treenode *CreateNode()
{
    treenode *node = (treenode *)malloc(sizeof(treenode));
    node->left = NULL;
    node->right = NULL;
    return node;
}

char *GetKey(treenode *tn)
{
    return tn->key;
}

void SetKey(treenode *tn, char *key)
{
    tn->key = (char *)malloc(strlen(key) + 1);
    strcpy(tn->key, key);
}

treenode *GetLeftSucc(treenode *tn)
{
    return tn->left;
}

treenode *GetRightSucc(treenode *tn)
{
    return tn->right;
}

void CreateLeftSucc(treenode *p, treenode *p_succ)
{
    if (p->left != NULL)
    {
        free(p->left);
    }
    p->left = p_succ;
}

void CreateRightSucc(treenode *p, treenode *p_succ)
{
    if (p->right != NULL)
    {
        free(p->right);
    }
    p->right = p_succ;
}

void ReplaceLeftSucc(treenode *main, treenode *sub)
{
    main->left = sub;
}

void ReplaceRightSucc(treenode *main, treenode *sub)
{
    main->right = sub;
}

void InsertNode(treenode **p, char *key)
{

    treenode *pNode = NULL; //parent node
    treenode *current = *p;
    treenode *newNode = NULL;

    while (current != NULL)
    {
        if (strcmp(key, GetKey(current)) == 0)
        {
            printf("\nThere is already same key in tree!\n");
            return;
        }

        pNode = current;

        if (strcmp(GetKey(current), key) > 0)
        {
            current = GetLeftSucc(current);
        }
        else
        {
            current = GetRightSucc(current);
        }
    }

    newNode = CreateNode();
    SetKey(newNode, key);

    if (pNode != NULL)
    {
        if (strcmp(key, GetKey(pNode)) < 0)
        {
            CreateLeftSucc(pNode, newNode);
        }
        else
        {
            CreateRightSucc(pNode, newNode);
        }
    }
    else
    {
        *p = newNode;
    }
}

treenode *SearchNode(treenode *tn, char *key)
{
    treenode *p;
    p = tn;
    while (p != NULL)
    {
        if (strcmp(key, p->key) < 0)
        {
            p = p->left;
        }
        else if (strcmp(key, p->key) == 0)
        {
            printf("\nThere is key %s in this tree!\n", key);
            return p;
        }
        else
        {
            p = p->right;
        }
    }
    if (p == NULL)
    {
        printf("\nThere is no key %s in this tree!\n", key);
        return p;
    }
}

treenode *DeleteLeftSucc(treenode *tn)
{
    treenode *dnode = NULL;

    if (tn != NULL)
    {
        dnode = tn->left;
        tn->left = NULL;
    }
    return dnode;
}

treenode *DeleteRightSucc(treenode *tn)
{
    treenode *dnode = NULL;

    if (tn != NULL)
    {
        dnode = tn->right;
        tn->right = NULL;
    }
    return dnode;
}

treenode *DeleteNode(treenode **p, char *key)
{
    treenode *vroot = CreateNode();
    treenode *pnode = vroot; //parent
    treenode *cnode = *p;    //curent
    treenode *dnode;         //delete

    ReplaceRightSucc(vroot, *p);

    while ((cnode != NULL) && (strcmp(GetKey(cnode), key) != 0))
    {
        pnode = cnode;

        if (strcmp(key, GetKey(cnode)) < 0)
            cnode = GetLeftSucc(cnode);
        else
            cnode = GetRightSucc(cnode);
    }

    if (cnode == NULL)
    { //there are nothing to delete
        printf("there is no key %s in this tree\n", key);
        return NULL;
    }

    dnode = cnode;

    if (GetLeftSucc(dnode) == NULL && GetRightSucc(dnode) == NULL)
    {
        if (GetLeftSucc(pnode) == dnode)
            DeleteLeftSucc(pnode);
        else
            DeleteRightSucc(pnode);
    }

    else if (GetLeftSucc(dnode) == NULL || GetRightSucc(dnode) == NULL)
    {
        treenode *d_succnode; // succnode of delete node

        if (GetLeftSucc(dnode) != NULL)
            d_succnode = GetLeftSucc(dnode);
        else
            d_succnode = GetRightSucc(dnode);

        if (GetLeftSucc(pnode) == d_succnode)
            ReplaceLeftSucc(pnode, d_succnode);
        else
            ReplaceRightSucc(pnode, d_succnode);
    }

    else
    {
        treenode *mnode = GetRightSucc(dnode); // mininum node
        treenode *p_mnode = dnode;             // parent of mininum node
        char *delKey;

        while (GetLeftSucc(mnode) != NULL)
        {
            p_mnode = mnode;
            mnode = GetLeftSucc(mnode);
        }

        delKey = GetKey(dnode);
        SetKey(dnode, GetKey(mnode));

        if (GetLeftSucc(p_mnode) == mnode)
            ReplaceLeftSucc(p_mnode, GetRightSucc(mnode));
        else
            ReplaceRightSucc(p_mnode, GetRightSucc(mnode));

        dnode = mnode;
        SetKey(dnode, delKey);
    }

    if (GetRightSucc(vroot) != *p)
        *p = GetRightSucc(vroot);

    free(vroot);
    return dnode;
}

void ShowTree(treenode *node, int level)

{
    int i, n;
    if (node)
    {
        for (i = 0; i < level - 1; i++)
            printf(" ");
        if (level)
            printf("----");
        printf("%s\n", node->key);
        if ((node->left == NULL && node->right == NULL))
            return;
        ShowTree(node->left, level + 1);
        ShowTree(node->right, level + 1);
    }
    else
    {
        for (n = 0; n < level - 1; n++)
            printf(" ");
        if (level)
            printf("----[null]\n");
    }
}

int main(int argc, char const *argv[])
{
    treenode *root = NULL;
    char menu;
    char *key = (char *)malloc(sizeof(char) * 10);

    do
    {
        printf("1.I 2.S 3.D 4.Q\n");
        scanf("%c", &menu);

        if (menu == 'Q')
            break;
        scanf("%s", key);
        getchar();
        if (menu == 'I')
        {
            printf("Let’s insert new Key %s!\n", key);
            InsertNode(&root, key);
            ShowTree(root, 0);
            printf("\n");
        }
        else if (menu == 'S')
        {
            printf("Let’s search Key %s!\n", key);
            SearchNode(root, key);
            ShowTree(root, 0);
            printf("\n");
        }
        else if (menu == 'D')
        {
            printf("Let’s delete Key %s!\n", key);
            DeleteNode(&root, key);
            ShowTree(root, 0);
            printf("\n");
        }
        else if (menu == 'Q')
        {
            break;
        }

    } while (menu != 'Q');

    return 0;
}
