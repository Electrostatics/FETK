%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% MC = < Manifold Code >
%%% Copyright (C) 1994-- Michael Holst 
%%%
%%% This library is free software; you can redistribute it and/or 
%%% modify it under the terms of the GNU Lesser General Public 
%%% License as published by the Free Software Foundation; either  
%%% version 2.1 of the License, or (at your option) any later version. 
%%%
%%% This library is distributed in the hope that it will be useful, 
%%% but WITHOUT ANY WARRANTY; without even the implied warranty of             
%%% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
%%% Lesser General Public License for more details. 
%%%
%%% You should have received a copy of the GNU Lesser General Public 
%%% License along with this library; if not, write to the Free Software  
%%% Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mcsf_begin=1;

      dim=2;    % intrinsic manifold dimension
    dimii=3;    % imbedding manifold dimension
 vertices=97;    % number of vertices
simplices=148;    % number of simplices

vert=[
%-------- ---- ----------------- ----------------- -----------------
% Vert-ID Chrt X0-Coordinate     X1-Coordinate     X2-Coordinate
%-------- ---- ----------------- ----------------- -----------------
0         0     0.0000000000e+00  0.0000000000e+00  0.0000000000e+00
1         0     8.4516028073e-01 -2.0313504280e-01  0.0000000000e+00
2         0     1.7643017780e+00 -6.3762906693e-01  0.0000000000e+00
3         0     2.7474951151e+00 -1.1677204029e+00  0.0000000000e+00
4         0     3.7926969480e+00 -1.6692614231e+00  0.0000000000e+00
5         0     4.9066486500e+00 -2.0104068569e+00  0.0000000000e+00
6         0     6.0659869078e+00 -2.0489974343e+00  0.0000000000e+00
7         0     7.2025688862e+00 -1.7623995571e+00  0.0000000000e+00
8         0     8.2930898680e+00 -1.2473748358e+00  0.0000000000e+00
9         0     9.3388902376e+00 -5.9519644440e-01  0.0000000000e+00
10        0     1.0349815963e+01  9.8090781056e-02  0.0000000000e+00
11        0     0.0000000000e+00  1.0000000000e+00  0.0000000000e+00
12        0     1.1548397193e+00  7.9686495608e-01  0.0000000000e+00
13        0     2.2356981922e+00  3.6237087133e-01  0.0000000000e+00
14        0     3.2525041121e+00 -1.6772215184e-01  0.0000000000e+00
15        0     4.2073156549e+00 -6.6913575979e-01  0.0000000000e+00
16        0     5.0955170920e+00 -1.0160164982e+00  0.0000000000e+00
17        0     5.9403806922e+00 -1.0546070715e+00  0.0000000000e+00
18        0     6.8059514657e+00 -7.6227458582e-01  0.0000000000e+00
19        0     7.7154490818e+00 -2.4732705058e-01  0.0000000000e+00
20        0     8.6705139250e+00  4.0261141503e-01  0.0000000000e+00
21        0     9.6621897623e+00  1.0935769263e+00  0.0000000000e+00
22        0     4.9999999995e-01  4.4918009662e-01  0.0000000000e+00
23        0     3.5000042875e+00 -9.3409957217e-01  0.0000000000e+00
24        0     4.4995887309e+00 -1.3801696552e+00  0.0000000000e+00
25        0     5.5021333328e+00 -1.5925385441e+00  0.0000000000e+00
26        0     6.5046779370e+00 -1.4538932738e+00  0.0000000000e+00
27        0     7.5042640853e+00 -1.0362681978e+00  0.0000000000e+00
28        0     8.5041039766e+00 -4.3766743298e-01  0.0000000000e+00
29        0     9.5049496432e+00  2.4851200213e-01  0.0000000000e+00
30        0     4.1645029081e-01 -6.9301234429e-02  0.0000000000e+00
31        0     5.8354970928e-01  9.3069876557e-01  0.0000000000e+00
32        0     1.5000000040e+00  1.0798412011e-01  0.0000000000e+00
33        0     2.5000000820e+00 -3.9718786992e-01  0.0000000000e+00
34        0     3.2615690095e+00 -1.4296474946e+00  0.0000000000e+00
35        0     3.7384221501e+00 -4.2964297554e-01  0.0000000000e+00
36        0     4.3411187633e+00 -1.8691152581e+00  0.0000000000e+00
37        0     4.6594648459e+00 -8.6875739718e-01  0.0000000000e+00
38        0     5.4849034402e+00 -2.0738956660e+00  0.0000000000e+00
39        0     5.5193632267e+00 -1.0855914884e+00  0.0000000000e+00
40        0     6.6400023652e+00 -1.9406401123e+00  0.0000000000e+00
41        0     6.3679473863e+00 -9.4028234010e-01  0.0000000000e+00
42        0     7.7534843256e+00 -1.5274676446e+00  0.0000000000e+00
43        0     7.2550543497e+00 -5.2746135452e-01  0.0000000000e+00
44        0     8.8214667268e+00 -9.3343470170e-01  0.0000000000e+00
45        0     8.1872962951e+00  6.6709962378e-02  0.0000000000e+00
46        0     9.8469947738e+00 -2.4739688824e-01  0.0000000000e+00
47        0     9.1634847700e+00  7.4807967282e-01  0.0000000000e+00
48        0     1.0000000002e+00  3.0805304845e-01  0.0000000000e+00
49        0     3.9999682526e+00 -1.1768535681e+00  0.0000000000e+00
50        0     4.9998188440e+00 -1.5260729962e+00  0.0000000000e+00
51        0     6.0044478168e+00 -1.5657637967e+00  0.0000000000e+00
52        0     7.0042987700e+00 -1.2733002765e+00  0.0000000000e+00
53        0     8.0042534334e+00 -7.5396542077e-01  0.0000000000e+00
54        0     1.0005943804e+01  5.9468288116e-01  0.0000000000e+00
55        0     0.0000000000e+00  5.0000000000e-01  0.0000000000e+00
56        0     2.3157019650e-01  2.3108004921e-01  0.0000000000e+00
57        0     8.1056720276e-01  6.3067927118e-01  0.0000000000e+00
58        0     1.2909363256e+00 -4.0354093212e-01  0.0000000000e+00
59        0     1.7090636693e+00  5.9645906263e-01  0.0000000000e+00
60        0     2.2509966517e+00 -9.0097514981e-01  0.0000000000e+00
61        0     2.7490032767e+00  9.9024748954e-02  0.0000000000e+00
62        0     3.1267817362e+00 -1.0518681893e+00  0.0000000000e+00
63        0     3.8618612580e+00 -8.0656467903e-01  0.0000000000e+00
64        0     4.1578827678e+00 -1.5303395156e+00  0.0000000000e+00
65        0     4.8134170910e+00 -1.2062884275e+00  0.0000000000e+00
66        0     5.2229802238e+00 -1.8108269601e+00  0.0000000000e+00
67        0     5.7421410636e+00 -1.3354359989e+00  0.0000000000e+00
68        0     6.3042459377e+00 -1.7621355342e+00  0.0000000000e+00
69        0     6.6703751074e+00 -1.1156313363e+00  0.0000000000e+00
70        0     7.3664332942e+00 -1.4066342015e+00  0.0000000000e+00
71        0     7.6194668768e+00 -6.4652074741e-01  0.0000000000e+00
72        0     8.4060420456e+00 -8.4690399084e-01  0.0000000000e+00
73        0     8.5911671467e+00 -1.9099265395e-02  0.0000000000e+00
74        0     9.4237268391e+00 -1.7426666119e-01  0.0000000000e+00
75        0     9.5840524170e+00  6.7090845991e-01  0.0000000000e+00
76        0     6.8943279720e-01  1.3067927152e-01  0.0000000000e+00
77        0     4.3420756543e+00 -1.0300417662e+00  0.0000000000e+00
78        0     4.6861804834e+00 -1.7051246721e+00  0.0000000000e+00
79        0     5.2787946342e+00 -1.3154895033e+00  0.0000000000e+00
80        0     5.7646174111e+00 -1.8307734592e+00  0.0000000000e+00
81        0     6.2046898156e+00 -1.2632993102e+00  0.0000000000e+00
82        0     6.8381998143e+00 -1.6159287421e+00  0.0000000000e+00
83        0     7.1420971082e+00 -9.0658972485e-01  0.0000000000e+00
84        0     7.8890668068e+00 -1.1465371357e+00  0.0000000000e+00
85        0     9.9270168984e+00  1.7322923809e-01  0.0000000000e+00
86        0     2.6842980350e-01  7.3108004924e-01  0.0000000000e+00
87        0     1.3409310390e+00  4.5955092796e-01  0.0000000000e+00
88        0     2.0000000294e+00 -1.3926102436e-01  0.0000000000e+00
89        0     3.6381420623e+00 -1.3066096599e+00  0.0000000000e+00
90        0     3.3732192339e+00 -5.5186949913e-01  0.0000000000e+00
91        0     8.9172066558e+00 -5.1865202933e-01  0.0000000000e+00
92        0     8.1024750352e+00 -3.4678633256e-01  0.0000000000e+00
93        0     9.0854996593e+00  3.2399316043e-01  0.0000000000e+00
94        0     1.1590689613e+00 -4.0449068758e-02  0.0000000000e+00
95        0     3.0000007923e+00 -6.6852103253e-01  0.0000000000e+00
96        0     9.0041815267e+00 -9.9082963391e-02  0.0000000000e+00
];

simp=[
%-------- ---- ---- ------------------- ---------------------------------------
% Simp-ID Grp  Mat  Face-Types          Vertex-Numbers
%-------- ---- ---- ------------------- ---------------------------------------
0         0    0    0    0    0         22 56 30
1         0    0    0    0    0         22 57 31
2         0    0    0    0    0         32 94 58
3         0    0    0    0    2         13 59 32
4         0    0    0    0    2         2 60 33
5         0    0    0    0    2         14 61 33
6         0    0    0    0    0         23 62 34
7         0    0    0    0    0         23 63 35
8         0    0    0    0    0         24 64 36
9         0    0    0    0    0         24 65 37
10        0    1    0    0    0         25 66 38
11        1    1    0    0    0         25 67 39
12        0    0    0    0    0         26 68 40
13        0    0    0    0    0         26 69 41
14        0    0    0    0    0         27 70 42
15        0    0    0    0    0         27 71 43
16        0    0    0    0    0         28 72 44
17        0    0    0    0    0         28 73 45
18        2    2    0    0    0         29 74 46
19        0    2    0    0    0         29 75 47
20        0    0    0    0    0         22 76 48
21        0    0    0    0    0         23 89 49
22        0    0    0    0    0         24 77 49
23        0    0    0    0    0         24 78 50
24        0    1    0    0    0         25 79 50
25        1    1    0    0    0         25 80 51
26        0    0    0    0    0         26 81 51
27        0    0    0    0    0         26 82 52
28        0    0    0    0    0         27 83 52
29        0    0    0    0    0         27 84 53
30        0    0    0    0    0         28 92 53
31        0    0    0    0    0         28 91 96
32        2    2    0    0    0         29 93 96
33        0    2    0    0    0         29 85 54
34        0    0    0    0    0         22 86 55
35        0    0    0    0    0         23 90 95
36        0    0    0    2    0         1 76 30
37        0    0    0    2    0         11 86 31
38        0    0    0    0    0         32 87 48
39        0    0    0    0    0         2 88 32
40        0    0    0    0    0         13 88 33
41        0    0    0    0    0         3 95 33
42        0    0    0    2    0         4 89 34
43        0    0    0    2    0         14 90 35
44        0    0    0    2    0         5 78 36
45        0    0    0    2    0         15 77 37
46        0    1    0    2    0         6 80 38
47        1    1    0    4    0         16 79 39
48        0    0    0    2    0         7 82 40
49        0    0    0    2    0         17 81 41
50        0    0    0    2    0         8 84 42
51        0    0    0    2    0         18 83 43
52        0    0    0    2    0         9 91 44
53        0    0    0    2    0         19 92 45
54        2    2    0    6    0         10 85 46
55        0    2    0    2    0         20 93 47
56        0    0    0    0    0         12 57 48
57        0    0    0    0    0         4 64 49
58        0    0    0    0    0         16 65 50
59        0    1    0    0    0         5 66 50
60        1    1    0    0    0         17 67 51
61        0    0    0    0    0         6 68 51
62        0    0    0    0    0         18 69 52
63        0    0    0    0    0         7 70 52
64        0    0    0    0    0         19 71 53
65        0    2    0    2    0         21 75 54
66        0    0    0    1    0         0 56 55
67        0    0    0    0    0         1 94 48
68        0    0    0    0    0         15 63 49
69        0    0    0    0    0         8 72 53
70        0    0    0    0    2         0 30 56
71        0    0    0    0    2         12 31 57
72        0    0    0    2    0         2 32 58
73        0    0    0    2    0         12 87 59
74        0    0    0    2    0         3 33 60
75        0    0    0    2    0         13 33 61
76        0    0    0    0    2         3 34 62
77        0    0    0    0    2         15 35 63
78        0    0    0    0    2         4 36 64
79        0    0    0    0    2         16 37 65
80        0    1    0    0    2         5 38 66
81        1    1    0    0    4         17 39 67
82        0    0    0    0    2         6 40 68
83        0    0    0    0    2         18 41 69
84        0    0    0    0    2         7 42 70
85        0    0    0    0    2         19 43 71
86        0    0    0    0    2         8 44 72
87        0    0    0    0    2         20 45 73
88        2    2    0    0    6         9 46 74
89        0    2    0    0    2         21 47 75
90        0    0    0    0    0         1 48 76
91        0    0    0    0    0         15 49 77
92        0    0    0    0    0         5 50 78
93        0    1    0    0    0         16 50 79
94        1    1    0    0    0         6 51 80
95        0    0    0    0    0         17 51 81
96        0    0    0    0    0         7 52 82
97        0    0    0    0    0         18 52 83
98        0    0    0    0    0         8 53 84
99        0    2    0    0    2         10 54 85
100       0    0    0    0    1         11 55 86
101       0    0    0    0    0         22 30 76
102       0    0    0    0    0         22 31 86
103       0    0    0    0    0         12 48 87
104       0    0    0    0    0         13 32 88
105       0    0    0    0    0         23 34 89
106       0    0    0    0    0         23 35 90
107       0    0    0    0    0         24 36 78
108       0    0    0    0    0         24 37 77
109       0    1    0    0    0         25 38 80
110       1    1    0    0    0         25 39 79
111       0    0    0    0    0         26 40 82
112       0    0    0    0    0         26 41 81
113       0    0    0    0    0         27 42 84
114       0    0    0    0    0         27 43 83
115       0    0    0    0    0         28 44 91
116       0    0    0    0    0         28 45 92
117       2    2    0    0    0         29 46 85
118       0    2    0    0    0         29 47 93
119       0    0    0    0    0         22 48 57
120       0    0    0    0    0         24 49 64
121       0    0    0    0    0         24 50 65
122       0    1    0    0    0         25 50 66
123       1    1    0    0    0         25 51 67
124       0    0    0    0    0         26 51 68
125       0    0    0    0    0         26 52 69
126       0    0    0    0    0         27 52 70
127       0    0    0    0    0         27 53 71
128       0    2    0    0    0         29 54 75
129       0    0    0    0    0         22 55 56
130       0    0    0    0    0         32 48 94
131       0    0    0    0    0         3 62 95
132       0    0    0    0    0         23 49 63
133       0    0    0    0    0         28 53 72
134       0    0    0    0    0         20 73 96
135       2    2    0    0    0         9 74 96
136       0    0    0    0    0         32 59 87
137       0    0    0    0    0         2 33 88
138       0    0    0    0    0         4 49 89
139       0    0    0    0    0         19 53 92
140       0    0    0    0    2         1 58 94
141       0    0    0    0    0         14 33 95
142       0    0    0    0    0         14 95 90
143       0    0    0    0    0         23 95 62
144       0    0    0    0    0         9 96 91
145       0    0    0    0    0         28 96 73
146       2    2    0    0    0         20 96 93
147       2    2    0    0    0         29 96 74
];

mcsf_end=1;

