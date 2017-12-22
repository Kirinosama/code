var
  n,m,i,j,k,t,s,head,tail:longint;
  a,b,f,next:array[1..6000000]of longint;
  d,p,q,now:array[1..1000000]of longint;
 
function
  get(x,y:longint):longint;
begin
  exit((x-1)*m+y);
end;
 
function
  min(x,y:longint):longint;
begin
  if x<y
  then exit(x)
  else exit(y);
end;
 
procedure
  insert(x,y,z:longint);
begin
  inc(k);a[k]:=x;b[k]:=y;f[k]:=z;
  next[k]:=p[a[k]];p[a[k]]:=k;
  inc(k);a[k]:=y;b[k]:=x;f[k]:=z;
  next[k]:=p[a[k]];p[a[k]]:=k;
end;
 
function
  travel:boolean;
begin
  fillchar(d,sizeof(d),0);d[1]:=1;
  q[1]:=1;head:=1;tail:=1;now:=p;
  while head<=tail do
    begin
      t:=p[q[head]];
      while t<>0 do
        begin
          if (f[t]<>0) and (d[b[t]]=0)
          then begin
                 inc(tail);q[tail]:=b[t];
                 d[b[t]]:=d[q[head]]+1;
               end;
          t:=next[t];
        end;
      inc(head);
    end;
  exit(d[n*m]<>0);
end;
 
function
  maxflow(x,lmt:longint):longint;
var
  s,c:longint;
begin
  if x=n*m then exit(lmt);s:=0;
  while now[x]<>0 do
    begin
      if (f[now[x]]<>0) and (d[b[now[x]]]=d[x]+1)
      then begin
             c:=maxflow(b[now[x]],min(lmt-s,f[now[x]]));
             dec(f[now[x]],c);inc(f[now[x] xor 1],c);
             inc(s,c);if s=lmt then exit(lmt);
           end;
      now[x]:=next[now[x]];
    end;
  exit(s);
end;
 
begin
  read(n,m);k:=1;
  for i:=1 to n do
    for j:=1 to m-1 do
      begin
        read(t);
        insert(get(i,j),get(i,j+1),t);
      end;
  for i:=1 to n-1 do
    for j:=1 to m do
      begin
        read(t);
        insert(get(i,j),get(i+1,j),t);
      end;
  for i:=1 to n-1 do
    for j:=1 to m-1 do
      begin
        read(t);
        insert(get(i,j),get(i+1,j+1),t);
      end;
  while travel do inc(s,maxflow(1,maxlongint));
  writeln(s);
end.