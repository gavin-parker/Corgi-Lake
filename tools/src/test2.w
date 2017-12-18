def testFun(x y) (
    write(x);
    write(x);
    write(y);
    y := 5;
)
x := 1;
y := 2;
z := testFun(x y);
write(z);