import os
import re

def main():
    try:
        prefix = input("请输入重命名前缀 (如 qoj, 留空则不重命名): ").strip()
        contest_type = input("请输入比赛类型 (如 OI/XCPC, 可留空): ").strip()
        contest_name = input("请输入这些文件所属的比赛名 (可留空): ").strip()
    except EOFError:
        print("未检测到输入，退出程序。")
        return

    code_dir = 'code'
    if not os.path.exists(code_dir):
        print(f"❌ 错误：当前目录下不存在 '{code_dir}' 文件夹！")
        return
        
    success_count = 0
    
    for fname in os.listdir(code_dir):
        if not fname.endswith('.cpp'): continue
        
        s = fname[:-4].strip()  # 获取原文件名
        
        # 【核心拦截】：只处理形如 A, B, C, A1, B2, AA 的比赛题号文件
        # 正则含义：1到2个字母 开头，后面跟着可选的数字（屏蔽掉诸如 brute, qoj10115, template 等其他文件）
        if not re.match(r'^[A-Za-z]{1,2}\d*$', s):
            continue
            
        filepath = os.path.join(code_dir, fname)
        try:
            with open(filepath, 'r', encoding='utf-8') as f: 
                lines = f.readlines()
        except Exception:
            continue
            
        # 提取链接 (优先读第 2 行，如果没有 http 再看第 3 行以兼容旧版)
        link = ""
        if len(lines) > 1:
            l2 = re.sub(r'^[\s/*#]+', '', lines[1]).strip()
            if l2.startswith("http"):
                link = l2
        if not link and len(lines) > 2:
            link = re.sub(r'^[\s/*#]+', '', lines[2]).strip()
            
        # 严格提取题目编号：就是原文件名大写 (如 A.cpp 就是 A)
        pid = s.upper()

        # 根据链接提取数字进行重命名
        new_base = s
        if prefix and link:
            # 找到链接里所有的连续数字组合
            nums = re.findall(r'\d+', link)
            if nums:
                # 取最后一串数字作为新名字
                new_base = f"{prefix}{nums[-1]}"
                
        # 执行重命名
        new_cpp_path = os.path.join(code_dir, f"{new_base}.cpp")
        if new_base != s:
            try:
                if filepath != new_cpp_path:
                    os.rename(filepath, new_cpp_path)
                    print(f"🔄 自动重命名: {fname} -> {new_base}.cpp")
            except Exception as e:
                print(f"❌ 重命名 {fname} 失败: {e}")
                new_base = s  # 失败则回退到原名
                new_cpp_path = filepath
        
        # 写入 6 行版 conf 配置文件
        conf_path = os.path.join(code_dir, f"{new_base}.conf")
        try:
            with open(conf_path, 'w', encoding='utf-8') as f:
                f.write("\n")                # 第 1 行: 标签/难度
                f.write(f"{contest_type}\n") # 第 2 行: 比赛归类
                f.write(f"{link}\n")         # 第 3 行: 题目链接
                f.write(f"{contest_name}\n") # 第 4 行: 比赛名
                f.write(f"{pid}\n")          # 第 5 行: 严格提取的题目编号 (A, B, C...)
                f.write("\n")                # 第 6 行: 备注 (留空待填)
                
            print(f"✅ 生成 {new_base}.conf 成功！(题号: {pid})")
            success_count += 1
        except Exception as e:
            print(f"❌ 写入文件 {new_base}.conf 失败: {e}")
            
    print(f"\n🎉 完毕！共处理了 {success_count} 个题号代码文件。")

if __name__ == '__main__':
    main()