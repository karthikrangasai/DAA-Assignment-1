import os
import argparse
import matplotlib.pyplot as plt


def main(input_file_path, output_file_path, output_image_number, output_image_file):
    with open(input_file_path, 'r') as file:
        n_recs = file.readline()
        n_recs = n_recs.strip(' \n')
        n_recs = int(n_recs)
        for line in range(n_recs):
            rec_points = file.readline()
            rec_points = rec_points.strip(' \n')
            rec_points = [int(i) for i in rec_points.split()]  # x1 x2 y1 y2
            x1, x2, y1, y2 = rec_points
            plt.plot([x1, x1], [y1, y2], color='red')
            plt.plot([x2, x2], [y1, y2], color='red')
            plt.plot([x1, x2], [y1, y1], color='red')
            plt.plot([x1, x2], [y2, y2], color='red')

    with open(output_file_path, 'r') as file:
        isY = False
        title = []
        for line in file:
            line = line.strip(' \n')
            if '@' in line:
                isY = not isY
                continue
            if len(line.split()) == 1:
                title.append("Measure:")
                title.append(line)
            elif line[0] == '#':
                title.append("Perimeter:")
                title.append(line.split()[1])
            else:
                points = [int(i) for i in line.split()]
                if isY is False:
                    plt.plot([points[0], points[1]], [
                             points[2], points[2]], color='green', linewidth=1)  # x1 x2 y
                else:
                    plt.plot([points[2], points[2]], [
                             points[0], points[1]], color='green', linewidth=1)  # y1 y2 x

    # plt.show()
    plt.title(' '.join(title))
    plt.savefig(os.path.join(os.getcwd(), output_image_file))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input', type=str, required=True,
                        help='Path to file with input set of points for algorithm')
    parser.add_argument('-o', '--output', type=str, required=True,
                        help='Path to file with output set of points from algorithm')
    parser.add_argument('-n', '--number', type=str, required=False,
                        help='Path to file with output set of points from algorithm')
    parser.add_argument('-img', '--image', type=str, required=True,
                        help='Path to file where plot must be saved.')
    args = vars(parser.parse_args())
    main(input_file_path=args['input'],
         output_file_path=args['output'],
         output_image_number=args['number'],
         output_image_file=args['image'])
