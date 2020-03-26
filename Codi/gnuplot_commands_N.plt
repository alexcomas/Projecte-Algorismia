clear
set title "Ratio de falsos positius segons el nombre de posicions del filtre de Bloom, k = 7 , n = 200 , p = 1%"
set xlabel "Mida Filtre de Bloom (m)"
set ylabel "Ratio de falsos positius en % (RFP)"
set autoscale
set xzeroaxis linestyle 7
show xzeroaxis
set terminal png size 1024,768
set output "plot_N.png"
plot 'plot_N.dat' using 1:2 linetype 8  smooth acsplines title "Trendline (acsplines)", \
      'plot_N.dat' using 1:2 pt 7 ps 2  lt "black" title "Dades"
replot