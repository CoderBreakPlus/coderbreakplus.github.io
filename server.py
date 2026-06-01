import http.server
import socketserver
import urllib.parse
import json
import os

# 允许地址重用，防止退出后立即启动报错
socketserver.TCPServer.allow_reuse_address = True

class EditorHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urllib.parse.urlparse(self.path)
        
        # 接口 1: 读取文件
        if parsed_path.path == '/api/read':
            query = urllib.parse.parse_qs(parsed_path.query)
            filepath = query.get('file', [''])[0]
            
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
            
            if '..' in filepath or filepath.startswith('/'):
                self.send_error(403, "Forbidden")
                return
            
            os.makedirs(os.path.dirname(filepath) or '.', exist_ok=True)
            
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(content)
                
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps({'status': 'ok'}).encode('utf-8'))
            return
            
        # 接口 3: 触发网页重新构建
        if parsed_path.path == '/api/rebuild':
            print("\n🔄 正在后台重新构建静态网页...")
            os.system("python3 _run.py")
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps({'status': 'ok'}).encode('utf-8'))
            return
            
        return super().do_POST()

if __name__ == "__main__":
    # 自动探测可用端口，防止 98 报错
    for port in range(8000, 9000):
        try:
            httpd = socketserver.TCPServer(("", port), EditorHandler)
            print("=" * 60)
            print("🚀 算法平台本地服务器已启动！")
            print(f"👉 请在浏览器中打开: http://localhost:{port}/index.html")
            print("✨ 享受网页在线编辑代码与配置的快感吧。")
            print("⚠️ 请保持此窗口开启，按 Ctrl+C 可停止服务器。")
            print("=" * 60)
            httpd.serve_forever()
            break
        except OSError as e:
            if e.errno == 98:
                continue
            else:
                raise