import os
import re

def main():
    contest_dir = 'contest'
    os.makedirs(contest_dir, exist_ok=True)
    
    print("=== 全新比赛信息录入 ===")
    c_name = input("1. 请输入比赛名 (如 XOJ Round 1): ").strip()
    c_type = input("2. 请输入比赛类型 (OI / OIs / XCPC): ").strip()
    c_link = input("3. 请输入比赛完整链接 (可留空): ").strip()
    
    first_id = input("4. 请输入A题的题号 (如 qoj100, p1001, 100): ").strip()
    try:
        num = int(input("5. 请输入题目总数 (如 6): ").strip())
    except ValueError:
        print("❌ 题目数量必须是整数！")
        return
        
    c_remark = input("6. 请输入比赛备注 (可留空): ").strip()
    
    # 智能推断后续题号
    m = re.match(r'^(.*?)(\d+)$', first_id)
    if not m:
        print("❌ 无法解析起始题号，题号末尾必须是数字！")
        return
        
    prefix = m.group(1)
    start_num = int(m.group(2))
    pad_len = len(m.group(2)) # 保留前导零特性
    
    # 寻找下一个可用的自增编号
    existing = [f for f in os.listdir(contest_dir) if f.endswith('.conf')]
    max_idx = 0
    for f in existing:
        try: max_idx = max(max_idx, int(f[:-5]))
        except: pass
    
    new_conf = f"{max_idx + 1:04d}.conf"
    
    with open(os.path.join(contest_dir, new_conf), 'w', encoding='utf-8') as f:
        f.write(f"{c_name}\n{c_type}\n{c_link}\n")
        for i in range(num):
            label = chr(ord('A') + i)
            curr_num = str(start_num + i).zfill(pad_len)
            f.write(f"{label} {prefix}{curr_num}\n")
        if c_remark:
            f.write(f"{c_remark}\n")
            
    print(f"\n✅ 成功生成配置 -> {contest_dir}/{new_conf} (包含 A ~ {chr(ord('A') + num - 1)} 共 {num} 题)。")

if __name__ == '__main__':
    main()