# 角色与任务背景
你现在是一个资深的 Python 开发者和前端工程师。我正在开发一个**「算法竞赛题目整理工具」**，该工具通过扫描本地的代码和配置文件，自动生成带有响应式矩阵表格、Kenkoooo 风格难度圆环、以及多条件检索、纯前端状态持久化的 HTML 静态仪表盘和分类页。

这是我们目前最新、最完美的项目进度、核心规则以及所有 Python 脚本代码。请你先阅读并理解这些上下文。在理解完毕后，回复我“已完全掌握项目上下文，请问需要进行什么修改或新增什么功能？”即可。

---

## 1. 项目目录与文件识别规则
- **数据目录 (`data/`)**：存放 `.cpp` (代码)、`.md` (题解) 和 `.conf` (配置) 文件。
- **版本识别**：同名题目以 `1` 或 `_e1` 结尾为 Easy version，以 `2` 或 `_e2` 结尾为 Hard version。
- **官方/自动链接生成**：
  - Codeforces (`cf...`)：自动补全比赛和题号，生成官方链接。
  - AtCoder (`abc/arc/agc...`)：自动补全并分组，生成官方链接。
  - Luogu (`p10001`)：自动生成洛谷链接 (`luogu.com.cn/problem/P10001`)。
  - QOJ (`qoj1233`)：自动生成 QOJ 链接 (`qoj.ac/problem/1233`)。
- **创建日期提取**：自动读取 `.cpp` 第一行的 `// created time: YYYY-MM-DD`。

## 2. 配置文件 (`.conf`) 核心语法 (固定 6 行)
- **第 1 行**：标签/关键词（多个用空格隔开，末尾如果为数字自动解析为难度）。
- **第 2 行**：比赛分类（如 `OI` / `OIs` / `XCPC`）。支持用 `|` 隔开多个。CF/AT 留空默认归档官方。
- **第 3 行**：URL 链接（完整链接。CF/AT/Luogu/QOJ 留空自动生成）。
- **第 4 行**：比赛名称（支持用 `|` 隔开多场，如 `XOJ Round 1|YOJ 2`）。
- **第 5 行**：题目编号（支持用 `|` 隔开多个，如 `C|D`）。
- **第 6 行**：备注/备忘录（在表格中独立成列展示，不需要可留空）。

## 3. 核心业务逻辑与前端特性
1. **一题多端映射与官方截断**：通过 `|` 分隔符，一道题可同时出现在多个比赛的矩阵中。如果 CF/AT 题指定了 `OI/XCPC` 类别，则从官方 CF/AT 表格中移除。
2. **Easy/Hard 智能显示**：官方 CF/AT 页面中，矩阵同一列内自动拆分为左/右半格（如 `C1` / `C2`）；在自定义的 OI/XCPC 表格中不带 1/2 后缀（仅显示 `C`）。
3. **列表表格 (Summary / Todo)**：
   - 有 `.conf` 但无 `.cpp` 的题目流入 Todo，其余流入 Summary。
   - 列宽严格设定为：题目(35%)、标签(15%)、难度(9%)、日期(10%)、备注(22%)、文件(9%)。
   - 支持双重稳定排序（优先日期降序，其次文件名字典序）。
4. **比赛智能排序**：矩阵页面左侧的“比赛名称”按照先提取中文/阿拉伯数字外的文本作为字典序降序排列，再将所有提取出来的数字依次作为第二/三关键字排序。OI 页面第一列扩宽至 35%。
5. **极客仪表盘首页**：双列 Grid 布局，包含纯数字徽章的数据统计卡片，及 C++ `pragma` 优化指令说明。
6. **前端交互与 URL 记忆**：点击标签触发搜索或取消；查询词 `q`、难度 `min`/`max` 实时写入 `window.history` 的 URL Search 参数中刷新不丢失。难度 3200 满红圈，3300+ 金圈。

---

## 4. 当前最新代码资产 (共 4 个 Python 文件)

### 文件一：`run.py` (核心构建引擎，生成全套 HTML)
```python
import os
import sys
import re
from collections import defaultdict
from datetime import datetime

def get_diff_style(diff):
    if diff >= 3300:
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
    ratio = 100 if clamped_diff >= 3200 else (clamped_diff % 400) / 400 * 100
    return f'background: linear-gradient(to top, {color} {ratio}%, transparent {ratio}%); border: 1px solid {color}; border-radius: 50%;'

def contest_sort_key(name):
    if not name: return ("",)
    def replace_cn(m):
        s = m.group(0)
        val_map = {'零':0, '一':1, '二':2, '两':2, '三':3, '四':4, '五':5, '六':6, '七':7, '八':8, '九':9}
        unit_map = {'十':10, '百':100, '千':1000, '万':10000}
        res = 0; tmp = 0
        for char in s:
            if char in val_map: tmp = val_map[char]
            elif char in unit_map:
                if tmp == 0 and char == '十': tmp = 1
                res += tmp * unit_map[char]
                tmp = 0
        res += tmp
        return str(res)
    name_num = re.sub(r'[零一二两三四五六七八九十百千万]+', replace_cn, name)
    parts = re.split(r'(\d+)', name_num)
    non_num = "".join([p for p in parts if not p.isdigit()]).strip().lower()
    nums = [int(p) for p in parts if p.isdigit()]
    return (non_num, *nums)

HTML_TEMPLATE = """<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{title} - 题目整理</title>
    <style>
        :root {{ var(--primary: #2563eb; --primary-hover: #1d4ed8; --bg: #f4f5f8; --text-main: #1e293b; --text-muted: #64748b; --border: #e2e8f0; --panel-bg: #f8fafc; }}
        body {{ font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; background: var(--bg); color: var(--text-main); margin: 0; padding: 20px; line-height: 1.6; overflow-x: hidden; }}
        .container {{ width: 100%; max-width: 1400px; margin: 10px auto 30px; padding: 30px; background: #fff; border-radius: 16px; box-shadow: 0 4px 15px rgba(0,0,0,0.03); border: 1px solid var(--border); box-sizing: border-box; }}
        h1 {{ color: #0f172a; font-size: 2.2em; font-weight: 800; margin-top: 0; margin-bottom: 20px; letter-spacing: -0.5px; }}
        h2 {{ color: #0f172a; font-weight: 700; margin-bottom: 12px; }}
        .nav-bar {{ margin-bottom: 24px; padding-bottom: 16px; border-bottom: 1px solid var(--border); display: flex; align-items: center; flex-wrap: wrap; gap: 15px; }}
        .nav-bar a {{ color: var(--primary); text-decoration: none; font-weight: 600; transition: color 0.2s; }}
        .nav-bar a:hover {{ color: var(--primary-hover); text-decoration: underline; }}
        .btn {{ background: #fff; border: 1px solid var(--border); border-radius: 8px; padding: 8px 14px; cursor: pointer; font-size: 0.9em; font-weight: 600; transition: all 0.2s; color: var(--text-main); }}
        .btn:hover {{ background: var(--panel-bg); border-color: #cbd5e1; transform: translateY(-1px); box-shadow: 0 2px 4px rgba(0,0,0,0.02); }}
        .toggle-diff-btn {{ margin-left: auto; color: var(--primary); border-color: #bfdbfe; }}
        .toggle-diff-btn:hover {{ background: #eff6ff; }}
        .toggle-remark-btn {{ color: #475569; border-color: #e2e8f0; background: #f8fafc; margin-left: 10px; }}
        .toggle-remark-btn:hover {{ background: #f1f5f9; }}
        .stats-bar {{ display: flex; justify-content: space-between; align-items: center; background: var(--panel-bg); border: 1px solid var(--border); padding: 16px 20px; border-radius: 12px; margin-bottom: 24px; flex-wrap: wrap; gap: 10px; box-sizing: border-box; }}
        .stats-info span {{ margin-right: 18px; font-size: 0.95em; color: #334155; font-weight: 600; display: inline-block; }}
        .sort-btns button {{ margin-left: 8px; color: var(--primary); }}
        table {{ width: 100%; border-collapse: separate; border-spacing: 0; table-layout: fixed; word-wrap: break-word; overflow-wrap: break-word; }}
        th, td {{ padding: 12px 14px; box-sizing: border-box; text-align: left; vertical-align: middle; }}
        .matrix-table, .normal-table {{ background: #fff; margin-bottom: 30px; border-radius: 12px; overflow: hidden; border: 1px solid var(--border); }}
        thead {{ background: var(--panel-bg); }}
        th {{ color: #475569; font-weight: 600; border-bottom: 2px solid var(--border); }}
        td {{ border-bottom: 1px solid var(--border); }}
        th:not(:last-child), td:not(:last-child) {{ border-right: 1px solid var(--border); }}
        tbody tr:last-child td {{ border-bottom: none; }}
        tbody tr:hover td {{ background-color: #f8fafc; }}
        .matrix-table th, .matrix-table td {{ text-align: center; }}
        .contest-name-cell {{ text-align: left !important; font-weight: 600; color: #0f172a; background: #fff; }}
        .normal-table th:nth-child(1) {{ width: 35%; }}  
        .normal-table th:nth-child(2) {{ width: 15%; }}  
        .normal-table th:nth-child(3) {{ width: 9%; }}   
        .normal-table th:nth-child(4) {{ width: 10%; }}  
        .normal-table th.remark-col {{ width: 22%; color: var(--text-muted); font-weight: 500; font-size: 0.95em; }} 
        .normal-table th:last-child {{ width: 9%; }}     
        .normal-table td.remark-col {{ color: var(--text-muted); font-size: 0.9em; }}
        .prob-cell {{ display: flex; flex-direction: column; align-items: center; gap: 8px; justify-content: center; }}
        .prob-link-wrap {{ font-size: 0.9em; display: inline-flex; align-items: center; justify-content: center; gap: 6px; background: #f1f5f9; padding: 4px 12px; border-radius: 12px; flex-wrap: nowrap; white-space: nowrap; }}
        .prob-link-wrap a {{ color: var(--primary); text-decoration: none; font-weight: 700; }}
        .prob-link-wrap a:hover {{ text-decoration: underline; }}
        .diff-indicator {{ display: inline-flex; align-items: center; gap: 4px; font-weight: bold; font-size: 0.9em; }}
        .diff-circle {{ width: 12px; height: 12px; display: inline-block; }}
        .mini-version-row {{ display: flex; align-items: center; justify-content: center; gap: 6px; font-size: 1.1em; flex-wrap: wrap; }}
        .mini-tag {{ font-size: 0.7em; padding: 2px 5px; border-radius: 4px; font-weight: bold; line-height: 1; }}
        .mini-tag-easy {{ background: #dcfce7; color: #166534; }}
        .mini-tag-hard {{ background: #fee2e2; color: #991b1b; }}
        .mini-file-link {{ text-decoration: none; display: inline-block; transition: transform 0.2s; }}
        .mini-file-link:hover {{ transform: scale(1.15); }}
        .version-row {{ margin-bottom: 6px; display: flex; align-items: center; flex-wrap: wrap; gap: 8px; }}
        .file-link {{ color: var(--primary); text-decoration: none; font-size: 1.05em; white-space: nowrap; transition: transform 0.2s; display: inline-block; }}
        .file-link:hover {{ transform: scale(1.1); }}
        .tag-pill {{ background: #f1f5f9; color: #475569; font-size: 0.85em; padding: 3px 10px; border-radius: 12px; font-weight: 500; display: inline-block; margin: 2px; border: 1px solid #e2e8f0; transition: all 0.2s; }}
        .tag-pill:hover {{ background: #e2e8f0; border-color: #cbd5e1; transform: translateY(-1px); box-shadow: 0 2px 4px rgba(0,0,0,0.03); }}
        .list-filter-bar {{ background: #fff; border: 1px solid var(--border); padding: 18px; border-radius: 12px; margin-bottom: 24px; display: flex; flex-wrap: wrap; gap: 14px; align-items: center; box-sizing: border-box; }}
        .list-filter-bar input {{ padding: 8px 12px; border: 1px solid #cbd5e1; border-radius: 6px; outline: none; font-size: 0.95em; transition: border-color 0.2s; color: var(--text-main); }}
        .list-filter-bar input:focus {{ border-color: var(--primary); box-shadow: 0 0 0 3px rgba(37,99,235,0.1); }}
        .footer {{ margin-top: 40px; padding-top: 20px; border-top: 1px solid var(--border); text-align: center; color: #94a3b8; font-size: 0.85em; }}
    </style>
</head>
<body>
    <div class="container">
        <div class="nav-bar">
            <a href="index.html">🏠 Dashboard</a>
            <span style="color:#cbd5e1;">|</span>
            <span style="font-size: 0.9em; color: var(--text-muted); font-weight: 500;">Archive Matrix</span>
            <button class="btn toggle-diff-btn" onclick="toggleDiff()">🌕 隐藏难度</button>
            {nav_extra}
        </div>
        <h1>{title}</h1>
        {stats_block}
        {content_html}
        <div class="footer">最后构建: {gen_time} | Algorithm Platform Generator</div>
    </div>
    <script>
        let isDiffVisible = true;
        function toggleDiff() {{
            isDiffVisible = !isDiffVisible;
            const btn = document.querySelector('.toggle-diff-btn');
            if (isDiffVisible) {{
                btn.innerHTML = '🌕 隐藏难度';
                btn.style.color = 'var(--primary)';
                btn.style.borderColor = '#bfdbfe';
                btn.style.background = '#fff';
            }} else {{
                btn.innerHTML = '🌑 显示难度';
                btn.style.color = '#475569';
                btn.style.borderColor = '#e2e8f0';
                btn.style.background = '#f8fafc';
            }}
            document.querySelectorAll('.diff-indicator').forEach(el => {{ el.style.display = isDiffVisible ? 'inline-flex' : 'none'; }});
        }}
        
        let isRemarkVisible = true;
        function toggleRemark() {{
            isRemarkVisible = !isRemarkVisible;
            document.querySelectorAll('.remark-col').forEach(el => {{ el.style.display = isRemarkVisible ? 'table-cell' : 'none'; }});
            const btn = document.querySelector('.toggle-remark-btn');
            if (btn) {{
                btn.innerHTML = isRemarkVisible ? '🚫 隐藏备注' : '📝 显示备注';
                btn.style.color = isRemarkVisible ? '#475569' : '#059669';
                btn.style.borderColor = isRemarkVisible ? '#e2e8f0' : '#a7f3d0';
                btn.style.background = isRemarkVisible ? '#f8fafc' : '#fff';
            }}
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
                        return b.dataset.name.localeCompare(a.dataset.name, undefined, {{numeric: true}});
                    }}
                }});
                rows.forEach(r => tbody.appendChild(r));
            }});
        }}

        function addTagToFilter(tag, tableId) {{
            const input = document.getElementById('filter-tag-' + tableId);
            if (!input) return;
            let terms = input.value.trim().split(/\\s+/).filter(t => t);
            const lowerTag = tag.toLowerCase();
            const index = terms.findIndex(t => t.toLowerCase() === lowerTag);
            if (index === -1) {{ terms.push(tag); }} else {{ terms.splice(index, 1); }}
            input.value = terms.length > 0 ? terms.join(' ') + ' ' : '';
            filterListTable(tableId);
            input.focus();
        }}

        function clearTagFilter(tableId) {{
            const input = document.getElementById('filter-tag-' + tableId);
            if (input) {{ input.value = ''; filterListTable(tableId); input.focus(); }}
        }}

        function filterListTable(tableId) {{
            const input = document.getElementById('filter-tag-' + tableId);
            const tagVal = input ? input.value.toLowerCase().trim() : '';
            const searchTerms = tagVal.split(/\\s+/).filter(t => t);
            
            const clearBtn = document.getElementById('clear-btn-' + tableId);
            if (clearBtn) {{ clearBtn.style.display = tagVal.length > 0 ? 'block' : 'none'; }}
            
            const minInput = document.getElementById('filter-diff-min-' + tableId);
            const maxInput = document.getElementById('filter-diff-max-' + tableId);
            const minStr = minInput ? minInput.value : '';
            const maxStr = maxInput ? maxInput.value : '';
            const minVal = minStr !== '' ? parseFloat(minStr) : -Infinity;
            const maxVal = maxStr !== '' ? parseFloat(maxStr) : Infinity;

            if (tableId.includes('table')) {{
                const url = new URL(window.location);
                if (tagVal) url.searchParams.set('q', tagVal); else url.searchParams.delete('q');
                if (minStr) url.searchParams.set('min', minStr); else url.searchParams.delete('min');
                if (maxStr) url.searchParams.set('max', maxStr); else url.searchParams.delete('max');
                window.history.replaceState({{}}, '', url);
            }}

            const dateStart = document.getElementById('filter-date-start-' + tableId) ? document.getElementById('filter-date-start-' + tableId).value : '';
            const dateEnd = document.getElementById('filter-date-end-' + tableId) ? document.getElementById('filter-date-end-' + tableId).value : '';

            const rows = document.querySelectorAll('#' + tableId + ' tbody tr');
            rows.forEach(row => {{
                const tags = row.getAttribute('data-tags').toLowerCase();
                const baseName = (row.getAttribute('data-base') || '').toLowerCase();
                const diffStr = row.getAttribute('data-diff');
                const rDate = row.getAttribute('data-date');
                const diff = diffStr !== 'None' ? parseFloat(diffStr) : NaN;

                let matchTag = true;
                if (searchTerms.length > 0) {{ matchTag = searchTerms.every(term => tags.includes(term) || baseName.includes(term)); }}
                let matchDiff = true;
                if (minStr !== '' || maxStr !== '') {{
                    if (isNaN(diff)) matchDiff = false;
                    else if (diff < minVal || diff > maxVal) matchDiff = false;
                }}
                let matchDate = true;
                if (dateStart && (rDate === '未知' || rDate < dateStart)) matchDate = false;
                if (dateEnd && (rDate === '未知' || rDate > dateEnd)) matchDate = false;

                row.style.display = (matchTag && matchDiff && matchDate) ? '' : 'none';
            }});
        }}

        let sortDirection = {{}};
        function sortListTable(tableId, col) {{
            if (!sortDirection[tableId]) sortDirection[tableId] = {{ 'diff': 1, 'date': 1 }};
            const tbody = document.querySelector('#' + tableId + ' tbody');
            if (!tbody) return;
            const rows = Array.from(tbody.querySelectorAll('tr'));
            sortDirection[tableId][col] *= -1;
            const dir = sortDirection[tableId][col];
            
            rows.sort((a, b) => {{
                let res = 0;
                if (col === 'diff') {{
                    let v1 = parseFloat(a.dataset.diff);
                    let v2 = parseFloat(b.dataset.diff);
                    if (isNaN(v1)) v1 = -Infinity;
                    if (isNaN(v2)) v2 = -Infinity;
                    res = (v1 - v2) * dir;
                }} else if (col === 'date') {{
                    let d1 = a.dataset.date;
                    let d2 = b.dataset.date;
                    if (d1 === '未知') d1 = '';
                    if (d2 === '未知') d2 = '';
                    res = d1.localeCompare(d2) * dir;
                }}
                if (res === 0) {{
                    let baseA = a.dataset.base || '';
                    let baseB = b.dataset.base || '';
                    return baseA.localeCompare(baseB, undefined, {{numeric: true}});
                }}
                return res;
            }});
            rows.forEach(r => tbody.appendChild(r));
        }}

        function switchAtCoderTab(targetId, btn) {{
            document.querySelectorAll('.atcoder-tab-content').forEach(el => el.style.display = 'none');
            document.getElementById(targetId).style.display = 'block';
            document.querySelectorAll('.atcoder-tab-btn').forEach(el => {{
                el.style.background = '#fff';
                el.style.color = '#334155';
                el.style.borderColor = '#e2e8f0';
            }});
            btn.style.background = 'var(--primary)';
            btn.style.color = '#fff';
            btn.style.borderColor = 'var(--primary)';
        }}

        window.addEventListener('DOMContentLoaded', () => {{
            const urlParams = new URLSearchParams(window.location.search);
            const q = urlParams.get('q');
            const min = urlParams.get('min');
            const max = urlParams.get('max');
            const input = document.querySelector('input[id^="filter-tag-"]');
            if (input) {{
                const tableId = input.id.replace('filter-tag-', '');
                if (q) input.value = q + ' ';
                const minInput = document.getElementById('filter-diff-min-' + tableId);
                if (minInput && min) minInput.value = min;
                const maxInput = document.getElementById('filter-diff-max-' + tableId);
                if (maxInput && max) maxInput.value = max;
                if (q || min || max) {{ filterListTable(tableId); }}
            }}
        }});
    </script>
</body>
</html>
"""

INDEX_HTML_TEMPLATE = """<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>算法主页 | Algorithm Dashboard</title>
    <style>
        :root {{ --bg: #f4f5f8; --text-main: #1e293b; --text-muted: #64748b; }}
        body {{ font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; background: var(--bg); color: var(--text-main); margin: 0; padding: 40px 20px; line-height: 1.6; }}
        .container {{ max-width: 1100px; margin: 0 auto; }}
        header {{ text-align: center; margin-bottom: 50px; }}
        h1 {{ font-size: 2.5em; margin-bottom: 5px; font-weight: 800; letter-spacing: -0.5px; color: #0f172a; }}
        .subtitle {{ color: var(--text-muted); font-size: 1.1em; }}
        .dashboard-grid {{ display: grid; grid-template-columns: repeat(2, 1fr); gap: 24px; margin-bottom: 40px; }}
        @media (max-width: 768px) {{ .dashboard-grid {{ grid-template-columns: 1fr; }} }}
        .card {{ background: #fff; border-radius: 16px; padding: 24px; padding-bottom: 28px; box-shadow: 0 4px 15px rgba(0,0,0,0.03); border: 1px solid #e2e8f0; text-decoration: none; color: inherit; display: flex; flex-direction: column; position: relative; overflow: hidden; transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1); }}
        .card:hover {{ transform: translateY(-5px); box-shadow: 0 12px 25px rgba(0,0,0,0.08); border-color: #cbd5e1; }}
        .card::before {{ content: ""; position: absolute; top: 0; left: 0; right: 0; height: 4px; }}
        .card-summary::before {{ background: linear-gradient(90deg, #8b5cf6, #d946ef); }}
        .card-todo::before {{ background: linear-gradient(90deg, #f59e0b, #fbbf24); }}
        .card-oi::before {{ background: linear-gradient(90deg, #3b82f6, #0ea5e9); }}
        .card-xcpc::before {{ background: linear-gradient(90deg, #10b981, #34d399); }}
        .card-cf::before {{ background: linear-gradient(90deg, #ef4444, #f87171); }}
        .card-at::before {{ background: linear-gradient(90deg, #1e293b, #475569); }}
        .card-header {{ display: flex; justify-content: space-between; align-items: center; margin-bottom: 16px; }}
        .card-title {{ font-size: 1.4em; font-weight: 700; margin: 0; display: flex; align-items: center; gap: 8px; }}
        .card-badge {{ font-size: 0.8em; padding: 4px 10px; border-radius: 8px; font-weight: 700; font-family: ui-monospace, SFMono-Regular, Consolas, monospace; }}
        .card-stats {{ display: flex; align-items: baseline; gap: 8px; margin-bottom: 0; }}
        .stat-number {{ font-size: 3.2em; font-weight: 800; line-height: 1; }}
        .stat-label {{ color: var(--text-muted); font-size: 1.05em; font-weight: 500; }}
        .info-grid {{ display: grid; grid-template-columns: 1fr 1fr; gap: 24px; }}
        @media (max-width: 900px) {{ .info-grid {{ grid-template-columns: 1fr; }} }}
        .info-box {{ background: #fff; border-radius: 16px; padding: 30px; box-shadow: 0 4px 15px rgba(0,0,0,0.03); border: 1px solid #e2e8f0; display: flex; flex-direction: column; }}
        .info-box h3 {{ margin-top: 0; margin-bottom: 15px; color: #0f172a; display: flex; align-items: center; gap: 8px; font-weight: 700; font-size: 1.1em; }}
        .syntax-code {{ display: grid; gap: 10px; font-family: ui-monospace, SFMono-Regular, Consolas, monospace; font-size: 0.88em; background: #f8fafc; padding: 20px; border-radius: 12px; border: 1px solid #f1f5f9; overflow-x: auto; flex-grow: 1; }}
        .line-def {{ display: flex; gap: 16px; }}
        .line-num {{ color: #94a3b8; user-select: none; width: 15px; text-align: right; font-weight: bold; }}
        .line-desc {{ color: #334155; }}
        .highlight {{ color: #2563eb; font-weight: 600; }}
        .cpp-code {{ background: #1e293b; color: #f8fafc; padding: 20px; border-radius: 12px; font-family: ui-monospace, SFMono-Regular, Consolas, monospace; font-size: 0.85em; overflow-x: auto; margin: 0; line-height: 1.6; flex-grow: 1; display: flex; flex-direction: column; justify-content: center; }}
        .cpp-keyword {{ color: #c678dd; }}
        .cpp-include {{ color: #98c379; }}
        .footer {{ text-align: center; color: #94a3b8; font-size: 0.85em; margin-top: 50px; }}
    </style>
</head>
<body>
    <div class="container">
        <header>
            <h1>Algorithm Dashboard</h1>
            <div class="subtitle">个人算法竞赛题目归档与整理工作台</div>
        </header>
        <div class="dashboard-grid">
            <a href="Summary.html" class="card card-summary">
                <div class="card-header"><h2 class="card-title"><span>📚</span> Summary</h2><span class="card-badge" style="color: #8b5cf6; background: #ede9fe;">All</span></div>
                <div class="card-stats"><span class="stat-number">{s_count}</span><span class="stat-label">个独立版本</span></div>
            </a>
            <a href="todo.html" class="card card-todo">
                <div class="card-header"><h2 class="card-title"><span>🎯</span> Todo</h2><span class="card-badge" style="color: #d97706; background: #fef3c7;">Task</span></div>
                <div class="card-stats"><span class="stat-number">{t_count}</span><span class="stat-label">道待补题</span></div>
            </a>
            <a href="OI.html" class="card card-oi">
                <div class="card-header"><h2 class="card-title"><span>🏅</span> OI</h2><span class="card-badge" style="color: #2563eb; background: #dbeafe;">{oi_c}</span></div>
                <div class="card-stats"><span class="stat-number">{oi_p}</span><span class="stat-label">题归档</span></div>
            </a>
            <a href="XCPC.html" class="card card-xcpc">
                <div class="card-header"><h2 class="card-title"><span>🏆</span> XCPC</h2><span class="card-badge" style="color: #059669; background: #d1fae5;">{xcpc_c}</span></div>
                <div class="card-stats"><span class="stat-number">{xcpc_p}</span><span class="stat-label">题归档</span></div>
            </a>
            <a href="Codeforces.html" class="card card-cf">
                <div class="card-header"><h2 class="card-title"><span>⚡</span> Codeforces</h2><span class="card-badge" style="color: #dc2626; background: #fee2e2;">{cf_c}</span></div>
                <div class="card-stats"><span class="stat-number">{cf_p}</span><span class="stat-label">题归档</span></div>
            </a>
            <a href="AtCoder.html" class="card card-at">
                <div class="card-header"><h2 class="card-title"><span>🗻</span> AtCoder</h2><span class="card-badge" style="color: #334155; background: #f1f5f9;">{at_c}</span></div>
                <div class="card-stats"><span class="stat-number">{at_p}</span><span class="stat-label">题归档</span></div>
            </a>
        </div>
        <div class="info-grid">
            <div class="info-box">
                <h3><span>⚙️</span> .conf 语法规则 (固定 6 行)</h3>
                <div class="syntax-code">
                    <div class="line-def"><span class="line-num">1</span> <span class="line-desc"><span class="highlight">标签/关键词</span> (多个用空格隔开，末尾数字解析为难度)</span></div>
                    <div class="line-def"><span class="line-num">2</span> <span class="line-desc"><span class="highlight">比赛分类</span> (支持 | 隔开，填 OI / OIs / XCPC。CF/AT 留空自动归档)</span></div>
                    <div class="line-def"><span class="line-num">3</span> <span class="line-desc"><span class="highlight">URL 链接</span> (完整链接。Luogu/QOJ/CF/AT 等留空自动生成)</span></div>
                    <div class="line-def"><span class="line-num">4</span> <span class="line-desc"><span class="highlight">比赛名称</span> (支持 | 隔开多场，如 XOJ Round 1|YOJ 2)</span></div>
                    <div class="line-def"><span class="line-num">5</span> <span class="line-desc"><span class="highlight">题目编号</span> (支持 | 隔开多个，如 C|D)</span></div>
                    <div class="line-def"><span class="line-num">6</span> <span class="line-desc"><span class="highlight">备注/备忘录</span> (在表格中独立成列展示，不需要可留空)</span></div>
                </div>
            </div>
            <div class="info-box">
                <h3><span>🚀</span> GCC 编译优化指令</h3>
                <pre class="cpp-code"><code><span class="cpp-keyword">#pragma</span> GCC optimize(3,<span class="cpp-include">"inline"</span>)
<span class="cpp-keyword">#pragma</span> GCC optimize(<span class="cpp-include">"Ofast,no-stack-protector,unroll-loops,fast-math"</span>)
<span class="cpp-keyword">#pragma</span> GCC target(<span class="cpp-include">"sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2"</span>)</code></pre>
            </div>
        </div>
        <div class="footer">最后构建: {gen_time} | Algorithm Platform Generator</div>
    </div>
</body>
</html>
"""

class ProblemVersion:
    def __init__(self, name, base_filename=""):
        self.name = name
        self.base_filename = base_filename
        self.files = {'cpp': None, 'md': None, 'conf': None}
        self.link = "#"
        self.tags = []
        self.difficulty = None
        self.remark = ""
        self.has_conf = False
        self.date = "未知"
        self.appearances = [] 

class ProblemGroup:
    def __init__(self, base_name):
        self.base_name = base_name
        self.has_conf = False
        self.versions = {}
        self.version_order = ['Normal', 'Easy', 'Hard']
        self.appearances = []

    def add_file(self, version, ext, filename, base_filename):
        if version not in self.versions:
            self.versions[version] = ProblemVersion(version, base_filename)
        if ext == '.cpp': self.versions[version].files['cpp'] = filename
        elif ext == '.md': self.versions[version].files['md'] = filename
        elif ext == '.conf': self.versions[version].files['conf'] = filename
        
    def get_pid_in_contest(self, contest):
        for cat, c, p in self.appearances:
            if c == contest: return p
        return ""

def scan_and_group_files(data_dir):
    groups = {}
    conf_bases = set()
    if os.path.exists(data_dir):
        for f in os.listdir(data_dir):
            if f.endswith('.conf'): conf_bases.add(f[:-5])

    for f in os.listdir(data_dir):
        if not os.path.isfile(os.path.join(data_dir, f)): continue
        name, ext = os.path.splitext(f)
        if ext not in ['.cpp', '.md', '.conf']: continue
            
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
        groups[base_name].add_file(version, ext, f, name)
        
    return groups

def apply_categories_and_links(groups, data_dir):
    for group in groups.values():
        m_cf = re.match(r'^cf(\d+)([a-zA-Z]+)$', group.base_name, re.IGNORECASE)
        m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+)$', group.base_name, re.IGNORECASE)
        m_luogu = re.match(r'^p(\d+)$', group.base_name, re.IGNORECASE)
        m_qoj = re.match(r'^qoj(\d+)$', group.base_name, re.IGNORECASE)
        
        is_cf, is_at, is_luogu, is_qoj = bool(m_cf), bool(m_ac), bool(m_luogu), bool(m_qoj)

        group.appearances = []
        group.has_conf = False
        
        for v_name in group.version_order:
            if v_name not in group.versions: continue
            v = group.versions[v_name]
            
            if v.files.get('cpp'):
                fp = os.path.join(data_dir, v.files['cpp'])
                if os.path.exists(fp):
                    try:
                        with open(fp, 'r', encoding='utf-8') as f:
                            first_line = f.readline()
                            m = re.search(r'//\s*created time:\s*(\d{4}-\d{2}-\d{2})', first_line, re.IGNORECASE)
                            if m: v.date = m.group(1)
                    except Exception: pass
                    
            primary_link = "#"
            cat_list_clean = []
            
            if v.files.get('conf'):
                v.has_conf = True
                group.has_conf = True
                fp = os.path.join(data_dir, v.files['conf'])
                try:
                    with open(fp, 'r', encoding='utf-8') as f:
                        lines = [line.strip() for line in f.readlines()]
                    while len(lines) < 6: lines.append('')
                    
                    parts = lines[0].split()
                    if parts:
                        try:
                            v.difficulty = float(parts[-1])
                            v.tags = parts[:-1]
                        except ValueError:
                            v.tags = parts
                            v.difficulty = None
                            
                    cat_str = lines[1].strip()
                    c_str = lines[3].strip()
                    p_str = lines[4].strip()
                    
                    if cat_str or c_str or p_str:
                        cat_list_raw = [x.strip() for x in cat_str.split('|')] if cat_str else []
                        c_list = [x.strip() for x in c_str.split('|')] if c_str else []
                        p_list = [x.strip() for x in p_str.split('|')] if p_str else []
                        
                        for cat in cat_list_raw:
                            if cat.lower() == 'oi': cat_list_clean.append('OI')
                            elif cat.lower() == 'ois': cat_list_clean.append('OIs')
                            elif cat.lower() == 'xcpc': cat_list_clean.append('XCPC')
                            else: cat_list_clean.append(cat)
                            
                        if not c_list:
                            if is_cf: c_list = [f"Codeforces Round {m_cf.group(1)}"]
                            elif is_at: c_list = [f"{m_ac.group(1).upper()}{m_ac.group(2)}"]
                        if not p_list:
                            if is_cf: p_list = [m_cf.group(2).upper()]
                            elif is_at: p_list = [m_ac.group(3).upper()]
                            
                        max_len = max(len(cat_list_clean), len(c_list), len(p_list))
                        
                        for i in range(max_len):
                            cat = cat_list_clean[i] if i < len(cat_list_clean) else (cat_list_clean[-1] if cat_list_clean else "")
                            c = c_list[i] if i < len(c_list) else (c_list[-1] if c_list else "")
                            p = p_list[i] if i < len(p_list) else (p_list[-1] if p_list else "")
                            
                            current_cat = cat
                            if not current_cat:
                                if is_cf and c == f"Codeforces Round {m_cf.group(1)}":
                                    current_cat = 'Codeforces'
                                elif is_at and c == f"{m_ac.group(1).upper()}{m_ac.group(2)}":
                                    current_cat = 'AtCoder'
                                    
                            if c and current_cat:
                                v.appearances.append((current_cat, c, p))
                            elif c and not current_cat:
                                v.appearances.append(('', c, p))
                                
                    primary_link = lines[2].strip()
                    v.remark = lines[5]
                except Exception:
                    pass
            
            add_official_cf = is_cf
            add_official_at = is_at
            if v.has_conf and (lines[1].strip() or lines[3].strip() or lines[4].strip()):
                if is_cf and 'Codeforces' not in cat_list_clean:
                    add_official_cf = False
                if is_at and 'AtCoder' not in cat_list_clean:
                    add_official_at = False

            suffix = "1" if v_name == 'Easy' else ("2" if v_name == 'Hard' else "")
            cf_at_link = "#"
            
            if add_official_cf:
                c = f"Codeforces Round {m_cf.group(1)}"
                base_p = m_cf.group(2).upper()
                v.appearances.append(('Codeforces', c, base_p))
            if is_cf:
                cf_at_link = f"https://codeforces.com/problemset/problem/{m_cf.group(1)}/{m_cf.group(2).upper() + suffix}"
                
            if add_official_at:
                c = f"{m_ac.group(1).upper()}{m_ac.group(2)}"
                base_p = m_ac.group(3).upper()
                v.appearances.append(('AtCoder', c, base_p))
            if is_at:
                cf_at_link = f"https://atcoder.jp/contests/{m_ac.group(1).lower()}{m_ac.group(2)}/tasks/{m_ac.group(1).lower()}{m_ac.group(2)}_{(m_ac.group(3).upper() + suffix).lower()}"
                
            if not v.appearances:
                v.appearances.append(('Summary', '', ''))
                
            if not primary_link or primary_link == "#":
                if is_cf or is_at:
                    primary_link = cf_at_link
                elif is_luogu:
                    primary_link = f"https://www.luogu.com.cn/problem/P{m_luogu.group(1)}"
                elif is_qoj:
                    primary_link = f"https://qoj.ac/problem/{m_qoj.group(1)}"
                    
            v.link = primary_link

            for app in v.appearances:
                if app not in group.appearances:
                    group.appearances.append(app)

def render_single_version(v, rel_path, contest_pid="", is_official=False):
    display_pid = v.base_filename
    if contest_pid:
        display_pid = contest_pid
        if is_official and v.name in ['Easy', 'Hard'] and not contest_pid[-1].isdigit():
            display_pid += "1" if v.name == 'Easy' else "2"
            
    link_html = f'<a href="{v.link}" target="_blank">{display_pid}</a>' if v.link != '#' else f'<span>{display_pid}</span>'
    diff_html = ""
    if v.difficulty is not None:
        style = get_diff_style(v.difficulty)
        diff_html = f'<span class="diff-indicator" title="难度: {v.difficulty}"><span class="diff-circle" style="{style}"></span> {int(v.difficulty) if v.difficulty.is_integer() else v.difficulty}</span>'
    
    links = []
    if v.files.get('cpp'): links.append(f'<a href="{rel_path}/{v.files["cpp"]}" class="file-link" title="代码" style="text-decoration:none;">📝</a>')
    if v.files.get('md'): 
        md_href = v.files['md'][:-3] if v.files['md'].endswith('.md') else v.files['md']
        links.append(f'<a href="{rel_path}/{md_href}" class="file-link" title="题解" style="text-decoration:none;">💡</a>')
    if v.files.get('conf'): links.append(f'<a href="{rel_path}/{v.files["conf"]}" class="file-link" title="配置" style="text-decoration:none;">⚙️</a>')
    
    return f"""
    <div class="prob-cell" style="margin-bottom:8px;">
        <div class="prob-link-wrap">{link_html}{diff_html}</div>
        <div class="version-row" style="flex-wrap: nowrap;"><span style="white-space: nowrap; display: inline-flex; gap: 6px;">{"".join(links)}</span></div>
    </div>"""

def build_matrix_table(groups_dict, rel_path, is_official=False, first_col_width=20):
    if not groups_dict: return ""
    all_pids = set()
    for contest, c_groups in groups_dict.items():
        for g in c_groups:
            pid = g.get_pid_in_contest(contest)
            all_pids.add(pid if pid else "未知")
            
    def alnum_key(s): return [int(c) if c.isdigit() else c.lower() for c in re.split('([0-9]+)', s)]
    sorted_pids = sorted(list(all_pids), key=lambda x: ([float('inf')] if x == '未知' else alnum_key(x)))

    html = f'<div style="overflow-x: auto;"><table class="matrix-table"><thead><tr><th style="text-align: left; width: {first_col_width}%; padding-left: 20px;">比赛名称</th>'
    col_width = (100 - first_col_width) / max(1, len(sorted_pids))
    for pid in sorted_pids: html += f'<th style="width: {col_width}%;">{pid}</th>'
    html += '</tr></thead><tbody>'
    
    sorted_contests = sorted(groups_dict.items(), key=lambda x: contest_sort_key(x[0]), reverse=True)
    for contest, c_groups in sorted_contests:
        pid_map = defaultdict(list)
        for g in c_groups:
            pid = g.get_pid_in_contest(contest)
            pid_map[pid if pid else "未知"].append(g)
        
        html += f'<tr data-name="{contest}" data-count="{len(c_groups)}">'
        display_contest = contest if contest else "无名比赛"
        html += f'<td class="contest-name-cell" style="padding-left: 20px;">{display_contest} <br><span style="font-size:0.85em; color:var(--text-muted); font-weight:normal;">({len(c_groups)} 题)</span></td>'
        
        for pid in sorted_pids:
            html += '<td>'
            if pid in pid_map:
                for g in sorted(pid_map[pid], key=lambda x: x.base_name):
                    if 'Normal' in g.versions and len(g.versions) == 1:
                        html += render_single_version(g.versions['Normal'], rel_path, pid, is_official)
                    else:
                        html += '<div style="display: flex; gap: 4px; justify-content: center; width: 100%;">'
                        for v_name in ['Easy', 'Hard']:
                            if v_name in g.versions:
                                border = 'border-right: 1px dashed #cbd5e1; padding-right: 4px;' if v_name == 'Easy' and 'Hard' in g.versions else ''
                                html += f'<div style="flex: 1; {border}">'
                                html += render_single_version(g.versions[v_name], rel_path, pid, is_official)
                                html += '</div>'
                        html += '</div>'
            html += '</td>'
        html += '</tr>'
    html += '</tbody></table></div>'
    return html

def build_category_page(title, groups_dict, out_path, rel_path):
    all_versions = []
    if title == 'OI':
        for sub_gs in groups_dict.values():
            for gs in sub_gs.values():
                for g in gs: all_versions.extend(g.versions.values())
    else:
        for gs in groups_dict.values():
            for g in gs: all_versions.extend(g.versions.values())
                
    has_cpp = sum(1 for v in all_versions if v.files.get('cpp'))
    has_md = sum(1 for v in all_versions if v.files.get('md'))
    has_conf = sum(1 for v in all_versions if v.files.get('conf'))

    if title == 'OI':
        total_contests = len(groups_dict.get('OI', {})) + len(groups_dict.get('OIs', {}))
    else:
        total_contests = len(groups_dict)

    stats_html = f"<span>📁 独立题目: {len(all_versions)}</span><span>📝 有代码: {has_cpp}</span><span>💡 有题解: {has_md}</span><span>⚙️ 有配置: {has_conf}</span><span>🏆 比赛数: {total_contests}</span>"
    sort_html = """<div class="sort-btns"><button class="btn" onclick="sortContests('count')">按题目数降序</button><button class="btn" onclick="sortContests('name')">按比赛名字典序</button></div>"""
    stats_block = f'<div class="stats-bar"><div class="stats-info">{stats_html}</div>{sort_html}</div>'

    content_html = ""
    is_official = (title in ['Codeforces', 'AtCoder'])
    first_col_width = 35 if title == 'OI' else 20
    
    if title == 'AtCoder':
        sub_cats = {'ABC': {}, 'ARC': {}, 'AGC': {}, '其他': {}}
        for contest, c_groups in groups_dict.items():
            if contest.upper().startswith('ABC'): sub_cats['ABC'][contest] = c_groups
            elif contest.upper().startswith('ARC'): sub_cats['ARC'][contest] = c_groups
            elif contest.upper().startswith('AGC'): sub_cats['AGC'][contest] = c_groups
            else: sub_cats['其他'][contest] = c_groups
        
        tabs_html = '<div class="atcoder-tabs" style="margin-bottom: 24px; display: flex; gap: 12px; flex-wrap: wrap;">'
        tables_html = ''
        first = True
        for sc_name in ['ABC', 'ARC', 'AGC', '其他']:
            if not sub_cats[sc_name]: continue
            btn_style = "background: var(--primary); color: #fff; border-color: var(--primary);" if first else "background: #fff; color: #334155; border-color: #e2e8f0;"
            tabs_html += f'<button class="atcoder-tab-btn" data-target="tab-{sc_name}" onclick="switchAtCoderTab(\'tab-{sc_name}\', this)" style="padding: 8px 20px; border: 1px solid; border-radius: 8px; cursor: pointer; font-weight: 600; font-size: 0.95em; transition: all 0.2s; {btn_style}">{sc_name}</button>'
            display = "block" if first else "none"
            tables_html += f'<div id="tab-{sc_name}" class="atcoder-tab-content" style="display: {display};">'
            tables_html += f"<h2 style='margin-top: 10px; color: var(--primary);'>📌 {sc_name}</h2>"
            tables_html += build_matrix_table(sub_cats[sc_name], rel_path, is_official, first_col_width)
            tables_html += '</div>'
            first = False
        tabs_html += '</div>'
        content_html = tabs_html + tables_html
    elif title == 'OI':
        tabs_html = '<div class="atcoder-tabs" style="margin-bottom: 24px; display: flex; gap: 12px; flex-wrap: wrap;">'
        tables_html = ''
        first = True
        for sc_name in ['OI', 'OIs']:
            if not groups_dict[sc_name]: continue
            display_name = "3~4题场" if sc_name == 'OI' else "5+题场"
            btn_style = "background: var(--primary); color: #fff; border-color: var(--primary);" if first else "background: #fff; color: #334155; border-color: #e2e8f0;"
            tabs_html += f'<button class="atcoder-tab-btn" data-target="tab-{sc_name}" onclick="switchAtCoderTab(\'tab-{sc_name}\', this)" style="padding: 8px 20px; border: 1px solid; border-radius: 8px; cursor: pointer; font-weight: 600; font-size: 0.95em; transition: all 0.2s; {btn_style}">{display_name}</button>'
            display = "block" if first else "none"
            tables_html += f'<div id="tab-{sc_name}" class="atcoder-tab-content" style="display: {display};">'
            tables_html += f"<h2 style='margin-top: 10px; color: var(--primary);'>📌 {display_name}</h2>"
            tables_html += build_matrix_table(groups_dict[sc_name], rel_path, is_official, first_col_width)
            tables_html += '</div>'
            first = False
        tabs_html += '</div>'
        content_html = tabs_html + tables_html
    else:
        content_html = build_matrix_table(groups_dict, rel_path, is_official, first_col_width)

    html = HTML_TEMPLATE.format(
        title=title, stats_block=stats_block, nav_extra="",
        content_html=content_html, gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def build_list_page(title, all_versions, out_path, rel_path, table_id="list-table"):
    has_cpp = sum(1 for v in all_versions if v.files.get('cpp'))
    has_md = sum(1 for v in all_versions if v.files.get('md'))

    stats_html = f"<span>📁 独立题目: {len(all_versions)}</span><span>📝 有代码: {has_cpp}</span><span>💡 有题解: {has_md}</span>"
    stats_block = f'<div class="stats-bar"><div class="stats-info">{stats_html}</div></div>'
    nav_extra = '<button class="btn toggle-remark-btn" onclick="toggleRemark()">🚫 隐藏备注</button>'
    
    content_html = f"""
    <div class="list-filter-bar">
        <strong style="color: var(--primary); font-size: 1.1em;">🔍 筛选</strong>
        <div style="position: relative; display: inline-block;">
            <input type="text" id="filter-tag-{table_id}" placeholder="标签/名称 (空格分隔)..." onkeyup="filterListTable('{table_id}')" style="min-width: 220px; padding-right: 30px;">
            <span onclick="clearTagFilter('{table_id}')" id="clear-btn-{table_id}" style="position: absolute; right: 10px; top: 50%; transform: translateY(-50%); cursor: pointer; color: #94a3b8; font-size: 14px; display: none;" title="清空筛选">✖</span>
        </div>
        
        <span style="color:var(--text-muted); margin-left: 10px; font-weight: 500;">📊 难度:</span>
        <input type="number" id="filter-diff-min-{table_id}" placeholder="Min" style="width: 70px;" onkeyup="filterListTable('{table_id}')" onchange="filterListTable('{table_id}')">
        <span style="color:var(--border);">-</span>
        <input type="number" id="filter-diff-max-{table_id}" placeholder="Max" style="width: 70px;" onkeyup="filterListTable('{table_id}')" onchange="filterListTable('{table_id}')">
        
        <span style="color:var(--text-muted); margin-left: 10px; font-weight: 500;">📅 日期:</span>
        <input type="date" id="filter-date-start-{table_id}" onchange="filterListTable('{table_id}')">
        <span style="color:var(--border);">-</span>
        <input type="date" id="filter-date-end-{table_id}" onchange="filterListTable('{table_id}')">
    </div>
    
    <div style="overflow-x: auto;">
        <table class="normal-table" id="{table_id}">
            <thead>
                <tr>
                    <th style="padding-left: 20px;">题目与来源</th>
                    <th>标签</th>
                    <th onclick="sortListTable('{table_id}', 'diff')" style="cursor:pointer; user-select:none; color: var(--primary);" title="点击按难度双向排序">难度 ↕</th>
                    <th onclick="sortListTable('{table_id}', 'date')" style="cursor:pointer; user-select:none; color: var(--primary);" title="点击按日期双向排序">添加日期 ↕</th>
                    <th class="remark-col">备注</th>
                    <th>文件</th>
                </tr>
            </thead>
            <tbody>
    """
    
    sorted_versions = sorted(all_versions, key=lambda x: x.base_filename)
    sorted_versions.sort(key=lambda x: (x.date != "未知", x.date), reverse=True)
    
    for v in sorted_versions: 
        origin_parts = []
        seen = set()
        for cat, c, p in v.appearances:
            s = f"{cat} - {c}" if cat and c else (c if not cat else cat)
            if s not in seen and s != "Summary" and s:
                origin_parts.append(s)
                seen.add(s)
        if not origin_parts: origin_parts.append("Summary")
        origin = "<br>".join(origin_parts)
        
        display_name = v.base_filename 
        
        name_html = f'<a href="{v.link}" target="_blank" style="color:var(--primary); text-decoration:none;"><b>{display_name}</b></a>' if v.link != '#' else f'<b>{display_name}</b>'
        tags_str = " ".join(v.tags) if v.tags else ""
        tags_html = "".join([f'<span class="tag-pill" style="cursor:pointer;" onclick="addTagToFilter(\'{t}\', \'{table_id}\')" title="点击筛选/取消">{t}</span>' for t in v.tags])
        diff_val = v.difficulty if v.difficulty is not None else 'None'
        diff_html = "-"
        remark_text = v.remark if v.remark else "-"
        
        if v.difficulty is not None:
            style = get_diff_style(v.difficulty)
            diff_html = f'<span class="diff-indicator" title="难度: {v.difficulty}"><span class="diff-circle" style="{style}"></span> {int(v.difficulty) if v.difficulty.is_integer() else v.difficulty}</span>'
        
        links = []
        if v.files.get('cpp'): links.append(f'<a href="{rel_path}/{v.files["cpp"]}" class="file-link" title="代码" style="text-decoration:none;">📝</a>')
        if v.files.get('md'): 
            md_href = v.files['md'][:-3] if v.files['md'].endswith('.md') else v.files['md']
            links.append(f'<a href="{rel_path}/{md_href}" class="file-link" title="题解" style="text-decoration:none;">💡</a>')
        if v.files.get('conf'): links.append(f'<a href="{rel_path}/{v.files["conf"]}" class="file-link" title="配置" style="text-decoration:none;">⚙️</a>')
        v_html = f'<div class="version-row" style="flex-wrap: nowrap;"><span style="white-space: nowrap; display: inline-flex; gap: 6px;">{"".join(links)}</span></div>'
        
        content_html += f"""
        <tr data-tags="{tags_str}" data-diff="{diff_val}" data-date="{v.date}" data-base="{v.base_filename}">
            <td style="padding-left: 20px;">{name_html}<br><span style="font-size:0.85em; color:var(--text-muted); line-height: 1.4; display: inline-block; margin-top: 4px;">{origin}</span></td>
            <td>{tags_html}</td>
            <td>{diff_html}</td>
            <td style="font-size: 0.9em; color: var(--text-muted); font-weight: 500;">{v.date}</td>
            <td class="remark-col">{remark_text}</td>
            <td>{v_html}</td>
        </tr>"""
        
    content_html += "</tbody></table></div>"

    html = HTML_TEMPLATE.format(
        title=title, stats_block=stats_block, nav_extra=nav_extra,
        content_html=content_html, gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def build_index_page(categories, summary_versions, todo_versions, out_path):
    s_count = len(summary_versions)
    t_count = len(todo_versions)
    
    oi_p = sum(len(g.versions) for gs in categories.get('OI', {}).values() for g in gs) + sum(len(g.versions) for gs in categories.get('OIs', {}).values() for g in gs)
    oi_c = len(categories.get('OI', {})) + len(categories.get('OIs', {}))
    
    xcpc_p = sum(len(g.versions) for gs in categories.get('XCPC', {}).values() for g in gs)
    xcpc_c = len(categories.get('XCPC', {}))
    
    cf_p = sum(len(g.versions) for gs in categories.get('Codeforces', {}).values() for g in gs)
    cf_c = len(categories.get('Codeforces', {}))
    
    at_p = sum(len(g.versions) for gs in categories.get('AtCoder', {}).values() for g in gs)
    at_c = len(categories.get('AtCoder', {}))

    html = INDEX_HTML_TEMPLATE.format(
        s_count=s_count, t_count=t_count,
        oi_p=oi_p, oi_c=oi_c,
        xcpc_p=xcpc_p, xcpc_c=xcpc_c,
        cf_p=cf_p, cf_c=cf_c,
        at_p=at_p, at_c=at_c,
        gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
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
        'OI': defaultdict(list), 'OIs': defaultdict(list), 'XCPC': defaultdict(list)
    }
    
    summary_versions = []
    todo_versions = []

    for g in groups.values():
        added_to_cat = set()
        for cat, contest, pid in g.appearances:
            if cat in categories and contest:
                key = f"{cat}-{contest}"
                if key not in added_to_cat:
                    categories[cat][contest].append(g)
                    added_to_cat.add(key)
            
        for v in g.versions.values():
            is_todo = v.has_conf and not v.files.get('cpp')
            if is_todo:
                todo_versions.append(v)
            elif v.has_conf:
                summary_versions.append(v)
            else:
                is_cf_at = any(cat in ('Codeforces', 'AtCoder') for cat, c, p in v.appearances)
                if not is_cf_at:
                    summary_versions.append(v)

    print(f"🛠️ 正在生成 HTML 到 '{out_dir}' (当前目录)...")
    for cat in ['Codeforces', 'AtCoder', 'XCPC']:
        build_category_page(cat, categories[cat], os.path.join(out_dir, f"{cat}.html"), rel_data_path)
        
    build_category_page('OI', {'OI': categories['OI'], 'OIs': categories['OIs']}, os.path.join(out_dir, "OI.html"), rel_data_path)
        
    build_list_page('Summary', summary_versions, os.path.join(out_dir, 'Summary.html'), rel_data_path, "summary-table")
    build_list_page('Todo', todo_versions, os.path.join(out_dir, 'todo.html'), rel_data_path, "todo-table")

    build_index_page(categories, summary_versions, todo_versions, os.path.join(out_dir, "index.html"))
    print(f"🎉 处理完成！请在浏览器中打开: {os.path.abspath(os.path.join(out_dir, 'index.html'))}")

if __name__ == '__main__':
    main()
```

文件二：`collect.py`
```py
import os
import re

def main():
    try:
        prefix = input("请输入重命名前缀 (如 qoj, 留空则不重命名): ").strip()
        contest_type = input("请输入比赛类型 (如 OI/OIs/XCPC, 可留空): ").strip()
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
        
        s = fname[:-4].strip() 
        
        # 【核心拦截】：只处理形如 A, B, C, A1, B2, AA 的比赛题号文件
        if not re.match(r'^[A-Za-z]{1,2}\d*$', s):
            continue
            
        filepath = os.path.join(code_dir, fname)
        try:
            with open(filepath, 'r', encoding='utf-8') as f: 
                lines = f.readlines()
        except Exception:
            continue
            
        link = ""
        if len(lines) > 1:
            l2 = re.sub(r'^[\s/*#]+', '', lines[1]).strip()
            if l2.startswith("http"):
                link = l2
        if not link and len(lines) > 2:
            link = re.sub(r'^[\s/*#]+', '', lines[2]).strip()
            
        # 严格提取题目编号：就是原文件名大写 (如 A.cpp 就是 A)
        pid = s.upper()

        new_base = s
        if prefix and link:
            nums = re.findall(r'\d+', link)
            if nums:
                new_base = f"{prefix}{nums[-1]}"
                
        new_cpp_path = os.path.join(code_dir, f"{new_base}.cpp")
        if new_base != s:
            try:
                if filepath != new_cpp_path:
                    os.rename(filepath, new_cpp_path)
                    print(f"🔄 自动重命名: {fname} -> {new_base}.cpp")
            except Exception as e:
                print(f"❌ 重命名 {fname} 失败: {e}")
                new_base = s
                new_cpp_path = filepath
        
        conf_path = os.path.join(code_dir, f"{new_base}.conf")
        try:
            with open(conf_path, 'w', encoding='utf-8') as f:
                f.write("\n")                # 第 1 行: 标签/难度
                f.write(f"{contest_type}\n") # 第 2 行: 比赛归类
                f.write(f"{link}\n")         # 第 3 行: 题目链接
                f.write(f"{contest_name}\n") # 第 4 行: 比赛名
                f.write(f"{pid}\n")          # 第 5 行: 题目编号
                f.write("\n")                # 第 6 行: 备注
                
            print(f"✅ 生成 {new_base}.conf 成功！(题号: {pid})")
            success_count += 1
        except Exception as e:
            print(f"❌ 写入文件 {new_base}.conf 失败: {e}")
            
    print(f"\n🎉 完毕！共处理了 {success_count} 个题号代码文件。")

if __name__ == '__main__':
    main()
```

其他文件已经无用。