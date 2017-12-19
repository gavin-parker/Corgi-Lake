def partition(a lo hi) (
    pivot := a[hi];
    i := lo - 1;
    j := lo;
    while (j < hi) do (
        if (a[j] < pivot) then(
            i := i + 1;
            temp := a[i];
            a[i] := a[j];
            a[j] := temp;

        ) else (
            writeln;
        );

    );
    if (a[hi] < a[i+1]) then (
        temp2 := a[i+1];
        a[i+1] := a[hi];
        a[hi] := temp2;
    ) else (
        writeln;
    );
    hi := i+1;
)
def quicksort(a lo hi) (
    if(lo < hi) then (
        p := partition(a lo hi);
        pl := p-1;
        ph := p+1;
        quicksort(a lo pl);
        quicksort(a ph hi);

    ) else (
        writeln;
    );
)

a := [10];
a[0] := 5;
a[1] := 3;
a[2] := 7;
a[3] := 4;
a[4] := 9;
a[5] := 2;
a[6] := 11;
a[7] := 1;
a[8] := 9;
a[9] := 4;

lo := 0;
hi := 9;
quicksort(a lo hi);

i := 0;
max := 10;
while(i < max) do (
    write(a[i]);
    i := i + 1;
);