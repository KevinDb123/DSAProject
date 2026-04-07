#ifndef RELATION_TREE_H
#define RELATION_TREE_H

#include "TreeNode.h"

// 关系树：包含根节点指针和下一个可分配节点编号。
typedef struct RelationTree {
    TreeNode* root;
    int next_id;
} RelationTree;

void Init(RelationTree* tree, const char* root_name);
void Destroy(RelationTree* tree);

int GetRootId(const RelationTree* tree);
void PrintTree(const RelationTree* tree);

int AddNode(RelationTree* tree, const char* parent_name, const char* name, NodeType type);
int DeleteNode(RelationTree* tree, const char* name);
int PrintPathToLeaf(RelationTree* tree, const char* name);

#endif
