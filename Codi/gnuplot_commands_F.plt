clear
set title "Ratio alsos positius segons el nombre de funcions de hashing, m = 1917 , n = 200 , p = 1%"
set xlabel "Nombre de funcions de hashing (k)"
set ylabel "Ratio de falsos positius en % (RFP)"
set autoscale
set xzeroaxis linestyle 7
show xzeroaxis
set terminal png size 1024,768
set output "plot_F.png"

plot 'plot_F.dat' using 1:2 linetype 8  smooth acsplines title "Trendline (acsplines)", \
      'plot_F.dat' using 1:2 pt 7 ps 2  lt "black" title "Dades"
replot