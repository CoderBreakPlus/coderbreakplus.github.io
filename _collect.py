import os
import re

def get_offset(label):
    """
    计算题号字母的偏移量
    A -> 0, B -> 1, C -> 2 ... Z -> 25, AA -> 26
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

    # 1. 扫描符合规范的 cpp 文件 (如 A.cpp, B.cpp)
    valid_files = []
    for fname in os.listdir(code_dir):
        if not fname.endswith('.cpp'): continue
        base = fname[:-4]
        # 只识别纯字母构成的文件名，如 A, B, c, D
        if re.match(r'^[A-Za-z]+$', base):
            valid_files.append((base.upper(), fname))
            
    if not valid_files:
        print(f"⚠️ 在 '{code_dir}' 文件夹中没有找到形如 A.cpp, B.cpp 的纯字母代码文件。")
        return

    print(f"🔍 找到 {len(valid_files)} 个代码文件: {', '.join([f[1] for f in valid_files])}")
    
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
            print(f"🔄 重命名: {fname} -> {new_base}.cpp")
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

    print(f"\n🎉 完毕！共成功处理了 {success_count} 个文件组合。")

if __name__ == '__main__':
    main()