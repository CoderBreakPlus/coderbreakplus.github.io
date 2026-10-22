"""Run from package root, after compiling solution and val there."""
import subprocess,time,json,sys
from pathlib import Path
root=Path(__file__).resolve().parents[1]
solution=Path(sys.argv[1]).resolve() if len(sys.argv)>1 else root/'solution'
validator=Path(sys.argv[2]).resolve() if len(sys.argv)>2 else root/'val'
results=[]
for i in range(1,81):
 p=root/'uoj_data'/f'test{i}.in';limit=10 if i<=20 else 1000 if i<=40 else 50000 if i<=60 else 200000
 with p.open('rb') as f:
  v=subprocess.run([str(validator),str(limit)],stdin=f,capture_output=True)
 assert v.returncode==0,(i,v.stderr)
 assert p.with_suffix('.ans').read_text()=='AC\n'
 t=time.monotonic()
 with p.open('rb') as f:
  s=subprocess.run([str(solution)],stdin=f,capture_output=True,timeout=30)
 elapsed=time.monotonic()-t
 assert s.returncode==0 and s.stdout==b'AC\n',(i,s.returncode,s.stdout,s.stderr)
 results.append(dict(test=i,seconds=round(elapsed,4),result='AC'))
 print(i,round(elapsed,4),'AC',flush=True)
(root/'validation_results.json').write_text(json.dumps(results,indent=2))
