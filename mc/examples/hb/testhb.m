lev = 5;
minlev = 1;

Amat;
Anodal = A;
clear A A_00 A_00_IJA;

Ahb = zeros(size(Anodal));

for i=lev:-1:(minlev+1)
  eval(['Ahb_' num2str(i) ';']);
  [n m] = size(A21);
  Ahb((m+1):(m+n),1:m) = A21;
  Ahb(1:m,(m+1):(m+n)) = A12;
  Ahb((m+1):(m+n),(m+1):(m+n)) = A22;
  clear A12_00 A12_00_IJA A12;
  clear A21_00 A21_00_IJA A21;
  clear A22_00 A22_00_IJA A22;
end

eval(['Ahb_' num2str(minlev) ';']);
[n n] = size(A11);
Ahb(1:n,1:n) = A11;
clear A11_00 A11_00_IJA A11;

sparse(Ahb - Ahb')

clear n m;

for i=lev:-1:(minlev+1)
  eval(['Ghb_' num2str(i) ';']);
  [n m] = size(G21);
  S = eye(n+m,n+m);
  S((m+1):(m+n),1:m) = S((m+1):(m+n),1:m) + G21;
  S(1:m,(m+1):(m+n)) = S(1:m,(m+1):(m+n)) + G12;
  S((m+1):(m+n),(m+1):(m+n)) = S((m+1):(m+n),(m+1):(m+n)) + G22;
  eval(['S_' num2str(i) num2str(i-1) ' = S;']);
  
  clear G21_00 G21_00_IJA G21 S;
  clear G12_00 G12_00_IJA G12;
  clear G22_00 G22_00_IJA G22;
end

clear n m;

Atest = Anodal;

for i=lev:-1:(minlev+1)
  eval(['S = S_' num2str(i) num2str(i-1) ';']);
  [n n] = size(S);
  Atest(1:n,1:n) = S'*Atest(1:n,1:n)*S;
end

clear S n i;

