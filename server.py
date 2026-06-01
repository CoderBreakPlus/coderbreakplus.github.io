import http.server
import socketserver
import urllib.parse
import json
import os

PORT = 8000

class EditorHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urllib.parse.urlparse(self.path)
        
        # 接口 1: 读取文件
        if parsed_path.path == '/api/read':
            query = urllib.parse.parse_qs(parsed_path.query)
            filepath = query.get('file', [''])[0]
            
            # 安全校验：防止跨目录访问
            if '..' in filepath or filepath.startswith('/'):
                self.send_error(403, "Forbidden")
                return
                
            if not os.path.exists(filepath):
                self.send_response(404)
                self.end_headers()
                return
                
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
                
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps({'content': content}).encode('utf-8'))
            return
            
        return super().do_GET()

    def do_POST(self):
        parsed_path = urllib.parse.urlparse(self.path)
        
        # 接口 2: 写入文件
        if parsed_path.path == '/api/write':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            data = json.loads(post_data)
            
            filepath = data.get('file', '')
            content = data.get('content', '')
            
            # 安全校验
            if '..' in filepath or filepath.startswith('/'):
                self.send_error(403, "Forbidden")
                return
            
            # 如果目录不存在自动创建
            os.makedirs(os.path.dirname(filepath) or '.', exist_ok=True)
            
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(content)
                
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps({'status': 'ok'}).encode('utf-8'))
            return
            
        # 接口 3: 触发网页重新构建 (run.py)
        if parsed_path.path == '/api/rebuild':
            print("\n🔄 正在后台重新构建静态网页...")
            os.system("python _run.py")
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps({'status': 'ok'}).encode('utf-8'))
            return
            
        return super().do_POST()

if __name__ == "__main__":
    print("=" * 60)
    print("🚀 算法平台本地服务器已启动！")
    print(f"👉 请在浏览器中打开: http://localhost:{PORT}/index.html")
    print("✨ 你现在可以在网页上新建和编辑 .cpp, .md, .conf 了。")
    print("⚠️ 请保持此窗口开启，按 Ctrl+C 可停止服务器。")
    print("=" * 60)
    
    with socketserver.TCPServer(("", PORT), EditorHandler) as httpd:
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\n⏹️ 服务器已关闭。")