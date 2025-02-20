#include "avl_tree.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/*
 * print the tree in in-order traversal
 */
void in_order(struct Node *root)
{
    if (!root)
        return;
    in_order(root->left);
    printf("%p ", root->address);
    in_order(root->right);
}

/*
 * print the tree in visualizable tree structure
 */
void printTree(struct Node *root, int space) {
    const int COUNT = 10;
    if (root == NULL)
        return;

    space += COUNT;
    printTree(root->right, space);
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%p\n", root->address);
    printTree(root->left, space);
}

/*
 * Return height of the current node, where leaf node have height 1, root have max height
 */
static int get_height(struct Node *root)
{
    if (!root) return 0;
    return root->height;
}

/*
 * Perform right rotation of the current tree with following steps
 * 1. use root->left node to be new root
 * 2. orig root become new root (root->left) right child
 * 3. the right subtree of new root (root->left) become the left subtree of orig root left subtree
 */
static struct Node *right_rotate(struct Node *root)
{
    struct Node *new_root = root->left;
    struct Node *left_tree = new_root->right;

    new_root->right = root;
    root->left = left_tree;

    root->height = MAX(get_height(root->left), get_height(root->right)) + 1;
    new_root->height = MAX(get_height(new_root->left), get_height(new_root->right)) + 1;
    return new_root;
}

/*
 * Perform left rotation of the current tree with following steps
 * 1. use root->right node to be new root
 * 2. orig root become new root (root->right) left child
 * 3. the left subtree of new root (root->right) become the right subtree of orig root right subtree
 */
static struct Node *left_rotate(struct Node *root)
{
    struct Node *new_root = root->right;
    struct Node *right_tree = new_root->left;

    //Rotate right to be root, orig root to be the left child, orig
    new_root->left = root;
    root->right = right_tree;

    root->height = MAX(get_height(root->left), get_height(root->right)) + 1;
    new_root->height = MAX(get_height(new_root->left), get_height(new_root->right)) + 1;
    return new_root;
}

/*
 * Create and insert a node to the tree with recursion and balance
 * Balance situations:
 * LL: right rotate the tree
 * RR: left rotate the tree
 * LR: left rotate the left child and then right rotate the tree
 * RL: right rotate the right child and then left rotate the tree
 */
struct Node *avl_insert(struct Node *root, void *address)
{
    if (root == NULL)
        return newNode(address);

    if (address < root->address)
        root->left = avl_insert(root->left, address);
    else if (address > root->address)
        root->right = avl_insert(root->right, address);
    else
        return root;

    //update height
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    root->height = 1 + MAX(left_height, right_height);
    int height_diff = left_height - right_height;

    // LL
    if (height_diff > 1 && address < root->left->address)
        return right_rotate(root);

    // RR
    if (height_diff < -1 && address > root->right->address)
        return left_rotate(root);

    // LR
    if (height_diff > 1 && address > root->left->address) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // RL
    if (height_diff < -1 && address < root->right->address) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

static int get_height_diff(struct Node *root)
{
    if (!root)
        return 0;
    return get_height(root->left) - get_height(root->right);
}

/*
 * Find and delete a node in the tree with recursion and balance
 * Delete situations:
 * leaf node or one child node: delete the node
 * two children node: switch value (void *address) with smallest node in right tree, delete the smallest node
 * Balance situations:
 * LL: right rotate the tree
 * RR: left rotate the tree
 * LR: left rotate the left child and then right rotate the tree
 * RL: right rotate the right child and then left rotate the tree
 */
struct Node *avl_delete(struct Node *root, void *address)
{
    if (!root)
        return root;

    if (address < root->address)
        root->left = avl_delete(root->left, address);
    else if (address > root->address)
        root->right = avl_delete(root->right, address);
    else {
        // delete node
        if ((root->left == NULL) || (root->right == NULL)) { // leaf node or node with only one child
            struct Node *temp = root->left ? root->left : root->right;

            if (!temp) { // leaf node
                temp = root;
                root = NULL;
            } else // one child node
                *root = *temp;

            free(temp);
        } else { // two children
            //get min value node in right tree, switch the value and delete the node
            struct Node *temp = root->right;
            while (temp->left != NULL)
                    temp = temp->left;
            root->address = temp->address;
            root->right = avl_delete(root->right, temp->address);
        }
    }

    if (!root)
        return root;

    //update height
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    root->height = 1 + MAX(left_height, right_height);
    int height_diff = left_height - right_height;

    // LL
    if (height_diff > 1 && get_height_diff(root->left) >= 0)
        return right_rotate(root);

    // RR
    if (height_diff < -1 && get_height_diff(root->right) <= 0)
        return left_rotate(root);

    // LR
    if (height_diff > 1 && get_height_diff(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // RL
    if (height_diff < -1 && get_height_diff(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

/*
 * Search for node contain given address, return null if not found
 */
struct Node *avl_search(struct Node *root, void *address)
{
   struct Node *floor_node = NULL;

    while (root) {
        if (root->address == address) {
            return root;
        } else if (root->address < address) {
            floor_node = root; // Potential floor address
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return floor_node;
}


