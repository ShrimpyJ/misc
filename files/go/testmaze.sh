nguests=$1
length=$2

time go run /home/pete/misc/files/go/maze.go $1 $2 n && time python3 /home/pete/misc/files/py/maze.py $1 $2 n
