# 动态欧拉回路：原版 UOJ 题目包

本包保留求欧拉回路及其序列哈希的原版接口，尚未改成边定向版本。

## 上传

1. 新建 UOJ 题目，把 `题面.md` 粘贴到题面编辑器，题名可设为“动态欧拉回路”。
2. 上传 `uoj_data.zip`，其根目录直接包含 `problem.conf`，不套额外目录。若通过 SVN 上传，应放入对应题目的 `1/` 目录。
3. 在后台关闭 Hack，点击“与 SVN 仓库同步”。本包没有用于开放 Hack 的 `val.cpp`；`source/validate_all.cpp` 是检查固定 80 组数据的离线工具。
4. 使用 C++17 提交 `source/std.cpp`，检查站点编译和时间限制配置。

配置依据：https://vfleaking.github.io/uoj/problem/

## 内容

- `uoj_data.zip`：可上传的数据包；展开目录 `uoj_data/` 同样随包提供，方便修改。
- `source/std.cpp`：此前简化的 FHQ Treap 标程，算法未改动。
- `source/implementer.cpp`、`source/path.h`：可直接本地联编的评测库与接口。
- `uoj_data/std17.cpp`：同一标程的 UOJ C++17 命名版本，避免旧 UOJ 把 `std.cpp` 当作 C++03 编译。
- `uoj_data/require/`：线上评测库及头文件。
- `uoj_data/download/`：向选手公开的本地评测库、接口、模板、样例；不含标程及线上 token。
- `test1.in` 至 `test80.in`、对应的 `.ans`：每包 20 点，每包 25 分，答案文件均为 `AC`。
- `ex_test1.in/.ans`：题面样例。
- `题解.md`：此前详细题解，含复杂度成立所需假设及尚未证明的部分。
- `验证记录.md`：本次打包验证结果。

## 判定语义与部署注意事项

线上库仅在全部操作和检查完成后输出私有 token 与 `AC`。UOJ 去掉 token 后用内建 `wcmp` 和 `.ans` 比较。不要把整个出题包作为选手附件公开；只公开 `download/` 内容。

评测库在调用 `init` 前读完操作并关闭标准输入，不向选手接口透露未来操作。所有评测开销计入程序总时间。函数式同进程交互及 token 是 UOJ 的常规机制，不是对任意恶意机器码的安全隔离。

依照原题约定，只有紧跟 `4` 的查询会检查哈希对应的具体欧拉回路；其余 `3` 只检查返回值范围。不会额外调用 `query_path()`，也不会拿标程产生的某一条欧拉回路哈希作为唯一答案。这一设计不能保证检查到所有未追问查询的错误。

当前标程使用三组随机采样，并带精确扫描兜底，随机性只影响运行时间。没有已证明的最坏情况 15 秒保证，亦没有已证明的无条件总期望 O(n log³ n) 界；包中保留原有实现及题解说明。下面的实测记录只反映本次运行环境。

## 本地编译

```sh
cd source
g++ -std=c++17 -O2 std.cpp implementer.cpp -o solution
./solution < ../uoj_data/test1.in
```

数据合法性验证（回滚并查集离线检查每个查询的连通性）：

```sh
g++ -std=c++17 -O2 source/validate_all.cpp -o validate
./validate uoj_data
```

本包没有访问你的 UOJ 服务器，仍需完成后台同步并试交标程，以验证具体站点版本的兼容性。
