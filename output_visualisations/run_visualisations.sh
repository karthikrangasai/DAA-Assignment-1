bash compile.sh
echo ""
for shape in simple bars smiley pikachu saitama
do
	echo "> Running the code for the example: $shape"
	../daaaaaaaaaaa ./inputs/$shape.txt ./outputs/$shape.txt ./outputs/$shape"_details".txt
	python3 ./visualization.py -i ./inputs/$shape.txt -o ./outputs/$shape.txt -img ./images/$shape.png
done