#!/usr/bin/env python3

import os
import shutil
import subprocess

import yaml


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

        with open(os.path.join(lib_dir, "cpplib.yaml")) as specfile:
            config = yaml.safe_load(specfile)
        print(config)

        stdinc = config["CPPLIB"]["Standard Include"]["file"]
        texfile.write("\\section{Standard Include}{\n")
        texfile.write(f'  \\includecode{{\"{stdinc}\"}}\n')
        texfile.write("}\n\n")
        del config["CPPLIB"]["Standard Include"]

        for subject, content in sorted(config["CPPLIB"].items()):
            texfile.write(f"\\section{{{subject}}}{{\n")

            dirpath = content["dir"]
            for task, info in sorted(content["items"].items()):
                filepath = os.path.join(dirpath, info["file"])

                if "tags" in info:
                    task += " (" + ", ".join(info["tags"]) + ")"

                texfile.write(f"  \\subsection{{{task}}}{{\n")
                texfile.write(f'    \\includecode{{\"{filepath}\"}}\n')
                texfile.write(f"  }}\n")
            texfile.write("}\n\n")

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
