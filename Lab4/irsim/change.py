import os
def walkFile(file):
    for root, dirs, files in os.walk(file):
        for f in files:
            with open(os.path.join(root, f)) as fp:
                newfile = open("./convert/" + f.split(".")[0] + ".json", "a")
                newfile.write("[\n[[], [")
                flag = 0
                for line in fp:
                    line = line.strip('\n')
                    if flag == 0:
                        newfile.write(line)
                        flag = 1
                    else:
                        newfile.write("," + line)
                newfile.write("], 0]\n]")
walkFile("./expects")