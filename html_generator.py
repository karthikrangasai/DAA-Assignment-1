import argparse


def generate_html(filename):
    with open(filename, 'w') as file:
        file.write("<html lang=\"en\">\n")
        file.write("\t<head>\n")
        file.write("\t\t<meta charset=\"UTF-8\">\n")
        file.write(
            "\t\t<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n")
        file.write(
            "\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n")
        file.write("\t\t<title>Document</title>\n")
        file.write("\t\t<style>\n")
        file.write("\t\t\thtml,\n")
        file.write("\t\t\tbody {\n")
        file.write("\t\t\t\tmargin: 0;\n")
        file.write("\t\t\t\tpadding: 0;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t\t.nav-style {\n")
        file.write("\t\t\t\twidth: 50%;\n")
        file.write("\t\t\t\tmargin: 0 auto;\n")
        file.write("\t\t\t\ttext-align: center;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t\t.section {\n")
        file.write("\t\t\t\tdisplay: flex;\n")
        file.write("\t\t\t\tflex-direction: column;\n")
        file.write("\t\t\t\twidth: 98%;\n")
        file.write("\t\t\t\ttext-align: center;\n")
        file.write("\t\t\t\tborder: 3px solid black;\n")
        file.write("\t\t\t\tmargin: 5px auto;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t\t.sub-section {\n")
        file.write("\t\t\t\tdisplay: flex;\n")
        file.write("\t\t\t\tflex-direction: row;\n")
        file.write("\t\t\t\tjustify-content: space-evenly;\n")
        file.write("\t\t\t\twidth: 95%;\n")
        file.write("\t\t\t\ttext-align: center;\n")
        file.write("\t\t\t\tborder: 3px solid black;\n")
        file.write("\t\t\t\tmargin: 5px auto;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t\t.diagram-div {\n")
        file.write("\t\t\t\tdisplay: flex;\n")
        file.write("\t\t\t\tflex-direction: row;\n")
        file.write("\t\t\t\tjustify-content: space-evenly;\n")
        file.write("\t\t\t\tmargin: 10px 0;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t\t.diagram-div-img {\n")
        file.write("\t\t\t\tdisplay: flex;\n")
        file.write("\t\t\t\twidth: 40%;\n")
        file.write("\t\t\t\tjustify-content: center;\n")
        file.write("\t\t\t\theight: 400px;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t\t.diagram-div-text {\n")
        file.write("\t\t\t\ttext-align: center;\n")
        file.write("\t\t\t\tdisplay: flex;\n")
        file.write("\t\t\t\tflex-direction: column;\n")
        file.write("\t\t\t\twidth: 60%;\n")
        file.write("\t\t\t\tborder: 1px black solid;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t\tul {\n")
        file.write("\t\t\t\tlist-style-type: none;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t\tul>li {\n")
        file.write("\t\t\t\tmargin: 15px 0;\n")
        file.write("\t\t\t\tfont-size: 30px;\n")
        file.write("\t\t\t}\n")
        file.write("\t\t</style>\n")
        file.write("\t</head>\n")
        file.write("\t<body>\n")

        file.write("\t\t<nav class=\"nav-style\">\n")
        file.write(
            "\t\t\t<h1>CS F364 - Design and Analysis of Algorithms - Assignment 1</h1>\n")
        file.write("\t\t\t<h2>Varun Parthasarathy - 2017B3A70515H</h2>\n")
        file.write("\t\t\t<h2>G Sathyaram - 2017B2A71335H</h2>\n")
        file.write("\t\t\t<h2>Siddarth Gopalakrishnan - 2017B3A71379H</h2>\n")
        file.write("\t\t\t<h2>Sivaraman Karthik Rangasai - 2017B4A71499H</h2>\n")
        file.write("\t\t</nav>\n")

        file.write("\t\t<div class=\"section\">\n")
        file.write("\t\t\t<div>\n")
        file.write("\t\t\t<div><h1>Time Analysis of our Code</h1></div>\n")
        file.write("\t\t\t<div><h2>Tested for 10000 testcases.</h2></div>\n")
        file.write(
            "\t\t\t<div><h2>Starting from 1 rectangles to 10000 rectangles.</h2></div>\n")
        file.write(
            "\t\t\t<div><h2>Implementation is O(nlogn) for c = 10 and n >= 1.</h2></div>\n")
        file.write(
            "\t\t\t<div><h2>Implementation is Θ(nlogn) for c1 = 10, c2 = 150, and n >= 1.</h2></div>\n")
        file.write("\t\t\t</div>\n")
        file.write(
            "\t\t\t<div><img src=\"./output_visualisations/complexity/time_analysis_10_30.png\" style=\"width: 50%;\"></div>\n")
        file.write(
            "\t\t\t<div><img src=\"./output_visualisations/complexity/time_analysis_1_50.png\" style=\"width: 50%;\"></div>\n")
        file.write(
            "\t\t\t<div><img src=\"./output_visualisations/complexity/time_analysis_1_150.png\" style=\"width: 50%;\"></div>\n")
        file.write("\t\t</div>\n")

        file.write("\t\t<div class=\"section\">\n")
        file.write(
            "\t\t\t<div style=\"text-align: center;margin: 5px 0;\"><h1>Contour Visualisations</h1></div>\n")

        # For loop here
        for image_filename in ["simple", "bars", "smiley", "saitama", "pikachu"]:
            file.write("\t\t\t<div class=\"sub-section\">\n")
            file.write("\t\t\t\t<div class=\"diagram-div-img\"><img src=\"./output_visualisations/images/" +
                       image_filename + ".png\"></div>\n")
            file.write("\t\t\t\t<div class=\"diagram-div-text\">\n")
            file.write("\t\t\t\t\t<div><h1>" + image_filename.title() +
                       " Shape Visualisation</h1></div>\n")
            file.write("\t\t\t\t\t<div>\n")
            file.write("\t\t\t\t\t\t<ul>\n")
            with open("./output_visualisations/outputs/" + image_filename + "_details.txt") as f:
                l = f.readline().split(' ')
                file.write(
                    "\t\t\t\t\t\t\t<li>Number of Rectangles: " + l[0] + "</li>\n")
                file.write("\t\t\t\t\t\t\t<li>Measure: " + l[1] + "</li>\n")
                file.write("\t\t\t\t\t\t\t<li>Perimeter: " + l[2] + "</li>\n")
                file.write("\t\t\t\t\t\t\t<li>Time taken: " +
                           l[3] + " μs</li>\n")
            file.write("\t\t\t\t\t\t</ul>\n")
            file.write("\t\t\t\t\t</div>\n")
            file.write("\t\t\t\t</div>\n")
            file.write("\t\t\t</div>\n")

        file.write("\t\t</div>\n")

        file.write("\t\t<div class=\"section\">\n")
        file.write("\t\t\t<div><h1>Issues in Coding</h1></div>\n")
        file.write("\t\t\t<div>\n")
        file.write("\t\t\t\t<ul>\n")
        file.write(
            "\t\t\t\t\t<li>- Maintaining lower constant in Linear Complexity for Merge function.</li>\n")
        file.write(
            "\t\t\t\t\t<li>- Generation of random testcases for stress testing and checking correctness of program.</li>\n")
        file.write(
            "\t\t\t\t\t<li>- Careful generation of testcases for aesthetic outputs.</li>\n")
        file.write("\t\t\t\t</ul>\n")
        file.write("\t\t\t</div>\n")
        file.write("\t\t</div>\n")

        file.write("\t\t<div class=\"section\">\n")
        file.write("\t\t\t<div><h1>References</h1></div>\n")
        file.write("\t\t\t<div style=\"font-size: 20px;\">\n")
        file.write("\t\t\t\t<ul>\n")
        file.write("\t\t\t\t\t<li><a href=\"https://link.springer.com/article/10.1007/BF00264251\">Guting, R.H. Optimal divide-and-conquer to compute measure and contour for a set of iso-rectangles.</a></li>")
        file.write("\t\t\t\t</ul>\n")
        file.write("\t\t\t</div>\n")
        file.write("\t\t</div>\n")

        file.write("\t</body>\n")
        file.write("</html>\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--file', type=str,
                        required=True, help='Path to output html file')
    args = vars(parser.parse_args())
    generate_html(filename=args['file'])
