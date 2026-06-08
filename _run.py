import os
import sys
import re
import json  # <--- 新增
from collections import defaultdict
from datetime import datetime, timedelta  # <--- 增加了 timedelta
def get_diff_style(diff):
    if diff >= 3300: return 'background: linear-gradient(to right, #FFD700, #DAA520); border: 1px solid #DAA520; border-radius: 50%;'
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

EDITOR_HTML_TEMPLATE = """<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>代码/配置 本地编辑器</title>
    <style>
        body, html { margin: 0; padding: 0; height: 100%; overflow: hidden; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif; background: #ffffff; }
        .toolbar { display: flex; justify-content: space-between; align-items: center; padding: 0 20px; background: #f1f5f9; color: #334155; height: 50px; border-bottom: 1px solid #cbd5e1; box-sizing: border-box; }
        .filename { font-weight: 600; font-family: monospace; font-size: 1.1em; color: #2563eb; }
        .btn { background: #2563eb; color: #fff; border: none; padding: 6px 14px; border-radius: 4px; cursor: pointer; font-weight: bold; transition: background 0.2s; font-size: 0.9em; box-shadow: 0 1px 3px rgba(0,0,0,0.1); }
        .btn:hover { background: #1d4ed8; }
        .btn-green { background: #16a34a; }
        .btn-green:hover { background: #15803d; }
        #editor-container { height: calc(100vh - 50px); width: 100%; }
        #status { margin-left: 15px; color: #059669; font-size: 0.95em; font-weight: 600; }
        .overlay { position: absolute; top: 0; left: 0; width: 100%; height: 100%; background: rgba(255,255,255,0.95); color: #0f172a; display: flex; flex-direction: column; align-items: center; justify-content: center; z-index: 9999; display: none; text-align: center; }
    </style>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/monaco-editor/0.39.0/min/vs/loader.min.js"></script>
</head>
<body>
    <div class="overlay" id="err-overlay">
        <h2 style="color: #ef4444;">⚠️ 无法连接到本地服务器</h2>
        <p>你似乎直接双击打开了 HTML 文件 (file://)，由于浏览器安全限制，无法编辑文件。</p>
        <p>请在项目根目录运行命令行：<code style="background: #e2e8f0; padding: 4px 8px; border-radius: 4px; color:#0f172a;">python server.py</code></p>
        <p>然后通过浏览器访问 <a href="http://localhost:8000/index.html" style="color: #2563eb;">http://localhost:8000</a> 即可解锁在线编辑！</p>
    </div>
    
    <div class="toolbar">
        <div style="display: flex; align-items: center;">
            <button onclick="window.close()" style="background: #fff; border: 1px solid #cbd5e1; color: #475569; padding: 4px 10px; border-radius: 4px; margin-right: 15px; cursor: pointer; box-shadow: 0 1px 2px rgba(0,0,0,0.05);">← 关闭窗口</button>
            <span class="filename" id="fname-display">loading...</span>
            <span id="status"></span>
        </div>
        <div>
            <button class="btn" onclick="saveFile()">💾 保存 (Ctrl+S)</button>
            <button class="btn btn-green" style="margin-left: 10px;" onclick="saveAndRebuild()">🚀 保存并重构网页</button>
        </div>
    </div>
    <div id="editor-container"></div>

    <script>
        const params = new URLSearchParams(window.location.search);
        const file = params.get('file');
        const action = params.get('action');
        document.getElementById('fname-display').innerText = file || '未指定文件';

        let editor;

        if (window.location.protocol === 'file:') {
            document.getElementById('err-overlay').style.display = 'flex';
        }

        require.config({ paths: { 'vs': 'https://cdnjs.cloudflare.com/ajax/libs/monaco-editor/0.39.0/min/vs' }});
        require(['vs/editor/editor.main'], function() {
            let lang = 'plaintext';
            if (file.endsWith('.cpp')) lang = 'cpp';
            if (file.endsWith('.md')) lang = 'markdown';
            
            fetch(`/api/read?file=${encodeURIComponent(file)}`)
                .then(res => {
                    if (res.status === 404 && action === 'create') {
                        let def = '';
                        if (lang === 'cpp') def = '#include <bits/stdc++.h>\\nusing namespace std;\\n\\nint main() {\\n    \\n    return 0;\\n}\\n';
                        if (lang === 'markdown') def = '# 题解\\n\\n';
                        if (file.endsWith('.conf')) def = '\\n\\n\\n';
                        return {content: def};
                    }
                    if (!res.ok) throw new Error('File read failed');
                    return res.json();
                })
                .then(data => {
                    editor = monaco.editor.create(document.getElementById('editor-container'), {
                        value: data.content || '',
                        language: lang,
                        theme: 'vs',
                        automaticLayout: true,
                        fontSize: 15,
                        fontFamily: 'Consolas, "Courier New", monospace',
                        mouseWheelZoom: true,
                        wordWrap: 'on'
                    });
                    
                    editor.addCommand(monaco.KeyMod.CtrlCmd | monaco.KeyCode.KeyS, function() { saveFile(); });
                })
                .catch(err => {
                    document.getElementById('status').innerText = '❌ 加载失败';
                    if (window.location.protocol !== 'file:') {
                        document.getElementById('err-overlay').style.display = 'flex';
                    }
                });
        });

        function saveFile() {
            document.getElementById('status').innerText = '保存中...';
            fetch('/api/write', {
                method: 'POST',
                body: JSON.stringify({ file: file, content: editor.getValue() })
            }).then(r => r.json()).then(d => {
                document.getElementById('status').innerText = '✅ 已保存';
                setTimeout(() => document.getElementById('status').innerText = '', 2000);
            });
        }

        function saveAndRebuild() {
            document.getElementById('status').innerText = '保存并触发全站重构中...';
            fetch('/api/write', {
                method: 'POST',
                body: JSON.stringify({ file: file, content: editor.getValue() })
            }).then(r => r.json()).then(d => {
                fetch('/api/rebuild', {method: 'POST'}).then(() => {
                    document.getElementById('status').innerText = '🎉 保存并重构成功！';
                    setTimeout(() => window.close(), 1500); 
                });
            });
        }
    </script>
</body>
</html>
"""

HTML_TEMPLATE = """<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>{title} - 题目整理</title>
    <style>
        :root {{ --primary: #2563eb; --primary-hover: #1d4ed8; --bg: #f4f5f8; --text-main: #1e293b; --text-muted: #64748b; --border: #e2e8f0; --panel-bg: #f8fafc; }}
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
        
        .matrix-table, .normal-table, .plist-table {{ background: #fff; margin-bottom: 30px; border-radius: 12px; overflow: hidden; border: 1px solid var(--border); }}
        .normal-table, .plist-table {{ min-width: 800px; }}
        .matrix-table {{ min-width: 600px; }}
        
        thead {{ background: var(--panel-bg); }}
        th {{ color: #475569; font-weight: 600; border-bottom: 2px solid var(--border); }}
        td {{ border-bottom: 1px solid var(--border); }}
        th:not(:last-child), td:not(:last-child) {{ border-right: 1px solid var(--border); }}
        tbody tr:last-child td {{ border-bottom: none; }}
        tbody tr:hover td {{ background-color: #f8fafc; }}
        .matrix-table th, .matrix-table td {{ text-align: center; }}
        .contest-name-cell {{ text-align: left !important; font-weight: 600; color: #0f172a; background: #fff; }}
        
        .remark-col {{ display: none; }}
        .normal-table th:nth-child(1) {{ width: 35%; }}  
        .normal-table th:nth-child(2) {{ width: 15%; }}  
        .normal-table th:nth-child(3) {{ width: 9%; }}   
        .normal-table th:nth-child(4) {{ width: 10%; }}  
        .normal-table th.remark-col {{ width: 22%; color: var(--text-muted); font-weight: 500; font-size: 0.95em; }} 
        .normal-table th:last-child {{ width: 12%; }}     
        .normal-table td.remark-col {{ color: var(--text-muted); font-size: 0.9em; }}
        .matrix-table th.remark-col {{ width: 14%; color: var(--text-muted); font-weight: 500; font-size: 0.95em; }} 
        
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
        
        .add-file-btn {{ display: none; opacity: 0.4; transition: opacity 0.2s; }}
        .add-file-btn:hover {{ opacity: 1; }}
        
        .tag-pill {{ background: #f1f5f9; color: #475569; font-size: 0.85em; padding: 3px 10px; border-radius: 12px; font-weight: 500; display: inline-block; margin: 2px; border: 1px solid #e2e8f0; transition: all 0.2s; }}
        .tag-pill:hover {{ background: #e2e8f0; border-color: #cbd5e1; transform: translateY(-1px); box-shadow: 0 2px 4px rgba(0,0,0,0.03); }}
        .list-filter-bar {{ background: #fff; border: 1px solid var(--border); padding: 18px; border-radius: 12px; margin-bottom: 24px; display: flex; flex-wrap: wrap; gap: 14px; align-items: center; box-sizing: border-box; }}
        .list-filter-bar input {{ padding: 8px 12px; border: 1px solid #cbd5e1; border-radius: 6px; outline: none; font-size: 0.95em; transition: border-color 0.2s; color: var(--text-main); }}
        .list-filter-bar input:focus {{ border-color: var(--primary); box-shadow: 0 0 0 3px rgba(37,99,235,0.1); }}
        .footer {{ margin-top: 40px; padding-top: 20px; border-top: 1px solid var(--border); text-align: center; color: #94a3b8; font-size: 0.85em; }}
        
        .plist-grid {{ display: grid; grid-template-columns: repeat(auto-fill, minmax(320px, 1fr)); gap: 24px; }}
        .plist-card {{ background: #fff; border: 1px solid var(--border); border-radius: 12px; padding: 24px; text-decoration: none; color: inherit; transition: all 0.2s; display: flex; flex-direction: column; }}
        .plist-card:hover {{ transform: translateY(-3px); box-shadow: 0 8px 20px rgba(0,0,0,0.06); border-color: var(--primary); }}
        .plist-card h3 {{ margin: 0 0 10px 0; color: #0f172a; font-size: 1.3em; }}
        .plist-card .count {{ font-size: 0.95em; color: var(--text-muted); background: #f8fafc; display: inline-block; padding: 4px 10px; border-radius: 8px; font-weight: 500; border: 1px solid var(--border); }}
        
        .blog-item {{ display: flex; justify-content: space-between; align-items: center; padding: 18px 24px; border-bottom: 1px solid #e2e8f0; text-decoration: none; color: inherit; transition: background 0.2s; }}
        .blog-item:last-child {{ border-bottom: none; }}
        .blog-item:hover {{ background: #f8fafc; }}
        .blog-item-title {{ font-weight: 600; color: #1e293b; font-size: 1.1em; display: flex; align-items: center; gap: 10px; }}
        .blog-item-date {{ color: #64748b; font-size: 0.95em; font-family: ui-monospace, SFMono-Regular, Consolas, monospace; }}
    </style>
</head>
<body>
    <div class="container">
        <div class="nav-bar">
            <a href="{base_url}index.html">🏠 Dashboard</a>
            <span style="color:#cbd5e1;">|</span>
            <a href="{base_url}Summary.html">📚 Summary</a>
            <a href="{base_url}plist/index.html">📋 题单</a>
            <a href="{base_url}Blog.html">✍️ Blog</a>
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
        
        let isRemarkVisible = false;
        function toggleRemark() {{
            isRemarkVisible = !isRemarkVisible;
            document.querySelectorAll('.remark-col').forEach(el => {{ el.style.display = isRemarkVisible ? 'table-cell' : 'none'; }});
            document.querySelectorAll('.toggle-remark-btn').forEach(btn => {{
                btn.innerHTML = isRemarkVisible ? '🚫 隐藏备注' : '📝 显示备注';
                btn.style.color = isRemarkVisible ? '#475569' : '#059669';
                btn.style.borderColor = isRemarkVisible ? '#e2e8f0' : '#a7f3d0';
                btn.style.background = isRemarkVisible ? '#f8fafc' : '#fff';
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

            if (tableId === 'summary-table' || tableId === 'todo-table') {{
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
                const tags = (row.getAttribute('data-tags') || '').toLowerCase();
                const baseName = (row.getAttribute('data-base') || '').toLowerCase();
                const diffStr = row.getAttribute('data-diff');
                const rDate = row.getAttribute('data-date');
                const diff = diffStr && diffStr !== 'None' ? parseFloat(diffStr) : NaN;

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
            if (!sortDirection[tableId]) sortDirection[tableId] = {{ 'diff': 1, 'date': 1, 'index': 1 }};
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
                }} else if (col === 'index') {{
                    let i1 = parseInt(a.dataset.index) || 0;
                    let i2 = parseInt(b.dataset.index) || 0;
                    res = (i1 - i2) * dir;
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
        
        function filterPList() {{
            const val = document.getElementById('plist-search').value.toLowerCase();
            document.querySelectorAll('.plist-card').forEach(card => {{
                card.style.display = card.innerText.toLowerCase().includes(val) ? '' : 'none';
            }});
        }}

        window.addEventListener('DOMContentLoaded', () => {{
            const urlParams = new URLSearchParams(window.location.search);
            const q = urlParams.get('q');
            const min = urlParams.get('min');
            const max = urlParams.get('max');
            const input = document.querySelector('input[id^="filter-tag-"]');
            if (input && (input.id === 'filter-tag-summary-table' || input.id === 'filter-tag-todo-table')) {{
                const tableId = input.id.replace('filter-tag-', '');
                if (q) input.value = q + ' ';
                const minInput = document.getElementById('filter-diff-min-' + tableId);
                if (minInput && min) minInput.value = min;
                const maxInput = document.getElementById('filter-diff-max-' + tableId);
                if (maxInput && max) maxInput.value = max;
                if (q || min || max) {{ filterListTable(tableId); }}
            }}
            
            if (window.location.hostname === 'localhost' || window.location.hostname === '127.0.0.1') {{
                document.querySelectorAll('.add-file-btn').forEach(el => el.style.display = 'inline-block');
                document.querySelectorAll('.file-link').forEach(el => {{
                    if (el.hasAttribute('data-editor-href')) {{
                        el.href = el.getAttribute('data-editor-href');
                    }}
                }});
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
    <!-- 引入 ECharts -->
    <script src="https://cdn.jsdelivr.net/npm/echarts@5.5.0/dist/echarts.min.js"></script>
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
        .card-plist::before {{ background: linear-gradient(90deg, #ec4899, #f43f5e); }}
        .card-blog::before {{ background: linear-gradient(90deg, #14b8a6, #2dd4bf); }}
        .card-header {{ display: flex; justify-content: space-between; align-items: center; margin-bottom: 16px; }}
        .card-title {{ font-size: 1.4em; font-weight: 700; margin: 0; display: flex; align-items: center; gap: 8px; }}
        .card-badge {{ font-size: 0.8em; padding: 4px 10px; border-radius: 8px; font-weight: 700; font-family: ui-monospace, SFMono-Regular, Consolas, monospace; }}
        .card-stats {{ display: flex; align-items: baseline; gap: 8px; margin-bottom: 0; }}
        .stat-number {{ font-size: 3.2em; font-weight: 800; line-height: 1; }}
        .stat-label {{ color: var(--text-muted); font-size: 1.05em; font-weight: 500; }}

        .info-grid {{ display: grid; grid-template-columns: 1fr 1fr; gap: 24px; margin-top: 40px; }}
        @media (max-width: 900px) {{ .info-grid {{ grid-template-columns: 1fr; }} }}
        .info-box {{ background: #fff; border-radius: 16px; padding: 30px; box-shadow: 0 4px 15px rgba(0,0,0,0.03); border: 1px solid #e2e8f0; display: flex; flex-direction: column; }}
        .info-box h3 {{ margin-top: 0; margin-bottom: 15px; color: #0f172a; display: flex; align-items: center; gap: 8px; font-weight: 700; font-size: 1.1em; }}
        .syntax-code {{ display: grid; gap: 10px; font-family: ui-monospace, SFMono-Regular, Consolas, monospace; font-size: 0.88em; background: #f8fafc; padding: 20px; border-radius: 12px; border: 1px solid #f1f5f9; overflow-x: auto; flex-grow: 1; }}
        .cpp-code {{ background: #1e293b; color: #f8fafc; padding: 20px; border-radius: 12px; font-family: ui-monospace, SFMono-Regular, Consolas, monospace; font-size: 0.85em; overflow-x: auto; margin: 0; line-height: 1.6; flex-grow: 1; display: flex; flex-direction: column; justify-content: center; }}
        .cpp-keyword {{ color: #c678dd; }}
        .cpp-include {{ color: #98c379; }}
        .footer {{ text-align: center; color: #94a3b8; font-size: 0.85em; margin-top: 50px; }}
        
        /* 切换按钮样式 */
        .chart-controls {{ display: flex; align-items: center; gap: 12px; flex-wrap: wrap; }}
        .btn-toggle {{ background: #f8fafc; border: 1px solid #cbd5e1; color: #334155; padding: 6px 14px; border-radius: 8px; cursor: pointer; font-weight: 600; transition: all 0.2s; }}
        .btn-toggle:hover {{ background: #e2e8f0; }}
        .btn-toggle.active {{ background: #2563eb; color: #fff; border-color: #2563eb; }}
        .ma-input {{ width: 50px; padding: 4px; border: 1px solid #cbd5e1; border-radius: 6px; text-align: center; outline: none; }}
        .ma-input:focus {{ border-color: #2563eb; }}
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
            <a href="plist/index.html" class="card card-plist">
                <div class="card-header"><h2 class="card-title"><span>📋</span> Problem List</h2><span class="card-badge" style="color: #ec4899; background: #fce7f3;">Menu</span></div>
                <div class="card-stats"><span class="stat-number">{plist_count}</span><span class="stat-label">个自建题单</span></div>
            </a>
            <a href="Blog.html" class="card card-blog">
                <div class="card-header"><h2 class="card-title"><span>✍️</span> Blog</h2><span class="card-badge" style="color: #0f766e; background: #ccfbf1;">Notes</span></div>
                <div class="card-stats"><span class="stat-number">{blog_count}</span><span class="stat-label">篇技术博客</span></div>
            </a>
        </div>

        <!-- === 做题活动可视化双模图表 === -->
        <div class="chart-container" style="background: #fff; border-radius: 16px; padding: 24px; box-shadow: 0 4px 15px rgba(0,0,0,0.03); border: 1px solid #e2e8f0; margin-bottom: 40px;">
            <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; flex-wrap: wrap; gap: 15px;">
                <h2 style="margin: 0; font-size: 1.4em; display: flex; align-items: center; gap: 8px; color: #0f172a;">📈 趋势分析</h2>
                
                <div class="chart-controls">
                    <button id="btn-bar" class="btn-toggle active">📊 每日柱状图</button>
                    <button id="btn-line" class="btn-toggle">🌊 滑动平均曲线图</button>
                    <div id="ma-settings" style="display: none; align-items: center; gap: 6px; font-size: 0.9em; color: #64748b; background: #f8fafc; padding: 4px 10px; border-radius: 8px; border: 1px solid #e2e8f0;">
                        平滑天数: 
                        <input type="number" id="ma-window" class="ma-input" value="7" min="3" max="30" step="2">
                    </div>
                </div>
            </div>
            
            <div id="activity-chart" style="width: 100%; height: 400px;"></div>
        </div>

        <div class="info-grid">
            <div class="info-box">
                <h3><span>⚙️</span> 新架构说明</h3>
                <div class="syntax-code" style="padding-top: 15px; padding-bottom: 15px; display: block; line-height: 1.8;">
                    <div style="font-weight: bold; color: var(--primary);">/data/*.conf (单个题目精简配置)</div>
                    <div>1. 标签/关键词 (空格隔开，末尾数字为难度)</div>
                    <div>2. 题目完整链接 (留空自动生成)</div>
                    <div style="margin-bottom: 15px;">3. 题目独立备注</div>
                    <div style="font-weight: bold; color: #10b981;">/contest/*.conf (全新独立比赛配置)</div>
                    <div>1. 比赛名称</div>
                    <div>2. 比赛分类 (OI / OIs / XCPC)</div>
                    <div>3. 比赛链接</div>
                    <div>...</div>
                </div>
            </div>
            <div class="info-box">
                <h3><span>🚀</span> GCC 编译优化</h3>
                <pre class="cpp-code"><code><span class="cpp-keyword">#pragma</span> GCC optimize(3,<span class="cpp-include">"inline"</span>)
<span class="cpp-keyword">#pragma</span> GCC optimize(<span class="cpp-include">"Ofast,unroll-loops"</span>)
<span class="cpp-keyword">#pragma</span> GCC target(<span class="cpp-include">"avx,avx2"</span>)</code></pre>
            </div>
        </div>
        <div class="footer">最后构建: {gen_time} | Algorithm Platform Generator</div>
    </div>

    <!-- ECharts 双模渲染脚本 -->
    <script>
        document.addEventListener('DOMContentLoaded', function() {{
            const chartData = {chart_data_json};
            const chartDom = document.getElementById('activity-chart');
            const myChart = echarts.init(chartDom);
            
            let currentMode = 'bar'; // 'bar' 或 'line'
            
            // 基础颜色映射
            const colors = {{
                l1: '#94a3b8', // <2000
                l2: '#2dd4bf', // 2000-2599
                l3: '#3b82f6', // 2600-2999
                l4: '#f43f5e', // >=3000
                u:  '#e2e8f0'  // 未知
            }};

            // 滑动平均计算逻辑（仅除以窗口内真实的有效天数，防止头尾数据断崖下跌）
            function calculateMA(data, windowSize) {{
                let result = [];
                let half = Math.floor(windowSize / 2);
                for (let i = 0; i < data.length; i++) {{
                    let sum = 0;
                    let count = 0;
                    for (let j = i - half; j <= i + half; j++) {{
                        if (j >= 0 && j < data.length) {{
                            sum += data[j];
                            count++;
                        }}
                    }}
                    result.push((sum / count).toFixed(2));
                }}
                return result;
            }}

            // 生成渐变色对象
            function getGradient(colorBase) {{
                // 简单的 Hex 转 RGB (不带透明度的hex)
                let r = parseInt(colorBase.slice(1, 3), 16);
                let g = parseInt(colorBase.slice(3, 5), 16);
                let b = parseInt(colorBase.slice(5, 7), 16);
                return new echarts.graphic.LinearGradient(0, 0, 0, 1, [
                    {{ offset: 0, color: `rgba(${{r}}, ${{g}}, ${{b}}, 0.8)` }},
                    {{ offset: 1, color: `rgba(${{r}}, ${{g}}, ${{b}}, 0.1)` }}
                ]);
            }}

            // 保存当前时间轴的缩放比例，以便在切换视图时保持位置不变
            let currentZoomStart = Math.max(0, chartData.dates.length - 30);
            let currentZoomEnd = chartData.dates.length - 1;
            
            myChart.on('datazoom', function(params) {{
                let option = myChart.getOption();
                currentZoomStart = option.dataZoom[0].startValue;
                currentZoomEnd = option.dataZoom[0].endValue;
            }});

            // 获取公共配置 (坐标轴、时间轴等)
            function getBaseOption() {{
                return {{
                    tooltip: {{
                        trigger: 'axis',
                        axisPointer: {{ type: currentMode === 'bar' ? 'shadow' : 'cross' }}
                    }},
                    legend: {{
                        data: ['<2000', '2000-2599', '2600-2999', '≥3000', '未知难度'],
                        top: 0, icon: 'circle'
                    }},
                    grid: {{ left: '2%', right: '2%', bottom: '15%', top: '12%', containLabel: true }},
                    dataZoom: [
                        {{
                            type: 'slider', show: true, xAxisIndex: [0],
                            startValue: currentZoomStart, endValue: currentZoomEnd,
                            bottom: 0, height: 24,
                            borderColor: '#e2e8f0', backgroundColor: '#f8fafc',
                            fillerColor: 'rgba(37, 99, 235, 0.15)',
                            handleStyle: {{ color: '#2563eb' }},
                            textStyle: {{ color: '#64748b' }}
                        }},
                        {{ type: 'inside', xAxisIndex: [0] }}
                    ],
                    xAxis: {{
                        type: 'category', data: chartData.dates,
                        axisTick: {{ alignWithLabel: true }},
                        axisLabel: {{ color: '#64748b' }},
                        axisLine: {{ lineStyle: {{ color: '#cbd5e1' }} }}
                    }},
                    yAxis: {{
                        type: 'value',
                        name: currentMode === 'bar' ? '做题数' : '平均做题数',
                        nameTextStyle: {{ color: '#64748b', padding: [0, 0, 0, 20] }},
                        minInterval: currentMode === 'bar' ? 1 : 0,
                        axisLabel: {{ color: '#64748b' }},
                        splitLine: {{ lineStyle: {{ color: '#f1f5f9', type: 'dashed' }} }}
                    }}
                }};
            }}

            // 渲染视图的函数
            function renderChart() {{
                let option = getBaseOption();
                
                if (currentMode === 'bar') {{
                    option.series = [
                        {{ name: '<2000', type: 'bar', stack: 'total', itemStyle: {{ color: colors.l1 }}, data: chartData.l1 }},
                        {{ name: '2000-2599', type: 'bar', stack: 'total', itemStyle: {{ color: colors.l2 }}, data: chartData.l2 }},
                        {{ name: '2600-2999', type: 'bar', stack: 'total', itemStyle: {{ color: colors.l3 }}, data: chartData.l3 }},
                        {{ name: '≥3000', type: 'bar', stack: 'total', itemStyle: {{ color: colors.l4 }}, data: chartData.l4 }},
                        {{ name: '未知难度', type: 'bar', stack: 'total', itemStyle: {{ color: colors.u }}, data: chartData.u }}
                    ];
                }} else {{
                    let w = parseInt(document.getElementById('ma-window').value) || 7;
                    option.series = [
                        {{ name: '<2000', type: 'line', stack: 'total', smooth: true, showSymbol: false, lineStyle: {{ width: 2, color: colors.l1 }}, areaStyle: {{ color: getGradient(colors.l1) }}, itemStyle: {{ color: colors.l1 }}, data: calculateMA(chartData.l1, w) }},
                        {{ name: '2000-2599', type: 'line', stack: 'total', smooth: true, showSymbol: false, lineStyle: {{ width: 2, color: colors.l2 }}, areaStyle: {{ color: getGradient(colors.l2) }}, itemStyle: {{ color: colors.l2 }}, data: calculateMA(chartData.l2, w) }},
                        {{ name: '2600-2999', type: 'line', stack: 'total', smooth: true, showSymbol: false, lineStyle: {{ width: 2, color: colors.l3 }}, areaStyle: {{ color: getGradient(colors.l3) }}, itemStyle: {{ color: colors.l3 }}, data: calculateMA(chartData.l3, w) }},
                        {{ name: '≥3000', type: 'line', stack: 'total', smooth: true, showSymbol: false, lineStyle: {{ width: 2, color: colors.l4 }}, areaStyle: {{ color: getGradient(colors.l4) }}, itemStyle: {{ color: colors.l4 }}, data: calculateMA(chartData.l4, w) }},
                        {{ name: '未知难度', type: 'line', stack: 'total', smooth: true, showSymbol: false, lineStyle: {{ width: 2, color: colors.u }}, areaStyle: {{ color: getGradient(colors.u) }}, itemStyle: {{ color: colors.u }}, data: calculateMA(chartData.u, w) }}
                    ];
                }}
                
                myChart.setOption(option, true); // true表示不合并前一个状态，完全重绘
            }}

            // 初始化渲染
            renderChart();

            // 监听按钮切换
            document.getElementById('btn-bar').addEventListener('click', function() {{
                currentMode = 'bar';
                this.classList.add('active');
                document.getElementById('btn-line').classList.remove('active');
                document.getElementById('ma-settings').style.display = 'none';
                renderChart();
            }});

            document.getElementById('btn-line').addEventListener('click', function() {{
                currentMode = 'line';
                this.classList.add('active');
                document.getElementById('btn-bar').classList.remove('active');
                document.getElementById('ma-settings').style.display = 'flex';
                renderChart();
            }});

            // 监听天数输入框变动 (防抖，提升体验)
            let timeout = null;
            document.getElementById('ma-window').addEventListener('input', function() {{
                clearTimeout(timeout);
                timeout = setTimeout(() => {{
                    if(currentMode === 'line') renderChart();
                }}, 300);
            }});

            window.addEventListener('resize', () => myChart.resize());
        }});
    </script>
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
            if f.endswith('.conf'): conf_bases.add(f[:-5].lower())

    for f in os.listdir(data_dir):
        if not os.path.isfile(os.path.join(data_dir, f)): continue
        name, ext = os.path.splitext(f)
        if ext not in ['.cpp', '.md', '.conf']: continue
            
        base_name, version = None, 'Normal'
        m_cf = re.match(r'^cf(\d+)([a-zA-Z]+?)(1|2)?$', name, re.IGNORECASE)
        m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+?)(1|2)?$', name, re.IGNORECASE)
        m_oj = re.match(r'^(qoj|uoj|soj|p)(\d+)$', name, re.IGNORECASE)

        if m_cf:
            base_name = f"cf{m_cf.group(1)}{m_cf.group(2).lower()}"
            version = 'Easy' if m_cf.group(3) == '1' else ('Hard' if m_cf.group(3) == '2' else 'Normal')
        elif m_ac:
            base_name = f"{m_ac.group(1).lower()}{m_ac.group(2)}{m_ac.group(3).lower()}"
            version = 'Easy' if m_ac.group(4) == '1' else ('Hard' if m_ac.group(4) == '2' else 'Normal')
        elif m_oj:
            base_name = name.lower()
            version = 'Normal'
        else:
            name_lower = name.lower()
            matched_conf_base = None
            if name_lower in conf_bases:
                matched_conf_base = name
                version = 'Normal'
            else:
                for cb in sorted(conf_bases, key=len, reverse=True):
                    if name_lower == cb + '1' or name_lower == cb + '_e1':
                        matched_conf_base = name[:-1] if name_lower.endswith('1') else name[:-3]
                        version = 'Easy'
                        break
                    elif name_lower == cb + '2' or name_lower == cb + '_e2':
                        matched_conf_base = name[:-1] if name_lower.endswith('2') else name[:-3]
                        version = 'Hard'
                        break
                        
            if matched_conf_base:
                base_name = matched_conf_base
            else:
                if name_lower.endswith('_e1'): base_name, version = name[:-3], 'Easy'
                elif name_lower.endswith('_e2'): base_name, version = name[:-3], 'Hard'
                elif name_lower.endswith('1'): base_name, version = name[:-1], 'Easy'
                elif name_lower.endswith('2'): base_name, version = name[:-1], 'Hard'
                else: base_name, version = name, 'Normal'

        key = base_name.lower()
        if key not in groups:
            groups[key] = ProblemGroup(base_name)
        groups[key].add_file(version, ext, f, name)
        
    return groups

def apply_categories_and_links(groups, data_dir):
    contest_info = defaultdict(lambda: defaultdict(dict))
    custom_apps = defaultdict(list)
    
    if os.path.exists('contest'):
        for f in os.listdir('contest'):
            if not f.endswith('.conf'): continue
            path = os.path.join('contest', f)
            try:
                with open(path, 'r', encoding='utf-8') as file:
                    lines = [l.split('#')[0].strip() for l in file.readlines()]
                while len(lines) < 3: lines.append('')
                
                c_name, cat, c_link = lines[0], lines[1], lines[2]
                remark = ""
                probs = []
                for line in lines[3:]:
                    if not line: continue
                    parts = line.split()
                    if len(parts) == 2 and re.match(r'^[A-Za-z0-9]+$', parts[0]):
                        probs.append((parts[0], parts[1]))
                    else:
                        remark = line
                
                if cat and c_name:
                    contest_info[cat][c_name] = {'link': c_link, 'remark': remark}
                    for pid, base_name in probs:
                        custom_apps[base_name.lower()].append((cat, c_name, pid))
            except Exception: pass

    for group in groups.values():
        m_cf = re.match(r'^cf(\d+)([a-zA-Z]+)$', group.base_name, re.IGNORECASE)
        m_ac = re.match(r'^(abc|arc|agc)(\d+)([a-zA-Z]+)$', group.base_name, re.IGNORECASE)
        m_oj = re.match(r'^(qoj|uoj|soj|p)(\d+)$', group.base_name, re.IGNORECASE)
        
        is_cf, is_at, is_oj = bool(m_cf), bool(m_ac), bool(m_oj)

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
            
            if v.files.get('conf'):
                v.has_conf = True
                group.has_conf = True
                fp = os.path.join(data_dir, v.files['conf'])
                try:
                    with open(fp, 'r', encoding='utf-8') as f:
                        lines = [line.split('#')[0].strip() for line in f.readlines()]
                    while len(lines) < 3: lines.append('')
                    
                    parts = lines[0].split()
                    if parts:
                        try:
                            v.difficulty = float(parts[-1])
                            v.tags = sorted(parts[:-1]) 
                        except ValueError:
                            v.tags = sorted(parts)
                            v.difficulty = None
                            
                    primary_link = lines[1].strip()
                    v.remark = lines[2].strip()
                except Exception: pass
            
            suffix = "1" if v_name == 'Easy' else ("2" if v_name == 'Hard' else "")
            cf_at_link = "#"
            
            if is_cf:
                c = f"Codeforces Round {m_cf.group(1)}"
                base_p = m_cf.group(2).upper()
                v.appearances.append(('Codeforces', c, base_p))
                cf_at_link = f"https://codeforces.com/problemset/problem/{m_cf.group(1)}/{m_cf.group(2).upper() + suffix}"
                
            if is_at:
                c = f"{m_ac.group(1).upper()}{m_ac.group(2)}"
                base_p = m_ac.group(3).upper()
                v.appearances.append(('AtCoder', c, base_p))
                cf_at_link = f"https://atcoder.jp/contests/{m_ac.group(1).lower()}{m_ac.group(2)}/tasks/{m_ac.group(1).lower()}{m_ac.group(2)}_{(m_ac.group(3).upper() + suffix).lower()}"
                
            for app in custom_apps.get(group.base_name.lower(), []):
                if app not in v.appearances:
                    v.appearances.append(app)
                
            if not v.appearances:
                v.appearances.append(('Summary', '', ''))
                
            if not primary_link or primary_link == "#":
                if is_cf or is_at:
                    primary_link = cf_at_link
                elif is_oj:
                    oj_prefix = m_oj.group(1).lower()
                    oj_num = m_oj.group(2)
                    if oj_prefix == 'p': primary_link = f"https://www.luogu.com.cn/problem/P{oj_num}"
                    elif oj_prefix == 'qoj': primary_link = f"https://qoj.ac/problem/{oj_num}"
                    elif oj_prefix == 'uoj': primary_link = f"https://uoj.ac/problem/{oj_num}"
                    elif oj_prefix == 'soj': primary_link = f"http://121.196.149.251:8080/problem/{oj_num}"
                    
            v.link = primary_link

            for app in v.appearances:
                if app not in group.appearances:
                    group.appearances.append(app)

    return contest_info

def render_single_version(v, rel_path, contest_pid="", is_official=False, base_url="", data_dir="data"):
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
    
    conf_fname = v.files.get("conf") or f"{v.base_filename}.conf"
    cpp_fname = v.files.get("cpp") or f"{v.base_filename}.cpp"
    md_fname = v.files.get("md") or f"{v.base_filename}.md"
    
    links = []
    
    if v.files.get('conf'):
        raw_href = f"{rel_path}/{v.files['conf']}"
        editor_href = f"{base_url}editor.html?file={data_dir}/{v.files['conf']}"
        links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="配置" style="text-decoration:none;">⚙️</a>')
    else:
        editor_href = f"{base_url}editor.html?file={data_dir}/{conf_fname}&action=create"
        links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建配置" style="text-decoration:none;">➕⚙️</a>')
        
    if v.files.get('cpp'):
        raw_href = f"{rel_path}/{v.files['cpp']}"
        editor_href = f"{base_url}editor.html?file={data_dir}/{v.files['cpp']}"
        links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="代码" style="text-decoration:none;">📝</a>')
    else:
        editor_href = f"{base_url}editor.html?file={data_dir}/{cpp_fname}&action=create"
        links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建代码" style="text-decoration:none;">➕📝</a>')
        
    if v.files.get('md'): 
        actual_md = v.files["md"]
        md_raw_fname = actual_md[:-3] if actual_md.endswith('.md') else actual_md
        raw_href = f"{rel_path}/{md_raw_fname}"
        editor_href = f"{base_url}editor.html?file={data_dir}/{actual_md}"
        links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="题解" style="text-decoration:none;">💡</a>')
    else:
        editor_href = f"{base_url}editor.html?file={data_dir}/{md_fname}&action=create"
        links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建题解" style="text-decoration:none;">➕💡</a>')
    
    return f"""
    <div class="prob-cell" style="margin-bottom:8px;">
        <div class="prob-link-wrap">{link_html}{diff_html}</div>
        <div class="version-row" style="flex-wrap: nowrap;"><span style="white-space: nowrap; display: inline-flex; gap: 6px;">{"".join(links)}</span></div>
    </div>"""

def build_matrix_table(groups_dict, contest_info_dict, rel_path, is_official=False, first_col_width=20, base_url="", data_dir="data"):
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
    
    if not is_official:
        html += '<th class="remark-col" style="text-align: left;">比赛备注</th>'
        
    html += '</tr></thead><tbody>'
    
    sorted_contests = sorted(groups_dict.items(), key=lambda x: contest_sort_key(x[0]), reverse=True)
    for contest, c_groups in sorted_contests:
        pid_map = defaultdict(list)
        for g in c_groups:
            pid = g.get_pid_in_contest(contest)
            pid_map[pid if pid else "未知"].append(g)
            
        c_link = contest_info_dict.get(contest, {}).get('link', '')
        c_remark = contest_info_dict.get(contest, {}).get('remark', '')
        
        display_contest = f'<a href="{c_link}" target="_blank" style="color:var(--primary); font-weight:700; text-decoration:none;">{contest}</a>' if c_link else contest
        display_contest = display_contest if display_contest else "无名比赛"
        
        html += f'<tr data-name="{contest}" data-count="{len(c_groups)}">'
        html += f'<td class="contest-name-cell" style="padding-left: 20px;">{display_contest} <br><span style="font-size:0.85em; color:var(--text-muted); font-weight:normal;">({len(c_groups)} 题)</span></td>'
        
        for pid in sorted_pids:
            html += '<td>'
            if pid in pid_map:
                for g in sorted(pid_map[pid], key=lambda x: x.base_name):
                    if not is_official:
                        rep_v = 'Normal' if 'Normal' in g.versions else ('Hard' if 'Hard' in g.versions else 'Easy')
                        html += render_single_version(g.versions[rep_v], rel_path, pid, is_official, base_url, data_dir)
                    elif 'Normal' in g.versions and len(g.versions) == 1:
                        html += render_single_version(g.versions['Normal'], rel_path, pid, is_official, base_url, data_dir)
                    else:
                        html += '<div style="display: flex; gap: 4px; justify-content: center; width: 100%;">'
                        for v_name in ['Easy', 'Hard']:
                            if v_name in g.versions:
                                border = 'border-right: 1px dashed #cbd5e1; padding-right: 4px;' if v_name == 'Easy' and 'Hard' in g.versions else ''
                                html += f'<div style="flex: 1; {border}">'
                                html += render_single_version(g.versions[v_name], rel_path, pid, is_official, base_url, data_dir)
                                html += '</div>'
                        html += '</div>'
            html += '</td>'
            
        if not is_official:
            html += f'<td class="remark-col" style="text-align: left; font-size:0.9em; color:var(--text-muted); line-height: 1.4;">{c_remark}</td>'
            
        html += '</tr>'
    html += '</tbody></table></div>'
    return html

def build_category_page(title, groups_dict, contest_info_dict, out_path, rel_path, base_url="", data_dir="data"):
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

    is_official = (title in ['Codeforces', 'AtCoder'])
    first_col_width = 30 if title == 'OI' else 20
    
    nav_extra = ""
    if not is_official:
        nav_extra = '<button class="btn toggle-remark-btn" onclick="toggleRemark()" style="color: #059669; border-color: #a7f3d0; background: #fff;">📝 显示备注</button>'

    content_html = ""
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
            tables_html += build_matrix_table(sub_cats[sc_name], contest_info_dict.get('AtCoder', {}), rel_path, is_official, first_col_width, base_url, data_dir)
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
            tables_html += build_matrix_table(groups_dict[sc_name], contest_info_dict.get(sc_name, {}), rel_path, is_official, first_col_width, base_url, data_dir)
            tables_html += '</div>'
            first = False
        tabs_html += '</div>'
        content_html = tabs_html + tables_html
    else:
        content_html = build_matrix_table(groups_dict, contest_info_dict.get(title, {}), rel_path, is_official, first_col_width, base_url, data_dir)

    html = HTML_TEMPLATE.format(
        title=title, stats_block=stats_block, nav_extra=nav_extra,
        content_html=content_html, gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        base_url=base_url
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def build_list_page(title, all_versions, out_path, rel_path, table_id="list-table", base_url="", data_dir="data"):
    has_cpp = sum(1 for v in all_versions if v.files.get('cpp'))
    has_md = sum(1 for v in all_versions if v.files.get('md'))

    stats_html = f"<span>📁 独立题目: {len(all_versions)}</span><span>📝 有代码: {has_cpp}</span><span>💡 有题解: {has_md}</span>"
    stats_block = f'<div class="stats-bar"><div class="stats-info">{stats_html}</div></div>'
    nav_extra = '<button class="btn toggle-remark-btn" onclick="toggleRemark()" style="color: #059669; border-color: #a7f3d0; background: #fff;">📝 显示备注</button>'
    
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
        
        conf_fname = v.files.get("conf") or f"{v.base_filename}.conf"
        cpp_fname = v.files.get("cpp") or f"{v.base_filename}.cpp"
        md_fname = v.files.get("md") or f"{v.base_filename}.md"
        
        links = []
        if v.files.get('conf'):
            raw_href = f"{rel_path}/{v.files['conf']}"
            editor_href = f"{base_url}editor.html?file={data_dir}/{v.files['conf']}"
            links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="配置" style="text-decoration:none;">⚙️</a>')
        else:
            editor_href = f"{base_url}editor.html?file={data_dir}/{conf_fname}&action=create"
            links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建配置" style="text-decoration:none;">➕⚙️</a>')
            
        if v.files.get('cpp'):
            raw_href = f"{rel_path}/{v.files['cpp']}"
            editor_href = f"{base_url}editor.html?file={data_dir}/{v.files['cpp']}"
            links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="代码" style="text-decoration:none;">📝</a>')
        else:
            editor_href = f"{base_url}editor.html?file={data_dir}/{cpp_fname}&action=create"
            links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建代码" style="text-decoration:none;">➕📝</a>')
            
        if v.files.get('md'): 
            actual_md = v.files["md"]
            md_raw_fname = actual_md[:-3] if actual_md.endswith('.md') else actual_md
            raw_href = f"{rel_path}/{md_raw_fname}"
            editor_href = f"{base_url}editor.html?file={data_dir}/{actual_md}"
            links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="题解" style="text-decoration:none;">💡</a>')
        else:
            editor_href = f"{base_url}editor.html?file={data_dir}/{md_fname}&action=create"
            links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建题解" style="text-decoration:none;">➕💡</a>')
            
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
        content_html=content_html, gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        base_url=base_url
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def scan_problem_lists(plist_dir, groups):
    plists = {}
    if not os.path.exists(plist_dir):
        return plists
    
    for f in os.listdir(plist_dir):
        if f.endswith('.conf'):
            name = f[:-5]
            path = os.path.join(plist_dir, f)
            with open(path, 'r', encoding='utf-8') as file:
                ids = [line.split('#')[0].strip() for line in file.readlines()]
                ids = [x for x in ids if x]
            
            matched_versions = []
            for pid in ids:
                target_group = groups.get(pid.lower())
                if target_group:
                    if 'Normal' in target_group.versions:
                        matched_versions.append(target_group.versions['Normal'])
                    else:
                        matched_versions.append(list(target_group.versions.values())[0])
                else:
                    dummy = ProblemVersion("Normal", pid)
                    dummy.link = "#"
                    matched_versions.append(dummy)
                    
            plists[name] = matched_versions
    return plists

def build_problem_lists_index(plists, out_path, base_url=""):
    cards_html = ""
    for name, versions in plists.items():
        cards_html += f"""
        <a href="{name}.html" class="plist-card">
            <h3>📂 {name}</h3>
            <div><span class="count">包含 {len(versions)} 道题目</span></div>
        </a>"""
    
    content = f"""
    <div class="list-filter-bar">
        <strong style="color: var(--primary); font-size: 1.1em;">🔍 检索题单</strong>
        <input type="text" id="plist-search" placeholder="输入题单名称进行检索..." onkeyup="filterPList()" style="width:100%; max-width:400px; margin-left:10px;">
    </div>
    <div class="plist-grid">{cards_html}</div>
    """
    
    html = HTML_TEMPLATE.format(
        title="📋 Problem List 题单总览", stats_block="", nav_extra="",
        content_html=content, gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        base_url=base_url
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def build_single_plist_page(name, versions, out_path, rel_path, base_url="", data_dir="data"):
    table_id = f"plist-{name}"
    
    content_html = f"""
    <div class="list-filter-bar">
        <input type="text" id="filter-tag-{table_id}" placeholder="搜索本题单题目..." onkeyup="filterListTable('{table_id}')">
    </div>
    <div style="overflow-x: auto;">
        <table class="plist-table" id="{table_id}">
            <thead>
                <tr>
                    <th style="width: 33.33%; padding-left:20px;">题目</th>
                    <th style="width: 33.33%;">标签</th>
                    <th style="width: 33.33%;">文件</th>
                </tr>
            </thead>
            <tbody>
    """
    
    for i, v in enumerate(versions):
        tags_str = " ".join(v.tags) if v.tags else ""
        tags_html = "".join([f'<span class="tag-pill">{t}</span>' for t in v.tags])
        
        conf_fname = v.files.get("conf") or f"{v.base_filename}.conf"
        cpp_fname = v.files.get("cpp") or f"{v.base_filename}.cpp"
        md_fname = v.files.get("md") or f"{v.base_filename}.md"
        
        links = []
        if v.files.get('conf'):
            raw_href = f"{rel_path}/{v.files['conf']}"
            editor_href = f"{base_url}editor.html?file={data_dir}/{v.files['conf']}"
            links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="配置" style="text-decoration:none;">⚙️</a>')
        else:
            editor_href = f"{base_url}editor.html?file={data_dir}/{conf_fname}&action=create"
            links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建配置" style="text-decoration:none;">➕⚙️</a>')
            
        if v.files.get('cpp'):
            raw_href = f"{rel_path}/{v.files['cpp']}"
            editor_href = f"{base_url}editor.html?file={data_dir}/{v.files['cpp']}"
            links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="代码" style="text-decoration:none;">📝</a>')
        else:
            editor_href = f"{base_url}editor.html?file={data_dir}/{cpp_fname}&action=create"
            links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建代码" style="text-decoration:none;">➕📝</a>')
            
        if v.files.get('md'): 
            actual_md = v.files["md"]
            md_raw_fname = actual_md[:-3] if actual_md.endswith('.md') else actual_md
            raw_href = f"{rel_path}/{md_raw_fname}"
            editor_href = f"{base_url}editor.html?file={data_dir}/{actual_md}"
            links.append(f'<a href="{raw_href}" data-editor-href="{editor_href}" target="_blank" class="file-link" title="题解" style="text-decoration:none;">💡</a>')
        else:
            editor_href = f"{base_url}editor.html?file={data_dir}/{md_fname}&action=create"
            links.append(f'<a href="{editor_href}" target="_blank" class="file-link add-file-btn" title="新建题解" style="text-decoration:none;">➕💡</a>')

        display_name = v.base_filename 
        name_html = f'<a href="{v.link}" target="_blank" style="color:var(--primary); font-weight:bold; text-decoration:none;">{display_name}</a>' if v.link != '#' else f'<b>{display_name}</b>'

        content_html += f"""
        <tr data-index="{i}" data-base="{v.base_filename}" data-tags="{tags_str}">
            <td style="padding-left:20px;">{name_html}</td>
            <td>{tags_html}</td>
            <td>
                <div class="version-row" style="flex-wrap: nowrap;">
                    <span style="white-space: nowrap; display: inline-flex; gap: 6px;">{"".join(links)}</span>
                </div>
            </td>
        </tr>"""
        
    content_html += "</tbody></table></div>"

    html = HTML_TEMPLATE.format(
        title=f"📁 题单: {name}", 
        stats_block=f'<div class="stats-bar"><div class="stats-info"><span>共 {len(versions)} 题</span></div></div>',
        nav_extra="",
        content_html=content_html, 
        gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        base_url=base_url
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def scan_blogs(blog_dir):
    blogs = []
    if not os.path.exists(blog_dir):
        return blogs
        
    for f in os.listdir(blog_dir):
        if f.endswith('.md'):
            filepath = os.path.join(blog_dir, f)
            title = os.path.splitext(f)[0]
            mtime = os.path.getmtime(filepath)
            date_str = datetime.fromtimestamp(mtime).strftime("%Y-%m-%d")

            try:
                with open(filepath, 'r', encoding='utf-8') as file:
                    for i, line in enumerate(file):
                        if i > 10: break
                        stripped = line.strip()
                        if stripped.startswith('# '):
                            title = stripped[2:].strip()
                            break
            except Exception:
                pass

            blogs.append({
                'filename': f,
                'title': title,
                'date': date_str,
                'mtime': mtime
            })
            
    blogs.sort(key=lambda x: x['mtime'], reverse=True)
    return blogs

def build_blog_index_page(blogs, rel_blog_path, out_path, base_url=""):
    if not blogs:
        content_html = '<div style="padding: 30px; text-align: center; color: var(--text-muted); background: #fff; border-radius: 12px; border: 1px solid var(--border);">暂无博客文章。请在 blog/ 目录下放入 .md 文件。</div>'
    else:
        blog_list_html = ""
        for b in blogs:
            link = f"{rel_blog_path}/{b['filename'][:-3]}"
            blog_list_html += f"""
            <a href="{link}" target="_blank" class="blog-item">
                <div class="blog-item-title">📄 {b['title']}</div>
                <div class="blog-item-date">{b['date']}</div>
            </a>
            """
        
        content_html = f"""
        <div style="background: #fff; border-radius: 12px; border: 1px solid var(--border); box-shadow: 0 4px 15px rgba(0,0,0,0.03); overflow: hidden;">
            {blog_list_html}
        </div>
        """
    
    html = HTML_TEMPLATE.format(
        title="✍️ 博客笔记目录", 
        stats_block=f'<div class="stats-bar"><div class="stats-info"><span>共 {len(blogs)} 篇博客文章</span></div></div>', 
        nav_extra="",
        content_html=content_html, 
        gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        base_url=base_url
    )
    with open(out_path, 'w', encoding='utf-8') as f: 
        f.write(html)

def build_index_page(categories, summary_versions, todo_versions, plists, blog_count, out_path):
    s_count = len(summary_versions)
    t_count = len(todo_versions)
    plist_count = len(plists)
    
    oi_p = sum(len(g.versions) for gs in categories.get('OI', {}).values() for g in gs) + sum(len(g.versions) for gs in categories.get('OIs', {}).values() for g in gs)
    oi_c = len(categories.get('OI', {})) + len(categories.get('OIs', {}))
    
    xcpc_p = sum(len(g.versions) for gs in categories.get('XCPC', {}).values() for g in gs)
    xcpc_c = len(categories.get('XCPC', {}))
    
    cf_p = sum(len(g.versions) for gs in categories.get('Codeforces', {}).values() for g in gs)
    cf_c = len(categories.get('Codeforces', {}))
    
    at_p = sum(len(g.versions) for gs in categories.get('AtCoder', {}).values() for g in gs)
    at_c = len(categories.get('AtCoder', {}))

    # --- 全局时间跨度与图表数据聚合 ---
    today = datetime.now()
    valid_dates = [v.date for v in summary_versions if v.date and v.date != "未知"]
    
    # 获取最早的做题日期，如果没有则默认为30天前
    if valid_dates:
        min_date_str = min(valid_dates)
        try:
            min_date = datetime.strptime(min_date_str, "%Y-%m-%d")
        except ValueError:
            min_date = today - timedelta(days=30)
    else:
        min_date = today - timedelta(days=30)
        
    # 确保图表至少有 30 天的跨度，即使是从今天才开始做的
    if (today - min_date).days < 30:
        min_date = today - timedelta(days=30)

    delta_days = (today - min_date).days
    date_list = [(min_date + timedelta(days=i)).strftime("%Y-%m-%d") for i in range(delta_days + 1)]
    
    # 初始化全局统计字典
    daily_stats = {d: {'l1': 0, 'l2': 0, 'l3': 0, 'l4': 0, 'u': 0} for d in date_list}
    
    for v in summary_versions:
        d = v.date
        if d in daily_stats:
            # ✅ 已同步你的新难度分级：2000, 2600, 3000
            if v.difficulty is None: daily_stats[d]['u'] += 1
            elif v.difficulty < 2000: daily_stats[d]['l1'] += 1
            elif v.difficulty < 2600: daily_stats[d]['l2'] += 1
            elif v.difficulty < 3000: daily_stats[d]['l3'] += 1
            else: daily_stats[d]['l4'] += 1

    chart_data = {
        'dates': date_list,  # 跨度变长了，保留 YYYY-MM-DD 以防跨年看不懂
        'l1': [daily_stats[d]['l1'] for d in date_list],
        'l2': [daily_stats[d]['l2'] for d in date_list],
        'l3': [daily_stats[d]['l3'] for d in date_list],
        'l4': [daily_stats[d]['l4'] for d in date_list],
        'u': [daily_stats[d]['u'] for d in date_list],
    }

    html = INDEX_HTML_TEMPLATE.format(
        s_count=s_count, t_count=t_count,
        oi_p=oi_p, oi_c=oi_c,
        xcpc_p=xcpc_p, xcpc_c=xcpc_c,
        cf_p=cf_p, cf_c=cf_c,
        at_p=at_p, at_c=at_c,
        plist_count=plist_count,
        blog_count=blog_count,
        chart_data_json=json.dumps(chart_data),
        gen_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    with open(out_path, 'w', encoding='utf-8') as f: f.write(html)

def main():
    data_dir = sys.argv[1] if len(sys.argv) > 1 else 'data'
    out_dir = sys.argv[2] if len(sys.argv) > 2 else '.'
    plist_dir = 'plist'
    blog_dir = 'blog'

    if not os.path.exists(data_dir):
        print(f"❌ 错误: 数据目录 '{data_dir}' 不存在！")
        sys.exit(1)
    if out_dir != '.' and not os.path.exists(out_dir): os.makedirs(out_dir)

    with open(os.path.join(out_dir, "editor.html"), 'w', encoding='utf-8') as f:
        f.write(EDITOR_HTML_TEMPLATE)

    rel_data_path = os.path.relpath(data_dir, out_dir).replace('\\', '/')
    rel_blog_path = os.path.relpath(blog_dir, out_dir).replace('\\', '/')

    print(f"🔍 正在扫描 '{data_dir}'...")
    groups = scan_and_group_files(data_dir)
    print(f"✅ 找到 {len(groups)} 个基础题组，正在分析配置...")
    
    contest_info = apply_categories_and_links(groups, data_dir)
    
    print(f"📋 正在扫描题单目录 '{plist_dir}'...")
    plists = scan_problem_lists(plist_dir, groups)
    if plists:
        print(f"✅ 找到 {len(plists)} 个题单。")
        
    print(f"✍️ 正在扫描博客目录 '{blog_dir}'...")
    blogs = scan_blogs(blog_dir)
    if blogs:
        print(f"✅ 找到 {len(blogs)} 篇博客。")

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

    print(f"🛠️ 正在生成 HTML 到 '{out_dir}'...")
    for cat in ['Codeforces', 'AtCoder', 'XCPC']:
        build_category_page(cat, categories[cat], contest_info, os.path.join(out_dir, f"{cat}.html"), rel_data_path, base_url="", data_dir=data_dir)
        
    build_category_page('OI', {'OI': categories['OI'], 'OIs': categories['OIs']}, contest_info, os.path.join(out_dir, "OI.html"), rel_data_path, base_url="", data_dir=data_dir)
        
    build_list_page('Summary', summary_versions, os.path.join(out_dir, 'Summary.html'), rel_data_path, "summary-table", base_url="", data_dir=data_dir)
    build_list_page('Todo', todo_versions, os.path.join(out_dir, 'todo.html'), rel_data_path, "todo-table", base_url="", data_dir=data_dir)

    build_blog_index_page(blogs, rel_blog_path, os.path.join(out_dir, "Blog.html"), base_url="")

    out_plist_dir = os.path.join(out_dir, 'plist')
    os.makedirs(out_plist_dir, exist_ok=True)
    build_problem_lists_index(plists, os.path.join(out_plist_dir, "index.html"), base_url="../")
    
    if plists:
        rel_plist_path = os.path.relpath(data_dir, out_plist_dir).replace('\\', '/')
        for name, versions in plists.items():
            out_file = os.path.join(out_plist_dir, f"{name}.html")
            build_single_plist_page(name, versions, out_file, rel_plist_path, base_url="../", data_dir=data_dir)

    build_index_page(categories, summary_versions, todo_versions, plists, len(blogs), os.path.join(out_dir, "index.html"))
    print(f"🎉 处理完成！请在浏览器中打开: {os.path.abspath(os.path.join(out_dir, 'index.html'))}")

if __name__ == '__main__':
    main()