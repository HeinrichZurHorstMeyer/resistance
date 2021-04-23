# ADT_calc

Run the programm with the formula as argument.

For two resistors in series, write "r(R1, R2)" with R1 and R2 as the resistance.
For two resistors in parallel, write "p(R1, R2)" with R1 and R2 as the resistance.
You can chain those together like "r(100, 200, p(300, 400), 50.5)".

You might need to escape the string, depending on your shell like "r\(100, 200, p\(300, 400\), 50.5\)".
I am working on an interactive mode where this is not necessary.
