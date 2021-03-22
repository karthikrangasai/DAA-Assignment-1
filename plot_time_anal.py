import os
import argparse
import matplotlib.pyplot as plt
import numpy as np


def main(input_filename, output_filename):
    # with open(os.path.join(os.getcwd(), 'time_analysis/outputs/' + input_folder + '/final_output.txt'), 'r') as file:
    with open(input_filename, 'r') as file:
        points = list()
        for line in file:
            rec_points = line.strip(' \n')
            rec_points = [int(i) for i in rec_points.split()]
            points.append(rec_points)

        points = np.array(sorted(points, key=lambda k: k[0]))
        z = np.linspace(10000, 15000, 10000)
        plt.plot(points[:, 0], points[:, 3], color='red')
        plt.plot(z, 10 * z * np.log(z), color='green')
        plt.plot(z, 15 * z * np.log(z), color='violet')
        plt.plot(z, 18 * z * np.log(z), color='black')
        plt.plot(z, 30 * z * np.log(z), color='blue')
        plt.legend([
            'Algorithm time complexity', 'Graph of 10nlogn',
            'Graph of 15nlogn', 'Graph of 18nlogn', 'Graph of 30nlogn'
        ])
        plt.xlabel('Number of rectangles')
        plt.ylabel('Running time (microseconds)')

    # plt.savefig(os.path.join(os.getcwd(), 'time_analysis/time_analysis_10000_15000_2_points.png'))
    plt.savefig(output_filename)
    plt.show()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-o',
                        '--out_file',
                        type=str,
                        required=True,
                        help='Path to output html file')
    parser.add_argument('-img',
                        '--image',
                        type=str,
                        required=True,
                        help='Path to output html file')
    args = vars(parser.parse_args())
    main(input_filename=args['out_file'], output_filename=args['image'])