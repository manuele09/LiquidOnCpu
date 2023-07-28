set terminal pngcairo enhanced size 800,600
set output "../gnuplot/distribution_plot.png"
set title "Gaussian Distribution | Mean=0.97 | Stddev=99.91 | Min=-445.96 | Max=460.90"
set xlabel "Value"
set ylabel "Frequency"
set grid
binwidth=0.1
bin(x,width)=width*floor(x/width)
plot '../gnuplot/samples.txt' using (bin($1,binwidth)):(1.0) smooth freq with boxes title "Samples"
