#ifndef TREE_NODE_H
#define TREE_NODE_H

#define NAME_LEN 64
#define MAX_SIZE 100

typedef enum NodeType {
    NODE_FACULTY = 1,
    NODE_COLLEGE = 2,
    NODE_DEPARTMENT = 3,
    NODE_LEADER = 4,
    NODE_GENERIC = 5
} NodeType;

// 组织结构树中的节点定义。
typedef struct TreeNode {
    // 节点唯一编号。
    int id;
    // 节点名称。
    char name[NAME_LEN];
    // 节点类型。
    NodeType type;
    // 父节点指针（仅根节点为 NULL）。
    struct TreeNode* parent;

    // 固定大小的子节点数组。
    struct TreeNode* children[MAX_SIZE];
    // 当前子节点数量。
    int child_count;
} TreeNode;

const char* NodeTypeToString(NodeType type);

#endif
