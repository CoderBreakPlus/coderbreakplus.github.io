import subprocess,time,json
from pathlib import Path
results=[]
for i in range(1,81):
 t=time.monotonic()
 with open(f'../uoj_data/test{i}.in','rb') as f:
  p=subprocess.run(['./solution'],stdin=f,stdout=subprocess.PIPE,stderr=subprocess.PIPE,timeout=60)
 dt=time.monotonic()-t
 assert p.returncode==0 and p.stdout==b'AC\n',(i,p.returncode,p.stdout,p.stderr)
 results.append({'test':i,'seconds':round(dt,3),'result':'AC'})
 print(i,round(dt,3),'AC',flush=True)
Path('results.json').write_text(json.dumps(results,indent=2))
