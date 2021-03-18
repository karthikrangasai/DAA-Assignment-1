bash compile.sh
echo ""
for shape in simple bars smiley pikachu saitama
do
	echo "> Running the code for the example: $shape"
	./daaaaaaaaaaa ./output_visualisations/inputs/$shape.txt ./output_visualisations/outputs/$shape.txt ./output_visualisations/outputs/$shape"_details".txt
	python3 visualization.py -i ./output_visualisations/inputs/$shape.txt -o ./output_visualisations/outputs/$shape.txt -img ./output_visualisations/images/$shape.png
done