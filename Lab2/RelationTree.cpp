#include "RelationTree.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::endl;

// 创建一个新树节点并初始化其字段。
static TreeNode* CreateNode(int id, const char* name, NodeType type, TreeNode* parent) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) return NULL;

    node->id = id;
    node->type = type;
    node->parent = parent;
    node->child_count = 0;

    strncpy(node->name, name, NAME_LEN - 1);
    node->name[NAME_LEN - 1] = '\0';
    return node;
}

// 递归释放以 node 为根的整棵子树。
static void FreeSubtree(TreeNode* node) {
    int i;
    if (node == NULL) return;
    for (i = 0; i < node->child_count; ++i) {
        FreeSubtree(node->children[i]);
    }
    free(node);
}

// 以树形缩进格式深度优先打印当前节点及其后代。
static void PrintDfs(const TreeNode* node, const char* prefix, int is_last) {
    int i;
    char next_prefix[256];

    cout << prefix << (is_last ? "`-- " : "|-- ")
         << "[" << node->id << "] " << node->name << " (" << NodeTypeToString(node->type) << ")" << endl;

    snprintf(next_prefix, sizeof(next_prefix), "%s%s", prefix, is_last ? "    " : "|   ");
    for (i = 0; i < node->child_count; ++i) {
        PrintDfs(node->children[i], next_prefix, (i == node->child_count - 1));
    }
}

// 初始化关系树并创建根节点。
void Init(RelationTree* tree, const char* root_name) {
    tree->next_id = 1;
    tree->root = CreateNode(tree->next_id++, root_name, NODE_FACULTY, NULL);
}

// 销毁整棵关系树并重置状态。
void Destroy(RelationTree* tree) {
    FreeSubtree(tree->root);
    tree->root = NULL;
    tree->next_id = 1;
}

// 返回根节点 id，不存在时返回 -1。
int GetRootId(const RelationTree* tree) {
    if (tree == NULL || tree->root == NULL) return -1;
    return tree->root->id;
}

// 打印整棵树的结构。
void PrintTree(const RelationTree* tree) {
    int i;

    if (tree == NULL || tree->root == NULL) return;

    cout << "[" << tree->root->id << "] " << tree->root->name
         << " (" << NodeTypeToString(tree->root->type) << ")" << endl;
    for (i = 0; i < tree->root->child_count; ++i) {
        PrintDfs(tree->root->children[i], "", (i == tree->root->child_count - 1));
    }
}

// 在指定父节点下添加一个新子节点。
int AddNode(RelationTree* tree, const char* parent_name, const char* name, NodeType type) {
    TreeNode* parent = NULL;  // 查找到的父节点指针，未找到时保持 NULL。
    TreeNode* nodes[4096];  // 遍历整棵树时用的临时节点数组。
    TreeNode* child;  // 新创建并准备挂接到 parent 下的子节点。

    if (tree == NULL || tree->root == NULL || parent_name == NULL || name == NULL) return -1;

    // TODO：遍历整棵树，按 parent_name 查找父节点，找到后把该节点赋给 parent。
    

    if (parent == NULL) return -1;
    if (parent->child_count >= MAX_SIZE) return -1;

    child = CreateNode(tree->next_id++, name, type, parent);
    if (child == NULL) return -1;

    // 挂接到父节点孩子数组，并返回新节点 id。
    parent->children[parent->child_count++] = child;
    return child->id;
}

// 按名称删除节点（不允许删除根节点）。
int DeleteNode(RelationTree* tree, const char* name) {
    TreeNode* target = NULL;  // 要删除的目标节点指针，未找到时为 NULL。
    TreeNode* nodes[4096];  // 遍历整棵树时用的临时节点数组。

    if (tree == NULL || tree->root == NULL || name == NULL) return 0;

    // TODO：遍历整棵树，按 name 查找目标节点，找到后把该节点赋给 target。
    

    // 目标不存在、目标为根、父指针异常时删除失败。
    if (target == NULL) return 0;
    if (target == tree->root) return 0;
    if (target->parent == NULL) return 0;

    // TODO：在 target 的父节点 children 数组中定位 target，释放 target 子树并将后续元素前移，最后 child_count-- 并返回 1。
    

    return 0;
}

// 输出从根到指定叶子节点的路径。
int PrintPathToLeaf(RelationTree* tree, const char* name) {
    TreeNode* target = NULL;  // 查找到的目标节点。
    TreeNode* nodes[4096];  // 查找目标节点时使用的临时遍历数组。
    TreeNode* path[256];  // 存放“目标到根”路径的临时数组，输出时需要逆序。

    if (tree == NULL || tree->root == NULL || name == NULL) return 0;

    // TODO：遍历整棵树，按 name 查找目标节点，找到后把该节点赋给 target。
    

    // 目标不存在或目标不是叶子节点则失败。
    if (target == NULL) return 0;
    if (target->child_count != 0) return 0;

    // TODO：从 target 沿 parent 回溯到根，依次写入 path 数组并累计 len。
    
    
    if (target != NULL) return 0;

    // TODO：将 path 逆序输出为“根 -> ... -> 叶子”的格式。
    
    
    cout << endl;
    return 1;
}
