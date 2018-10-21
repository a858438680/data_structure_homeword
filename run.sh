hw=$1
p=$2
file=HW${hw}/HW${hw}P${p}
g++ ${file}.cpp -o $file
./$file < HW${hw}_input/HW${hw}P${p}.txt