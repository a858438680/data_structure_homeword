hw=$1
p=$2
file=HW${hw}P${p}
g++ ${file}.cpp -o $file
./$file < ${file}.txt