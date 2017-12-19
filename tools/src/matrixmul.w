aA := [16];
aA[0] := 5;
aA[1] := 3;
aA[2] := 7;
aA[3] := 4;
aA[4] := 9;
aA[5] := 2;
aA[6] := 11;
aA[7] := 1;
aA[8] := 9;
aA[9] := 4;
aA[10] := 5;
aA[11] := 3;
aA[12] := 7;
aA[13] := 4;
aA[14] := 9;
aA[15] := 2;

aB := [16];
aB[0] := 5;
aB[1] := 3;
aB[2] := 7;
aB[3] := 4;
aB[4] := 9;
aB[5] := 2;
aB[6] := 11;
aB[7] := 1;
aB[8] := 9;
aB[9] := 4;
aB[10] := 5;
aB[11] := 3;
aB[12] := 7;
aB[13] := 4;
aB[14] := 9;
aB[15] := 2;

aC := [16];

i := 0;
while(i < 4) do (
    j := 0;
    while(j < 4) do (
        idx1 := i*4 + j;
        idx2 := j*4 + i;
        c := aA[idx1] * aB[idx2];
        write(c);
        aC[idx1] := c;
        j := j + 1;
    );

    i := i + 1;
);
b := 0;
while (b < 16) do (
    write(aC[b]);
    b := b + 1;
);
writeln;
