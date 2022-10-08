set terminal postscript eps monochrome enhanced dashed "Helvetica" 18
set output "comparison.eps"
set style data linespoints
set title "Hill Climbing"
set xlabel "x"
set ylabel "y"
plot "hill_cost.txt" using 1:2 lc 1 title "Hill Climbing" , "iteratedhc_cost.txt" using 1:2 lc 2 title "Iterated Hill Climb", "beamsearch_cost.txt" using 1:2 lc 3 title "Beam Search", "simulate_cost.txt" using 1:2 lc 4 title "Simulated"
