unit rational;
interface 

type rat = record 
  chisl, znam : integer;
  end;
procedure ReadF(var res: rat);
procedure WriteF(var res: rat);
procedure Add(var a, b: rat);
procedure Substract(var a, b: rat);
procedure Mult(var a, b: rat);
procedure Divide(var a, b: rat);

implementation

function НОК(n, m:integer) : integer;
begin
  var c := n*m;
  repeat
    if n > m then n := n-m else m := m-n;
  until n = m;
  НОК := c div n;
end;

function НОД(n, m: integer) : integer;
begin
 while n<>m do if m>n then m:=m-n else n:=n-m;
 нод:=m;
end;

procedure Сокращение(res: rat);
begin
  var d := НОД(res.chisl, res.znam);
  var целаячасть := res.chisl div res.znam;
  if целаячасть <> 0 then print($'{целаячасть}*({(res.chisl - res.znam*целаячасть) div d}/{res.znam div d})')
  else print($'{res.chisl div d}/{res.znam div d}');
end;

procedure ReadF;
begin
  (res.chisl, res.znam) := readinteger2('Введите числитель и знаменатель через пробел:');
end;

procedure WriteF;
begin
  print($'{res.chisl}/{res.znam}');
end;

procedure Add;
begin
  var res : rat;
  if (a.znam = b.znam) then begin
    res.znam := a.znam;
    res.chisl := a.chisl + b.chisl;
  end
  else begin
    res.chisl := a.chisl*b.znam + b.chisl*a.znam;
    res.znam := a.znam*b.znam;
  end;
  print($'{a.chisl}/{a.znam} + {b.chisl}/{b.znam} =');
  Сокращение(res);
end;

procedure Substract;
begin
  var res: rat;
  if (a.znam = b.znam) then begin
    res.znam := a.znam;
    res.chisl := a.chisl - b.chisl;
  end
  else begin
    res.znam := НОК(a.znam, b.znam);
    var t1 := res.znam/a.znam;
    var t2 := res.znam/b.znam;
    res.chisl := trunc((a.chisl*t1)-(b.chisl*t2));
  end;
  print($'{a.chisl}/{a.znam} - {b.chisl}/{b.znam} =');
  Сокращение(res);
end;

procedure Mult;
begin
  var res: rat;
  res.chisl := a.chisl*b.chisl;
  res.znam := a.znam*b.znam;
  print($'{a.chisl}/{a.znam} * {b.chisl}/{b.znam} =');
  Сокращение(res);
end;

procedure Divide;
begin
  var res: rat;
  res.chisl := a.chisl*b.znam;
  res.znam := a.znam*b.chisl;
  print($'{a.chisl}/{a.znam} : {b.chisl}/{b.znam} =');
  Сокращение(res);
end;
end.
