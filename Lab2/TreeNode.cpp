#include "TreeNode.h"

// 将节点类型转换为显示字符串。
const char* NodeTypeToString(NodeType type) {
    switch (type) {
        case NODE_FACULTY:
            return "学部";
        case NODE_COLLEGE:
            return "学院";
        case NODE_DEPARTMENT:
            return "系";
        case NODE_LEADER:
            return "老师";
        default:
            return "通用";
    }
}
