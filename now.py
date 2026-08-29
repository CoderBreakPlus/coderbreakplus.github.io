import requests
import json

url = "https://www.luogu.com.cn/article/83lljbo7?_contentOnly=1"
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
    "x-luogu-type": "content-only"
}

response = requests.get(url, headers=headers)
if response.status_code == 200:
    data = response.json()
    article = data.get("currentData", {}).get("article", {})
    
    print("标题:", article.get("title"))
    print("Markdown 源码:\n", article.get("content"))
    
    # 保存为 Markdown 文件
    with open("article.md", "w", encoding="utf-8") as f:
        f.write(article.get("content", ""))
else:
    print(f"请求失败，状态码: {response.status_code}")
