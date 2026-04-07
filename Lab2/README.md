# Lab2: 组织结构关系树

## 一、实验目标

本实验使用树结构表示组织关系：`学部 -> 学院 -> 系 -> 老师`。

**省流：完成RelationTree.cpp里的TODO然后参考 五、编译与运行 进行编译运行**


## 二、当前代码约定

### 1) 名称约定（已在 `main.cpp` 初始化）

- 根节点：`信智学部`
- 学院：`信院`、`计科`、`微电子`
- 系：`6系`、`10系`、`计算机系`、`软件工程系`、`微电子系`、`集成电路系`
- 预置老师：`王永`、`刘斌`、`李向阳`

### 2) 操作约定

- 添加节点：按“父节点名称 + 新节点名称”添加
- 删除节点：按“节点名称”删除
- 路径输出：按“叶子节点名称”输出从根到叶子的路径
- 设定：默认不重名（实现时可按“找到即用”处理）

## 三、需要完成的 3 个函数

文件：`RelationTree.cpp`

### 1) `AddNode`

要求：
1. 做参数合法性检查。
2. 在树中找到父节点名称对应的节点。
3. 判断父节点孩子数是否达到 `MAX_SIZE`。
4. 创建新节点并挂接到父节点。
5. 成功返回新节点 ID，失败返回 `-1`。

TODO 具体补充内容：
1. 在 `// TODO：遍历整棵树，按 parent_name 查找父节点...` 位置，使用遍历（BFS/DFS 均可）在整棵树中找出名字为 `parent_name` 的节点。
2. 找到后将该节点赋值给 `parent`，找不到则保持 `parent == NULL` 并返回 `-1`。
3. 不要修改已给定的创建节点和挂接逻辑，只补全“查父节点”这部分。

### 2) `DeleteNode`

要求：
1. 做参数合法性检查。
2. 在树中找到目标节点（按名称）。
3. 禁止删除根节点。
4. 删除目标节点及其子树。
5. 删除后维护父节点 `children` 数组连续。
6. 成功返回 `1`，失败返回 `0`。

TODO 具体补充内容：
1. 在 `// TODO：遍历整棵树，按 name 查找目标节点...` 位置，找到待删除节点 `target`。
2. 在 `// TODO：在 target 的父节点 children 数组中定位 target...` 位置：
   - 在 `target->parent->children[]` 中找到 `target` 的下标。
   - 调用已提供的 `FreeSubtree(target)` 释放目标子树。
   - 将后续孩子前移，保持数组连续。
   - `child_count--`，并返回 `1`。
3. 如果遍历后没找到，或在父节点孩子数组中未定位到目标，返回 `0`。

### 3) `PrintPathToLeaf`

要求：
1. 做参数合法性检查。
2. 找到目标节点（按名称）。
3. 仅当目标是叶子节点时继续。
4. 回溯父指针得到路径并按 `根 -> ... -> 叶子` 输出。
5. 成功返回 `1`，失败返回 `0`。

TODO 具体补充内容：
1. 在 `// TODO：遍历整棵树，按 name 查找目标节点...` 位置，先定位 `target`。
2. 在 `// TODO：从 target 沿 parent 回溯到根...` 位置，把从目标到根的节点依次存入 `path[]`，同时累计 `len`。
3. 在 `// TODO：将 path 逆序输出...` 位置，按 `path[len-1] -> ... -> path[0]` 输出，节点间用 `" -> "` 连接。
4. 注意仅叶子节点允许输出路径，非叶子节点直接返回 `0`。

## 四、已给出的函数

`RelationTree.cpp` 中已提供：

- `Init`
- `Destroy`
- `GetRootId`
- `PrintTree`
- 以及内部辅助函数：`CreateNode`、`FreeSubtree`、`PrintDfs`

## 五、编译与运行

在 `Lab2` 目录执行：（如果在上一层DSAProject文件夹的话cd Lab2即可）

```bash
g++ -std=c++11 -Wall -Wextra -finput-charset=UTF-8 -fexec-charset=GBK -o main.exe main.cpp RelationTree.cpp TreeNode.cpp

./main.exe
```

## 六、实验预期效果


1. 打印树（已实现，不需要完成）
<img src="../img/lab2/1.png" alt="打印树效果" style="max-width: 420px; width: 100%; height: auto;" />

2. 添加节点
<img src="../img/lab2/2.png" alt="添加节点效果" style="max-width: 420px; width: 100%; height: auto;" />

3. 删除节点
<img src="../img/lab2/3.png" alt="删除节点效果" style="max-width: 420px; width: 100%; height: auto;" />

4. 查找节点（输出根到目标节点路径）
<img src="../img/lab2/4.png" alt="查找节点效果" style="max-width: 420px; width: 100%; height: auto;" />
