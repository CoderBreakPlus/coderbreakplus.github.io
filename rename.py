import os
import re

def main():
    try:
        prefix = input("请输入比赛前缀 (例如 cf2137, arc123): ").strip()
        if not prefix:
            print("⚠️ 未输入前缀，操作已取消。")
            return
    except EOFError:
        print("未检测到输入，退出程序。")
        return

    code_dir = 'code'
    if not os.path.exists(code_dir):
        print(f"❌ 错误：当前目录下不存在 '{code_dir}' 文件夹！")
        return
        
    success_count = 0
    
    # 遍历 code 目录下的文件
    for fname in os.listdir(code_dir):
        if not fname.endswith('.cpp'): 
            continue
            
        base_name = fname[:-4].strip()
        
        # 【白名单拦截】只处理形如 A, B, C, C1, D2, AA 这种单纯的比赛题号文件
        # 屏蔽掉诸如 template, brute, cf2137a 等已经命名好或其他无关的文件
        if not re.match(r'^[A-Za-z]{1,2}\d*$', base_name):
            continue
            
        # 拼接新的基础文件名，强制将原题号转为小写
        # 例如: prefix="cf2137", base_name="A" -> "cf2137a"
        new_base = f"{prefix}{base_name.lower()}"
        
        old_cpp_path = os.path.join(code_dir, fname)
        new_cpp_path = os.path.join(code_dir, f"{new_base}.cpp")
        conf_path = os.path.join(code_dir, f"{new_base}.conf")
        
        # 1. 重命名 .cpp 文件
        try:
            if not os.path.exists(new_cpp_path):
                os.rename(old_cpp_path, new_cpp_path)
                print(f"🔄 重命名: {fname} -> {new_base}.cpp")
            else:
                print(f"⚠️ 警告: {new_base}.cpp 已存在，跳过重命名。")
                continue
        except Exception as e:
            print(f"❌ 重命名 {fname} 失败: {e}")
            continue
            
        # 2. 创建配套的空 .conf 文件
        # 写入 6 个换行符，完全符合主引擎 6 行配置文件的解析标准
        try:
            if not os.path.exists(conf_path):
                with open(conf_path, 'w', encoding='utf-8') as f:
                    f.write("\n\n\n\n\n\n")
                print(f"✅ 建配置: {new_base}.conf")
            else:
                print(f"⚠️ 警告: {new_base}.conf 已存在，跳过创建。")
        except Exception as e:
            print(f"❌ 创建 {new_base}.conf 失败: {e}")
            
        success_count += 1
        
    print(f"\n🎉 完毕！共成功处理了 {success_count} 个文件。")

if __name__ == '__main__':
    main()