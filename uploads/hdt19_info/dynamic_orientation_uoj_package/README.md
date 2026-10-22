# 动态平衡定向：UOJ 完整题目包

这是边定向的弱化版。接口仍使用 path.h 和 query_path，但 query_path 返回正向边编号集合；不要求图连通或输出欧拉回路。

## 上传方法

1. 创建题目，将 `题面.md` 粘贴到题面编辑器。
2. 上传包内 `uoj_data.zip`；其根目录直接包含 `problem.conf`。使用 SVN 时，把数据放入题目的 `1/` 目录。
3. 点击“与 SVN 仓库同步”，再用 C++17 提交 `source/std.cpp` 试交。

配置为 15 秒、1024 MB，四个打包子任务各 25 分，每个 20 点；第四个子任务 n,q≤200000。

本包提供了 val17.cpp，因此具备标准程序与数据验证器。是否开放 Hack 由后台决定；固定题库使用时可以关闭。验证器对任意输入检查全局约束；source/run_all.py 另外按测试点编号检查子任务上界。

UOJ 原始数据格式依据：https://vfleaking.github.io/uoj/problem/

## 文件

- `uoj_data.zip`：上传用压缩包。
- `uoj_data/`：相同内容的展开目录，便于修改。
- `source/std.cpp`、`source/path.h`：简化 FHQ Treap 标程和接口。
- `source/implementer.cpp`：本地评测库。
- `source/val.cpp`：自包含数据验证器，无 testlib 或其他自定义头文件依赖。
- `source/brute.cpp`：每次查询重新构造方向的慢速参考解。
- `source/generate.py`：80 点生成器，固定种子，可复现。
- `source/run_all.py`：数据合法性及标程全量测试脚本。
- `source/verify.cpp`：小图穷举及随机状态验证程序。
- `题解.md`、`数据说明.md`、`验证记录.md`：做法、覆盖目标及验证结果。

UOJ 根目录中的 std17.cpp 和 val17.cpp 与 source 中对应代码一致。使用这些名字是为了让 UOJ 按 C++17 编译，而非旧版默认的 C++03。

## 本地编译

在本包根目录执行：

```sh
g++ -std=c++17 -O2 source/std.cpp source/implementer.cpp -o solution
g++ -std=c++17 -O2 source/val.cpp -o val
./solution < uoj_data/test1.in
python3 source/run_all.py
```

重新生成数据：

```sh
python3 source/generate.py uoj_data
```

小图验证：

```sh
g++ -std=c++17 -O2 source/verify.cpp -o verify
./verify
```

重新生成只覆盖 test1..80 和数据清单，不修改 problem.conf、样例或线上库。修改展开目录后，请重新压缩 uoj_data 内部的文件以更新上传 zip。

## 评测约定

文件格式仍是 n q 后接 q 行操作：1 u v、2 u v、3、4。所有端点满足 u<v，边编号由评测库根据添加次数自动产生，不另行写在输入文件中。

所有 .ans 内容均为 AC。线上库只在全部检查通过后输出私有 token 和 AC，UOJ 去掉 token 后由内置 wcmp 比较。没有自定义 chk.cpp，判定工作在 implementer.cpp 中完成。

require/ 是线上库，download/ 是可公开附件。不要公开整个出题包或线上 token。线上库和本地库的判断逻辑相同，区别仅在最终的 token 输出。

依照题目约定，每个文件最多追问十次。仅在追问时检查具体集合和对应哈希，其他 query 只检查返回值范围。不会用标程选出的某一种定向作为唯一答案，也不会额外调用 query_path。

评测库预读操作后关闭标准输入，再调用选手接口，接口本身不透露后续操作。它与选手代码在同一进程中运行，采用 UOJ 常规函数式交互机制。

尚未访问实际 UOJ 服务器；上传后仍应完成后台同步及标程试交。
