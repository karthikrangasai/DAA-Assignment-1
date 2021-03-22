start_rect_num=1000
end_rect_num=1500
step_val=5
distribution=100
folder_name=$start_rect_num"__"$step_val"__"$end_rect_num"_N(-$distribution,$distribution)"
echo $folder_name

mkdir -p time_analysis
mkdir -p time_analysis/inputs
mkdir -p time_analysis/inputs/$folder_name
mkdir -p time_analysis/outputs
mkdir -p time_analysis/outputs/$folder_name
touch  time_analysis/outputs/$folder_name/final_output.txt

bash compile.sh

for (( i=$start_rect_num; i<=$end_rect_num; i++ ))
do
	./build/tests/test_case_generator.o $i ./time_analysis/inputs/$folder_name/in$i.txt $distribution
	./daaaaaaaaaaa ./time_analysis/inputs/$folder_name/in$i.txt ./time_analysis/outputs/$folder_name/out$i.txt ./time_analysis/outputs/$folder_name/out$i"_details".txt
	cat ./time_analysis/outputs/$folder_name/out$i.txt >> ./time_analysis/outputs/$folder_name/final_output.txt
done

python3 ./time_analysis/plot_time_anal.py -f $folder_name