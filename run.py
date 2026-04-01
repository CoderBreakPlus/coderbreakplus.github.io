import os
import sys
import re
from collections import defaultdict
from datetime import datetime

# =======================
#   HTML & CSS 模板定义
# =======================

HTML_TEMPLATE = """<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{title} - 题目整理索引</title>
    <style>
        :root {{ --primary: #1a73e8; --bg: #f4f5f7; --text: #333; --border: #e0e0e0; }}
        body {{ font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif; background: var(--bg); color: var(--text); margin: 0; padding: 0; line-height: 1.6; }}
        .container {{ max-width: 1200px; margin: 20px auto; padding: 20px; background: #fff; border-radius: 8px; box-shadow: 0 2px 8px rgba(0,0,0,0.05); }}
        h1, h2, h3 {{ color: #202124; margin-bottom: 10px; }}
        
        /* 导航与跳转 */
        .nav-bar {{ margin-bottom: 20px; padding-bottom: 10px; border-bottom: 2px solid var(--border); }}
        .nav-bar a {{ color: var(--primary); text-decoration: none; font-weight: 500; margin-right: 15px; }}
        .nav-bar a:hover {{ text-decoration: underline; }}
        .quick-jump {{ background: #f8f9fa; padding: 15px; border-radius: 6px; margin-bottom: 20px; font-size: 0.9em; }}
        .quick-jump a {{ display: inline-block; margin: 4px 12px 4px 0; color: #5f6368; text-decoration: none; }}
        .quick-jump a:hover {{ color: var(--primary); }}
        
        /* 统计栏与排序 */
        .stats-bar {{ display: flex; justify-content: space-between; align-items: center; background: #e8f0fe; padding: 15px 20px; border-radius: 6px; margin-bottom: 20px; flex-wrap: wrap; gap: 10px; }}
        .stats-info span {{ margin-right: 15px; font-size: 0.95em; color: #174ea6; font-weight: 500; }}
        .sort-btns button {{ background: #fff; border: 1px solid #d2e3fc; color: #1a73e8; padding: 6px 12px; border-radius: 4px; cursor: pointer; font-size: 0.9em; transition: 0.2s; margin-left: 5px; }}
        .sort-btns button:hover {{ background: #f1f3f4; }}

        /* 比赛分组折叠 */
        .contest-wrapper {{ margin-bottom: 20px; }}
        .contest-header {{ background: #fafafa; padding: 12px 15px; border: 1px solid var(--border); border-radius: 4px; cursor: pointer; font-weight: bold; display: flex; justify-content: space-between; align-items: center; transition: background 0.2s; }}
        .contest-header:hover {{ background: #f1f3f4; }}
        .arrow {{ transition: transform 0.3s ease; display: inline-block; }}
        
        /* 表格样式 */
        table {{ width: 100%; border-collapse: collapse; margin-top: 10px; }}
        th, td {{ border: 1px solid var(--border); padding: 12px; text-align: left; vertical-align: top; }}
        th {{ background: #f8f9fa; color: #5f6368; font-weight: 600; }}
        tr:hover {{ background-color: #fcfcfc; }}
        
        /* 标签与链接 */
        .tag {{ display: inline-block; padding: 2px 8px; border-radius: 4px; font-size: 0.8em; font-weight: bold; min-width: 45px; text-align: center; margin-right: 8px; }}
        .tag-easy {{ background: #e6f4ea; color: #1e8e3e; }}
        .tag-hard {{ background: #fce8e6; color: #d93025; }}
        .tag-normal {{ background: #f1f3f4; color: #5f6368; }}
        .file-link {{ color: var(--primary); text-decoration: none; margin-right: 12px; font-size: 0.95em; }}
        .file-link:hover {{ text-decoration: underline; }}
        .version-row {{ margin-bottom: 6px; display: flex; align-items: center; }}
        .version-row:last-child {{ margin-bottom: 0; }}
        
        .footer {{ margin-top: 40px; padding-top: 20px; border-top: 1px solid var(--border); text-align: center; color: #80868b; font-size: 0.85em; }}
    </style>
</head>
<body>
    <div class="container">
        <div class="nav-bar">
            <a href="index.html">🏠 返回首页</a>
            <span style="color:#aaa;">|</span>
            <span style="margin-left: 15px; font-size: 0.9em; color: #666;">支持 Easy/Hard Version 自动合并显示</span>
        </div>
        
        <h1>{title}</h1>
        {subtitle}
        
        <div class="stats-bar">
            <div class="stats-info">{stats_html}</div>
            {sort_html}
        </div>
        
        {quick_jump_html}
        
        <div id="contests-container">
            {content_html}
        </div>
        
        <div class="footer">
            生成时间: {gen_time} | 题目整理工具自动生成
        </div>
    </div>

    <script>
        function toggleContest(header) {{
            const content = header.nextElementSibling;
            const arrow = header.querySelector('.arrow');
            if (content.style.display === 'none') {{
                content.style.display = 'table';
                arrow.style.transform = 'rotate(0deg)';
            }} else {{
                content.style.display = 'none';
                arrow.style.transform = 'rotate(-90deg)';
            }}
        }}

        function sortContests(type) {{
            const container = document.getElementById('contests-container');
            const wrappers = Array.from(container.getElementsByClassName('contest-wrapper'));
            wrappers.sort((a, b) => {{
                if (type === 'count') {{
                    return parseInt(b.dataset.count) - parseInt(a.dataset.count);
                }} else {{
                    return a.dataset.name.localeCompare(b.dataset.name);
                }}
            }});
            wrappers.forEach(w => container.appendChild(w));
        }}
    </script>
</body>
</html>
"""

# =======================
#   数据结构与解析模型
# =======================

class ProblemVersion:
    def __init__(self, name):
        self.name = name  # 'Normal', 'Easy', 'Hard'
        self.files = {'cpp': None, 'md': None, 'conf': None}

class ProblemGroup:
    def __init__(self, base_name):
        self.base_name = base_name
        self.category = "杂题"
        self.contest_name = ""
        self.problem_id = ""
        self.link = "#"
        self.note = ""
        self.versions = {}
        self.version_order =['Normal', 'Easy', 'Hard']

    def add_file(self, version, ext, filename):
        if version not in self.versions:
            self.versions[version] = ProblemVersion(version)
        if ext == '.cpp': self.versions[version].files['cpp'] = filename
        elif ext == '.md': self.versions[version].files['md'] = filename
        elif ext == '.conf': self.versions[version].files['conf'] = filename

def scan_and_group_files(data_dir):
    groups = {}
    
    # 步骤1：找到所有明确的 .conf base name
    conf_bases = set()
    if os.path.exists(data_dir):
        for f in os.listdir(data_dir):
            if f.endswith('.conf'):
                conf_bases.add(f[:-5])

    # 步骤2：遍历识别并分组
    for f in os.listdir(data_dir):
        if not os.path.isfile(os.path.join(data_dir, f)):
            continue
        
        name, ext = os.path.splitext(f)
        if ext not in ['.cpp', '.md', '.conf']:
            continue

        base_name = None
        version = 'Normal'
        
        # A. CF 正则匹配 (如 cf1336e1)
        m_cf = re.match(r'^cf(\d+)([a-zA-Z]+?)(1|2)?$', name, re.IGNORECASE)
        # B. AtCoder 正则匹配 (如 abc001a1)
        m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+?)(1|2)?$', name, re.IGNORECASE)

        if m_cf:
            base_name = f"cf{m_cf.group(1)}{m_cf.group(2).lower()}"
            version = 'Easy' if m_cf.group(3) == '1' else ('Hard' if m_cf.group(3) == '2' else 'Normal')
        elif m_ac:
            base_name = f"{m_ac.group(1).lower()}{m_ac.group(2)}{m_ac.group(3).lower()}"
            version = 'Easy' if m_ac.group(4) == '1' else ('Hard' if m_ac.group(4) == '2' else 'Normal')
        else:
            # C. 匹配已知 conf 的题目组
            matched_conf_base = None
            for cb in sorted(conf_bases, key=len, reverse=True):
                if name == cb:
                    matched_conf_base, version = cb, 'Normal'
                    break
                elif name == cb + '1' or name == cb + '_e1':
                    matched_conf_base, version = cb, 'Easy'
                    break
                elif name == cb + '2' or name == cb + '_e2':
                    matched_conf_base, version = cb, 'Hard'
                    break
            
            if matched_conf_base:
                base_name = matched_conf_base
            else:
                # D. 杂题/其他格式回退匹配
                if name.endswith('_e1'): base_name, version = name[:-3], 'Easy'
                elif name.endswith('_e2'): base_name, version = name[:-3], 'Hard'
                elif name.endswith('1'): base_name, version = name[:-1], 'Easy'
                elif name.endswith('2'): base_name, version = name[:-1], 'Hard'
                else: base_name, version = name, 'Normal'

        if base_name not in groups:
            groups[base_name] = ProblemGroup(base_name)
        groups[base_name].add_file(version, ext, f)

    return groups

def apply_categories_and_links(groups, data_dir):
    for group in groups.values():
        conf_file = None
        for v in group.versions.values():
            if v.files['conf']:
                conf_file = v.files['conf']
                break

        if conf_file:
            try:
                with open(os.path.join(data_dir, conf_file), 'r', encoding='utf-8') as f:
                    lines =[line.strip() for line in f.readlines()]
                if len(lines) >= 5:
                    cat = lines[0].lower()
                    group.category = cat if cat in['oi', 'xcpc', 'xcpc+'] else '杂题'
                    group.link = lines[1] if lines[1] else '#'
                    group.contest_name = lines[2]
                    group.problem_id = lines[3]
                    group.note = lines[4]
                else:
                    group.category = '杂题'
            except Exception as e:
                print(f"读取 {conf_file} 失败: {e}")
                group.category = '杂题'
        else:
            m_cf = re.match(r'^cf(\d+)([a-zA-Z]+)$', group.base_name, re.IGNORECASE)
            m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+)$', group.base_name, re.IGNORECASE)
            
            if m_cf:
                group.category = 'Codeforces'
                group.contest_name = f"Codeforces Round {m_cf.group(1)}"
                group.problem_id = m_cf.group(2).upper()
                group.link = f"https://codeforces.com/problemset/problem/{m_cf.group(1)}/{m_cf.group(2).upper()}"
            elif m_ac:
                group.category = 'AtCoder'
                c_type = m_ac.group(1).upper()
                c_num = m_ac.group(2)
                group.contest_name = f"{c_type} {c_num}"
                group.problem_id = m_ac.group(3).upper()
                c_name_lower = f"{c_type.lower()}{c_num}"
                group.link = f"https://atcoder.jp/contests/{c_name_lower}/tasks/{c_name_lower}_{group.problem_id.lower()}"
            else:
                group.category = '杂题'

# =======================
#   HTML 生成逻辑
# =======================

def generate_versions_html(group, rel_path):
    v_htmls =[]
    has_multiple = len(group.versions) > 1
    
    for v_name in group.version_order:
        if v_name in group.versions:
            v = group.versions[v_name]
            tag = ""
            if has_multiple:
                if v_name == 'Easy': tag = '<span class="tag tag-easy">Easy</span>'
                elif v_name == 'Hard': tag = '<span class="tag tag-hard">Hard</span>'
                else: tag = '<span class="tag tag-normal">Normal</span>'
            
            links = []
            if v.files['cpp']: 
                links.append(f'<a href="{rel_path}/{v.files["cpp"]}" class="file-link">📝 代码</a>')
            
            if v.files['md']: 
                # 这里移除 .md 后缀
                md_filename = v.files['md']
                md_href = md_filename[:-3] if md_filename.endswith('.md') else md_filename
                links.append(f'<a href="{rel_path}/{md_href}" class="file-link">💡 题解</a>')
                
            if v.files['conf']: 
                links.append(f'<a href="{rel_path}/{v.files["conf"]}" class="file-link">⚙️ 配置</a>')
            
            v_htmls.append(f'<div class="version-row">{tag}{"".join(links)}</div>')
    
    return "".join(v_htmls)

def build_category_page(title, groups_dict, out_path, rel_path, is_flat=False):
    total_groups = 0
    total_versions = 0
    has_cpp = 0
    has_md = 0
    has_conf = 0
    
    all_groups =[]
    if is_flat:
        all_groups = groups_dict
    else:
        for gs in groups_dict.values():
            all_groups.extend(gs)
            
    total_groups = len(all_groups)
    for g in all_groups:
        total_versions += len(g.versions)
        if any(v.files['cpp'] for v in g.versions.values()): has_cpp += 1
        if any(v.files['md'] for v in g.versions.values()): has_md += 1
        if any(v.files['conf'] for v in g.versions.values()): has_conf += 1

    stats_html = f"""
        <span>📁 题目组数: {total_groups}</span>
        <span>📄 总版本数: {total_versions}</span>
        <span>📝 有代码: {has_cpp}</span>
        <span>💡 有题解: {has_md}</span>
        <span>⚙️ 有配置: {has_conf}</span>
    """
    
    if not is_flat:
        stats_html += f"<span>🏆 比赛数: {len(groups_dict)}</span>"
        sort_html = """
        <div class="sort-btns">
            <button onclick="sortContests('count')">按题目数降序</button>
            <button onclick="sortContests('name')">按字典序排列</button>
        </div>"""
    else:
        sort_html = ""

    content_html = ""
    quick_jump_html = ""
    
    if is_flat:
        content_html += """
        <table>
            <tr><th width="30%">题目名称</th><th width="70%">代码/题解/配置</th></tr>"""
        for g in sorted(all_groups, key=lambda x: x.base_name):
            v_html = generate_versions_html(g, rel_path)
            content_html += f"""
            <tr>
                <td><b>{g.base_name}</b></td>
                <td>{v_html}</td>
            </tr>"""
        content_html += "</table>"
    else:
        jump_links =[]
        sorted_contests = sorted(groups_dict.items(), key=lambda x: len(x[1]), reverse=True)
        
        for idx, (contest, c_groups) in enumerate(sorted_contests):
            c_id = f"contest-{idx}"
            jump_links.append(f'<a href="#{c_id}">📍 {contest} ({len(c_groups)})</a>')
            
            content_html += f"""
            <div class="contest-wrapper" data-name="{contest}" data-count="{len(c_groups)}">
                <div class="contest-header" onclick="toggleContest(this)" id="{c_id}">
                    <span>{contest} ({len(c_groups)} 题)</span>
                    <span class="arrow">▼</span>
                </div>
                <table class="contest-table" style="display: table;">
                    <tr>
                        <th width="20%">题目编号</th>
                        <th width="25%">题目链接</th>
                        <th width="40%">代码/题解/配置</th>
                        <th width="15%">备注</th>
                    </tr>"""
            
            for g in sorted(c_groups, key=lambda x: x.problem_id):
                v_html = generate_versions_html(g, rel_path)
                link_html = f'<a href="{g.link}" target="_blank">{g.link[:40] + "..." if len(g.link)>40 else g.link}</a>' if g.link != '#' else '无链接'
                content_html += f"""
                    <tr>
                        <td><b>{g.problem_id if g.problem_id else g.base_name}</b></td>
                        <td style="word-break: break-all;">{link_html}</td>
                        <td>{v_html}</td>
                        <td>{g.note}</td>
                    </tr>"""
            content_html += "</table></div>"
            
        quick_jump_html = f'<div class="quick-jump"><strong>快速跳转：</strong><br>{"".join(jump_links)}</div>'

    html = HTML_TEMPLATE.format(
        title=title,
        subtitle="",  # 子页面无副标题
        stats_html=stats_html,
        sort_html=sort_html,
        quick_jump_html=quick_jump_html,
        content_html=content_html,
        gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    
    with open(out_path, 'w', encoding='utf-8') as f:
        f.write(html)


def build_index_page(categories, out_path):
    stats =[]
    for cat, data in categories.items():
        if cat == '杂题':
            count = len(data)
            stats.append((cat, count, f"{count} 个杂题组"))
        else:
            c_count = len(data)
            p_count = sum(len(gs) for gs in data.values())
            stats.append((cat, p_count, f"{c_count} 个比赛，{p_count} 个题目组"))
            
    # 1. 首页独有的“第二行” .conf 配置文件说明副标题
    subtitle_html = """
    <div style="background: #e8f0fe; color: #174ea6; padding: 12px 18px; border-radius: 6px; margin-bottom: 25px; font-size: 0.95em; border: 1px solid #d2e3fc;">
        <strong>📝 .conf 配置文件写法（固定5行）：</strong>
        第1行: 比赛归类(oi/xcpc/xcpc+) &nbsp;|&nbsp;
        第2行: 完整URL链接 &nbsp;|&nbsp;
        第3行: 比赛名称 &nbsp;|&nbsp;
        第4行: 题目编号 &nbsp;|&nbsp;
        第5行: 备注说明
    </div>
    """

    # 2. 分类导航卡片
    content = "<div style='display:flex; flex-wrap:wrap; gap:20px;'>"
    for cat, _, desc in stats:
        content += f"""
        <div style="background:#fff; border:1px solid #e0e0e0; padding:20px; border-radius:8px; width:calc(33% - 20px); min-width:250px; box-sizing:border-box; box-shadow: 0 2px 4px rgba(0,0,0,0.02);">
            <h2 style="margin-top:0; color:#1a73e8; margin-bottom: 10px;">{cat}</h2>
            <p style="color:#5f6368; font-size:0.95em;">{desc}</p>
            <a href="{cat}.html" style="display:inline-block; margin-top:10px; padding:8px 16px; background:#1a73e8; color:#fff; text-decoration:none; border-radius:4px; font-size:0.9em;">进入分类 →</a>
        </div>"""
    content += "</div>"

    html = HTML_TEMPLATE.format(
        title="首页索引",
        subtitle=subtitle_html,
        stats_html="<span>👋 欢迎使用题目自动整理工具</span>",
        sort_html="",
        quick_jump_html="",
        content_html=content,
        gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    
    with open(out_path, 'w', encoding='utf-8') as f:
        f.write(html)


def main():
    # 1. 参数解析
    data_dir = sys.argv[1] if len(sys.argv) > 1 else 'data'
    # 修改：未指定输出目录时，默认输出到当前目录 '.' （即脚本运行的位置）
    out_dir = sys.argv[2] if len(sys.argv) > 2 else '.'

    if not os.path.exists(data_dir):
        print(f"❌ 错误: 数据目录 '{data_dir}' 不存在！")
        sys.exit(1)

    if out_dir != '.' and not os.path.exists(out_dir):
        os.makedirs(out_dir)

    # 相对路径计算 (给 HTML 中的链接使用)
    rel_data_path = os.path.relpath(data_dir, out_dir).replace('\\', '/')

    print(f"🔍 正在扫描 '{data_dir}'...")
    groups = scan_and_group_files(data_dir)
    print(f"✅ 找到 {len(groups)} 个基础题组，正在分析配置和归类...")
    
    apply_categories_and_links(groups, data_dir)

    # 2. 分类结构化
    categories = {
        'Codeforces': defaultdict(list),
        'AtCoder': defaultdict(list),
        'oi': defaultdict(list),
        'xcpc': defaultdict(list),
        'xcpc+': defaultdict(list),
        '杂题':[]
    }

    for g in groups.values():
        if g.category == '杂题':
            categories['杂题'].append(g)
        else:
            categories[g.category][g.contest_name].append(g)

    # 3. 生成各分类 HTML
    print(f"🛠️ 正在生成 HTML 到 '{out_dir}' (当前目录)...")
    for cat in categories:
        if cat == '杂题':
            build_category_page(cat, categories[cat], os.path.join(out_dir, f"{cat}.html"), rel_data_path, is_flat=True)
        else:
            build_category_page(cat, categories[cat], os.path.join(out_dir, f"{cat}.html"), rel_data_path, is_flat=False)

    # 4. 生成主页 index.html
    build_index_page(categories, os.path.join(out_dir, "index.html"))

    index_abs_path = os.path.abspath(os.path.join(out_dir, 'index.html'))
    print(f"🎉 处理完成！请在浏览器中打开: {index_abs_path}")


if __name__ == '__main__':
    main()