{Computes the first 500 fib numbers}
def fib(n) (
    if (n < 2) then (
        e := n;
    ) else (
        a := n-1;
        b := n-2;
        c := fib(a);
        d := fib(b);
        e := c + d;
    );
    n := e;
)
x := 10;
y := fib(x);
write(y);
