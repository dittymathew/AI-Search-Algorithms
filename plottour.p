set terminal postscript eps monochrome enhanced dashed "Helvetica" 18
set output "tour.eps"
set style data linespoints
set title "Tour"
set xlabel "x"
set ylabel "y"
plot "tour.txt" using 1:2 lc 1 title "Tour"
