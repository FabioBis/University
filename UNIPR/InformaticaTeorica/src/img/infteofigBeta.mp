beginfig(1)

numeric u, N, a, b, seg, X[], Y[];

N = 50;
u = 0.2cm;
a = -b*1.5= u*10;
seg = (a-b)/(2*N);

z0 = (0,0);
z1 = -z2*2 = (15u,0);
z3 = -z4*2 = z1 rotated 90;

drawarrow z2--z1;
drawarrow z4--z3;

X[0] = b;
for i = 1 upto 2*N-1:
  X[i] = X[i-1]+seg;
endfor;

50*Y[0] = b*b-b;
for i = 1 upto 2*N-1:
  50*Y[i] = (X[i]*X[i])-X[i];
endfor;

for i = 6 upto 2*N+5:
  z[i] = (X[(i-6)], Y[(i-6)]);
endfor;

for i = 6 upto 2*N+4:
  draw z[i]..z[i+1];
endfor;

label.llft(btex $0$ etex, z0);
label.llft(btex $x$ etex, z1);
label.lft(btex $y$ etex, z3);
endfig;
