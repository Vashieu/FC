set terminal pdfcairo size 10cm,6.5cm font "Latin Modern Math,8"
set output "grafico.pdf"

set xlabel "{/Latin-Modern-Math:Italic t} [s]"
set ylabel "Energia [J]"

set xrange [0:1.4e16]

set grid lw 1 lc rgb "#767676" dt 3

plot "Energia.dat" every 3::0 u 1:3 w l title "{/Latin-Modern-Math:Italic V}", \
     "Energia.dat" every 3::1 u 1:3 w l title "{/Latin-Modern-Math:Italic T}", \
     "Energia.dat" every 3::2 u 1:3 w l title "{/Latin-Modern-Math:Italic E}"
