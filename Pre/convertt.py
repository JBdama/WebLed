import os
import codecs
css_list =[ "colorpicker.css",  "nav.css", "slider.css", "main.css"]         # List with all CSS filenames

def read_file(path, file):
    with codecs.open(os.path.join(path, file), "r", encoding="utf-8") as f:
        content = f.read()
        f.close()
        return content

def read_css(path, files):
    css = ""
    for c in files:
        content = read_file(path, c)
        for line in content:
            new = line.rstrip()
            css += new
        css += "\n"
    print(css)
def readcss():
    css = ""
    for css_file in css_list:
        with codecs.open(os.path.join("After", css_file), "r", encoding = 'utf-8') as f:
            css_temp = f.read()
            css_temp = css_temp.splitlines()
            css += "".join(css_temp)
            css += "\n"
            #css_stor.append(css)
            f.close()
    return css

def edithtml(html):
    #print(type(html))
    html_list = html.splitlines()
    html_copy = html_list.copy()

    for i, line in enumerate(html_list):
        if line == "<head>":
            #print(i)
            css_count = len(css_list)
            half_one = html_copy[:i+1]
            half_two = html_copy[i+1+css_count:]
            half_two.pop()

            string1 = "".join(half_one)
            string2 = "".join(half_two)
            #(string1, "\n")
            #print(string2)
            return string1, string2
            break
    
    #print(html_copy)


def writehtml(html1, html2, css, js):
    with open(os.path.join("NodeMCU/src", "text.txt"), "w") as f:
        js = str(js).replace('"', "'")
        js.strip()
        js = js.splitlines()
        html1 = str(html1).replace('"', "'")
        html1 = html1.splitlines()
        html2 = str(html2).replace('"', "'")

        html2 = html2.splitlines()
        for line in html1:
            f.write(line)
        f.write('\n  <style>\n')
        f.write(css)
        f.write('  </style>\n')

        for line in html2:
            f.write(line)
        f.write('\n  <script> \n ')
        for line in js:
            f.write(line)
        f.write('\n  </script>')
        f.write('\n</html>')
        f.close()

def calculate():
    #print(os.getcwd())
    js = read_file("After", "logic.js")
    html = read_file("After", "index.html")
    css = read_css("After", css_list)
    html1, html2 = edithtml(html)
    html = " "
    test = ""
    #css =  ""
    writehtml(html1, html2, css, js)
#calculate()

css = ""


#css = css.splitlines()
#css = "".join(css)
#print(css)
with open(os.path.join("Pre", "help.txt"), "w") as f:
    f.writelines(css)
