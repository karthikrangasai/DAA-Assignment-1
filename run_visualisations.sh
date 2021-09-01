# bash compile.sh
# echo ""
# for shape in simple bars smiley pikachu saitama
# do
# 	echo "> Running the code for the example: $shape"
# 	./daaaaaaaaaaa ./output_visualisations/inputs/$shape.txt ./output_visualisations/outputs/$shape.txt ./output_visualisations/outputs/$shape"_details".txt
# 	python3 visualization.py -i ./output_visualisations/inputs/$shape.txt -o ./output_visualisations/outputs/$shape.txt -img ./output_visualisations/images/$shape.png
# done

start_rect_num=1
end_rect_num=10000
step_val=1
distribution=500
folder_name=$start_rect_num"__"$step_val"__"$end_rect_num"_N(-$distribution,$distribution)"
echo "Saving to the folder: $folder_name"

mkdir -p tests
mkdir -p tests/inputs
mkdir -p tests/inputs/$folder_name
mkdir -p tests/outputs
mkdir -p tests/outputs/$folder_name

touch  tests/outputs/$folder_name/final_output.txt

mkdir -p tests/images
mkdir -p tests/images/$folder_name

bash compile.sh

echo ""
echo "> Starting Test Case Evaluation:"
for (( i=$start_rect_num; i<=$end_rect_num; i+=$step_val ))
do
	./build/tests/test_case_generator.o $i ./tests/inputs/$folder_name/in$i.txt $distribution
	./daaaaaaaaaaa ./tests/inputs/$folder_name/in$i.txt ./tests/outputs/$folder_name/out$i.txt ./tests/outputs/$folder_name/out$i"_details".txt
	cat ./tests/outputs/$folder_name/out$i"_details".txt >> ./tests/outputs/$folder_name/final_output.txt
	python3 visualization.py -i ./tests/inputs/$folder_name/in$i.txt -o ./tests/outputs/$folder_name/out$i.txt -img ./tests/images/$folder_name/$i.png
	echo "    Generated output for test case: Input - $i, Distribution - $distribution"
	sleep 1
done
echo "Outputs generation done."

# for (( i=$start_rect_num; i<=$end_rect_num; i++ ))
# do
# 	python3 visualization.py -i ./tests/inputs/$folder_name/in$i.txt -o ./tests/outputs/$folder_name/out$i.txt -img ./tests/images/$folder_name/$i.png
# done
echo ""
echo "Generating time analysis graph"
echo "    Saving it to ./tests/images/$folder_name/time_analyis.png"
python3 ./plot_time_anal.py -o ./tests/outputs/$folder_name/final_output.txt -img ./tests/images/$folder_name/time_analysis.png -s $start_rect_num -e $end_rect_num