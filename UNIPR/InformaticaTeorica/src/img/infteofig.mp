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


beginfig(2)

  numeric u;

  u = 0.4cm;
  
  z0 = (0,0);
  z1 = (-u, -2u);
  z2 = (u, -2u);

  draw z0--z1;
  draw z0--z2;

  pickup pencircle scaled 3;

  draw z0;

  label.bot (btex $x$ etex,z1);
  label.bot (btex $K$ etex,z2);
endfig;


beginfig(3)

  numeric u;

  u = 0.4cm;

  z0 = (0,0);       % root
  z1 = (-u,-2u);    % 
  z2 = (-3u, -6u);  % S
  z3 = (0, -4u);    % 
  z4 = (-u, -6u);   % K
  z5 = (u, -6u);    % K
  z6 = (3u, -6u);   % y

  draw z0--z1--z2;
  draw z1--z3--z4;
  draw z3--z5;
  draw z0--z6;

  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z3;

  label.bot (btex $S$ etex,z2);
  label.bot (btex $K$ etex,z4);
  label.bot (btex $K$ etex,z5);
  label.bot (btex $y$ etex,z6);
  
endfig;


beginfig(4)

  numeric u;

  u = 0.25cm;

  z0 = (0,0);        % root
  z1 = (-u,-2u);
  z2 = (-2u, -4u);
  z3 = (-3u, -6u);
  z4 = (-4u, -8u);
  z5 = (-5u, -10u);
  z6 = (-6u, -12u);
  z7 = (-7u, -14u);
  z8 = (-8u, -16u);  % a
  z9 = (-6u, -16u);  % b
  z10= (-4u, -16u);  % c
  z11= (-2u, -16u);   % x
  z12= (0, -16u);   % y
  z13= (2u, -16u);   % K
  z14= (4u, -16u);   % I
  z15= (6u, -16u);     % x
  z16= (8u, -16u);    % a

  draw z0--z1--z2--z3--z4--z5--z6--z7--z8;
  draw z7--z9;
  draw z6--z10;
  draw z5--z11;
  draw z4--z12;
  draw z3--z13;
  draw z2--z14;
  draw z1--z15;
  draw z0--z16;

  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z2;
  draw z3;
  draw z4;
  draw z5;
  draw z6;
  draw z7;

  label.bot(btex $a$ etex,z8);
  label.bot(btex $b$ etex,z9);
  label.bot(btex $c$ etex,z10);
  label.bot(btex $x$ etex,z11);
  label.bot(btex $y$ etex,z12);
  label.bot(btex $K$ etex,z13);
  label.bot(btex $I$ etex,z14);
  label.bot(btex $x$ etex,z15);
  label.bot(btex $a$ etex,z16);
  
endfig;


beginfig(5)
numeric u;

  u = 0.25cm;

  z0 = (0,0);        % root
  z1 = (-u,-2u);
  z2 = (5u, -14u);
  z3 = (-3u, -6u);
  z4 = (0, -12u);
  z5 = (-u, -14u);
  z6 = (-6u, -12u);
  z7 = (-7u, -14u);
  z8 = (-8u, -16u);  % a
  z9 = (-6u, -16u);  % b
  z10= (-4u, -16u);  % c
  z11= (-2u, -16u);   % x
  z12= (0, -16u);   % y
  z13= (2u, -16u);   % K
  z14= (4u, -16u);   % I
  z15= (6u, -16u);     % x
  z16= (8u, -16u);    % a

  draw z0--z1--z2--z15;
  draw z2--z14;
  draw z0--z16;
  draw z1--z3--z4--z13;
  draw z4--z5--z12;
  draw z5--z11;
  draw z3--z6--z10;
  draw z6--z7--z9;
  draw z7--z8;

  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z2;
  draw z3;
  draw z4;
  draw z5;
  draw z6;
  draw z7;

  label.bot(btex $a$ etex,z8);
  label.bot(btex $b$ etex,z9);
  label.bot(btex $c$ etex,z10);
  label.bot(btex $x$ etex,z11);
  label.bot(btex $y$ etex,z12);
  label.bot(btex $K$ etex,z13);
  label.bot(btex $I$ etex,z14);
  label.bot(btex $x$ etex,z15);
  label.bot(btex $a$ etex,z16);
  

endfig;

beginfig(6)
  
  numeric u;

  u = 0.4cm;

  z0 = (0,0);       % root
  z1 = (u, -2u);
  z2 = (2u, -4u);
  z3 = (3u, -6u);
  z4 = (4u, -8u);   % a
  z5 = (2u, -8u);   % x
  z6 = (0, -8u);    % S
  z7 = (-2u, -8u);  % K
  z8 = (-4u, -8u);  % S

  draw z0--z1--z2--z3--z4;
  draw z3--z5;
  draw z2--z6;
  draw z1--z7;
  draw z0--z8;
  
  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z2;
  draw z3;

  label.bot(btex $a$ etex,z4);
  label.bot(btex $x$ etex,z5);
  label.bot(btex $S$ etex,z6);
  label.bot(btex $K$ etex,z7);
  label.bot(btex $S$ etex,z8);
  
endfig;

beginfig(7)

  numeric u;

  u = 0.4cm;

  z0 = (0, 0);
  z1 = (-2u, -2u);
  z2 = (-u, -4u);
  z3 = (0, -6u);    % K
  z4 = (-2u, -6u);   % K
  z5 = (-4u, -6u);  % S
  z6 = (2u, -6u);   % x
  z7 = (4u, -6u);   % I
  z8 = (3u, -4u);


  draw z0--z1--z2--z3;
  draw z2--z4;
  draw z1--z5;
  draw z0--z8--z6;
  draw z8--z7;

  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z2;
  draw z8;
  
  label.bot(btex $x$ etex,z6);
  label.bot(btex $I$ etex,z7);
  label.bot(btex $K$ etex,z4);
  label.bot(btex $K$ etex,z3);
  label.bot(btex $S$ etex,z5);
  
endfig;


beginfig(8)

  numeric u;

  u = 0.4cm;

  z0 = (u, u);
  z1 = (-2u, -2u);
  z2 = (-u, -4u);
  z3 = (0, -6u);    % K
  z4 = (-2u, -6u);   % K
  z5 = (-4u, -6u);  % S
  z6 = (2u, -6u);   % y
  z7 = (4u, -6u);   % S
  z8 = (6u, -6u);   % I
  z9 = (3u, -4u);
  z10 = (4u, -2u);


  draw z0--z1--z2--z3;
  draw z2--z4;
  draw z1--z5;
  draw z0--z10--z9--z6;
  draw z9--z7;
  draw z10--z8;

  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z2;
  draw z9;
  draw z10;

  label.bot(btex $y$ etex,z6);
  label.bot(btex $S$ etex,z7);
  label.bot(btex $K$ etex,z4);
  label.bot(btex $K$ etex,z3);
  label.bot(btex $S$ etex,z5);
  label.bot(btex $I$ etex,z8);
  
endfig;

beginfig(9)

  numeric u;

  u = 0.25cm;

  z0 = (0, 0);
  z1 = (-2u, -2u);
  z2 = (-3u, -4u);   %K
  z3 = (-u, -4u);    %K
  z4 = (2u, -2u);
  z5 = (u, -4u);     %x
  z6 = (3u, -4u);    %I

  draw z0--z1--z2;
  draw z1--z3;
  draw z0--z4--z5;
  draw z4--z6;

  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z4;

  label.bot (btex $K$ etex, z2);
  label.bot (btex $K$ etex, z3);
  label.bot (btex $x$ etex, z5);
  label.bot (btex $I$ etex, z6);

endfig;

beginfig(10)

  numeric u;

  u = 0.25cm;

  z0 = (0, 0);
  z1 = (-2u, -2u);
  z2 = (-u, -4u);
  z3 = (0, -6u);    % S
  z4 = (-2u, -6u);  % K
  z5 = (-4u, -6u);  % K
  z6 = (2u, -6u);   % x
  z7 = (4u, -6u);   % I
  z8 = (3u, -4u);


  draw z0--z1--z2--z3;
  draw z2--z4;
  draw z1--z5;
  draw z0--z8--z6;
  draw z8--z7;

  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z2;
  draw z8;
  
  label.bot (btex $x$ etex, z6);
  label.bot (btex $I$ etex, z7);
  label.bot (btex $K$ etex, z4);
  label.bot (btex $K$ etex, z3);
  label.bot (btex $S$ etex, z5);
  
endfig;


beginfig(11)

  numeric u;

  u = 0.5cm;

  z1 = (0, 0);
  z2 = (u, 0);
  z3 = (-u, -2u);
  z4 = (2u, -2u);
  z5 = (-u, -3u);
  z6 = (2u, -3u);
  z7 = (0, -5u);
  z8 = (u, -5u);

  drawarrow z1--z3;
  drawarrow z2--z4;
  drawarrow z5--z7;
  drawarrow z6--z8;

  label.urt (btex $X$ etex, z1);
  label.bot (btex $Y$ etex, z3);
  label.bot (btex $Z$ etex, z4);
  label.lrt (btex $U$ etex, z7);
  
endfig;


beginfig(12)

  numeric u;

  u = 0.25cm;

  z0 = (0, 0);
  z1 = (u, 0);
  z2 = (2u, u);
  z3 = (3u, 0);
  z4 = (4u, u);
  z5 = (5u, 0);
  z6 = (7u, 0);    % X^n
  z7 = (8u, 0);

  z8 = (7u, -7.5u);  % Z
  z9 = (4u, -4u);  % Z'
  z10 = (11u, -3u);% Y
  z11 = (3.2u, -3.5u);
  z12 = (0, -1u);
  z13 = (7.5u, -1u);
  z14 = (4.9u, -3.5u);
  z15 = (4u, -5u);
  z16 = (6.2u, -6.5u);
  z17 = (11u, -4u);
  z18 = (7.9u, -6.5u);
  z19 = (8.3u, -u);
  z20 = (10.2u, -2.5u);

  draw z1--z2--z3--z4;
  drawarrow z12--z11;
  drawarrow z4--z5;
  drawarrow z13--z14;
  drawarrow z15--z16;
  drawarrow z17--z18;
  drawarrow z19--z20;
  

  label (btex $X$ etex, z0);  
  label.rt (btex $X^{(n)}$ etex, z6);
  label(btex $Z$ etex, z8);
  label(btex $Z'$ etex, z9);
  label(btex $Y$ etex, z10);

  
endfig;

beginfig(13)

  numeric u;

  u = 0.25cm;

  z0 = (0, 0);
  z1 = (u, 0);
  z2 = (2u, u);
  z3 = (3u, 0);
  z4 = (4u, u);
  z5 = (5u, 0);
  z6 = (7u, 0);    % X^n
  z7 = (8u, 0);

  z9 = (4u, -4u);  % Z'
  z10 = (11u, -3u);% Y
  z11 = (3.2u, -3.5u);
  z12 = (0, -1u);
  z13 = (7.5u, -1u);
  z14 = (4.9u, -3.5u);
  z15 = (4u, -5u);
  z16 = (6.2u, -6.5u);
  z17 = (11u, -4u);
  z18 = (7.9u, -6.5u);
  z19 = (8.3u, -u);
  z20 = (10.2u, -2.5u);

  draw z1--z2--z3--z4;
  drawarrow z12--z11;
  drawarrow z4--z5;
  drawarrow z13--z14;
  drawarrow z20--z19;
  

  label (btex $X$ etex, z0);  
  label.rt (btex $X^{(n)}$ etex, z6);
  label(btex $Z'$ etex, z9);
  label(btex $Y$ etex, z10);

endfig;


beginfig(14)

  numeric u;

  u = 0.25cm;
  
  z0 = (0,0);
  z1 = (-u, -2u);
  z2 = (u, -2u);

  draw z0--z1;
  draw z0--z2;

  pickup pencircle scaled 2;

  draw z0;

  label.bot (btex $I$ etex,z1);
  label.bot (btex $x$ etex,z2);
endfig;

beginfig(15)

  numeric u;

  u = 0.25cm;
  
  z0 = (0,0);
  z1 = (-u, -2u);
  z2 = (u, -2u);
  z3 = (u, 2u);
  z4 = (3u, -2u);

  draw z0--z1;
  draw z0--z2;
  draw z3--z0;
  draw z3--z4;

  pickup pencircle scaled 2;

  draw z3;

  label.bot (btex $K$ etex,z1);
  label.bot (btex $x$ etex,z2);
  label.bot (btex $Y$ etex, z4);
endfig;

beginfig(16)

  numeric u;

  u = 0.25cm;
  
  z0 = (0,0);
  z1 = (-u, -2u);
  z2 = (u, -2u);
  z3 = (u, 2u);
  z4 = (3u, -2u);
  z5 = (2u, 4u);
  z6 = (5u, -2u);

  draw z0--z1;
  draw z0--z2;
  draw z3--z0;
  draw z3--z4;
  draw z5--z3;
  draw z5--z6;

  pickup pencircle scaled 2;

  draw z5;

  label.bot (btex $S$ etex,z1);
  label.bot (btex $X$ etex,z2);
  label.bot (btex $Y$ etex,z4);
  label.bot (btex $Z$ etex,z6);
  
endfig;

beginfig(17)

  numeric u;

  u = 0.25cm;
  
  z0 = (0,0); 
  z1 = (-u, -2u);
  z2 = (u, -2u);
  z3 = (4u, 0);
  z4 = (3u, -2u);
  z5 = (2u, 4u);
  z6 = (5u, -2u);

  draw z0--z1;
  draw z0--z2;
  draw z3--z4;
  draw z3--z6;
  draw z5--z0;
  draw z5--z3;


  pickup pencircle scaled 2;

  draw z5;

  label.bot (btex $X$ etex,z1);
  label.bot (btex $Z$ etex,z2);
  label.bot (btex $Y$ etex,z4);
  label.bot (btex $Z$ etex,z6);
  
endfig;


beginfig(18)

  numeric u;

  u = 1cm;

  z0 = (0,0);
  z1 = (4u, 0);
  z2 = (4u, 3u);
  z3 = (0, 3u);

  z4 = (0.5u, 1.25u);
  z5 = (u, 1.25u);
  z6 = (u, 1.75u);
  z7 = (0.5u, 1.75u);

  z8 = (3u, 1.25u);
  z9 = (3.5u, 1.25u);
  z10 = (3.5u, 1.75u);
  z11 = (3u, 1.75u);

  z20 = (-0.75u, 1.5u);
  z21 = (0.75u, 1.5u);
  z22 = (3.25u, 1.5u);
  z23 = (4.75u, 1.5u);

  draw z0--z1--z2--z3--z0;
  draw z4--z5--z6--z7--z4;
  draw z8--z9--z10--z11--z8;

  drawarrow z20--z21;
  drawarrow z22--z23;
  
  
endfig;

beginfig(19)

  numeric u;
  path p[];

  u = 1cm;
  
  % Rettangolo
  z0 = (0,0);
  z1 = (4u, 0);
  z2 = (4u, 3u);
  z3 = (0, 3u);
  p1 = z0--z1--z2--z3--cycle;

  % A
  z4 = (0.6u, 0.8u);
  z5 = (1.3u, 1.1u);
  z6 = (1.35u, 2u);
  z7 = (1.25u, 2.7u);
  z8 = (0.3u, 2.65u);
  z9 = (0.4u, u);
  p2 = z4..z5..z6..z7..z8..z9..cycle;

  % B'
  z10 = (0.9u, 0.6u);
  z40 = (2u, 0.4u);
  z11 = (3.4u, 0.5u);
  z12 = (3.7u, 1.1u);
  z13 = (3.7u, 2.6u);
  z14 = (3.1u, 2.75u);
  z15 = (2u, 2.6u);
  z16 = (1.6u, 1.7u);
  z17 = (1.4u, u);
  z18 = (u, 0.7u);
  p3 = z10..z40..z11..z12..z13..z14..z15..z16..z17..z18..cycle;

  % B
  z19 = (2.5u, u);
  z20 = (3.1u, u);
  z21 = (3.3u, 1.4u);
  z22 = (3.28u, 2.5u);
  z23 = (3u, 2.6u);
  z24 = (2.3u, 2.5u);
  z25 = (2u, 1.5u);
  z26 = (2.4u, 1.3u);
  p4 = z19..z20..z21..z22..z23..z24..z25..z26..cycle;

  draw p1;
  draw p2;
  draw p3;
  draw p4;

  label (btex $A$ etex, (0.8u, 1.9u));
  label (btex $B'$ etex, (1.9u, 0.9u));
  label (btex $B$ etex,(2.7u, 1.9u));

  drawarrow (-0.8u, 1.9u)--(0.7u, 1.9u);
  drawarrow (4.8u, 1.9u)--(2.9u, 1.9u);

  label.lft (btex $\varphi(n)=0$ etex, (-0.8u, 1.9u));
  label.rt (btex $\varphi(n)=1$ etex,(4.8u, 1.9u));
  
  
endfig;


beginfig(20)

  numeric u;

  u = 1cm;

  z0 = (0,u);
  z1 = (u,0);
  z2 = (2u,0);
  z3 = (3u,1.5u);

  z4 = (0, 1.5u);
  z5 = (1.5u, u);
  z6 = (1.5u, 1.5u);
  z7 = (1.5u, 3u);

  draw z7--z6--z5--z1;
  draw z7--z4--z0;
  draw z7--z3;
  draw z5--z2;

  label.bot(btex $y$ etex,z0);
  label.bot(btex $z$ etex,z1);
  label.bot(btex $y$ etex,z2);
  label.bot(btex $x$ etex,z3);

  label.lft(btex $x$ etex,z4);
  label.lft(btex $x$ etex,z6);

  pickup pencircle scaled 3;

  draw z6;
  draw z4;
  
endfig;

beginfig(21)

  numeric u;

  u = 1cm;

  z0 = (0,0);
  z1 = (0, -u);
  z2 = (0, -2u);
  z3 = (-0.5u, -3.5u);
  z4 = (0.5u, -3.5u);
  z5 = (0, -2.5u);

  label.bot(btex $z$ etex,z3);
  label.bot(btex $y$ etex,z4);
  label.rt(btex $x$ etex,z0);
  label.rt(btex $y$ etex,z1);
  label.rt(btex $z$ etex,z2);

  draw z0--z1--z2--z5--z3;
  draw z5--z4;
  
  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z2;
  
endfig;


beginfig(22)

  numeric u;

  u = 1cm;

  z0 = (0,0);
  z1 = (3u, 0);
  z3 = (1.5u, 4u);

  z4 = (u,0);
  z5 = (2u,0);
  z6 = (1.5u, 2u);

  draw z0--z1--z3--z0;
  draw z4--z6--z5;

  label.rt(btex $Y$ etex, z3);
  label.top(btex $X$ etex, z6);
  
endfig;

beginfig(23)

  numeric u;
  u = 1cm;

  z0 = (0.5u,0);
  z1 = (0, -u);
  z2 = (u, -u);
  z3 = (u, -1.5u);
  z4 = (0.5u, -2.5u);
  z5 = (1.5u, -2.5u);

  z10 = (-0.8u, -1.7u);
  z20 = (2.5u , -1.7u);
  
  draw z0--z1;
  draw z0--z2--z3--z4;
  draw z3--z5;

  drawarrow z10--(-0.2u, -1.2u);
  drawarrow z20--(1.6u, -2.4u);
  
  label.bot(btex $x$ etex,z1);
  label.bot(btex $y$ etex,z4);
  label.bot(btex $x$ etex,z5);
  label.rt(btex $x$ etex, z2);
  label.bot(btex libera etex, z10);
  label.top(btex vincolata etex, z20);

  pickup pencircle scaled 3;

  draw z2;
  
endfig;

beginfig(24)

  numeric u;

  u = 1cm;

  z0 = (0.5u,0);
  z1 = (0, -u);
  z2 = (u, -u);
  z3 = (u, -1.5u);
  z4 = (0.5u, -2.5u);
  z5 = (1.5u, -2.5u);

  z10 = (0.5u, 0.5u);
  z11 = (u, 1.5u);
  z12 = (1.5u, 0.5u);
  
  draw z0--z1;
  draw z0--z2--z3--z4;
  draw z3--z5;
  draw z11--z10;
  draw z11--z12;
  draw z10--z0;

  label.bot(btex $x$ etex,z1);
  label.bot(btex $y$ etex,z4);
  label.bot(btex $x$ etex,z5);
  label.bot(btex $z$ etex,z12);
  label.rt(btex $y$ etex, z2);
  label.lft(btex $x$ etex,z10);
  
  pickup pencircle scaled 3;

  draw z2;
  draw z10;
  
endfig;

beginfig(25)
numeric u;

  u = 0.4cm;

  z0 = (-u, 0);
  z1 = (-2u, -2u);
  z2 = (-u, -4u);
  z3 = (0, -6u);    % S
  z4 = (-2u, -6u);  % K
  z5 = (-4u, -6u);  % K
  z6 = (2u, -6u);   % x
  z7 = (4u, -6u);   % I
  z8 = (3u, -4u);


  draw z0--z1--z2--z3;
  draw z2--z4;
  draw z1--z5;
  draw z0--z6;
  %draw z8--z7;
  
  label.bot (btex $1$ etex, z6);
  label.bot (btex $-1$ etex, z4);
  label.bot (btex $-2$ etex, z3);
  label.bot (btex $-1$ etex, z5);
  
endfig;


beginfig(26)

  numeric u;
  u = 0.4cm;

  z0 = (0,0);
  z1 = (-u,-2u);
  z2 = (u, -2u);

  draw z0--z1;
  draw z0--z2;

  label.bot (btex $0$ etex, z1);
  label.bot (btex $1$ etex, z2);

  z3 = (6u, -2u);
  z4 = (10u, -2u);
  z5 = (6u, -u);
  z6 = (8u, 2u);

  draw z6--z4;
  draw z6--z5--z3;
  
  pickup pencircle scaled 3;

  draw z5;

  label.rt (btex $x$ etex, z5);
  label.bot (btex $x$ etex, z3);
  label.bot (btex $y$ etex, z4);
  
endfig;


beginfig(27)
  numeric u;
  u = 0.4cm;
  z3 = (8u, -2u);
  z4 = (12u, -2u);
  z5 = (8u, -u);
  z6 = (10u, 2u);

  draw z6--z4;
  draw z6--z5--z3;
  
  pickup pencircle scaled 3;

  draw z5;

  label.rt (btex $z$ etex, z5);
  label.bot (btex $z$ etex, z3);
  label.bot (btex $y$ etex, z4);
  
  
endfig;

beginfig(28)
  numeric u;

  u = 0.7cm;

  z5=(0,-4.5u);
  z6=(-u,-5.5u);
  z7=(-2u,-6.5u);
  z8=(0, -6.5u);
  z9=(2u,-6.5u);

  draw z5--z6--z7;
  draw z6--z8;
  draw z5--z9;
  
  label.bot (btex $-5$ etex, z7);
  label.bot (btex $-3$ etex, z8);
  label.bot (btex $-1$ etex, z9);
  
endfig;

beginfig(29)

  numeric u;
  u = 0.4cm;

  z0=(0,0);
  z1=(0,-u);
  z2=(0,-2u);
  z3=(0,-3u);
  z4=(0,-4u);
  z5=(0,-4.5u);
  z6=(-u,-5.5u);
  z7=(-2u,-6.5u);
  z8=(0, -6.5u);
  z9=(2u,-6.5u);

  draw z0--z1--z2--z3--z4--z5--z6--z7;
  draw z6--z8;
  draw z5--z9;

  label.bot (btex $x$ etex, z7);
  label.bot (btex $y$ etex, z8);
  label.bot (btex $v$ etex, z9);

  label.lft (btex $x$ etex, z0);
  label.lft (btex $w$ etex, z1);
  label.lft (btex $y$ etex, z2);
  label.lft (btex $u$ etex, z3);
  label.lft (btex $v$ etex, z4);

  pickup pencircle scaled 3;

  draw z0;
  draw z1;
  draw z2;
  draw z3;
  draw z4;
  
endfig;


beginfig(30)

  numeric u;
  u = 0.6cm;

  z0=(0,0); %root
  z1=(0.5u, -u); %x
  z2=(0.5u, -1.5u);
  z3=(0, -2.5u);
  z4=(-0.5u, -3.5u); %x
  z5=(0.5u, -3.5u); %z
  z6=(1.5u, -3.5u); %y
  z7=(-1.5u, -3.5u); %y

  draw z0--z1--z2--z3--z4;
  draw z3--z5;
  draw z2--z6;
  draw z0--z7;
  
  label.bot (btex $y$ etex, z7);
  label.bot (btex $x$ etex, z4);
  label.bot (btex $z$ etex, z5);
  label.bot (btex $y$ etex, z6);
  label.rt (btex $x$ etex, z1);

  pickup pencircle scaled 3;

  draw z1;
  
endfig;

beginfig(31)

  numeric u;
  u = 0.4cm;

  z0=(0,0); 
  z1=(0, -u); 

  draw z0--z1;
  
  label.top (btex $u$ etex, z0);
  label.bot (btex $v$ etex, z1);

endfig;

beginfig(32)

  numeric u;
  path p[];

  u = 1cm;

  z0=(0,0);
  z1=(3u,-1.5u);
  z2=(6u,0);
  z3=(3u, 1.5u);

  z4=(4u,0);
  z5=(7u,-1.5u);
  z6=(10u,0);
  z7=(7u,1.5u);

  p1 = z0..z1..z2..z3..cycle;
  p2 = z4..z5..z6..z7..cycle;

  draw p1;
  draw p2;

  z10=(5u,0);
  z20=(2u,0);
  z30=(8u,0);

  label(btex bijection etex, z10);
  label(btex inijection etex, z20);
  label(btex surjection etex, z30);

  
endfig;

beginfig(33)

  numeric u;

  u = 0.6cm;

  z0 = (0, 2u);
  z1 = (-2u, -2u);
  z2 = (-3u, -4u);   
  z3 = (-u, -4u);    
  z4 = (2u, -2u);
  z5 = (u, -4u);     
  z6 = (3u, -4u);    

  draw z0--z1--z2;
  draw z1--z3;
  draw z0--z4--z5;
  draw z4--z6;

  pickup pencircle scaled 2;

  draw z0;
  draw z1;
  draw z4;

  label.bot (btex $360$ etex, z2);
  label.bot (btex $At1$ etex, z3);
  label.bot (btex $At1$ etex, z5);
  label.bot (btex $Nil$ etex, z6);
  label.lft (btex $325$ etex, z1);
  label.rt  (btex $411$ etex, z4);

endfig;

beginfig(34)

  numeric u;
  u = 1cm;

  z0 = (0.5u,-0.5u);
  z1 = (u, -1.5u);
  z2 = (-0.5u, -2.5u);
  z4 = (0.5u, -2.5u);
  z5 = (1.5u, -2.5u);
  
  draw z0--z1--z4;
  draw z1--z5;
  draw z0--z2;
  
  label.bot(btex $At2$ etex,z4);
  label.bot(btex $Nil$ etex,z5);
  label.bot(btex $At1$ etex, z2);

  pickup pencircle scaled 2;

  draw z0;
  draw z1;
  
endfig;


beginfig(35)

  numeric u;
  path p[];

  u = 1cm;

  z0 = (0,0);
  z1 = -z5 = (u,0);
  z2 = (u, 0.5u);
  z3 = (0, 0.5u);
  z4 = (-u, 0.5u);

 
  z6 = (1.5u, -0.5u);
  z7 = (2.5u, -0.5u);
  z8 = (2.5u, -u);
  z9 = (1.5u, -u);
  z10 = (0.5u, -u);
  z11 =(0.5u, -0.5u);

  p1 = z0--z1--z2--z3--z0--z5--z4--z3--cycle;
  p2 = z8--z7--z6--z8--z9--z6--z11--z10--cycle;

  draw p1;
  draw p2;
  drawarrow (0.5u, 0.25u)--z11*1.4;

  label (btex $At1$ etex, (-0.5u, 0.25u));
  label (btex $At2$ etex, (u, -0.75u));

  
endfig;


beginfig(36)

  numeric u;
  path p[];

  u = 1cm;

  z0 = (0,0);
  z1 = -z5 = (u,0);
  z2 = (u, 0.5u);
  z3 = (0, 0.5u);
  z4 = (-u, 0.5u);

 
  z6 = (1.5u, -0.5u);
  z7 = (2.5u, -0.5u);
  z8 = (2.5u, -u);
  z9 = (1.5u, -u);
  z10 = (0.5u, -u);
  z11 =(0.5u, -0.5u);

  

  p1 = z0--z1--z2--z3--z0--z5--z4--z3--cycle;
  p2 = z8--z7--z6--z8--z9--z6--z11--z10--cycle;

  draw p1;
  draw p2;
  drawarrow (0.5u, 0.25u)--(u, -0.5u);

  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  z20 = (0,-2u);
  z21 = (u,-2u);
  z22 = (u, -1.5u);
  z23 = (0, -1.5u);
  z24 = (-u, -1.5u);
  z25 = ( -u, -2u);

 
  z26 = (1.5u, -2.5u);
  z27 = (2.5u, -2.5u);
  z28 = (2.5u, -3u);
  z29 = (1.5u, -3u);
  z30 = (0.5u, -3u);
  z31 =(0.5u, -2.5u);

  

  p3 = z20--z21--z22--z23--z20--z25--z24--z23--cycle;
  p4 = z28--z27--z26--z28--z29--z26--z31--z30--cycle;

  draw p3;
  draw p4;
  drawarrow (0.5u, -1.75u)--(u, -2.5u);
  drawarrow (u,-0.75u)--(-0.25u, -1.5u);

  label (btex $At1$ etex, (-0.5u, 0.25u));
  label (btex $At2$ etex, (-0.5u, -1.75u));
  label (btex $At1$ etex, (u, -2.75u));
  
endfig;


beginfig(37)

  numeric u;

  u = 1cm;

  z0 = (0,u);
  z1 = (u,0);
  z2 = (2u,0);
  z3 = (3u,1.5u);

  z4 = (0, 1.5u);
  z5 = (1.5u, u);
  z6 = (1.5u, 1.5u);
  z7 = (1.5u, 3u);

  draw z7--z5--z1;
  draw z7--z4--z0;
  draw z7--z3;
  draw z5--z2;

  label.bot(btex $n9$ etex,z0);
  label.bot(btex $n6$ etex,z1);
  label.bot(btex $n7$ etex,z2);
  label.bot(btex $n4$ etex,z3);

  label.lft(btex $n2$ etex,z4);
  label.lft(btex $n3$ etex,z5);
  label.lft(btex $n1$ etex,z7);

  pickup pencircle scaled 2;

  draw z4;
  draw z0;
  draw z1;
  draw z2;
  draw z3;
  draw z5;
  draw z7;
  
endfig;

beginfig(38)

  numeric u;
  u = 0.75cm;

  z0 = (0,0);
  z1 = (u,0);
  z2 = (2u,0);
  z3 = (2u,-0.5u);
  z4 = (u,-0.5u);
  z5 = (0,-0.5u);

  draw z0--z1--z2--z3--z4--z5--z0;
  draw z1--z4;
%%%%%%%%%%%

  z6 = (2u,-0.75u);
  z7 = (3u,-0.75u);
  z8 = (4u,-0.75u);
  z9 = (4u,-1.25u);
  z10 = (3u,-1.25u);
  z11 = (2u,-1.25u);

  draw z6--z7--z8--z9--z10--z11--z6;
  draw z7--z10;
%%%%%%%%%%%

  z12 = (2u,-1.50u);
  z13 = (3u,-1.50u);
  z14 = (4u,-1.50u);
  z15 = (4u,-2u);
  z16 = (3u,-2u);
  z17 = (2u,-2u);

  draw z12--z13--z14--z15--z16--z17--z12;
  draw z13--z16;
%%%%%%%%%%%

  z18 = (4.5u,-0.75u);
  z19 = (5.5u,-0.75u);
  z20 = (6.5u,-0.75u);
  z21 = (6.5u,-1.25u);
  z22 = (5.5u,-1.25u);
  z23 = (4.5u,-1.25u);

  draw z18--z19--z20--z21--z22--z23--z18;
  draw z19--z22;
%%%%%%%%%%%

  z24 = (4.5u,-1.50u);
  z25 = (5.5u,-1.50u);
  z26 = (6.5u,-1.50u);
  z27 = (6.5u,-2u);
  z28 = (5.5u,-2u);
  z29 = (4.5u,-2u);

  draw z24--z25--z26--z27--z28--z29--z24;
  draw z25--z28;
%%%%%%%%%%%

  z30 = (7u,-0.75u);
  z31 = (8u,-0.75u);
  z32 = (9u,-0.75u);
  z33 = (9u,-1.25u);
  z34 = (8u,-1.25u);
  z35 = (7u,-1.25u);

  draw z30--z31--z32--z33--z34--z35--z30;
  draw z31--z34;
%%%%%%%%%%%

  z36 = (7u,-1.50u);
  z37 = (8u,-1.50u);
  z38 = (9u,-1.50u);
  z39 = (9u,-2u);
  z40 = (8u,-2u);
  z41 = (7u,-2u);

  draw z36--z37--z38--z39--z40--z41--z36;
  draw z37--z40;
%%%%%%%%%%%

  z42 = (9.5u,-0.75u);
  z43 = (10.5u,-0.75u);
  z44 = (11.5u,-0.75u);
  z45 = (11.5u,-1.25u);
  z46 = (10.5u,-1.25u);
  z47 = (9.5u,-1.25u);

  draw z42--z43--z44--z45--z46--z47--z42;
  draw z43--z46;
  draw z43--z45;
%%%%%%%%%%%

  z48 = (9.5u,-1.50u);
  z49 = (10.5u,-1.50u);
  z50 = (11.5u,-1.50u);
  z51 = (11.5u,-2u);
  z52 = (10.5u,-2u);
  z53 = (9.5u,-2u);

  draw z48--z49--z50--z51--z52--z53--z48;
  draw z49--z52;
  draw z49--z51;
%%%%%%%%%%%

  z54 =(0.5u, -0.25u);
  z55 =(0.5u,-1.75u);
  z56 =(1.98u,-1.75u);

  draw z54--z55;
  drawarrow z55--z56;

  z57 =(1.5u,-0.25u);
  z58 =(1.5u,-u);
  z59 =(1.98u,-u);

  draw z57--z58;
  drawarrow z58--z59;


  z60 = (3.5u,-1.75u);
  z61 = (4.499u,-1.75u);
  drawarrow z60--z61;

  z62 = (6u,-1.75u);
  z63 = (6.999u,-1.75u);
  drawarrow z62--z63;

  z64 = (8.5u,-1.75u);
  z65 = (9.499u,-1.75u);
  drawarrow z64--z65;

  z66 = (3.5u,-u);
  z67 = (4.499u,-u);
  drawarrow z66--z67;

  z68 = (6u,-u);
  z69 = (6.999u,-u);
  drawarrow z68--z69;

  z70 = (8.5u,-u);
  z71 = (9.499u,-u);
  drawarrow z70--z71;

  
  
endfig;



beginfig(39)

  numeric u;
  u = 0.55cm;

  z0 = (0,0);
  z1 = (u,0);
  z2 = (2u,0);
  z3 = (2u,-0.5u);
  z4 = (u,-0.5u);
  z5 = (0,-0.5u);

  draw z0--z1--z2--z3--z4--z5--z0;
  draw z1--z4;

  z54 =(0.5u, -0.25u);
  z55 =(0.5u,-1.75u);
  z56 =(1.98u,-1.75u);

  draw z54--z55;
  drawarrow z55--z56;
  
  z57 =(1.5u,-0.25u);
  z58 =(1.5u,-u);
  z59 =(1.98u,-u);

  draw z57--z58;
  drawarrow z58--z59;

  label.rt (btex $a$ etex,z56);
  label.rt (btex $b$ etex,z59);

endfig;


beginfig(40)

  numeric u;
  path p[];

  u = 1cm;

  z0 = (0,0);
  z1 = -z5 = (u,0);
  z2 = (u, 0.5u);
  z3 = (0, 0.5u);
  z4 = (-u, 0.5u);
  
  z30 = (-0.5u, 0.25u);
  z33 = (-u, -0.45u);
  drawarrow z30--z33;
  label.ulft (btex $sx$ etex, z33);
 
  z6 = (1.5u, -0.5u);
  z7 = (2.5u, -0.5u);
  z8 = (2.5u, -u);
  z9 = (1.5u, -u);
  z10 = (0.5u, -u);
  z11 =(0.5u, -0.5u);

  p1 = z0--z1--z2--z3--z0--z5--z4--z3--cycle;
  p2 = z8--z7--z6--z8--z9--z6--z11--z10--cycle;

  draw p1;
  draw p2;
  drawarrow (0.5u, 0.25u)--(u,-0.45u);
  label.top (btex $A$ etex, z3);

  z12 = (-1.5u, -0.5u);
  z13 = (-2.5u, -0.5u);
  z14 = (-2.5u, -u);
  z15 = (-1.5u, -u);
  z16 = (-0.5u, -u);
  z17 =(-0.5u, -0.5u);
  p3 = z14--z13--z12--z15--z12--z17--z16--cycle;

  z31 = (-2u, -0.75u);
  z34 = (-2.5u, -1.45u);
  drawarrow z31--z34;
  label.ulft (btex $sx$ etex, z34);
  
  draw p3;

  z18 = (-3u, -1.5u);
  z19 = (-4u, -1.5u);
  z20 = (-4u, -2u);
  z21 = (-3u, -2u);
  z22 = (-2u, -2u);
  z23 =(-2u, -1.5u);
  p4 = z20--z19--z18--z21--z18--z23--z22--cycle;

  z32 = (-2.5u, -1.75u);
  z35 = (-2u,-2.45u);
  drawarrow z32--z35;
  label.urt (btex $dx$ etex, z35);
  
  draw p4;

  z24 = (-1.5u, -2.5u);
  z25 = (-2.5u, -2.5u);
  z26 = (-2.5u, -3u);
  z27 = (-1.5u, -3u);
  z28 = (-0.5u, -3u);
  z29 =(-0.5u, -2.5u);
  p5 = z26--z25--z24--z27--z24--z29--z28--cycle;

  
  draw p5;

  label.urt (btex $CAADR(A)$ etex, z29);
endfig;

