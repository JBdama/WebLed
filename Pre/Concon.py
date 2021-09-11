import sys, os
import codecs
from pathlib import Path
css_list =["main.css", "colorpicker.css",  "nav.css", "slider.css"]         # List with all CSS filenames

cpp1=  "class files {\n\tString get_html() {\n\t\tString message =F("
cpp2= ";\n\t\treturn message;\n\t}\n\tString get_css() {\n\t\tString message = "
cpp3 = ");\n\t\treturn message;\n\t}\n};"

cwd = os.getcwd()

#print("a",cwd, "b")
def readhtml ():
    html = open(os.path.join("After","index.html"), "r")
    html = html.read()
    return html

home = Path(Path.cwd()).parent
print(Path.cwd())
for files in os.listdir("NodeMCU/src"):
    print(files)
#with open(os.path.join(cwd+"/NodeMCU/src/text.txt", ),"w" ) as f:
#    f.write("Hier")
#    f.close()


def makefile(list, html, final_file):
    content_css = ""
    for css_file in list:                                                   # Join them together
        with open(os.path.join("After",css_file), "r") as f:
            content_css += f.read()
            f.close()
    content_css = content_css.strip("\n")
    with open(os.path.join("NodeMCU/src", final_file), "w") as f:
        print(final_file)
        html = html.splitlines()
        content_css = content_css.splitlines()
        f.write(cpp1)
        f.write('"')
        head = -2
        for i, line in enumerate(html):
            if line == "<head>":
                head  = i
            if i == head+1:
                f.write("<style> ")
                for inline in content_css:
                    f.writelines(line)
                f.write(" </style>")
                print("ja")
            f.writelines(line) 
            #f.write("\n") 
        f.write('"')
        f.write(cpp3)
        f.close()

def make_h(final_file):
    cwd = os.getcwd()
    final = cwd + "/NodeMCU/src/text.h"
    print(final)
    if  os.path.isfile(final):
        print("TRUE")
        os.remove(final)
    
    base = os.path.splitext(final_file)[0]
    os.rename(final_file, base + ".h")
    #os.rename(final_file, base + ".h")

if __name__  == "__main__":
    dest = cwd + "/NodeMCU/src/text.txt"
    html = readhtml()
    makefile(css_list, html, "text.txt")
    #make_h(dest)
    
