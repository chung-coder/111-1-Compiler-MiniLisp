import os
for dirPath, dirNames, fileNames in os.walk("data"):
    for current_file in sorted(fileNames):
        print("\nFile name: " + current_file)
        os.system('./miniLisp < data/' + current_file)