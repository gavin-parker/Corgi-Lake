{This is  test program}
def testFun(a b) (
    write(a);
    write(b);
)
x := 12;
y := 1;
while !(x = 1) do (
    testFun (x y);
    y := y * x;
    x := (x - 1);
);
write(y);
writeln;