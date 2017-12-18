{This is  test program}
x := 12;
y := 1;
while !(x = 1) do (
    write (x);
    y := y * x;
    x := (x - 1)
);
write(y);
writeln