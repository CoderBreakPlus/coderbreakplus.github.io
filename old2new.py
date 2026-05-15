import os

def main():
    data_dir = 'data'
    contest_dir = 'contest'
    if not os.path.exists(data_dir):
        print("❌ 找不到 data 目录！")
        return
        
    os.makedirs(contest_dir, exist_ok=True)
    contests = {} # (cat, c_name) -> list of (pid, base_name)
    
    for f in os.listdir(data_dir):
        if not f.endswith('.conf'): continue
        path = os.path.join(data_dir, f)
        base_name = f[:-5]
        
        with open(path, 'r', encoding='utf-8') as file:
            lines = [l.strip() for l in file.readlines()]
        while len(lines) < 6: lines.append('')
        
        tags_diff = lines[0]
        cats = lines[1].split('|') if lines[1] else []
        url = lines[2]
        c_names = lines[3].split('|') if lines[3] else []
        pids = lines[4].split('|') if lines[4] else []
        remark = lines[5]
        
        # 将原配置覆写为新的 3 行精简格式 (1: 标签/难度, 2: 链接, 3: 备注)
        with open(path, 'w', encoding='utf-8') as file:
            file.write(f"{tags_diff}\n{url}\n{remark}\n")
            
        # 提取并解构比赛信息
        for i in range(max(len(cats), len(c_names), len(pids))):
            cat = cats[i] if i < len(cats) else (cats[-1] if cats else '')
            c_name = c_names[i] if i < len(c_names) else (c_names[-1] if c_names else '')
            pid = pids[i] if i < len(pids) else (pids[-1] if pids else '')
            
            if cat and c_name:
                if (cat, c_name) not in contests:
                    contests[(cat, c_name)] = []
                contests[(cat, c_name)].append((pid, base_name))
                
    # 批量生成新的比赛配置文件
    c_idx = 1
    for (cat, c_name), probs in contests.items():
        conf_name = f"{c_idx:04d}.conf"
        with open(os.path.join(contest_dir, conf_name), 'w', encoding='utf-8') as f:
            f.write(f"{c_name}\n{cat}\n\n") # 老数据没有比赛链接，默认留空
            for pid, base_name in sorted(probs, key=lambda x: x[0]):
                f.write(f"{pid} {base_name}\n")
        c_idx += 1
        
    print(f"🎉 迁移完成！共提取生成了 {len(contests)} 场比赛配置到 /contest 目录下。")

if __name__ == '__main__':
    main()