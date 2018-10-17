n=$(find -name "*.cpp" | wc -l)
for ((i=1;i<=$n;++i))
do
    echo $i
    file=$(find -name "*.cpp" | head -n $i | tail -n 1)
    echo $file
    g++ $file -o ${file:0:-4}
    ./${file:0:-4} < ${file:0:-4}.txt
    echo
done