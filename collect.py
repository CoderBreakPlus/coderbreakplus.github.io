import os
import re

def main():
    # 1. 终端依次读入 比赛类型 和 比赛名
    try:
        contest_type = input("请输入比赛类型 (如 oi/xcpc/xcpc+，可留空走默认): ").strip()
        contest_name = input("请输入这些文件所属的比赛名 (可留空): ").strip()
    except EOFError:
        print("未检测到输入，退出程序。")
        return

    # 扫描的目标文件夹
    code_dir = 'code'
    
    if not os.path.exists(code_dir):
        print(f"❌ 错误：当前目录下不存在 '{code_dir}' 文件夹！")
        return
        
    # 需要被剔除的文件名子串
    exclude_subs =["gen", "brute", "std", "duipai", "sb", "test", "new", "try"]
    
    success_count = 0
    
    for fname in os.listdir(code_dir):
        # 仅处理 .cpp 文件
        if not fname.endswith('.cpp'):
            continue
        
        # 截取不包含后缀的名字 s
        s = fname[:-4]
        
        # 将文件名转小写后检查是否命中排除关键词
        s_lower = s.lower()
        if any(sub in s_lower for sub in exclude_subs):
            continue
            
        filepath = os.path.join(code_dir, fname)
        
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                lines = f.readlines()
        except Exception as e:
            print(f"⚠️ 读取文件 {fname} 失败: {e}")
            continue
            
        # 防止文件不够 3 行时导致数组越界
        line2 = lines[1] if len(lines) > 1 else ""
        line3 = lines[2] if len(lines) > 2 else ""
        
        # 1. 提取题目编号 (第二行的第一个大写字母)
        m = re.search(r'[A-Z]', line2)
        pid = m.group(0) if m else ""
        
        # 2. 提取题目链接 (第三行，并剥离所有的注释符和空白)
        link = re.sub(r'^[\s/*#]+', '', line3).strip()
        
        # 准备生成同名的 .conf 文件
        conf_path = os.path.join(code_dir, f"{s}.conf")
        try:
            with open(conf_path, 'w', encoding='utf-8') as f:
                f.write(f"{contest_type}\n") # 第1行: 比赛归类(如 oi/xcpc/xcpc+)
                f.write(f"{link}\n")         # 第2行: 题目链接
                f.write(f"{contest_name}\n") # 第3行: 比赛名
                f.write(f"{pid}\n")          # 第4行: 题目编号
                f.write("\n")                # 第5行: 备注标签(留空)
                
            print(f"✅ 生成 {s}.conf 成功！(类型: {contest_type if contest_type else '无'}, 编号: {pid if pid else '无'})")
            success_count += 1
            
        except Exception as e:
            print(f"❌ 写入文件 {s}.conf 失败: {e}")
            
    print(f"\n🎉 执行完毕！共为 {success_count} 个有效代码文件生成了配置文件。")

if __name__ == '__main__':
    main()