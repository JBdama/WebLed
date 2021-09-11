import os
import codecs
css_list =[ "colorpicker.css",  "nav.css", "slider.css", "main.css"]         # List with all CSS filenames
def readjs():
    with codecs.open(os.path.join("After", "logic.js"), "r") as f:
        js = f.read()
        f.close()
        return js

def readhtml():
    with codecs.open(os.path.join("After", "index.html"), "r", encoding = 'utf-8') as f:
        html = f.read()
        f.close()
        return html

def readcss():
    css = ""
    css_stor = []
    for css_file in css_list:
        with codecs.open(os.path.join("After", css_file), "r", encoding = 'utf-8') as f:
            css = f.read()
            css_stor.append(css)
            f.close()
    return css_stor
def edithtml(html):
    print(type(html))
    html_list = html.splitlines()
    html_copy = html_list.copy()
    for i in range(len(html_list)-1, -1, -1):
        if html_list[i] == "</body>":
            print(i, html_list[i])
            html_copy.insert(i, "JAVSCRIPT")
            break
    for i, line in enumerate(html_list):
        if line == "<head>":
            print(i)
            css_count = len(css_list)
            half_one = html_copy[:i+1]
            half_two = html_copy[i+1+css_count:]
            half_one.append("<style>")
            half_two.insert(0, "</style>")
            string1 = "".join(half_one)
            string2 = "".join(half_two)
            #(string1, "\n")
            #print(string2)
            return string1, string2
            break
    
    #print(html_copy)
 
def hans(html):
    html2 = html.splitlines()
    for i in range(len(html2)-1,-1,-1):
        print(html2[i])
        if html2[i] == "</body>":
            print(i)
    return html


def writehtml(html1, html2, css_stora, js):
    with open(os.path.join("NodeMCU/src", "text.txt"), "w") as f:
        #html = str(html).replace('\n', '\\n')
        js = str(js).replace('"', "'")
        js.strip()
        js = js.splitlines()
        html1 = str(html1).replace('"', "'")
        html1 = html1.splitlines()
        html2 = str(html2).replace('"', "'")
        html2 = html2.splitlines()
        f.write("<script>")
        for line in js:
            f.write(line)
        f.write('</script>')
        for line in html1:
            f.write(line)
        for line in html2:
            f.write(line)
        for css in css_stora:
            css = str(css).replace('"', "'")
            css = css.splitlines()
            f.write('"')
            for c in css:
                f.write(c)
            f.write('\\n "\n')
        f.close()

#print(os.getcwd())
js = readjs()
html = readhtml()
#html = hans(html)
html1, html2 = edithtml(html)
htnl1, html2 = "", ""
css = readcss()
html = ""
css =  ""
writehtml(html1, html2, css, js)