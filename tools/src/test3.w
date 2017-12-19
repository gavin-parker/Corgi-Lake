a := 0;
b := 1;
while(a < 5) do (
    write(a);
    b := b * a;
    a := a + 1;
);
write(a);
write(b);