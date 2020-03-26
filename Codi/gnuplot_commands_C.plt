clear
set title "Ratio de falsos positius segons el nombre de posicions del filtre de Bloom, p = 1% (varia tota la resta respecte n)"
set xlabel "Mida de el nombre d'elements que guardar al filtre (n)"
set ylabel "Ratio de falsos positius en % (RFP)"
set autoscale
set yrange [0:10]
set xzeroaxis linestyle 7
show xzeroaxis
set terminal png size 1024,768
set output "plot_C.png"

plot 'plot_C.dat' using 1:2 linetype 8 smooth acsplines title "Trendline (acsplines) BIT", \
      'plot_C.dat' using 1:2 pt 7 ps 2  lt rgb "black" title "Dades BIT", \
      'plot_C2.dat' using 1:2 linetype 7 smooth acsplines title "Trendline (acsplines) ENTER", \
      'plot_C2.dat' using 1:2 pt 7 ps 2  lt rgb "red" title "Dades ENTER"
replot