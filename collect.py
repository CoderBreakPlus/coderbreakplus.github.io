import os
import re

def main():
    try:
        contest_type = input("请输入比赛类型 (如 oi/xcpc，可留空): ").strip()
        contest_name = input("请输入这些文件所属的比赛名 (可留空): ").strip()
    except EOFError:
        print("未检测到输入，退出程序。")
        return

    code_dir = 'code'
    if not os.path.exists(code_dir):
        print(f"❌ 错误：当前目录下不存在 '{code_dir}' 文件夹！")
        return
        
    exclude_subs = ["gen", "brute", "std", "duipai", "sb", "test", "new", "try"]
    success_count = 0
    
    for fname in os.listdir(code_dir):
        if not fname.endswith('.cpp'): continue
        s = fname[:-4]
        if any(sub in s.lower() for sub in exclude_subs): continue
            
        filepath = os.path.join(code_dir, fname)
        try:
            with open(filepath, 'r', encoding='utf-8') as f: lines = f.readlines()
        except Exception:
            continue
            
        line2 = lines[1] if len(lines) > 1 else ""
        line3 = lines[2] if len(lines) > 2 else ""
        
        m = re.search(r'[A-Z]', line2)
        pid = m.group(0) if m else ""
        link = re.sub(r'^[\s/*#]+', '', line3).strip()
        
        conf_path = os.path.join(code_dir, f"{s}.conf")
        try:
            with open(conf_path, 'w', encoding='utf-8') as f:
                f.write("\n")                # 第 1 行: 标签/难度
                f.write(f"{contest_type}\n") # 第 2 行: 比赛归类
                f.write(f"{link}\n")         # 第 3 行: 题目链接
                f.write(f"{contest_name}\n") # 第 4 行: 比赛名
                f.write(f"{pid}\n")          # 第 5 行: 题目编号
                f.write("\n")                # 第 6 行: 备注 (留空待填)
                
            print(f"✅ 生成 {s}.conf 成功！(题号: {pid if pid else '无'})")
            success_count += 1
        except Exception as e:
            print(f"❌ 写入文件 {s}.conf 失败: {e}")
            
    print(f"\n🎉 完毕！共为 {success_count} 个代码文件生成了6行版配置文件。")

if __name__ == '__main__':
    main()