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
        .container {{ max-width: 1400px; margin: 20px auto; padding: 20px; background: #fff; border-radius: 8px; box-shadow: 0 2px 8px rgba(0,0,0,0.05); overflow: hidden; }}
        h1, h2, h3 {{ color: #202124; margin-bottom: 10px; }}
        
        /* 导航与跳转 */
        .nav-bar {{ margin-bottom: 20px; padding-bottom: 10px; border-bottom: 2px solid var(--border); }}
        .nav-bar a {{ color: var(--primary); text-decoration: none; font-weight: 500; margin-right: 15px; }}
        .nav-bar a:hover {{ text-decoration: underline; }}
        
        /* 统计栏与排序 */
        .stats-bar {{ display: flex; justify-content: space-between; align-items: center; background: #e8f0fe; padding: 15px 20px; border-radius: 6px; margin-bottom: 20px; flex-wrap: wrap; gap: 10px; }}
        .stats-info span {{ margin-right: 15px; font-size: 0.95em; color: #174ea6; font-weight: 500; }}
        .sort-btns button {{ background: #fff; border: 1px solid #d2e3fc; color: #1a73e8; padding: 6px 12px; border-radius: 4px; cursor: pointer; font-size: 0.9em; transition: 0.2s; margin-left: 5px; font-weight: 500; }}
        .sort-btns button:hover {{ background: #f1f3f4; }}

        .quick-jump {{ background: #f8f9fa; padding: 15px; border-radius: 6px; margin-bottom: 20px; font-size: 0.95em; line-height: 2; }}
        .quick-jump a {{ display: inline-block; margin: 0 12px 0 0; color: #1a73e8; text-decoration: none; background: #fff; border: 1px solid #d2e3fc; padding: 2px 10px; border-radius: 12px; font-size: 0.9em; }}
        .quick-jump a:hover {{ background: #e8f0fe; }}

        /* ------------------ 
           简约风格矩阵大表格 
           ------------------ */
        .matrix-table {{ width: 100%; border-collapse: collapse; background: #fff; border-radius: 8px; box-shadow: 0 1px 3px rgba(0,0,0,0.05); }}
        .matrix-table thead {{ background: #f8f9fa; }}
        .matrix-table th {{ padding: 12px 10px; border-bottom: 2px solid var(--border); color: #5f6368; font-weight: 600; text-align: center; white-space: nowrap; }}
        .matrix-table td {{ padding: 10px; border-bottom: 1px solid #f0f0f0; border-right: 1px solid #f0f0f0; text-align: center; vertical-align: top; }}
        .matrix-table td:last-child {{ border-right: none; }}
        .matrix-table tbody tr:hover {{ background-color: #fcfcfc; }}
        .contest-name-cell {{ text-align: left !important; font-weight: 600; color: #333; min-width: 150px; vertical-align: middle !important; }}
        
        /* 单元格内的题目模块 */
        .prob-cell {{ display: inline-flex; flex-direction: column; align-items: center; gap: 6px; }}
        .prob-link-wrap {{ font-size: 0.85em; display: flex; align-items: center; justify-content: center; gap: 4px; background: #f1f3f4; padding: 3px 10px; border-radius: 12px; transition: background 0.2s; }}
        .prob-link-wrap:hover {{ background: #e8eaed; }}
        .prob-link-wrap a {{ color: var(--primary); text-decoration: none; font-weight: bold; }}
        .prob-link-wrap a:hover {{ text-decoration: underline; }}
        .prob-note {{ cursor: help; filter: grayscale(1); opacity: 0.6; font-size: 0.9em; transition: 0.2s; }}
        .prob-note:hover {{ filter: none; opacity: 1; transform: scale(1.1); }}
        
        /* 单元格内的微型版本控制 (Code/Md/Conf) */
        .mini-version-row {{ display: flex; align-items: center; justify-content: center; gap: 5px; font-size: 1.05em; margin-bottom: 2px; }}
        .mini-tag {{ font-size: 0.7em; padding: 1px 4px; border-radius: 3px; font-weight: bold; line-height: 1; }}
        .mini-tag-easy {{ background: #e6f4ea; color: #1e8e3e; }}
        .mini-tag-hard {{ background: #fce8e6; color: #d93025; }}
        .mini-file-link {{ text-decoration: none; display: inline-block; transition: transform 0.1s; line-height: 1; }}
        .mini-file-link:hover {{ transform: scale(1.15); }}
        
        /* 杂题的常规表格样式 */
        .normal-table {{ width: 100%; border-collapse: collapse; margin-top: 10px; margin-bottom: 30px; }}
        .normal-table th, .normal-table td {{ border: 1px solid var(--border); padding: 12px; text-align: left; vertical-align: middle; }}
        .normal-table th {{ background: #f8f9fa; color: #5f6368; font-weight: 600; }}
        .normal-table tr:hover {{ background-color: #fcfcfc; }}
        .version-row {{ margin-bottom: 6px; display: flex; align-items: center; }}
        .version-row:last-child {{ margin-bottom: 0; }}
        .file-link {{ color: var(--primary); text-decoration: none; margin-right: 12px; font-size: 0.95em; }}
        .file-link:hover {{ text-decoration: underline; }}
        .tag {{ display: inline-block; padding: 2px 8px; border-radius: 4px; font-size: 0.8em; font-weight: bold; min-width: 45px; text-align: center; margin-right: 8px; }}
        .tag-easy {{ background: #e6f4ea; color: #1e8e3e; }}
        .tag-hard {{ background: #fce8e6; color: #d93025; }}
        .tag-normal {{ background: #f1f3f4; color: #5f6368; }}

        .footer {{ margin-top: 40px; padding-top: 20px; border-top: 1px solid var(--border); text-align: center; color: #80868b; font-size: 0.85em; }}
    </style>
</head>
<body>
    <div class="container">
        <div class="nav-bar">
            <a href="index.html">🏠 返回首页</a>
            <span style="color:#aaa;">|</span>
            <span style="margin-left: 15px; font-size: 0.9em; color: #666;">矩阵视图与智能标签归类</span>
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
        // 针对二维矩阵表格的行排序逻辑
        function sortContests(type) {{
            const tbody = document.querySelector('#contest-table tbody');
            if (!tbody) return;
            const rows = Array.from(tbody.querySelectorAll('tr'));
            rows.sort((a, b) => {{
                if (type === 'count') {{
                    return parseInt(b.dataset.count) - parseInt(a.dataset.count);
                }} else {{
                    return a.dataset.name.localeCompare(b.dataset.name);
                }}
            }});
            rows.forEach(r => tbody.appendChild(r));
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
        self.tags =[]      # 存储标签/关键词
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
        if ext not in['.cpp', '.md', '.conf']:
            continue

        base_name = None
        version = 'Normal'
        
        m_cf = re.match(r'^cf(\d+)([a-zA-Z]+?)(1|2)?$', name, re.IGNORECASE)
        m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+?)(1|2)?$', name, re.IGNORECASE)

        if m_cf:
            base_name = f"cf{m_cf.group(1)}{m_cf.group(2).lower()}"
            version = 'Easy' if m_cf.group(3) == '1' else ('Hard' if m_cf.group(3) == '2' else 'Normal')
        elif m_ac:
            base_name = f"{m_ac.group(1).lower()}{m_ac.group(2)}{m_ac.group(3).lower()}"
            version = 'Easy' if m_ac.group(4) == '1' else ('Hard' if m_ac.group(4) == '2' else 'Normal')
        else:
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
        
        # 1. 首先无论有无配置，都尝试按照正则执行默认初始化 (CF/AC 等)
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

        # 2. 如果存在配置文件，则进行安全覆盖
        conf_file = None
        for v in group.versions.values():
            if v.files['conf']:
                conf_file = v.files['conf']
                break

        if conf_file:
            try:
                with open(os.path.join(data_dir, conf_file), 'r', encoding='utf-8') as f:
                    lines =[line.strip() for line in f.readlines()]
                
                # 安全填充防越界 (确保至少 5 行)
                while len(lines) < 5:
                    lines.append('')
                    
                cat_conf = lines[0].lower()
                if cat_conf in ['oi', 'xcpc', 'xcpc+']:
                    group.category = cat_conf
                elif cat_conf:
                    # 如果填写了不认识的类别，归并至杂题
                    group.category = '杂题'
                # 若 cat_conf 为空，则保留原 category (如果是 CF/AC 则保留，否则默认为 杂题)

                if lines[1]: group.link = lines[1]
                if lines[2]: group.contest_name = lines[2]
                if lines[3]: group.problem_id = lines[3]
                if lines[4]: 
                    # 用空格分割获得全部关键词/标签
                    group.tags = [t for t in lines[4].split() if t]
                    
            except Exception as e:
                print(f"读取配置 {conf_file} 时警告: {e}")

# =======================
#   HTML 生成逻辑
# =======================

def generate_versions_html(group, rel_path, minimal=False):
    v_htmls =[]
    has_multiple = len(group.versions) > 1
    
    for v_name in group.version_order:
        if v_name in group.versions:
            v = group.versions[v_name]
            
            # -------- 极简矩阵样式 (用于比赛页) --------
            if minimal:
                tag = ""
                if has_multiple:
                    if v_name == 'Easy': tag = '<span class="mini-tag mini-tag-easy">E</span>'
                    elif v_name == 'Hard': tag = '<span class="mini-tag mini-tag-hard">H</span>'
                
                links =[]
                if v.files['cpp']: 
                    links.append(f'<a href="{rel_path}/{v.files["cpp"]}" class="mini-file-link" title="代码">📝</a>')
                if v.files['md']: 
                    md_filename = v.files['md']
                    md_href = md_filename[:-3] if md_filename.endswith('.md') else md_filename
                    links.append(f'<a href="{rel_path}/{md_href}" class="mini-file-link" title="题解">💡</a>')
                if v.files['conf']: 
                    links.append(f'<a href="{rel_path}/{v.files["conf"]}" class="mini-file-link" title="配置">⚙️</a>')
                
                v_htmls.append(f'<div class="mini-version-row">{tag}{"".join(links)}</div>')
            
            # -------- 传统列表样式 (用于杂题页) --------
            else:
                tag = ""
                if has_multiple:
                    if v_name == 'Easy': tag = '<span class="tag tag-easy">Easy</span>'
                    elif v_name == 'Hard': tag = '<span class="tag tag-hard">Hard</span>'
                    else: tag = '<span class="tag tag-normal">Normal</span>'
                
                links = []
                if v.files['cpp']: 
                    links.append(f'<a href="{rel_path}/{v.files["cpp"]}" class="file-link">📝 代码</a>')
                if v.files['md']: 
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
    
    # 因为杂题里可能跨 Tag 重复存放相同的题目，去重统计能确保上方统计栏数据精准
    unique_groups = set()
    
    if is_flat:
        # 杂题页面的 groups_dict 结构是 { 'Tag1':[g1, g2], 'Tag2': [g2, g3] }
        for gs in groups_dict.values():
            for g in gs:
                unique_groups.add(g)
    else:
        # 比赛页面的 groups_dict 结构是 { 'ContestName':[g1, g2] }
        for gs in groups_dict.values():
            for g in gs:
                unique_groups.add(g)
                
    total_groups = len(unique_groups)
    for g in unique_groups:
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
            <button onclick="sortContests('name')">按比赛名字典序</button>
        </div>"""
    else:
        sort_html = ""

    content_html = ""
    quick_jump_html = ""
    
    # 【杂题与标签页面】采用标准分类列表风格
    if is_flat:
        # 对 Tags 进行排序，确保 "无标签杂题" 排在最后
        sorted_tags = sorted(groups_dict.keys(), key=lambda x: (x == '无标签杂题', x))
        
        # 1. 生成顶部快速跳转锚点
        jump_links = []
        for idx, tag in enumerate(sorted_tags):
            if not groups_dict[tag]: continue
            c_id = f"tag-{idx}"
            display_tag = tag if tag != '无标签杂题' else '无标签杂题'
            jump_links.append(f'<a href="#{c_id}">📍 {display_tag} ({len(groups_dict[tag])})</a>')
            
        quick_jump_html = f'<div class="quick-jump" style="background:#fff; border:1px solid var(--border);"><strong>🏷️ 标签快速跳转索引：</strong><br>{"".join(jump_links)}</div>'

        # 2. 按 Tag 渲染对应表格
        for idx, tag in enumerate(sorted_tags):
            tag_groups = groups_dict[tag]
            if not tag_groups: continue
            
            c_id = f"tag-{idx}"
            icon = "🏷️" if tag != "无标签杂题" else "📂"
            content_html += f"<h2 id='{c_id}' style='margin-top:30px; color:#1a73e8; padding-bottom: 5px; border-bottom: 2px solid var(--border);'>{icon} {tag} <span style='font-size:0.6em; color:#888; font-weight:normal;'>({len(tag_groups)} 题)</span></h2>"
            content_html += """
            <table class="normal-table">
                <tr><th width="30%">题目名称</th><th width="70%">代码/题解/配置</th></tr>"""
            
            for g in sorted(tag_groups, key=lambda x: x.base_name):
                v_html = generate_versions_html(g, rel_path, minimal=False)
                # 若题目自身来自某个明确的比赛，在题目名后补个来源说明
                origin = f"<br><span style='font-size:0.8em; color:#888; font-weight:normal;'>来源: {g.category} - {g.contest_name}</span>" if g.contest_name else ""
                
                content_html += f"""
                <tr>
                    <td><b>{g.base_name}</b>{origin}</td>
                    <td>{v_html}</td>
                </tr>"""
            content_html += "</table>"
            
    # 【比赛类型】采用二维大表格矩阵风格
    else:
        # 1. 收集并排序所有存在的题目编号 (A, B, C...)
        all_pids = set()
        for c_groups in groups_dict.values():
            for g in c_groups:
                pid = g.problem_id.strip() if g.problem_id else "未知"
                all_pids.add(pid)
                
        def alnum_key(s):
            return[int(c) if c.isdigit() else c.lower() for c in re.split('([0-9]+)', s)]
        # "未知" 排在最后
        sorted_pids = sorted(list(all_pids), key=lambda x: ([float('inf')] if x == '未知' else alnum_key(x)))

        # 2. 构建二维表格
        content_html += '<div style="overflow-x: auto;">'
        content_html += '<table class="matrix-table" id="contest-table">'
        
        content_html += '<thead><tr>'
        content_html += '<th style="text-align: left;">比赛名称</th>'
        for pid in sorted_pids:
            content_html += f'<th>{pid}</th>'
        content_html += '</tr></thead><tbody>'
        
        sorted_contests = sorted(groups_dict.items(), key=lambda x: len(x[1]), reverse=True)
        
        for contest, c_groups in sorted_contests:
            # 有时一场比赛可能没填 PID 造成多人同 PID("未知")，需用 list 防止覆盖
            pid_map = defaultdict(list)
            for g in c_groups:
                pid = g.problem_id.strip() if g.problem_id else "未知"
                pid_map[pid].append(g)
            
            content_html += f'<tr data-name="{contest}" data-count="{len(c_groups)}">'
            
            # 第一列：比赛名
            display_contest = contest if contest else "未归档/无名比赛"
            content_html += f'<td class="contest-name-cell">{display_contest} <br><span style="font-size:0.85em; color:#888; font-weight:normal;">({len(c_groups)} 题)</span></td>'
            
            # 填充各题目列
            for pid in sorted_pids:
                content_html += '<td style="vertical-align: middle;">'
                if pid in pid_map:
                    # 将该 PID 下关联的所有题目铺在这一个格子里
                    for g in sorted(pid_map[pid], key=lambda x: x.base_name):
                        v_html = generate_versions_html(g, rel_path, minimal=True)
                        link_html = f'<a href="{g.link}" target="_blank">🔗题目</a>' if g.link != '#' else '<span style="color:#999; font-size:0.9em; font-weight:bold;">-</span>'
                        
                        # 悬浮备注升级为悬浮标签
                        note_icon = f'<span class="prob-note" title="标签: {", ".join(g.tags)}">🏷️</span>' if g.tags else ''
                        
                        content_html += f"""
                        <div class="prob-cell" style="margin-bottom:6px;">
                            <div class="prob-link-wrap">{link_html}{note_icon}</div>
                            {v_html}
                        </div>"""
                content_html += '</td>'
                    
            content_html += '</tr>'
        
        content_html += '</tbody></table></div>'

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
            # data 是 { 'tagA': [...], 'tagB': [...], '无标签杂题': [...] }
            # 需要先用 set 去重求真实题目数，以免跨标签导致重复计数
            unique_groups = set()
            for gs in data.values():
                for g in gs:
                    unique_groups.add(g.base_name)
                    
            tag_count = len([k for k in data.keys() if k != '无标签杂题' and data[k]])
            p_count = len(unique_groups)
            stats.append((cat, p_count, f"包含 {tag_count} 个关键词标签，共 {p_count} 个相关题目组"))
        else:
            c_count = len(data)
            p_count = sum(len(gs) for gs in data.values())
            stats.append((cat, p_count, f"共 {c_count} 场比赛，包含 {p_count} 个题目组"))
            
    # 首页独有的配置说明区块
    subtitle_html = """
    <div style="background: #e8f0fe; color: #174ea6; padding: 16px 20px; border-radius: 6px; margin-bottom: 25px; font-size: 0.95em; border: 1px solid #d2e3fc; line-height: 1.8;">
        <strong>📝 任何题目均可添加 .conf 配置文件（固定 5 行，不需要的信息可直接留空换行）：</strong><br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 1 行:</span> 比赛分类 (<code>oi</code> / <code>xcpc</code> / <code>xcpc+</code>)。留空则保留系统自动识别，或默认归至杂题。<br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 2 行:</span> 完整 URL 链接。CF/AT 等留空仍可自动生成官方链接。<br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 3 行:</span> 比赛名称。留空表示无所属具体赛事。<br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 4 行:</span> 题目编号 (如 A, B, C...)。<br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 5 行:</span> 标签/关键词。多个 tag 用空格隔开。<strong>所有含有标签的题目将全部被汇聚至“杂题”内作为知识点索引归类！</strong>
    </div>
    """

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
    data_dir = sys.argv[1] if len(sys.argv) > 1 else 'data'
    out_dir = sys.argv[2] if len(sys.argv) > 2 else '.'

    if not os.path.exists(data_dir):
        print(f"❌ 错误: 数据目录 '{data_dir}' 不存在！")
        sys.exit(1)

    if out_dir != '.' and not os.path.exists(out_dir):
        os.makedirs(out_dir)

    rel_data_path = os.path.relpath(data_dir, out_dir).replace('\\', '/')

    print(f"🔍 正在扫描 '{data_dir}'...")
    groups = scan_and_group_files(data_dir)
    print(f"✅ 找到 {len(groups)} 个基础题组，正在分析配置和归类...")
    
    apply_categories_and_links(groups, data_dir)

    # 对于杂题，其底层结构升级为：按照 Tag 为 Key 建立的字典
    categories = {
        'Codeforces': defaultdict(list),
        'AtCoder': defaultdict(list),
        'oi': defaultdict(list),
        'xcpc': defaultdict(list),
        'xcpc+': defaultdict(list),
        '杂题': defaultdict(list)
    }

    for g in groups.values():
        
        # 1. 投放到所属的大类与比赛中 (除了纯正的无归属杂题外)
        if g.category != '杂题':
            categories[g.category][g.contest_name].append(g)

        # 2. 【知识点索引投递】
        # 只要题目有 Tag，无论它是 CF/AT 还是 XCPC，都在“杂题”里为其建立跨越分类的 Tag 索引副本
        if g.tags:
            for tag in g.tags:
                categories['杂题'][tag].append(g)
        # 如果既没有 Tag 又是纯正的一道毫无归属的杂题，则投放到无标签的收容所里
        elif g.category == '杂题':
            categories['杂题']['无标签杂题'].append(g)

    print(f"🛠️ 正在生成 HTML 到 '{out_dir}' (当前目录)...")
    for cat in categories:
        if cat == '杂题':
            # 杂题启用扁平化标签页构建
            build_category_page(cat, categories[cat], os.path.join(out_dir, f"{cat}.html"), rel_data_path, is_flat=True)
        else:
            build_category_page(cat, categories[cat], os.path.join(out_dir, f"{cat}.html"), rel_data_path, is_flat=False)

    build_index_page(categories, os.path.join(out_dir, "index.html"))

    index_abs_path = os.path.abspath(os.path.join(out_dir, 'index.html'))
    print(f"🎉 处理完成！请在浏览器中打开: {index_abs_path}")

if __name__ == '__main__':
    main()