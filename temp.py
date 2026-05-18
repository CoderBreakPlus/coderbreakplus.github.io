import itertools
import time
from concurrent.futures import ProcessPoolExecutor

def get_lis_lds(P):
    """标准的耐心排序法求排列 P 的最长递增/递减子序列长度"""
    inc, dec = [], []
    for x in P:
        # LIS (最长递增)
        for i in range(len(inc)):
            if inc[i] >= x:
                inc[i] = x
                break
        else:
            inc.append(x)
            
        # LDS (最长递减)
        for i in range(len(dec)):
            if dec[i] < x:
                dec[i] = x
                break
        else:
            dec.append(x)
    return len(inc), len(dec)

def get_max_k_bfs(P):
    """
    【绝对正确的暴搜引擎】：基于耐心排序状态机的 BFS
    完全不依赖任何公式，纯粹模拟追加元素的过程，求出最多能加几个数。
    """
    target_lis, target_lds = get_lis_lds(P)
    N = len(P)
    
    # 初始化状态
    inc, dec = [], []
    for x in P:
        for i in range(len(inc)):
            if inc[i] >= x: inc[i] = x; break
        else: inc.append(x)
        for i in range(len(dec)):
            if dec[i] < x: dec[i] = x; break
        else: dec.append(x)
            
    # BFS 队列：存储当前深度的所有合法的 (inc_tails, dec_tails)
    current_level = {(tuple(inc), tuple(dec))}
    m = N  # 当前排列总长度
    k = 0  # 追加的元素个数
    
    while True:
        next_level = set()
        
        for state_inc, state_dec in current_level:
            # 枚举追加的元素的“相对大小”（可以插在 1 到 m+1 之间任何位置）
            for v in range(1, m + 2):
                
                # 1. 模拟将现有的 >= v 的数全推高 1 位，为新元素腾出大小空间
                n_inc = [x + 1 if x >= v else x for x in state_inc]
                
                # 插入新元素 v 到 LIS 状态机
                for i in range(len(n_inc)):
                    if n_inc[i] >= v:
                        n_inc[i] = v
                        break
                else:
                    n_inc.append(v)
                
                # 若 LIS 超标，剪枝废弃
                if len(n_inc) > target_lis:
                    continue
                    
                # 2. 对 LDS 状态机做同样的操作
                n_dec = [x + 1 if x >= v else x for x in state_dec]
                for i in range(len(n_dec)):
                    if n_dec[i] < v:
                        n_dec[i] = v
                        break
                else:
                    n_dec.append(v)
                
                # 若 LDS 超标，剪枝废弃
                if len(n_dec) > target_lds:
                    continue
                    
                next_level.add((tuple(n_inc), tuple(n_dec)))
                
        # 如果下一层没有任何合法状态，说明当前 k 就是极限！
        if not next_level:
            break
            
        current_level = next_level
        m += 1
        k += 1
        
    return k

def calc_formula(P):
    """计算我之前提到的【禁止阴影区面积公式】，作为对比"""
    coords = []
    for i, x in enumerate(P):
        lis_x, lds_x = 1, 1
        for j in range(i):
            if P[j] < x: lis_x = max(lis_x, coords[j][1] + 1)
            if P[j] > x: lds_x = max(lds_x, coords[j][0] + 1)
        coords.append((lds_x, lis_x))
        
    R = max(c[0] for c in coords)
    C = max(c[1] for c in coords)
    
    # 网格求阴影面积
    grid = [[False] * (C + 1) for _ in range(R + 1)]
    for r, c in coords:
        for i in range(1, r + 1):
            for j in range(1, c + 1):
                grid[i][j] = True
                
    shadow_area = sum(sum(row) for row in grid)
    return R * C - shadow_area

def check_permutation(P):
    """单进程验证任务"""
    brute = get_max_k_bfs(P)
    form = calc_formula(P)
    if brute != form:
        return False, P, brute, form
    return True, None, None, None

def main():
    print(f"{'排列 P':<15} | {'杨表列数(LIS)':<13} | {'杨表行数(LDS)':<13} | {'纯暴搜K':<10} | {'公式K':<10} | {'结果'}")
    print("-" * 80)
    
    # 1. 详细打印 N<=4 的直观结果
    for N in range(1, 5):
        for P in itertools.permutations(range(1, N + 1)):
            lis_v, lds_v = get_lis_lds(P)
            brute_k = get_max_k_bfs(P)
            form_k = calc_formula(P)
            match = "✅" if brute_k == form_k else "❌"
            print(f"{str(P):<15} | {lis_v:<13} | {lds_v:<13} | {brute_k:<10} | {form_k:<10} | {match}")

    # 2. 大规模静默验证 N=5, 6, 7, 8
    for N in range(5, 9):
        perms = list(itertools.permutations(range(1, N + 1)))
        total = len(perms)
        print(f"\n[🚀 正在启动多进程验证 N={N} 的全排列 (总计 {total} 个) ...]")
        
        start_time = time.time()
        all_match = True
        
        # 启用多进程池加速
        with ProcessPoolExecutor() as executor:
            chunk = max(1, total // 100)
            results = executor.map(check_permutation, perms, chunksize=chunk)
            
            for res in results:
                success, P, brute, form = res
                if not success:
                    print(f"\n❌ 发现反例！ 排列: {P}, 暴搜得出: {brute}, 公式得出: {form}")
                    all_match = False
                    break
                    
        if all_match:
            cost = time.time() - start_time
            print(f"✅ N={N} 验证完美通过！耗时: {cost:.2f} 秒。暴搜与公式结论 100% 吻合！")

if __name__ == '__main__':
    main()
