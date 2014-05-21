nohup ./nll2 0.1 0 > test.0.1_0 &
nohup ./nll2 0.1 1 > test.0.1_1 &
nohup ./nll2 0.1 0.1 > test.0.1_0.1 &
nohup ./nll2 0.01 0.1 > test.0.01_0.1 &
nohup ./nll2 0.01 0 > test.0.01_0 &
nohup ./nll2 0.01 1 > test.0.01_1 &
nohup ./nll2 0.001 0 > test.0.001_0 &
nohup ./nll2 0.001 1 > test.0.001_1 &
nohup ./nll2 0.001 0.1 > test.0.001_0.1 &

# cat test.* | sort -k4n | head -2000 | cut -f3 | sort | uniq -c
