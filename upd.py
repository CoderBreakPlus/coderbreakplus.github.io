#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
文件整理工具 - 自动移动代码、题解和配置文件到data目录，删除可执行文件，并运行run.py
支持重名文件交互式选择
"""

import os
import shutil
import subprocess
import sys
import stat
from pathlib import Path
from typing import List, Tuple, Set, Optional

class FileOrganizer:
    def __init__(self):
        """初始化整理器"""
        self.current_dir = Path.cwd()
        self.code_dir = self.current_dir / "code"
        self.data_dir = self.current_dir / "data"
        
        # 支持的文件扩展名
        self.supported_extensions = {'.cpp', '.md', '.conf'}
        
        # 排除的关键词（包含这些关键词的文件不会被移动）
        self.exclude_keywords = ['gen', 'brute', 'test', 'sb', 'duipai']
        
        # 可执行文件扩展名（Windows和Linux）
        self.executable_extensions = {
            '.exe', '.out', '.bin',  # Windows/Linux可执行文件
            '.o', '.obj',            # 编译中间文件
            '.a', '.so', '.dll',     # 库文件
            '.pyc', '.pyo'           # Python编译文件
        }
        
        # 统计信息
        self.stats = {
            'cpp_moved': 0,
            'cpp_skipped': 0,
            'cpp_overwritten': 0,
            'md_moved': 0,
            'md_skipped': 0,
            'md_overwritten': 0,
            'conf_moved': 0,
            'conf_skipped': 0,
            'conf_overwritten': 0,
            'executables_deleted': 0,
            'errors': 0
        }
        
        # 重名处理策略记忆（同一文件名多次出现时的默认选择）
        self.remember_choice = {}
        
        # 全局默认策略
        self.global_default = None  # 'overwrite', 'skip', 'rename'
    
    def check_directories(self) -> bool:
        """检查目录是否存在"""
        if not self.code_dir.exists():
            print(f"❌ 错误: code 目录不存在: {self.code_dir}")
            return False
        
        # 创建 data 目录（如果不存在）
        self.data_dir.mkdir(exist_ok=True)
        print(f"✅ data 目录已准备: {self.data_dir}")
        
        return True
    
    def should_exclude(self, filename: str) -> bool:
        """判断文件是否应该被排除"""
        filename_lower = filename.lower()
        for keyword in self.exclude_keywords:
            if keyword in filename_lower:
                return True
        return False
    
    def is_executable(self, file_path: Path) -> bool:
        """
        判断文件是否为可执行文件
        检查方法：1. 扩展名 2. Linux/Mac 执行权限
        """
        # 检查扩展名
        if file_path.suffix.lower() in self.executable_extensions:
            return True
        
        # 检查是否有执行权限（Linux/Mac）
        if sys.platform != 'win32':
            try:
                # 获取文件状态
                file_stat = file_path.stat()
                # 检查是否有执行权限（所有者、组或其他用户的执行位）
                is_exec = (file_stat.st_mode & (stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)) != 0
                if is_exec:
                    return True
            except:
                pass
        
        return False
    
    def delete_executable(self, file_path: Path, file_type: str) -> bool:
        """删除可执行文件"""
        try:
            file_path.unlink()
            print(f"   🗑️  已删除 [{file_type}]: {file_path.name}")
            return True
        except Exception as e:
            print(f"   ❌ 删除失败 [{file_type}]: {file_path.name} - {e}")
            return False
    
    def scan_and_delete_executables(self, directory: Path) -> int:
        """扫描并删除目录下的可执行文件"""
        if not directory.exists():
            return 0
        
        deleted_count = 0
        print(f"\n🔍 扫描 {directory.relative_to(self.current_dir)} 目录中的可执行文件...")
        
        for file_path in directory.iterdir():
            if file_path.is_file() and self.is_executable(file_path):
                # 确定文件类型
                if file_path.suffix.lower() in self.executable_extensions:
                    file_type = f"可执行文件{file_path.suffix}"
                else:
                    file_type = "可执行文件(有执行权限)"
                
                print(f"  发现: {file_path.name}")
                if self.delete_executable(file_path, file_type):
                    deleted_count += 1
        
        return deleted_count
    
    def get_file_type_name(self, suffix: str) -> str:
        """获取文件类型名称"""
        type_names = {
            '.cpp': 'C++代码',
            '.md': 'Markdown题解',
            '.conf': '配置文件'
        }
        return type_names.get(suffix, suffix)
    
    def get_choice(self, filename: str, file_type: str) -> str:
        """
        获取用户对重名文件的选择
        
        Returns:
            'overwrite', 'skip', 'rename', 'all_overwrite', 'all_skip', 'all_rename'
        """
        # 如果已经记住了这个文件的默认选择
        if filename in self.remember_choice:
            return self.remember_choice[filename]
        
        # 如果有全局默认策略
        if self.global_default:
            choice = self.global_default
            print(f"   📌 使用全局策略: {choice}")
            return choice
        
        # 交互式询问
        print(f"\n   ⚠️  文件已存在: {filename}")
        print(f"   类型: {file_type}")
        print(f"   选项:")
        print(f"     [O] 覆盖 (overwrite)")
        print(f"     [S] 跳过 (skip)")
        print(f"     [R] 重命名 (rename) - 自动添加序号")
        print(f"     [A] 全部覆盖 (overwrite all)")
        print(f"     [K] 全部跳过 (skip all)")
        print(f"     [E] 全部重命名 (rename all)")
        
        while True:
            choice = input("   请选择 (O/S/R/A/K/E): ").strip().lower()
            
            if choice in ['o', 'overwrite']:
                return 'overwrite'
            elif choice in ['s', 'skip']:
                return 'skip'
            elif choice in ['r', 'rename']:
                return 'rename'
            elif choice in ['a', 'all_overwrite']:
                self.global_default = 'overwrite'
                return 'overwrite'
            elif choice in ['k', 'all_skip']:
                self.global_default = 'skip'
                return 'skip'
            elif choice in ['e', 'all_rename']:
                self.global_default = 'rename'
                return 'rename'
            else:
                print("   无效输入，请重新选择")
    
    def move_file(self, source_path: Path, dest_path: Path, filename: str, file_type: str) -> Tuple[bool, str]:
        """
        移动文件，处理重名情况
        
        Returns:
            (success, action) - action: 'moved', 'skipped', 'overwritten', 'renamed'
        """
        try:
            # 如果目标文件不存在，直接移动
            if not dest_path.exists():
                shutil.move(str(source_path), str(dest_path))
                return True, 'moved'
            
            # 目标文件存在，需要用户选择
            choice = self.get_choice(filename, file_type)
            
            # 记住这个文件的选择（用于同一文件名的其他扩展名）
            self.remember_choice[filename] = choice
            
            if choice == 'overwrite':
                # 覆盖现有文件
                shutil.move(str(source_path), str(dest_path))
                return True, 'overwritten'
            
            elif choice == 'skip':
                # 跳过，不移动
                return False, 'skipped'
            
            elif choice == 'rename':
                # 重命名：添加序号
                counter = 1
                stem = dest_path.stem
                suffix = dest_path.suffix
                while dest_path.exists():
                    new_name = f"{stem}_{counter}{suffix}"
                    dest_path = self.data_dir / new_name
                    counter += 1
                shutil.move(str(source_path), str(dest_path))
                print(f"   📝 重命名为: {dest_path.name}")
                return True, 'renamed'
            
            return False, 'skipped'
            
        except Exception as e:
            print(f"   ❌ 移动失败: {e}")
            return False, 'error'
    
    def scan_and_process(self):
        """扫描并处理文件"""
        print("\n📁 扫描 code 目录...")
        
        # 收集所有需要处理的文件
        files_to_process = []
        for file_path in self.code_dir.iterdir():
            if file_path.is_file() and file_path.suffix in self.supported_extensions:
                files_to_process.append(file_path)
        
        if not files_to_process:
            print("⚠️  没有找到 .cpp、.md 或 .conf 文件")
            return False
        
        # 按文件类型分组显示
        files_by_type = {ext: [] for ext in self.supported_extensions}
        for file_path in files_to_process:
            files_by_type[file_path.suffix].append(file_path)
        
        print(f"\n找到 {len(files_to_process)} 个文件:")
        for ext, files in files_by_type.items():
            if files:
                print(f"  {self.get_file_type_name(ext)}: {len(files)} 个")
        
        print("\n" + "="*50)
        
        # 处理每个文件
        for file_path in files_to_process:
            filename = file_path.name
            file_suffix = file_path.suffix
            file_type = self.get_file_type_name(file_suffix)
            
            # 检查是否需要排除
            if self.should_exclude(filename):
                print(f"⏭️  跳过 [{file_type}]: {filename} (包含排除关键词)")
                if file_suffix == '.cpp':
                    self.stats['cpp_skipped'] += 1
                elif file_suffix == '.md':
                    self.stats['md_skipped'] += 1
                else:
                    self.stats['conf_skipped'] += 1
                continue
            
            # 目标路径
            dest_path = self.data_dir / filename
            
            # 移动文件
            print(f"📦 处理 [{file_type}]: {filename}")
            success, action = self.move_file(file_path, dest_path, filename, file_type)
            
            if success:
                if file_suffix == '.cpp':
                    if action == 'overwritten':
                        self.stats['cpp_overwritten'] += 1
                    elif action == 'renamed':
                        self.stats['cpp_moved'] += 1
                    else:
                        self.stats['cpp_moved'] += 1
                elif file_suffix == '.md':
                    if action == 'overwritten':
                        self.stats['md_overwritten'] += 1
                    elif action == 'renamed':
                        self.stats['md_moved'] += 1
                    else:
                        self.stats['md_moved'] += 1
                else:
                    if action == 'overwritten':
                        self.stats['conf_overwritten'] += 1
                    elif action == 'renamed':
                        self.stats['conf_moved'] += 1
                    else:
                        self.stats['conf_moved'] += 1
                
                if action == 'overwritten':
                    print(f"   ✅ 已覆盖原有文件")
                elif action == 'renamed':
                    print(f"   ✅ 已重命名并移动")
                else:
                    print(f"   ✅ 已移动")
            else:
                if action == 'skipped':
                    print(f"   ⏭️  已跳过")
                    if file_suffix == '.cpp':
                        self.stats['cpp_skipped'] += 1
                    elif file_suffix == '.md':
                        self.stats['md_skipped'] += 1
                    else:
                        self.stats['conf_skipped'] += 1
                else:
                    self.stats['errors'] += 1
        
        return True
    
    def clean_executables(self):
        """清理所有可执行文件"""
        print("\n" + "="*50)
        print("🗑️  清理可执行文件")
        print("="*50)
        
        # 清理 code 目录
        code_deleted = self.scan_and_delete_executables(self.code_dir)
        self.stats['executables_deleted'] += code_deleted
        
        # 清理 data 目录（如果存在）
        if self.data_dir.exists():
            data_deleted = self.scan_and_delete_executables(self.data_dir)
            self.stats['executables_deleted'] += data_deleted
        
        # 清理当前目录
        current_deleted = self.scan_and_delete_executables(self.current_dir)
        self.stats['executables_deleted'] += current_deleted
        
        if self.stats['executables_deleted'] == 0:
            print("\n✅ 没有找到可执行文件")
    
    def show_stats(self):
        """显示移动统计信息"""
        print("\n" + "="*50)
        print("📊 统计报告:")
        print("="*50)
        
        # 文件移动统计
        print("\n📁 文件移动:")
        if self.stats['cpp_moved'] > 0 or self.stats['cpp_overwritten'] > 0:
            print(f"  .cpp 文件:")
            print(f"    ✅ 新移动: {self.stats['cpp_moved']}")
            if self.stats['cpp_overwritten'] > 0:
                print(f"    🔄 覆盖: {self.stats['cpp_overwritten']}")
            print(f"    ⏭️  跳过: {self.stats['cpp_skipped']}")
        
        if self.stats['md_moved'] > 0 or self.stats['md_overwritten'] > 0:
            print(f"  .md 文件:")
            print(f"    ✅ 新移动: {self.stats['md_moved']}")
            if self.stats['md_overwritten'] > 0:
                print(f"    🔄 覆盖: {self.stats['md_overwritten']}")
            print(f"    ⏭️  跳过: {self.stats['md_skipped']}")
        
        if self.stats['conf_moved'] > 0 or self.stats['conf_overwritten'] > 0:
            print(f"  .conf 文件:")
            print(f"    ✅ 新移动: {self.stats['conf_moved']}")
            if self.stats['conf_overwritten'] > 0:
                print(f"    🔄 覆盖: {self.stats['conf_overwritten']}")
            print(f"    ⏭️  跳过: {self.stats['conf_skipped']}")
        
        total_moved = self.stats['cpp_moved'] + self.stats['md_moved'] + self.stats['conf_moved']
        total_overwritten = self.stats['cpp_overwritten'] + self.stats['md_overwritten'] + self.stats['conf_overwritten']
        total_skipped = self.stats['cpp_skipped'] + self.stats['md_skipped'] + self.stats['conf_skipped']
        
        print(f"\n  📈 文件移动总计:")
        print(f"    ✅ 新移动: {total_moved}")
        if total_overwritten > 0:
            print(f"    🔄 覆盖: {total_overwritten}")
        print(f"    ⏭️  跳过: {total_skipped}")
        
        # 可执行文件删除统计
        if self.stats['executables_deleted'] > 0:
            print(f"\n🗑️  可执行文件清理:")
            print(f"    🗑️  已删除: {self.stats['executables_deleted']} 个")
        
        if self.stats['errors'] > 0:
            print(f"\n❌ 错误数: {self.stats['errors']}")
        
        print("="*50)
    
    def run_py_script(self):
        """运行 run.py 脚本"""
        run_py_path = self.current_dir / "run.py"
        
        if not run_py_path.exists():
            print(f"\n⚠️  警告: run.py 不存在: {run_py_path}")
            print("文件移动完成，但未执行 run.py")
            return False
        
        print(f"\n🚀 正在执行 run.py...")
        print("="*50)
        
        try:
            # 运行 run.py
            result = subprocess.run(
                [sys.executable, str(run_py_path)],
                cwd=str(self.current_dir),
                capture_output=False,
                text=True
            )
            
            if result.returncode == 0:
                print("\n✅ run.py 执行成功")
                return True
            else:
                print(f"\n❌ run.py 执行失败，退出码: {result.returncode}")
                return False
                
        except Exception as e:
            print(f"\n❌ 执行 run.py 时出错: {e}")
            return False
    
    def run(self, auto_run: bool = False, dry_run: bool = False, skip_clean: bool = False):
        """
        主运行函数
        
        Args:
            auto_run: 是否自动运行 run.py
            dry_run: 是否模拟运行
            skip_clean: 是否跳过清理可执行文件
        """
        print("="*50)
        print("📁 文件整理工具 v4.0")
        print("="*50)
        print(f"当前目录: {self.current_dir}")
        print(f"code 目录: {self.code_dir}")
        print(f"data 目录: {self.data_dir}")
        print(f"支持的文件类型: {', '.join(self.supported_extensions)}")
        print(f"排除关键词: {', '.join(self.exclude_keywords)}")
        
        if dry_run:
            print("\n🔍 模拟运行模式 - 不会实际移动或删除文件")
        
        # 检查目录
        if not self.check_directories():
            return
        
        if dry_run:
            # 模拟运行，只显示会移动哪些文件
            self.dry_run()
        else:
            # 实际移动文件
            if not self.scan_and_process():
                return
            self.show_stats()
        
        # 清理可执行文件（如果不是模拟运行且没有跳过）
        if not dry_run and not skip_clean:
            self.clean_executables()
            if self.stats['executables_deleted'] > 0:
                print(f"\n✅ 已删除 {self.stats['executables_deleted']} 个可执行文件")
        
        # 询问是否运行 run.py
        if not auto_run and not dry_run:
            print("\n" + "="*50)
            response = input("是否继续运行 run.py? (y/n, 默认 y): ").strip().lower()
            
            if response == '' or response == 'y' or response == 'yes':
                self.run_py_script()
            else:
                print("⏭️  跳过执行 run.py")
        elif auto_run and not dry_run:
            # 自动运行模式
            self.run_py_script()
        
        print("\n✨ 完成!")
    
    def dry_run(self):
        """模拟运行，只显示会移动和删除的文件"""
        print("\n📁 模拟扫描 code 目录...")
        
        files_found = False
        conflicts = []
        
        for file_path in self.code_dir.iterdir():
            if file_path.is_file():
                if file_path.suffix in self.supported_extensions:
                    files_found = True
                    filename = file_path.name
                    file_suffix = file_path.suffix
                    file_type = self.get_file_type_name(file_suffix)
                    
                    if self.should_exclude(filename):
                        print(f"  ⏭️  [跳过] {file_type}: {filename} (包含排除关键词)")
                    else:
                        dest_path = self.data_dir / filename
                        if dest_path.exists():
                            conflicts.append(filename)
                            print(f"  ⚠️  [冲突] {file_type}: {filename} (目标文件已存在)")
                        else:
                            print(f"  ✅ [移动] {file_type}: {filename}")
                elif self.is_executable(file_path):
                    files_found = True
                    print(f"  🗑️  [删除] 可执行文件: {file_path.name}")
        
        if not files_found:
            print("  ⚠️  没有找到任何文件")
        elif conflicts:
            print(f"\n  ⚠️  发现 {len(conflicts)} 个重名冲突文件")
            print("  实际运行时会询问如何处理")
        
        # 模拟清理其他目录
        print("\n🔍 模拟清理其他目录的可执行文件...")
        for directory in [self.data_dir, self.current_dir]:
            if directory.exists():
                for file_path in directory.iterdir():
                    if file_path.is_file() and self.is_executable(file_path):
                        print(f"  🗑️  [将删除] {directory.relative_to(self.current_dir)}/{file_path.name}")


def main():
    """主函数"""
    import argparse
    
    parser = argparse.ArgumentParser(
        description='移动 code 目录中的 .cpp、.md、.conf 文件到 data 目录，删除可执行文件，并运行 run.py',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  %(prog)s                    # 移动文件，清理可执行文件，并交互式询问是否运行 run.py
  %(prog)s --auto-run         # 移动文件后自动运行 run.py
  %(prog)s --no-run           # 只移动文件，不运行 run.py
  %(prog)s --skip-clean       # 跳过清理可执行文件
  %(prog)s --dry-run          # 模拟运行，只显示会移动和删除哪些文件
  
重名处理说明:
  当目标文件已存在时，会询问:
    O - 覆盖原有文件
    S - 跳过此文件
    R - 重命名（添加序号）
    A - 全部覆盖（后续重名自动覆盖）
    K - 全部跳过（后续重名自动跳过）
    E - 全部重命名（后续重名自动重命名）
        """
    )
    
    parser.add_argument('--auto-run', action='store_true', 
                        help='移动文件后自动运行 run.py（不询问）')
    parser.add_argument('--no-run', action='store_true', 
                        help='移动文件后不运行 run.py')
    parser.add_argument('--skip-clean', action='store_true', 
                        help='跳过清理可执行文件')
    parser.add_argument('--dry-run', action='store_true', 
                        help='模拟运行，不实际移动或删除文件')
    
    args = parser.parse_args()
    
    # 处理 --no-run 和 --auto-run 冲突
    if args.no_run and args.auto_run:
        print("❌ 错误: --no-run 和 --auto-run 不能同时使用")
        return
    
    organizer = FileOrganizer()
    
    # 确定是否自动运行
    auto_run = args.auto_run or False
    if args.no_run:
        auto_run = False
    
    organizer.run(auto_run=auto_run, dry_run=args.dry_run, skip_clean=args.skip_clean)


if __name__ == "__main__":
    main()