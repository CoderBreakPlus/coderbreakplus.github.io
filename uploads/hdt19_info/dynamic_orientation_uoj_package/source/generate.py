"""Deterministic generator. Run: python3 source/generate.py uoj_data"""
import random,sys,json,math
from pathlib import Path
OUT=Path(sys.argv[1] if len(sys.argv)>1 else '../uoj_data');OUT.mkdir(parents=True,exist_ok=True)
STATS=[]
def edge(u,v):return (min(u,v),max(u,v))
def cycle(v):return [edge(v[j-1],v[j]) for j in range(len(v))]
class Case:
 def __init__(self,i,n,q,name):
  self.i,self.n,self.q,self.name=i,n,q,name
  self.rng=random.Random(20261022+i*100003);self.ops=[];self.es=[];self.pos={};self.deg=[0]*(n+1)
  self.odd=0;self.paths=0;self.queries=0;self.adds=0;self.work=0;self.peak=0
  self.targets=[q*j//10 for j in range(10)]
 def room(self):return self.q-len(self.ops)
 def change(self,e):
  u,v=e
  if e in self.pos:
   op=2;k=self.pos.pop(e);z=self.es.pop()
   if k<len(self.es):self.es[k]=z;self.pos[z]=k
  else:
   op=1;self.pos[e]=len(self.es);self.es.append(e);self.adds+=1
  for x in e:
   self.odd-=self.deg[x]&1;self.deg[x]+=1 if op==1 else -1;self.odd+=self.deg[x]&1
  self.ops.append((op,u,v));self.peak=max(self.peak,len(self.es))
 def query(self,force=False):
  assert self.odd==0
  self.ops.append((3,));self.queries+=1;self.work+=len(self.es)
  if self.paths<10 and self.room() and (force or len(self.ops)>=self.targets[self.paths]):
   self.ops.append((4,));self.paths+=1
 def build(self,es):
  es=list(es);self.rng.shuffle(es)
  for e in es:
   assert e not in self.pos;self.change(e)
 def finish(self):
  assert not self.odd
  while self.room():self.query(force=self.room()>=2)
  assert len(self.ops)==self.q
  (OUT/f'test{self.i}.in').write_text(f'{self.n} {self.q}\n'+''.join(' '.join(map(str,o))+'\n' for o in self.ops))
  (OUT/f'test{self.i}.ans').write_text('AC\n')
  STATS.append(dict(test=self.i,n=self.n,q=self.q,name=self.name,queries=self.queries,paths=self.paths,additions=self.adds,peak_edges=self.peak,naive_edge_visits=self.work))

def small(i):
 if i==1:
  c=Case(i,4,10,'empty query, isolated vertex, deleted edge receives a new ID')
  c.ops=[(3,),(1,1,2),(1,2,3),(1,1,3),(3,),(4,),(2,1,3),(1,1,3),(3,),(4,)]
  # Use replay so statistics and checks remain accurate.
  ops=c.ops;c.ops=[]
  for op in ops:
   if op[0]<=2:c.change((op[1],op[2]))
   elif op[0]==3:c.ops.append(op);c.queries+=1;c.work+=len(c.es)
   else:c.ops.append(op);c.paths+=1
  c.finish();return
 if i in (2,3,4):
  c=Case(i,[1,2,10][i-2],10,'empty graph and repeated follow-ups');c.finish();return
 c=Case(i,10 if i%3==0 else 6,10,'small exhaustive-style boundary '+str(i))
 if i in (5,6,7):
  vs=[1,2,3,4][:3+(i==7)];c.build(cycle(vs));c.query(True)
  if c.room()>=4:
   e=c.es[c.rng.randrange(len(c.es))];c.change(e);c.change(e);c.query(True)
 elif i in (8,9,10):
  c.build(cycle([1,2,3])+cycle([4,5,6]));c.query(True)
 elif i in (11,12,13):
  c.build(cycle([1,2,3]));c.query(True)
  for e in list(c.es):c.change(e)
  c.query(True)
 else:
  vs=list(range(1,7));c.rng.shuffle(vs)
  k=3+(i%4);c.build(cycle(vs[:k]));c.query(True)
 c.finish()

def large(i,Q,kind):
 rng=random.Random(70001+i)
 if kind==20:
  c=Case(i,Q,Q,'maximum n, empty graph');c.finish();return
 if kind==11:
  c=Case(i,3,Q,'tiny live graph, large insertion IDs');c.build(cycle([1,2,3]))
 elif kind==17:
  c=Case(i,Q,Q,'insertion-only growing bouquet')
  for a in range(2,Q,2):
   if c.room()<6:break
   c.build(cycle([1,a,a+1]));c.query()
  c.finish();return
 elif kind in (4,14,18):
  k=int(math.sqrt(Q//2));k-=1-k%2;k=max(k,3)
  c=Case(i,Q if kind==18 else k,Q,'dense odd clique with '+('triangle toggles' if kind==4 else 'edge replacement'))
  c.build((u,v) for u in range(1,k+1) for v in range(u+1,k+1))
 elif kind in (2,3,9,12,13,19):
  count=max(2,Q//12)
  n=3*count if kind in (2,9,13,19) else 2*count+1
  c=Case(i,Q if kind==19 else n,Q,'disjoint triangles' if kind in (2,9,13,19) else 'high-degree bouquet')
  es=[]
  for j in range(count):es+=cycle([3*j+1,3*j+2,3*j+3] if kind in (2,9,13,19) else [1,2*j+2,2*j+3])
  c.build(es)
 elif kind in (5,8):
  c=Case(i,Q if kind==8 else min(Q,1000),Q,'overlapping random cycles with isolated vertices')
  k=min(c.n,200);c.build(cycle(list(range(1,k+1))))
 else:
  k=max(4,Q//3);c=Case(i,Q if kind==15 else k,Q,'long cycles, '+str(kind))
  vs=list(range(1,k+1));c.rng.shuffle(vs);c.build(cycle(vs))
 c.query(True)
 step=0
 while c.room()>=14:
  step+=1
  if kind in (1,7,11,12,14,15,18):
   e=c.es[c.rng.randrange(len(c.es))];c.change(e);c.change(e)
  elif kind==16:
   if step%19==0:
    e=c.es[c.rng.randrange(len(c.es))];c.change(e);c.change(e)
  elif kind==10:
   # Long open intervals, delete and restore up to 64 unrelated edges.
   take=min(64,len(c.es),(c.room()-4)//2)
   es=c.rng.sample(c.es,take)
   for e in es:c.change(e)
   c.rng.shuffle(es)
   for e in es:c.change(e)
  elif kind in (6,13):
   # A degree-preserving 2-switch can split or join circuits.
   done=False
   for _ in range(30):
    (a,b),(d,e)=c.rng.sample(c.es,2)
    if len({a,b,d,e})<4:continue
    x,y=edge(a,d),edge(b,e)
    if x in c.pos or y in c.pos:continue
    for z in [(a,b),(d,e),x,y]:c.change(z)
    done=True;break
   if not done:
    e=c.es[0];c.change(e);c.change(e)
  elif kind==2:
   j=c.rng.randrange(count);es=cycle([3*j+1,3*j+2,3*j+3])
   for e in es:c.change(e)
   for e in reversed(es):c.change(e)
  elif kind==3:
   j=c.rng.randrange(count)
   for e in cycle([1,2*j+2,2*j+3]):c.change(e)
  elif kind==19:
   j=(step-1)%count
   for e in cycle([3*j+1,3*j+2,3*j+3]):c.change(e)
  else:
   k=3 if kind in (4,9) else c.rng.randint(3,8)
   upper=min(c.n,200) if kind in (5,8) else c.n
   for e in cycle(c.rng.sample(range(1,upper+1),k)):c.change(e)
  c.query()
 c.finish()

for i in range(1,81):
 if i<=20:small(i)
 else:large(i,1000 if i<=40 else 50000 if i<=60 else 200000,(i-1)%20+1)
 print(i,STATS[-1]['name'],flush=True)
(OUT.parent/'data_manifest.json').write_text(json.dumps(STATS,ensure_ascii=False,indent=2))
