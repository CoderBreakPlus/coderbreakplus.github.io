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
        
        /* 按钮样式 */
        .toggle-btn {{ background: #fff; border: 1px solid #d2e3fc; padding: 6px 12px; border-radius: 4px; cursor: pointer; color: #1a73e8; font-size: 0.9em; transition: 0.2s; font-weight: bold; margin-right: 5px; }}
        .toggle-btn:hover {{ background: #f8f9fa; }}
        .toggle-btn.active {{ background: #1a73e8; color: #fff; border-color: #1a73e8; }}

        .stats-bar {{ display: flex; justify-content: space-between; align-items: center; background: #e8f0fe; padding: 15px 20px; border-radius: 6px; margin-bottom: 20px; flex-wrap: wrap; gap: 10px; box-sizing: border-box; }}
        .stats-info span {{ margin-right: 15px; font-size: 0.95em; color: #174ea6; font-weight: 500; display: inline-block; }}

        table {{ width: 100%; border-collapse: collapse; table-layout: fixed; }}
        th, td {{ padding: 10px; box-sizing: border-box; }}
        
        .matrix-table {{ background: #fff; border-radius: 8px; margin-bottom: 20px; }}
        .matrix-table thead {{ background: #f8f9fa; }}
        .matrix-table th {{ border-bottom: 2px solid var(--border); color: #5f6368; font-weight: 600; text-align: center; }}
        .matrix-table td {{ border-bottom: 1px solid #f0f0f0; border-right: 1px solid #f0f0f0; text-align: center; vertical-align: middle; }}
        .matrix-table td:last-child {{ border-right: none; }}
        .contest-name-cell {{ text-align: left !important; font-weight: 600; color: #333; }}
        
        /* ID与难度紧贴且不换行 */
        .id-diff-nowrap {{ display: inline-flex; align-items: center; gap: 6px; white-space: nowrap; }}
        
        /* 图标紧贴且不换行 */
        .icons-nowrap {{ white-space: nowrap; display: inline-flex; gap: 4px; font-size: 1.1em; }}
        .mini-file-link {{ text-decoration: none; }}

        .diff-indicator {{ display: inline-flex; align-items: center; gap: 4px; font-weight: bold; font-size: 0.9em; }}
        .diff-circle {{ width: 12px; height: 12px; display: inline-block; }}

        /* 杂题筛选与排序 */
        .zhati-filter-bar {{ background: #fff; border: 1px solid #e0e0e0; padding: 15px; border-radius: 6px; margin-bottom: 20px; display: flex; flex-wrap: wrap; gap: 12px; align-items: center; }}
        .zhati-filter-bar input {{ padding: 6px 10px; border: 1px solid #ccc; border-radius: 4px; }}
        
        .sort-icon {{ cursor: pointer; font-size: 0.8em; margin-left: 4px; color: #aaa; text-decoration: none; }}
        .sort-icon:hover {{ color: #1a73e8; }}
        
        .normal-table {{ margin-bottom: 30px; }}
        .normal-table th, .normal-table td {{ border: 1px solid var(--border); text-align: left; vertical-align: middle; }}
        .normal-table th {{ background: #f8f9fa; }}
        
        .tag-pill {{ background: #f1f3f4; color: #5f6368; font-size: 0.85em; padding: 2px 8px; border-radius: 12px; display: inline-block; margin: 2px; }}
        .footer {{ margin-top: 40px; padding-top: 20px; border-top: 1px solid var(--border); text-align: center; color: #80868b; font-size: 0.85em; }}
    </style>
</head>
<body>
    <div class="container">
        <div class="nav-bar">
            <a href="index.html">🏠 返回首页</a>
            <span style="color:#aaa;">|</span>
            <button class="toggle-btn" id="diff-toggle-btn" onclick="toggleDiff()">🌕 隐藏难度</button>
            {atcoder_nav}
        </div>
        
        <h1>{title}</h1>
        {subtitle}
        
        <div class="stats-bar">
            <div class="stats-info">{stats_html}</div>
            {sort_btns_html}
        </div>
        
        <div id="content-area">
            {content_html}
        </div>
        
        <div class="footer">生成时间: {gen_time} | 题目整理工具</div>
    </div>

    <script>
        let isDiffVisible = true;
        function toggleDiff() {{
            isDiffVisible = !isDiffVisible;
            const btn = document.getElementById('diff-toggle-btn');
            btn.innerHTML = isDiffVisible ? '🌕 隐藏难度' : '🌑 显示难度';
            document.querySelectorAll('.diff-indicator').forEach(el => el.style.display = isDiffVisible ? 'inline-flex' : 'none');
        }}

        // AtCoder 切换
        function switchAtCoder(type, btn) {{
            document.querySelectorAll('.atcoder-section').forEach(s => s.style.display = 'none');
            document.getElementById('section-' + type).style.display = 'block';
            document.querySelectorAll('.at-nav-btn').forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
        }}

        // 杂题排序逻辑
        function sortZhati(col, dir) {{
            const tbody = document.querySelector('#zhati-table tbody');
            const rows = Array.from(tbody.querySelectorAll('tr'));
            rows.sort((a, b) => {{
                let valA, valB;
                if (col === 'diff') {{
                    valA = a.getAttribute('data-diff') === 'None' ? -1 : parseFloat(a.getAttribute('data-diff'));
                    valB = b.getAttribute('data-diff') === 'None' ? -1 : parseFloat(b.getAttribute('data-diff'));
                }} else {{
                    valA = a.getAttribute('data-date');
                    valB = b.getAttribute('data-date');
                    if (valA === '未知') valA = '0000-00-00';
                    if (valB === '未知') valB = '0000-00-00';
                }}
                return dir === 'asc' ? valA.toString().localeCompare(valB.toString(), undefined, {{numeric: true}}) : valB.toString().localeCompare(valA.toString(), undefined, {{numeric: true}});
            }});
            rows.forEach(r => tbody.appendChild(r));
        }}

        // 筛选逻辑
        function filterZhati() {{
            const tagVal = document.getElementById('filter-tag').value.toLowerCase().trim();
            const terms = tagVal.split(/\\s+/).filter(t => t);
            const minV = parseFloat(document.getElementById('filter-diff-min').value) || -Infinity;
            const maxV = parseFloat(document.getElementById('filter-diff-max').value) || Infinity;
            const dStart = document.getElementById('filter-date-start').value;
            const dEnd = document.getElementById('filter-date-end').value;

            document.querySelectorAll('#zhati-table tbody tr').forEach(row => {{
                const tags = row.getAttribute('data-tags').toLowerCase();
                const diff = row.getAttribute('data-diff') === 'None' ? NaN : parseFloat(row.getAttribute('data-diff'));
                const rDate = row.getAttribute('data-date');
                
                let mTag = terms.every(t => tags.includes(t));
                let mDiff = (isNaN(diff)) ? (minV === -Infinity && maxV === Infinity) : (diff >= minV && diff <= maxV);
                let mDate = (rDate !== '未知') ? ((!dStart || rDate >= dStart) && (!dEnd || rDate <= dEnd)) : (!dStart && !dEnd);
                row.style.display = (mTag && mDiff && mDate) ? '' : 'none';
            }});
        }}
    </script>
</body>
</html>
"""

class ProblemGroup:
    def __init__(self, base_name):
        self.base_name = base_name
        self.category, self.contest_name, self.problem_id = "杂题", "", ""
        self.link, self.date, self.difficulty = "#", "未知", None
        self.tags, self.has_conf = [], False
        self.versions = {} # {version_name: {cpp:..., md:..., conf:...}}

def scan_and_group_files(data_dir):
    groups = defaultdict(lambda: ProblemGroup(""))
    conf_bases = {f[:-5] for f in os.listdir(data_dir) if f.endswith('.conf')}
    
    for f in os.listdir(data_dir):
        name, ext = os.path.splitext(f)
        if ext not in ['.cpp', '.md', '.conf']: continue
        
        # 识别版本与BaseName
        m_cf = re.match(r'^cf(\d+)([a-zA-Z]+?)(1|2)?$', name, re.IGNORECASE)
        m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+?)(1|2)?$', name, re.IGNORECASE)
        
        version = 'Normal'
        if m_cf:
            base = f"cf{m_cf.group(1)}{m_cf.group(2).lower()}"
            if m_cf.group(3): version = 'Easy' if m_cf.group(3)=='1' else 'Hard'
        elif m_ac:
            base = f"{m_ac.group(1).lower()}{m_ac.group(2)}{m_ac.group(3).lower()}"
            if m_ac.group(4): version = 'Easy' if m_ac.group(4)=='1' else 'Hard'
        else:
            base = name
            for cb in sorted(conf_bases, key=len, reverse=True):
                if name.startswith(cb):
                    base = cb
                    suffix = name[len(cb):].lower()
                    if suffix in ['1', '_e1']: version = 'Easy'
                    elif suffix in ['2', '_e2']: version = 'Hard'
                    break
        
        g = groups[base]
        g.base_name = base
        if version not in g.versions: g.versions[version] = {'cpp':None, 'md':None, 'conf':None}
        g.versions[version][ext[1:]] = f

    return groups

def process_metadata(groups, data_dir):
    for base, g in groups.items():
        # 提取日期
        for v in g.versions.values():
            if v['cpp']:
                with open(os.path.join(data_dir, v['cpp']), 'r', encoding='utf-8', errors='ignore') as f:
                    m = re.search(r'//\s*created time:\s*(\d{4}-\d{2}-\d{2})', f.readline())
                    if m: g.date = m.group(1); break

        # 默认匹配 (CF/AC)
        m_cf = re.match(r'^cf(\d+)([a-zA-Z]+)$', base)
        m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+)$', base)
        if m_cf:
            g.category, g.contest_name = "Codeforces", f"Codeforces Round {m_cf.group(1)}"
            g.problem_id, g.link = m_cf.group(2).upper(), f"https://codeforces.com/problemset/problem/{m_cf.group(1)}/{m_cf.group(2).upper()}"
        elif m_ac:
            g.category, g.contest_name = "AtCoder", f"{m_ac.group(1).upper()}{m_ac.group(2)}"
            g.problem_id = m_ac.group(3).upper()
            g.link = f"https://atcoder.jp/contests/{m_ac.group(1).lower()}{m_ac.group(2)}/tasks/{m_ac.group(1).lower()}{m_ac.group(2)}_{m_ac.group(3).lower()}"

        # 配置文件覆盖
        conf_f = next((v['conf'] for v in g.versions.values() if v['conf']), None)
        if conf_f:
            g.has_conf = True
            with open(os.path.join(data_dir, conf_f), 'r', encoding='utf-8') as f:
                lines = [l.strip() for l in f.readlines()] + [""]*5
            parts = lines[0].split()
            if parts:
                try: g.difficulty = float(parts[-1]); g.tags = parts[:-1]
                except: g.tags = parts
            if lines[1]: g.category = lines[1]
            if lines[2]: g.link = lines[2]
            if lines[3]: g.contest_name = lines[3]
            if lines[4]: g.problem_id = lines[4]

def gen_icons_html(g, rel_path, is_minimal=True):
    html = ""
    for v_name in ['Normal', 'Easy', 'Hard']:
        if v_name not in g.versions: continue
        v = g.versions[v_name]
        tag = ""
        if len(g.versions) > 1:
            tag = f'<span class="mini-tag mini-tag-{"easy" if v_name=="Easy" else "hard" if v_name=="Hard" else "normal"}">{v_name[0]}</span>'
        
        icons = []
        if v['cpp']: icons.append(f'<a href="{rel_path}/{v["cpp"]}" class="mini-file-link">📝</a>')
        if v['md']: icons.append(f'<a href="{rel_path}/{v["md"][:-3]}" class="mini-file-link">💡</a>')
        if v['conf']: icons.append(f'<a href="{rel_path}/{v["conf"]}" class="mini-file-link">⚙️</a>')
        
        row_style = "" if not is_minimal else "margin-bottom:2px;"
        html += f'<div style="{row_style}"><span class="icons-nowrap">{tag}{"".join(icons)}</span></div>'
    return html

def build_matrix(groups_list, rel_path):
    if not groups_list: return ""
    contest_map = defaultdict(list)
    pids = set()
    for g in groups_list:
        contest_map[g.contest_name].append(g)
        pids.add(g.problem_id or "未知")
    
    def pid_key(s): return [int(c) if c.isdigit() else c for c in re.split('([0-9]+)', s)]
    sorted_pids = sorted(list(pids), key=lambda x: ([999] if x=="未知" else pid_key(x)))
    
    html = '<div style="overflow-x:auto;"><table class="matrix-table"><thead><tr><th class="contest-name-cell">比赛名称</th>'
    for p in sorted_pids: html += f'<th>{p}</th>'
    html += '</tr></thead><tbody>'
    
    for contest in sorted(contest_map.keys(), key=lambda x: len(contest_map[x]), reverse=True):
        row = contest_map[contest]
        html += f'<tr data-name="{contest}" data-count="{len(row)}"><td class="contest-name-cell">{contest}</td>'
        p_idx = {g.problem_id or "未知": g for g in row}
        for p in sorted_pids:
            html += '<td>'
            if p in p_idx:
                g = p_idx[p]
                diff_circle = ""
                if g.difficulty is not None:
                    diff_circle = f'<span class="diff-indicator" title="{g.difficulty}"><span class="diff-circle" style="{get_diff_style(g.difficulty)}"></span></span>'
                
                link_text = g.problem_id or g.base_name
                content = f'<a href="{g.link}" target="_blank">{link_text}</a>{diff_circle}'
                html += f'<div class="prob-cell"><div class="id-diff-nowrap">{content}</div>{gen_icons_html(g, rel_path)}</div>'
            html += '</td>'
        html += '</tr>'
    return html + "</tbody></table></div>"

def build_page(title, groups_dict, out_path, rel_path, is_zhati=False):
    atcoder_nav = ""
    content_html = ""
    sort_btns = ""
    
    if is_zhati:
        content_html = f"""<div class="zhati-filter-bar">
            <strong>🔍 筛选:</strong> <input type="text" id="filter-tag" placeholder="标签(空格多词)" onkeyup="filterZhati()">
            <strong>难度:</strong> <input type="number" id="filter-diff-min" placeholder="Min" style="width:60px" onchange="filterZhati()">-<input type="number" id="filter-diff-max" placeholder="Max" style="width:60px" onchange="filterZhati()">
            <strong>日期:</strong> <input type="date" id="filter-date-start" onchange="filterZhati()">-<input type="date" id="filter-date-end" onchange="filterZhati()">
        </div>
        <table class="normal-table" id="zhati-table"><thead><tr>
            <th>题目与来源</th><th>标签</th>
            <th>难度 <a class="sort-icon" onclick="sortZhati('diff','asc')">🔼</a><a class="sort-icon" onclick="sortZhati('diff','desc')">🔽</a></th>
            <th>添加日期 <a class="sort-icon" onclick="sortZhati('date','asc')">🔼</a><a class="sort-icon" onclick="sortZhati('date','desc')">🔽</a></th>
            <th>文件</th>
        </tr></thead><tbody>"""
        for g in sorted(groups_dict, key=lambda x: (x.date=="未知", x.date), reverse=True):
            diff_box = "-"
            if g.difficulty is not None:
                diff_box = f'<span class="diff-indicator"><span class="diff-circle" style="{get_diff_style(g.difficulty)}"></span> {int(g.difficulty)}</span>'
            tags_html = "".join([f'<span class="tag-pill">{t}</span>' for t in g.tags])
            content_html += f"""<tr data-tags="{" ".join(g.tags)}" data-diff="{g.difficulty or 'None'}" data-date="{g.date}">
                <td><a href="{g.link}" target="_blank"><b>{g.base_name}</b></a><br><small>{g.contest_name or g.category}</small></td>
                <td>{tags_html}</td><td>{diff_box}</td><td>{g.date}</td><td>{gen_icons_html(g, rel_path, False)}</td>
            </tr>"""
        content_html += "</tbody></table>"
    elif title == "AtCoder":
        sections = {'ABC':[], 'ARC':[], 'AGC':[], 'Other':[]}
        for contest, row in groups_dict.items():
            key = 'ABC' if 'ABC' in contest.upper() else 'ARC' if 'ARC' in contest.upper() else 'AGC' if 'AGC' in contest.upper() else 'Other'
            sections[key].extend(row)
        atcoder_nav = '<div style="margin-left:20px;">' + "".join([f'<button class="toggle-btn at-nav-btn {"active" if k=="ABC" else ""}" onclick="switchAtCoder(\'{k}\', this)">{k}</button>' for k in sections]) + '</div>'
        for k, v in sections.items():
            content_html += f'<div id="section-{k}" class="atcoder-section" style="display:{"block" if k=="ABC" else "none"}">{build_matrix(v, rel_path)}</div>'
    else:
        flat_list = [g for gs in groups_dict.values() for g in gs]
        content_html = build_matrix(flat_list, rel_path)
        sort_btns = '<div class="sort-btns"><button onclick="sortContests(\'count\')">按题数</button><button onclick="sortContests(\'name\')">按比赛名</button></div>'

    stats_html = f"<span>📁 题目数: {len(groups_dict) if is_zhati else sum(len(v) for v in groups_dict.values())}</span>"
    
    with open(out_path, 'w', encoding='utf-8') as f:
        f.write(HTML_TEMPLATE.format(title=title, subtitle="", stats_html=stats_html, sort_btns_html=sort_btns, atcoder_nav=atcoder_nav, content_html=content_html, gen_time=datetime.now().strftime("%Y-%m-%d")))

def main():
    data_dir, out_dir = 'data', '.'
    groups = scan_and_group_files(data_dir)
    process_metadata(groups, data_dir)
    
    cats = {'Codeforces': defaultdict(list), 'AtCoder': defaultdict(list), 'oi': defaultdict(list), 'xcpc': defaultdict(list), 'xcpc+': defaultdict(list)}
    zhati = []
    for g in groups.values():
        if g.category in cats: cats[g.category][g.contest_name].append(g)
        if g.has_conf or g.category == "杂题": zhati.append(g)
    
    for cname, cdata in cats.items(): build_page(cname, cdata, f"{cname}.html", "data")
    build_page("杂题", zhati, "杂题.html", "data", True)
    
    # Index
    with open("index.html", 'w', encoding='utf-8') as f:
        f.write(f"<html><head><title>Index</title><style>body{{font-family:sans-serif;padding:50px;background:#f4f5f7}} .card{{background:white;padding:20px;margin:10px;border-radius:8px;display:inline-block;width:200px;text-align:center;box-shadow:0 2px 5px rgba(0,0,0,0.1);text-decoration:none;color:#1a73e8;font-weight:bold}}</style></head><body><h1>题目整理索引</h1>")
        for c in list(cats.keys()) + ["杂题"]:
            f.write(f'<a class="card" href="{c}.html">{c}</a>')
        f.write("</body></html>")

if __name__ == '__main__': main()