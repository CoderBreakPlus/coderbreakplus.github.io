import os
import re

def get_offset(label):
    """
    计算题号字母的偏移量
    A -> 0, B -> 1, C -> 2 ... Z -> 25
    """
    label = label.upper()
    res = 0
    for char in label:
        res = res * 26 + (ord(char) - ord('A') + 1)
    return res - 1

def main():
    code_dir = 'code'
    if not os.path.exists(code_dir):
        print(f"❌ 错误：当前目录下不存在 '{code_dir}' 文件夹！")
        return

    print("🧹 正在清理无后缀名的编译产物...")
    deleted_count = 0
    valid_files = []
    
    # 1. 扫描文件，删除无后缀可执行文件，收集需要改名的【单字母】cpp 文件
    for fname in os.listdir(code_dir):
        filepath = os.path.join(code_dir, fname)
        if not os.path.isfile(filepath):
            continue
            
        # 如果文件名没有 '.'，认为是编译产生的无后缀名可执行文件并删除
        if '.' not in fname:
            try:
                os.remove(filepath)
                print(f"🗑️ 已删除无后缀文件: {fname}")
                deleted_count += 1
            except Exception as e:
                print(f"❌ 删除 {fname} 失败: {e}")
            continue

        # 收集符合规范的源码文件
        if fname.endswith('.cpp'):
            base = fname[:-4]
            # 【核心修改】：正则表达式去掉了 +, 严格限制必须只有 1 个字母！
            if re.match(r'^[A-Za-z]$', base):
                valid_files.append((base.upper(), fname))
                
    if deleted_count > 0:
        print(f"✅ 清理完成，共删除了 {deleted_count} 个无后缀可执行文件。\n")

    if not valid_files:
        print(f"⚠️ 在 '{code_dir}' 中没有找到形如 A.cpp, B.cpp 的单字母代码文件。其他文件已保持原样。")
        return

    print(f"🔍 找到 {len(valid_files)} 个待处理的单字母题号文件: {', '.join([f[1] for f in valid_files])}")
    
    # 2. 获取基准题号
    first_id = input("\n请输入 A 题对应的起始题号 (如 qoj1000, p1001, 100): ").strip()
    if not first_id:
        print("未输入题号，已取消操作。")
        return

    m = re.match(r'^([a-zA-Z]*)(\d+)$', first_id)
    if not m:
        print("❌ 无法解析题号，题号末尾必须包含数字！")
        return
        
    prefix = m.group(1)
    start_num = int(m.group(2))
    pad_len = len(m.group(2)) # 记录数字长度以便补零，比如 001 -> 002

    # 3. 批量处理替换
    success_count = 0
    for label, fname in valid_files:
        offset = get_offset(label)
        curr_num = str(start_num + offset).zfill(pad_len)
        new_base = f"{prefix}{curr_num}"
        
        old_cpp_path = os.path.join(code_dir, fname)
        new_cpp_path = os.path.join(code_dir, f"{new_base}.cpp")
        conf_path = os.path.join(code_dir, f"{new_base}.conf")
        
        # 重命名 cpp 文件
        try:
            os.rename(old_cpp_path, new_cpp_path)
            print(f"🔄 重命名: {fname}   ->   {new_base}.cpp")
        except Exception as e:
            print(f"❌ 重命名 {fname} 失败: {e}")
            continue
            
        # 生成对应的精简 3 行 .conf 文件
        try:
            with open(conf_path, 'w', encoding='utf-8') as f:
                f.write("\n")  # 第一行：标签/难度 (初始留空)
                f.write("\n")  # 第二行：题目链接 (留空，系统自动推导)
                f.write("\n")  # 第三行：题目独立备注 (初始留空)
            print(f"✅ 生成配置: {new_base}.conf")
            success_count += 1
        except Exception as e:
            print(f"❌ 写入 {new_base}.conf 失败: {e}")

    print(f"\n🎉 完毕！共成功处理了 {success_count} 个文件。其他长名字的 cpp (如 main.cpp) 均已保持原封不动。")

if __name__ == '__main__':
    main()