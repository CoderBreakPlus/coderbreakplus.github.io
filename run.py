import os
import sys
import re
from collections import defaultdict
from datetime import datetime

# =======================
#   难度颜色 & 填充率计算器
# =======================
def get_diff_style(diff):
    if diff >= 3200:
        return 'background: linear-gradient(to right, #FFD700, #DAA520); border: 1px solid #DAA520; border-radius: 50%;'
    if diff < 400: color = '#808080'
    elif diff < 800: color = '#804000'
    elif diff < 1200: color = '#008000'
    elif diff < 1600: color = '#00C0C0'
    elif diff < 2000: color = '#0000FF'
    elif diff < 2400: color = '#C0C000'
    elif diff < 2800: color = '#FF8000'
    else: color = '#FF0000'
    
    clamped_diff = max(0, diff)
    ratio = (clamped_diff % 400) / 400 * 100
    return f'background: linear-gradient(to top, {color} {ratio}%, transparent {ratio}%); border: 1px solid {color}; border-radius: 50%;'

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
        body {{ font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif; background: var(--bg); color: var(--text); margin: 0; padding: 0; line-height: 1.6; overflow-x: hidden; }}
        .container {{ width: 100%; max-width: 1400px; margin: 20px auto; padding: 20px; background: #fff; border-radius: 8px; box-shadow: 0 2px 8px rgba(0,0,0,0.05); box-sizing: border-box; }}
        h1, h2, h3 {{ color: #202124; margin-bottom: 10px; }}
        
        .nav-bar {{ margin-bottom: 20px; padding-bottom: 10px; border-bottom: 2px solid var(--border); display: flex; align-items: center; flex-wrap: wrap; gap: 15px; }}
        .nav-bar a {{ color: var(--primary); text-decoration: none; font-weight: 500; }}
        .nav-bar a:hover {{ text-decoration: underline; }}
        
        .toggle-diff-btn {{ margin-left: auto; background: #fff; border: 1px solid #d2e3fc; padding: 6px 12px; border-radius: 4px; cursor: pointer; color: #1a73e8; font-size: 0.9em; transition: 0.2s; font-weight: bold; }}
        .toggle-diff-btn:hover {{ background: #f8f9fa; }}
        
        .stats-bar {{ display: flex; justify-content: space-between; align-items: center; background: #e8f0fe; padding: 15px 20px; border-radius: 6px; margin-bottom: 20px; flex-wrap: wrap; gap: 10px; box-sizing: border-box; }}
        .stats-info span {{ margin-right: 15px; font-size: 0.95em; color: #174ea6; font-weight: 500; display: inline-block; }}
        .sort-btns button {{ background: #fff; border: 1px solid #d2e3fc; color: #1a73e8; padding: 6px 12px; border-radius: 4px; cursor: pointer; font-size: 0.9em; margin-left: 5px; }}
        .sort-btns button:hover {{ background: #f1f3f4; }}

        table {{ width: 100%; border-collapse: collapse; table-layout: fixed; word-wrap: break-word; overflow-wrap: break-word; }}
        th, td {{ padding: 10px; box-sizing: border-box; }}
        
        .matrix-table {{ background: #fff; border-radius: 8px; margin-bottom: 20px; }}
        .matrix-table thead {{ background: #f8f9fa; }}
        .matrix-table th {{ border-bottom: 2px solid var(--border); color: #5f6368; font-weight: 600; text-align: center; }}
        .matrix-table td {{ border-bottom: 1px solid #f0f0f0; border-right: 1px solid #f0f0f0; text-align: center; vertical-align: middle; }}
        .matrix-table td:last-child {{ border-right: none; }}
        .matrix-table tbody tr:hover {{ background-color: #fcfcfc; }}
        .contest-name-cell {{ text-align: left !important; font-weight: 600; color: #333; }}
        
        .prob-cell {{ display: flex; flex-direction: column; align-items: center; gap: 6px; justify-content: center; }}
        /* 强制 nowrap 紧随不换行 */
        .prob-link-wrap {{ font-size: 0.9em; display: inline-flex; align-items: center; justify-content: center; gap: 6px; background: #f1f3f4; padding: 4px 10px; border-radius: 12px; flex-wrap: nowrap; white-space: nowrap; text-align: center; }}
        .prob-link-wrap a {{ color: var(--primary); text-decoration: none; font-weight: bold; }}
        .prob-link-wrap a:hover {{ text-decoration: underline; }}
        
        .diff-indicator {{ display: inline-flex; align-items: center; gap: 4px; font-weight: bold; font-size: 0.9em; }}
        .diff-circle {{ width: 12px; height: 12px; display: inline-block; }}

        .mini-version-row {{ display: flex; align-items: center; justify-content: center; gap: 6px; font-size: 1.1em; flex-wrap: wrap; }}
        .mini-tag {{ font-size: 0.7em; padding: 2px 4px; border-radius: 3px; font-weight: bold; line-height: 1; }}
        .mini-tag-easy {{ background: #e6f4ea; color: #1e8e3e; }}
        .mini-tag-hard {{ background: #fce8e6; color: #d93025; }}
        .mini-file-link {{ text-decoration: none; display: inline-block; transition: 0.2s; }}
        .mini-file-link:hover {{ transform: scale(1.1); }}
        
        .zhati-filter-bar {{ background: #fff; border: 1px solid #e0e0e0; padding: 15px; border-radius: 6px; margin-bottom: 20px; display: flex; flex-wrap: wrap; gap: 12px; box-shadow: 0 1px 3px rgba(0,0,0,0.04); align-items: center; }}
        .zhati-filter-bar input {{ padding: 6px 10px; border: 1px solid #ccc; border-radius: 4px; outline: none; }}
        .zhati-filter-bar input:focus {{ border-color: #1a73e8; }}
        
        .normal-table {{ margin-bottom: 30px; }}
        .normal-table th, .normal-table td {{ border: 1px solid var(--border); text-align: left; vertical-align: middle; }}
        .normal-table th {{ background: #f8f9fa; color: #5f6368; font-weight: 600; }}
        .normal-table tr:hover {{ background-color: #fcfcfc; }}
        .normal-table th:nth-child(1) {{ width: 22%; }}
        .normal-table th:nth-child(2) {{ width: 23%; }}
        .normal-table th:nth-child(3) {{ width: 12%; }}
        .normal-table th:nth-child(4) {{ width: 13%; }}
        .normal-table th:nth-child(5) {{ width: 30%; }}
        
        .version-row {{ margin-bottom: 6px; display: flex; align-items: center; flex-wrap: wrap; gap: 8px; }}
        .file-link {{ color: var(--primary); text-decoration: none; font-size: 1.1em; white-space: nowrap; transition: 0.2s; }}
        .file-link:hover {{ transform: scale(1.1); }}
        .tag-pill {{ background: #f1f3f4; color: #5f6368; font-size: 0.85em; padding: 2px 8px; border-radius: 12px; display: inline-block; margin: 2px; }}

        .footer {{ margin-top: 40px; padding-top: 20px; border-top: 1px solid var(--border); text-align: center; color: #80868b; font-size: 0.85em; }}
    </style>
</head>
<body>
    <div class="container">
        <div class="nav-bar">
            <a href="index.html">🏠 返回首页</a>
            <span style="color:#aaa;">|</span>
            <span style="font-size: 0.9em; color: #666;">全动态自适应表格</span>
            <button class="toggle-diff-btn" onclick="toggleDiff()">🌕 隐藏难度</button>
        </div>
        
        <h1>{title}</h1>
        {subtitle}
        
        <div class="stats-bar">
            <div class="stats-info">{stats_html}</div>
            {sort_html}
        </div>
        
        {content_html}
        
        <div class="footer">
            生成时间: {gen_time} | 题目整理工具自动生成
        </div>
    </div>

    <script>
        let isDiffVisible = true;
        function toggleDiff() {{
            isDiffVisible = !isDiffVisible;
            const btn = document.querySelector('.toggle-diff-btn');
            
            if (isDiffVisible) {{
                btn.innerHTML = '🌕 隐藏难度';
                btn.style.color = '#1a73e8';
                btn.style.borderColor = '#d2e3fc';
                btn.style.background = '#fff';
            }} else {{
                btn.innerHTML = '🌑 显示难度';
                btn.style.color = '#5f6368';
                btn.style.borderColor = '#dadce0';
                btn.style.background = '#f1f3f4';
            }}
            
            document.querySelectorAll('.diff-indicator').forEach(el => {{
                el.style.display = isDiffVisible ? 'inline-flex' : 'none';
            }});
        }}

        function sortContests(type) {{
            const tables = document.querySelectorAll('.matrix-table');
            tables.forEach(table => {{
                const tbody = table.querySelector('tbody');
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
            }});
        }}

        // 杂题表格动态筛选
        function filterZhati() {{
            const tagVal = document.getElementById('filter-tag') ? document.getElementById('filter-tag').value.toLowerCase().trim() : '';
            const searchTerms = tagVal.split(/\\s+/).filter(t => t);
            
            const minStr = document.getElementById('filter-diff-min') ? document.getElementById('filter-diff-min').value : '';
            const maxStr = document.getElementById('filter-diff-max') ? document.getElementById('filter-diff-max').value : '';
            const minVal = minStr !== '' ? parseFloat(minStr) : -Infinity;
            const maxVal = maxStr !== '' ? parseFloat(maxStr) : Infinity;

            const dateStart = document.getElementById('filter-date-start') ? document.getElementById('filter-date-start').value : '';
            const dateEnd = document.getElementById('filter-date-end') ? document.getElementById('filter-date-end').value : '';

            const rows = document.querySelectorAll('#zhati-table tbody tr');
            rows.forEach(row => {{
                const tags = row.getAttribute('data-tags').toLowerCase();
                const diffStr = row.getAttribute('data-diff');
                const rDate = row.getAttribute('data-date');
                const diff = diffStr !== 'None' ? parseFloat(diffStr) : NaN;

                let matchTag = true;
                if (searchTerms.length > 0) {{
                    matchTag = searchTerms.every(term => tags.includes(term));
                }}

                let matchDiff = true;
                if (minStr !== '' || maxStr !== '') {{
                    if (isNaN(diff)) {{
                        matchDiff = false;
                    }} else {{
                        if (diff < minVal || diff > maxVal) matchDiff = false;
                    }}
                }}
                
                let matchDate = true;
                if (dateStart && (rDate === '未知' || rDate < dateStart)) matchDate = false;
                if (dateEnd && (rDate === '未知' || rDate > dateEnd)) matchDate = false;

                row.style.display = (matchTag && matchDiff && matchDate) ? '' : 'none';
            }});
        }}

        // 杂题表格双向排序
        let sortDirection = {{ 'diff': 1, 'date': 1 }};
        function sortZhatiTable(col) {{
            const tbody = document.querySelector('#zhati-table tbody');
            if (!tbody) return;
            const rows = Array.from(tbody.querySelectorAll('tr'));
            
            sortDirection[col] *= -1;
            const dir = sortDirection[col];
            
            rows.sort((a, b) => {{
                if (col === 'diff') {{
                    let v1 = parseFloat(a.dataset.diff);
                    let v2 = parseFloat(b.dataset.diff);
                    if (isNaN(v1)) v1 = -Infinity;
                    if (isNaN(v2)) v2 = -Infinity;
                    return (v1 - v2) * dir;
                }} else if (col === 'date') {{
                    let d1 = a.dataset.date;
                    let d2 = b.dataset.date;
                    if (d1 === '未知') d1 = '';
                    if (d2 === '未知') d2 = '';
                    return d1.localeCompare(d2) * dir;
                }}
            }});
            
            rows.forEach(r => tbody.appendChild(r));
        }}

        // AtCoder 标签页切换
        function switchAtCoderTab(targetId, btn) {{
            document.querySelectorAll('.atcoder-tab-content').forEach(el => el.style.display = 'none');
            document.getElementById(targetId).style.display = 'block';
            
            document.querySelectorAll('.atcoder-tab-btn').forEach(el => {{
                el.style.background = '#f1f3f4';
                el.style.color = '#333';
            }});
            btn.style.background = '#1a73e8';
            btn.style.color = '#fff';
        }}
    </script>
</body>
</html>
"""

class ProblemVersion:
    def __init__(self, name):
        self.name = name
        self.files = {'cpp': None, 'md': None, 'conf': None}

class ProblemGroup:
    def __init__(self, base_name):
        self.base_name = base_name
        self.category = "杂题"
        self.contest_name = ""
        self.problem_id = ""
        self.link = "#"
        self.tags =[]
        self.difficulty = None
        self.has_conf = False
        self.date = "未知"
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
    conf_bases = set()
    if os.path.exists(data_dir):
        for f in os.listdir(data_dir):
            if f.endswith('.conf'): conf_bases.add(f[:-5])

    for f in os.listdir(data_dir):
        if not os.path.isfile(os.path.join(data_dir, f)):
            continue
        name, ext = os.path.splitext(f)
        if ext not in['.cpp', '.md', '.conf']: continue
            
        base_name, version = None, 'Normal'
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
        group.date = "未知"
        for v in group.versions.values():
            if v.files.get('cpp'):
                fp = os.path.join(data_dir, v.files['cpp'])
                if os.path.exists(fp):
                    try:
                        with open(fp, 'r', encoding='utf-8') as f:
                            first_line = f.readline()
                            m = re.search(r'//\s*created time:\s*(\d{4}-\d{2}-\d{2})', first_line, re.IGNORECASE)
                            if m:
                                group.date = m.group(1)
                                break
                    except Exception:
                        pass

        m_cf = re.match(r'^cf(\d+)([a-zA-Z]+)$', group.base_name, re.IGNORECASE)
        m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+)$', group.base_name, re.IGNORECASE)
        is_cf, is_at = bool(m_cf), bool(m_ac)

        conf_file = None
        for v in group.versions.values():
            if v.files['conf']:
                conf_file = v.files['conf']
                break

        if conf_file:
            group.has_conf = True
            try:
                with open(os.path.join(data_dir, conf_file), 'r', encoding='utf-8') as f:
                    lines =[line.strip() for line in f.readlines()]
                while len(lines) < 5: lines.append('')
                
                parts = lines[0].split()
                if parts:
                    try:
                        group.difficulty = float(parts[-1])
                        group.tags = parts[:-1]
                    except ValueError:
                        group.tags = parts
                        group.difficulty = None
                
                cat_conf = lines[1].lower()
                if cat_conf in ['oi', 'xcpc', 'xcpc+']: group.category = cat_conf
                elif cat_conf: group.category = '杂题'
                else:
                    if is_cf: group.category = 'Codeforces'
                    elif is_at: group.category = 'AtCoder'
                    else: group.category = '杂题'
                
                if lines[2]: group.link = lines[2]
                else:
                    if is_cf: group.link = f"https://codeforces.com/problemset/problem/{m_cf.group(1)}/{m_cf.group(2).upper()}"
                    elif is_at: group.link = f"https://atcoder.jp/contests/{m_ac.group(1).lower()}{m_ac.group(2)}/tasks/{m_ac.group(1).lower()}{m_ac.group(2)}_{m_ac.group(3).lower()}"
                    else: group.link = '#'
                
                if lines[3]: group.contest_name = lines[3]
                else:
                    if is_cf: group.contest_name = f"Codeforces Round {m_cf.group(1)}"
                    elif is_at: group.contest_name = f"{m_ac.group(1).upper()}{m_ac.group(2)}"
                    else: group.contest_name = ""
                    
                if lines[4]: group.problem_id = lines[4]
                else:
                    if is_cf: group.problem_id = m_cf.group(2).upper()
                    elif is_at: group.problem_id = m_ac.group(3).upper()
                    else: group.problem_id = ""
            except Exception as e:
                pass
        else:
            if is_cf:
                group.category = 'Codeforces'
                group.contest_name = f"Codeforces Round {m_cf.group(1)}"
                group.problem_id = m_cf.group(2).upper()
                group.link = f"https://codeforces.com/problemset/problem/{m_cf.group(1)}/{m_cf.group(2).upper()}"
            elif is_at:
                group.category = 'AtCoder'
                group.contest_name = f"{m_ac.group(1).upper()}{m_ac.group(2)}"
                group.problem_id = m_ac.group(3).upper()
                group.link = f"https://atcoder.jp/contests/{m_ac.group(1).lower()}{m_ac.group(2)}/tasks/{m_ac.group(1).lower()}{m_ac.group(2)}_{m_ac.group(3).lower()}"
            else:
                group.category = '杂题'

def generate_versions_html(group, rel_path, minimal=False):
    v_htmls =[]
    has_multiple = len(group.versions) > 1
    
    for v_name in group.version_order:
        if v_name in group.versions:
            v = group.versions[v_name]
            tag = ""
            if minimal:
                if has_multiple:
                    if v_name == 'Easy': tag = '<span class="mini-tag mini-tag-easy">E</span>'
                    elif v_name == 'Hard': tag = '<span class="mini-tag mini-tag-hard">H</span>'
                links = []
                if v.files['cpp']: links.append(f'<a href="{rel_path}/{v.files["cpp"]}" class="mini-file-link" title="代码" style="text-decoration:none;">📝</a>')
                if v.files['md']: 
                    md_href = v.files['md'][:-3] if v.files['md'].endswith('.md') else v.files['md']
                    links.append(f'<a href="{rel_path}/{md_href}" class="mini-file-link" title="题解" style="text-decoration:none;">💡</a>')
                if v.files['conf']: links.append(f'<a href="{rel_path}/{v.files["conf"]}" class="mini-file-link" title="配置" style="text-decoration:none;">⚙️</a>')
                
                # 强制在一行不换行
                v_htmls.append(f'<div class="mini-version-row">{tag}<span style="white-space: nowrap; display: inline-flex; gap: 4px;">{"".join(links)}</span></div>')
            else:
                if has_multiple:
                    if v_name == 'Easy': tag = '<span class="tag-pill" style="background:#e6f4ea; color:#1e8e3e;">E</span>'
                    elif v_name == 'Hard': tag = '<span class="tag-pill" style="background:#fce8e6; color:#d93025;">H</span>'
                    else: tag = '<span class="tag-pill">N</span>'
                links =[]
                if v.files['cpp']: links.append(f'<a href="{rel_path}/{v.files["cpp"]}" class="file-link" title="代码" style="text-decoration:none;">📝</a>')
                if v.files['md']: 
                    md_href = v.files['md'][:-3] if v.files['md'].endswith('.md') else v.files['md']
                    links.append(f'<a href="{rel_path}/{md_href}" class="file-link" title="题解" style="text-decoration:none;">💡</a>')
                if v.files['conf']: links.append(f'<a href="{rel_path}/{v.files["conf"]}" class="file-link" title="配置" style="text-decoration:none;">⚙️</a>')
                
                # 去除文字，强制在一行不换行
                v_htmls.append(f'<div class="version-row" style="flex-wrap: nowrap;">{tag}<span style="white-space: nowrap; display: inline-flex; gap: 6px;">{"".join(links)}</span></div>')
    return "".join(v_htmls)

def build_matrix_table(groups_dict, rel_path):
    if not groups_dict: return ""
    
    all_pids = set()
    for c_groups in groups_dict.values():
        for g in c_groups:
            all_pids.add(g.problem_id.strip() if g.problem_id else "未知")
            
    def alnum_key(s): return[int(c) if c.isdigit() else c.lower() for c in re.split('([0-9]+)', s)]
    sorted_pids = sorted(list(all_pids), key=lambda x: ([float('inf')] if x == '未知' else alnum_key(x)))

    html = '<div style="overflow-x: auto;"><table class="matrix-table"><thead><tr><th style="text-align: left; width: 20%;">比赛名称</th>'
    col_width = 80 / max(1, len(sorted_pids))
    for pid in sorted_pids: html += f'<th style="width: {col_width}%;">{pid}</th>'
    html += '</tr></thead><tbody>'
    
    sorted_contests = sorted(groups_dict.items(), key=lambda x: len(x[1]), reverse=True)
    for contest, c_groups in sorted_contests:
        pid_map = defaultdict(list)
        for g in c_groups:
            pid_map[g.problem_id.strip() if g.problem_id else "未知"].append(g)
        
        html += f'<tr data-name="{contest}" data-count="{len(c_groups)}">'
        display_contest = contest if contest else "无名比赛"
        html += f'<td class="contest-name-cell">{display_contest} <br><span style="font-size:0.8em; color:#888; font-weight:normal;">({len(c_groups)} 题)</span></td>'
        
        for pid in sorted_pids:
            html += '<td>'
            if pid in pid_map:
                for g in sorted(pid_map[pid], key=lambda x: x.base_name):
                    v_html = generate_versions_html(g, rel_path, minimal=True)
                    display_pid = pid if pid != "未知" else g.base_name
                    link_html = f'<a href="{g.link}" target="_blank">{display_pid}</a>' if g.link != '#' else f'<span>{display_pid}</span>'
                    
                    diff_html = ""
                    if g.difficulty is not None:
                        style = get_diff_style(g.difficulty)
                        diff_html = f'<span class="diff-indicator" title="难度: {g.difficulty}"><span class="diff-circle" style="{style}"></span> {int(g.difficulty) if g.difficulty.is_integer() else g.difficulty}</span>'
                    
                    # .prob-link-wrap 在 css 中已设为 flex-wrap: nowrap 和 white-space: nowrap
                    html += f"""
                    <div class="prob-cell" style="margin-bottom:8px;">
                        <div class="prob-link-wrap">{link_html}{diff_html}</div>
                        {v_html}
                    </div>"""
            html += '</td>'
        html += '</tr>'
    html += '</tbody></table></div>'
    return html

def build_category_page(title, groups_dict, out_path, rel_path):
    all_groups =[]
    for gs in groups_dict.values(): all_groups.extend(gs)
                
    total_groups, total_versions, has_cpp, has_md, has_conf = len(all_groups), 0, 0, 0, 0
    for g in all_groups:
        total_versions += len(g.versions)
        if any(v.files['cpp'] for v in g.versions.values()): has_cpp += 1
        if any(v.files['md'] for v in g.versions.values()): has_md += 1
        if any(v.files['conf'] for v in g.versions.values()): has_conf += 1

    stats_html = f"<span>📁 题目组数: {total_groups}</span><span>📄 总版本数: {total_versions}</span><span>📝 有代码: {has_cpp}</span><span>💡 有题解: {has_md}</span><span>⚙️ 有配置: {has_conf}</span><span>🏆 比赛数: {len(groups_dict)}</span>"
    sort_html = """<div class="sort-btns"><button onclick="sortContests('count')">按题目数降序</button><button onclick="sortContests('name')">按比赛名字典序</button></div>"""

    content_html = ""
    if title == 'AtCoder':
        sub_cats = {'ABC': {}, 'ARC': {}, 'AGC': {}, '其他': {}}
        for contest, c_groups in groups_dict.items():
            if contest.upper().startswith('ABC'): sub_cats['ABC'][contest] = c_groups
            elif contest.upper().startswith('ARC'): sub_cats['ARC'][contest] = c_groups
            elif contest.upper().startswith('AGC'): sub_cats['AGC'][contest] = c_groups
            else: sub_cats['其他'][contest] = c_groups
        
        # AtCoder Tab 栏和按需显示内容
        tabs_html = '<div class="atcoder-tabs" style="margin-bottom: 20px; display: flex; gap: 10px; flex-wrap: wrap;">'
        tables_html = ''
        first = True
        for sc_name in ['ABC', 'ARC', 'AGC', '其他']:
            if not sub_cats[sc_name]: continue
            
            btn_style = "background: #1a73e8; color: #fff;" if first else "background: #f1f3f4; color: #333;"
            tabs_html += f'<button class="atcoder-tab-btn" data-target="tab-{sc_name}" onclick="switchAtCoderTab(\'tab-{sc_name}\', this)" style="padding: 8px 18px; border: none; border-radius: 4px; cursor: pointer; font-weight: bold; transition: 0.2s; {btn_style}">{sc_name}</button>'
            
            display = "block" if first else "none"
            tables_html += f'<div id="tab-{sc_name}" class="atcoder-tab-content" style="display: {display};">'
            tables_html += f"<h2 style='margin-top: 10px; color: var(--primary); border-bottom: 2px solid var(--border); padding-bottom: 5px;'>{sc_name} 模块</h2>"
            tables_html += build_matrix_table(sub_cats[sc_name], rel_path)
            tables_html += '</div>'
            first = False
            
        tabs_html += '</div>'
        content_html = tabs_html + tables_html
    else:
        content_html = build_matrix_table(groups_dict, rel_path)

    html = HTML_TEMPLATE.format(
        title=title, subtitle="", stats_html=stats_html, sort_html=sort_html,
        content_html=content_html, gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def build_zhati_page(title, all_groups, out_path, rel_path):
    total_groups, total_versions, has_cpp, has_md, has_conf = len(all_groups), 0, 0, 0, 0
    for g in all_groups:
        total_versions += len(g.versions)
        if any(v.files['cpp'] for v in g.versions.values()): has_cpp += 1
        if any(v.files['md'] for v in g.versions.values()): has_md += 1
        if any(v.files['conf'] for v in g.versions.values()): has_conf += 1

    stats_html = f"<span>📁 题目组数: {total_groups}</span><span>📄 总版本数: {total_versions}</span><span>📝 有代码: {has_cpp}</span><span>💡 有题解: {has_md}</span><span>⚙️ 有配置: {has_conf}</span>"
    
    # 加入点击双向排序功能表头
    content_html = """
    <div class="zhati-filter-bar">
        <strong style="color: #1a73e8;">🔍 筛选器</strong>
        <input type="text" id="filter-tag" placeholder="输入标签筛选(支持空格多词)..." onkeyup="filterZhati()" style="min-width: 200px;">
        
        <span style="color:#888; margin-left: 10px;">📊 难度:</span>
        <input type="number" id="filter-diff-min" placeholder="Min" style="width: 70px;" onkeyup="filterZhati()" onchange="filterZhati()">
        <span style="color:#888;">-</span>
        <input type="number" id="filter-diff-max" placeholder="Max" style="width: 70px;" onkeyup="filterZhati()" onchange="filterZhati()">
        
        <span style="color:#888; margin-left: 10px;">📅 日期:</span>
        <input type="date" id="filter-date-start" onchange="filterZhati()">
        <span style="color:#888;">-</span>
        <input type="date" id="filter-date-end" onchange="filterZhati()">
    </div>
    <table class="normal-table" id="zhati-table">
        <thead>
            <tr>
                <th>题目与来源</th>
                <th>标签</th>
                <th onclick="sortZhatiTable('diff')" style="cursor:pointer; user-select:none; color: var(--primary);" title="点击按难度双向排序">难度 ↕</th>
                <th onclick="sortZhatiTable('date')" style="cursor:pointer; user-select:none; color: var(--primary);" title="点击按日期双向排序">添加日期 ↕</th>
                <th>文件</th>
            </tr>
        </thead>
        <tbody>
    """
    
    for g in sorted(all_groups, key=lambda x: (x.date != "未知", x.date), reverse=True): 
        v_html = generate_versions_html(g, rel_path, minimal=False)
        origin = f"{g.category} - {g.contest_name}" if g.contest_name else g.category
        
        name_html = f'<a href="{g.link}" target="_blank" style="color:var(--primary); text-decoration:none;"><b>{g.base_name}</b></a>' if g.link != '#' else f'<b>{g.base_name}</b>'
        tags_str = " ".join(g.tags) if g.tags else ""
        tags_html = "".join([f'<span class="tag-pill">{t}</span>' for t in g.tags])
        diff_val = g.difficulty if g.difficulty is not None else 'None'
        diff_html = "-"
        
        if g.difficulty is not None:
            style = get_diff_style(g.difficulty)
            diff_html = f'<span class="diff-indicator" title="难度: {g.difficulty}"><span class="diff-circle" style="{style}"></span> {int(g.difficulty) if g.difficulty.is_integer() else g.difficulty}</span>'
        
        content_html += f"""
        <tr data-tags="{tags_str}" data-diff="{diff_val}" data-date="{g.date}">
            <td>{name_html}<br><span style="font-size:0.8em; color:#888;">{origin}</span></td>
            <td>{tags_html}</td>
            <td>{diff_html}</td>
            <td style="font-size: 0.9em; color: #5f6368;">{g.date}</td>
            <td>{v_html}</td>
        </tr>"""
        
    content_html += "</tbody></table>"

    html = HTML_TEMPLATE.format(
        title=title, subtitle="", stats_html=stats_html, sort_html="",
        content_html=content_html, gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def build_index_page(categories, zhati_list, out_path):
    stats =[]
    for cat, data in categories.items():
        c_count = len(data)
        p_count = sum(len(gs) for gs in data.values())
        stats.append((cat, p_count, f"共 {c_count} 场比赛，包含 {p_count} 个题目组"))
    
    z_count = len(zhati_list)
    stats.append(("杂题", z_count, f"全局题库汇总池，收录共 {z_count} 个题目组"))
            
    subtitle_html = """
    <div style="background: #e8f0fe; color: #174ea6; padding: 16px 20px; border-radius: 6px; margin-bottom: 25px; font-size: 0.95em; border: 1px solid #d2e3fc; line-height: 1.8;">
        <strong>📝 新版 .conf 配置文件语法规则（固定 5 行，不需要的信息可直接留空换行）：</strong><br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 1 行:</span> 标签/关键词。多个 tag 用空格隔开。如果最后为数字，则自动解析为<strong>难度</strong>数值。<br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 2 行:</span> 比赛分类 (<code>oi</code> / <code>xcpc</code> / <code>xcpc+</code>)。CF/AT 留空会自动归档，其他留空则无所属类别。<br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 3 行:</span> 完整 URL 链接。CF/AT 留空自动生成官方链接。<br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 4 行:</span> 比赛名称。CF/AT 留空会自动补全。<br>
        <span style="display:inline-block; width: 65px; font-weight:bold;">第 5 行:</span> 题目编号 (如 A, B, C...)。<br>
        <div style="margin-top: 8px; color:#d93025; font-weight:bold;">⚠️ 提示：所有配备 .conf 的题目均会同时收录进底部的「杂题」汇总表格中，支持全库 Excel 式条件检索。</div>
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
        title="首页索引", subtitle=subtitle_html, stats_html="<span>👋 欢迎使用题目自动整理工具</span>", sort_html="",
        content_html=content, gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def main():
    data_dir = sys.argv[1] if len(sys.argv) > 1 else 'data'
    out_dir = sys.argv[2] if len(sys.argv) > 2 else '.'

    if not os.path.exists(data_dir):
        print(f"❌ 错误: 数据目录 '{data_dir}' 不存在！")
        sys.exit(1)
    if out_dir != '.' and not os.path.exists(out_dir): os.makedirs(out_dir)

    rel_data_path = os.path.relpath(data_dir, out_dir).replace('\\', '/')

    print(f"🔍 正在扫描 '{data_dir}'...")
    groups = scan_and_group_files(data_dir)
    print(f"✅ 找到 {len(groups)} 个基础题组，正在分析配置...")
    
    apply_categories_and_links(groups, data_dir)

    categories = {
        'Codeforces': defaultdict(list), 'AtCoder': defaultdict(list),
        'oi': defaultdict(list), 'xcpc': defaultdict(list), 'xcpc+': defaultdict(list)
    }
    
    zhati_list =[]

    for g in groups.values():
        if g.category != '杂题':
            categories[g.category][g.contest_name].append(g)
            
        if g.has_conf or g.category == '杂题':
            zhati_list.append(g)

    print(f"🛠️ 正在生成 HTML 到 '{out_dir}' (当前目录)...")
    for cat in categories:
        build_category_page(cat, categories[cat], os.path.join(out_dir, f"{cat}.html"), rel_data_path)
        
    build_zhati_page('杂题', zhati_list, os.path.join(out_dir, '杂题.html'), rel_data_path)

    build_index_page(categories, zhati_list, os.path.join(out_dir, "index.html"))
    print(f"🎉 处理完成！请在浏览器中打开: {os.path.abspath(os.path.join(out_dir, 'index.html'))}")

if __name__ == '__main__':
    main()