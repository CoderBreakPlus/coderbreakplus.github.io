import os

def main():
    data_dir = 'data'
    if not os.path.exists(data_dir):
        print(f"❌ 未找到 {data_dir} 目录！")
        return
        
    count = 0
    for fname in os.listdir(data_dir):
        if not fname.endswith('.conf'):
            continue
            
            
        filepath = os.path.join(data_dir, fname)
        with open(filepath, 'r', encoding='utf-8') as f:
            lines =[line.strip() for line in f.readlines()]
            
        # 补齐不足 5 行的情况
        while len(lines) < 5:
            lines.append('')
            
        old_cat = lines[0]
        old_link = lines[1]
        old_contest = lines[2]
        old_pid = lines[3]
        old_tags = lines[4]
        
        # 写入新格式
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(f"{old_tags}\n")     # 第 1 行: 标签和难度
            f.write(f"{old_cat}\n")      # 第 2 行: 分类
            f.write(f"{old_link}\n")     # 第 3 行: 链接
            f.write(f"{old_contest}\n")  # 第 4 行: 比赛名
            f.write(f"{old_pid}\n")      # 第 5 行: 题号
            
        count += 1
        
    print(f"🎉 转换完成！共将 {count} 个 .conf 文件更新为新格式。")

if __name__ == '__main__':
    main()