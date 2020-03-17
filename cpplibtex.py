#!/usr/bin/env python3

import os
import shutil
import subprocess


def dfs(abspath, path, texfile, indent = 0):
    for filename in sorted(os.listdir(abspath)):
        absfilepath = os.path.join(abspath, filename)
        if os.path.isdir(absfilepath) or not filename.endswith(".hpp"):
            continue

        filepath = os.path.join(path, filename)
        filename = filename.split(".")[0].title().replace("-", " ")

        texfile.write(f'{" " * indent}\\{"section" if indent == 0 else "subsection"}{{{filename}}}{{\n')
        texfile.write(f'{" " * indent}  \\includecode{{\"{filepath}\"}}\n')
        texfile.write(f'{" " * indent}}}\n\n')

    for dirname in sorted(os.listdir(abspath)):
        absdirpath = os.path.join(abspath, dirname)
        if not os.path.isdir(absdirpath):
            continue

        dirpath = os.path.join(path, dirname)
        dirname = dirname.title().replace("-", " ")

        texfile.write(f'{" " * indent}\\{"section" if indent == 0 else "subsection"}{{{dirname}}}{{\n\n')
        dfs(absdirpath, dirpath, texfile, indent + 2)
        texfile.write(f'{" " * indent}}}\n\n')

def main():
    lib_dir = os.path.dirname(os.path.abspath(__file__))
    latex_dir = os.path.join(lib_dir, ".latex")
    cpplib_dir = os.path.join(lib_dir, "include", "cpplib")

    cpplibtex = os.path.join(latex_dir, "cpplib.tex")

    shutil.copyfile(
        os.path.join(latex_dir, "cpplib-prefix.tex"),
        cpplibtex
    )

    with open(cpplibtex, "a") as texfile:
        texfile.write("\n")

        dfs(cpplib_dir, "", texfile)

        with open(os.path.join(latex_dir, "cpplib-suffix.tex"), "r") as endfile:
            shutil.copyfileobj(endfile, texfile)

    os.symlink(cpplib_dir, os.path.join(latex_dir, "codes"), True)
    os.chdir(latex_dir)
    subprocess.run(["pdflatex", "cpplib.tex"])
    #: running twice to generate the table of contents.
    subprocess.run(["pdflatex", "cpplib.tex"])
    os.chdir(os.getcwd())
    os.unlink(os.path.join(latex_dir, "codes"))

    shutil.copy(os.path.join(latex_dir, "cpplib.pdf"), lib_dir)

if __name__ == "__main__":
    main()
