def print(x) (
    write(x);
)

def testFun(x) (
    if (x = 2) then (
        print(x);
        x := 5;
    ) else (
        print(x);
        x := 2;
    );
)
x := 1;
y := 2;
z := testFun(y);
print(z);
z := testFun(z);
print(z);