import shutil
import os

def removeIfExists(dirname):
    if os.path.exists(dirname):
        shutil.rmtree(dirname)

removeIfExists(".vs")
removeIfExists("packages")
removeIfExists("x64")
for i in [ x for x in os.listdir() if os.path.isdir(x)]:
    for j in [ x for x in os.listdir(i) if os.path.isdir(i + "/" + x)]:
        if j == "x64":
            shutil.rmtree(i + "/" + j)
