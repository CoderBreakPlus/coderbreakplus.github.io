import os
import re

def rename_files():
    # 匹配模式：cf2206 + 一个小写字母，后缀任意
    pattern = re.compile(r'^cf2206([a-z])\.')

    # 查找当前目录下匹配的文件
    files = []
    for filename in os.listdir('.'):
        if os.path.isfile(filename):
            match = pattern.match(filename)
            if match:
                # 提取小写字母
                letter = match.group(1)
                # 计算偏移：a -> 0, b -> 1, ..., z -> 25
                offset = ord(letter) - ord('a')
                # 新文件名编号：18234 + offset
                new_number = 18234 + offset
                # 获取原文件后缀
                _, ext = os.path.splitext(filename)
                # 新文件名
                new_filename = f"qoj{new_number}{ext}"
                files.append((filename, new_filename))

    # 执行重命名
    for old, new in files:
        print(f"重命名: {old} -> {new}")
        os.rename(old, new)

if __name__ == "__main__":
    rename_files()
