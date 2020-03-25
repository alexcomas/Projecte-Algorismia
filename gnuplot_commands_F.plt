clear
set title "Falços positius segons el nombre de funcions de hashing"
set xlabel "Nombre de funcions de hashing"
set ylabel "% de positius que són falços"
set autoscale
set xzeroaxis linestyle 7
show xzeroaxis
set terminal png size 1024,768
set output "plot_F.png"

plot 'plot_F.dat' using 1:2 linetype 8  smooth acsplines title "Trendline (acsplines)", \
      'plot_F.dat' using 1:2 pt 7 ps 2  lt "black" title "Dades"
replot