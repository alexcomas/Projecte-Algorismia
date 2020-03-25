clear
set title "Falços positius segons el nombre de posicions del filtre de Bloom"
set xlabel "Mida Filtre de Bloom"
set ylabel "% de positius que són falços"
set autoscale
set xzeroaxis linestyle 7
show xzeroaxis
set terminal png size 1024,768
set output "plot_N.png"
plot 'plot_N.dat' using 1:2 linetype 8  smooth acsplines title "Trendline (acsplines)", \
      'plot_N.dat' using 1:2 pt 7 ps 2  lt "black" title "Dades"
replot