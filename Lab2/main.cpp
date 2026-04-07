#include <cstdio>
#include <cstring>
#include <iostream>

#include "RelationTree.h"

using std::cin;
using std::cout;
using std::endl;

// 构建实验用的初始组织结构树。
static int BuildInitialTree(RelationTree* tree) {
    // 构建四层结构：学部 -> 学院 -> 系 -> 老师。
    int college_info_id;
    int college_cs_id;
    int college_micro_id;
    int dep_electronic_id;
    int dep_auto_id;
    int dep_cs_id;
    int dep_software_id;
    int dep_micro_device_id;
    int dep_ic_design_id;

    if (tree == NULL || tree->root == NULL) return 0;

    college_info_id = AddNode(tree, "信智学部", "信院", NODE_COLLEGE);
    college_cs_id = AddNode(tree, "信智学部", "计科", NODE_COLLEGE);
    college_micro_id = AddNode(tree, "信智学部", "微电子", NODE_COLLEGE);
    if (college_info_id == -1 || college_cs_id == -1 || college_micro_id == -1) return 0;

    dep_electronic_id = AddNode(tree, "信院", "6系", NODE_DEPARTMENT);
    dep_auto_id = AddNode(tree, "信院", "10系", NODE_DEPARTMENT);
    dep_cs_id = AddNode(tree, "计科", "计算机系", NODE_DEPARTMENT);
    dep_software_id = AddNode(tree, "计科", "软件工程系", NODE_DEPARTMENT);
    dep_micro_device_id = AddNode(tree, "微电子", "微电子系", NODE_DEPARTMENT);
    dep_ic_design_id = AddNode(tree, "微电子", "集成电路系", NODE_DEPARTMENT);
    if (dep_electronic_id == -1 || dep_auto_id == -1 || dep_cs_id == -1 || dep_software_id == -1 ||
        dep_micro_device_id == -1 || dep_ic_design_id == -1) return 0;

    if (AddNode(tree, "6系", "王永", NODE_LEADER) == -1) return 0;
    if (AddNode(tree, "10系", "刘斌", NODE_LEADER) == -1) return 0;
    if (AddNode(tree, "计算机系", "李向阳", NODE_LEADER) == -1) return 0;

    return 1;
}

// 深度优先打印所有系节点的辅助函数。
static void PrintDepartmentsDfs(const TreeNode* node) {
    int i;
    if (node == NULL) return;

    if (node->type == NODE_DEPARTMENT && node->parent != NULL) {
        cout << "  系ID=" << node->id << "，名称=" << node->name << "，所属学院=" << node->parent->name << endl;
    }

    for (i = 0; i < node->child_count; ++i) {
        PrintDepartmentsDfs(node->children[i]);
    }
}

// 打印可挂载老师的所有系。
static void PrintDepartments(const RelationTree* tree) {
    if (tree == NULL || tree->root == NULL) return;
    cout << "可挂载老师的系如下：" << endl;
    PrintDepartmentsDfs(tree->root);
}

// 深度优先收集同名节点的辅助函数。
static void FindNodesByNameDfsLocal(TreeNode* node, const char* name, TreeNode** out_nodes, int max_out, int* count) {
    int i;

    if (node == NULL) return;

    if (strcmp(node->name, name) == 0) {
        if (*count < max_out) out_nodes[*count] = node;
        (*count)++;
    }

    for (i = 0; i < node->child_count; ++i) {
        FindNodesByNameDfsLocal(node->children[i], name, out_nodes, max_out, count);
    }
}

// 在整棵树中按名称查找节点。
static int FindNodesByNameLocal(RelationTree* tree, const char* name, TreeNode** out_nodes, int max_out) {
    int count = 0;

    if (tree == NULL || tree->root == NULL || name == NULL || out_nodes == NULL || max_out <= 0) return 0;
    FindNodesByNameDfsLocal(tree->root, name, out_nodes, max_out, &count);
    if (count > max_out) return max_out;
    return count;
}

// 按名称查找唯一节点；未找到或重名时返回 NULL。
static TreeNode* FindUniqueNodeByName(RelationTree* tree, const char* name) {
    TreeNode* result[4];
    int n;

    if (tree == NULL || name == NULL) return NULL;
    n = FindNodesByNameLocal(tree, name, result, 4);
    if (n != 1) return NULL;
    return result[0];
}

// 按“学院名+系名”查找对应系节点。
static TreeNode* FindDepartmentInCollege(RelationTree* tree, const char* college_name, const char* dept_name) {
    TreeNode* dept;
    TreeNode* college;

    college = FindUniqueNodeByName(tree, college_name);
    dept = FindUniqueNodeByName(tree, dept_name);
    if (college == NULL || dept == NULL) return NULL;
    if (college->type != NODE_COLLEGE || dept->type != NODE_DEPARTMENT) return NULL;
    if (dept->parent == NULL) return NULL;
    if (strcmp(dept->parent->name, college_name) != 0) return NULL;
    return dept;
}

// 按名称查找并打印从根到该节点的路径。
static void PrintNodeByName(RelationTree* tree, const char* name) {
    TreeNode* node = FindUniqueNodeByName(tree, name);
    TreeNode* path[256];
    int len = 0;
    int i;

    if (node == NULL) {
        cout << "未找到节点，或名称不唯一：" << name << endl;
        return;
    }

    while (node != NULL && len < 256) {
        path[len++] = node;
        node = node->parent;
    }

    if (node != NULL) {
        cout << "路径过长，输出失败。" << endl;
        return;
    }

    cout << "从根节点到目标节点的路径：";
    for (i = len - 1; i >= 0; --i) {
        cout << path[i]->name;
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

// 打印交互菜单。
static void PrintMenu(void) {
    cout << "\n===== Lab2 组织关系树菜单 =====" << endl;
    cout << "1. 打印当前整棵树" << endl;
    cout << "2. 添加节点（先选择层级 2/3/4）" << endl;
    cout << "3. 删除节点" << endl;
    cout << "4. 查找节点" << endl;
    cout << "0. 退出程序" << endl;
    cout << "请输入选项：";
}

// 程序入口：初始化树并处理菜单操作。
int main(void) {
    RelationTree tree;
    int op;

    Init(&tree, "信智学部");
    if (!BuildInitialTree(&tree)) {
        cout << "初始化组织关系树失败。" << endl;
        Destroy(&tree);
        return 1;
    }

    cout << "初始化完成：默认组织关系树已创建。" << endl;

    while (1) {
        PrintMenu();
        if (!(cin >> op)) {
            cout << "输入无效，程序结束。" << endl;
            break;
        }

        if (op == 0) {
            cout << "已退出程序。" << endl;
            break;
        } else if (op == 1) {
            PrintTree(&tree);
        } else if (op == 2) {
            int level;
            int new_id;
            char name[NAME_LEN];
            char college_name[NAME_LEN];
            char dept_name[NAME_LEN];
            TreeNode* college;
            TreeNode* dept;

            cout << "请选择要添加的层级（2=学院，3=系，4=老师）：";
            cin >> level;

            if (level == 2) {
                cout << "请输入学院名称（不要包含空格）：";
                cin >> name;
                new_id = AddNode(&tree, "信智学部", name, NODE_COLLEGE);
            } else if (level == 3) {
                cout << "请输入父学院名称（不要包含空格）：";
                cin >> college_name;
                college = FindUniqueNodeByName(&tree, college_name);
                if (college == NULL || college->type != NODE_COLLEGE) {
                    cout << "添加失败：学院不存在，或名称不唯一。" << endl;
                    continue;
                }
                cout << "请输入新系名称（不要包含空格）：";
                cin >> name;
                new_id = AddNode(&tree, college_name, name, NODE_DEPARTMENT);
            } else if (level == 4) {
                cout << "请输入父学院名称（不要包含空格）：";
                cin >> college_name;
                cout << "请输入父系名称（不要包含空格）：";
                cin >> dept_name;
                dept = FindDepartmentInCollege(&tree, college_name, dept_name);
                if (dept == NULL) {
                    cout << "添加失败：学院与系不匹配。" << endl;
                    continue;
                }
                cout << "请输入老师姓名（不要包含空格）：";
                cin >> name;
                new_id = AddNode(&tree, dept_name, name, NODE_LEADER);
            } else {
                cout << "层级输入无效，请输入 2/3/4。" << endl;
                continue;
            }

            if (new_id == -1) cout << "添加失败。" << endl;
            else cout << "添加成功，新节点ID=" << new_id << endl;
        } else if (op == 3) {
            char name[NAME_LEN];

            cout << "请输入要删除的节点名称（不要包含空格）：";
            cin >> name;
            if (!DeleteNode(&tree, name)) cout << "删除失败。" << endl;
            else cout << "删除成功。" << endl;
        } else if (op == 4) {
            char name[NAME_LEN];
            cout << "请输入要查找的节点名称（不要包含空格）：";
            cin >> name;
            PrintNodeByName(&tree, name);
        } else if (op == 5) {
            char leaf_name[NAME_LEN];

            cout << "请输入叶子节点名称（不要包含空格）：";
            cin >> leaf_name;
            if (!PrintPathToLeaf(&tree, leaf_name)) {
                cout << "路径输出失败：节点不是叶子节点，或名称无效。" << endl;
            }
        } else if (op == 6) {
            PrintDepartments(&tree);
        } else {
            cout << "未知选项，请重试。" << endl;
        }
    }

    Destroy(&tree);
    return 0;
}
