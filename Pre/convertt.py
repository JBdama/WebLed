import os
import codecs
css_list =[ "colorpicker.css",  "nav.css", "slider.css", "main.css"]         # List with all CSS filenames

def read_file(path, file):
    with codecs.open(os.path.join(path, file), "r", encoding="utf-8") as f:
        content = str(f.read().replace('"', "'")).splitlines()
        content_list = [i.strip() for i in content]             # Create list that doesnt have spare Whitespaces in Strings
        f.close()
        return  content_list

def read_css(path, files):
    css = []
    for c in files:
        content = read_file(path, c)
        css.append(content)
    return css
                                                    
def edithtml(html):                                     # Function to split html at the place where css should be inserted
    h_file = html.copy()                             # Create copy to not iterate in
    for i, line in enumerate(html):
        if line == "<head>":
            half_one = h_file[:i+1]
            half_two = h_file[i+1+len(css_list):]     # +csscount because need to remove the remaining link includes
            half_two.pop()
            return half_one , half_two 

def writehtml(html1, html2, css_list, js):
    final = []
    final.append("".join(html1))
    final.append("<style>")
    for css in css_list:
        final.append("".join(css))
    final.append("</style>")
    final.append("".join(html2))
    final.append("<script>")
    final.append("".join(js))
    final.append("</script>")
    final.append("</html>")
    print(len(final))
    return final

def write_h(html):
    file = os.path.join("NodeMCU/src", "text.txt")
    with open(file, "w") as f:
        h_file = []
        h_file.append("using namespace std;\nclass files {\n\tpublic:\n\tString get_html() {\n\t\tString message =")
        for line in html:
            h_file.append('"'+line+'\\n "\n')
        h_file[1] = " F("+h_file[1]
        h_file[-1] = '"'+html[-1] + '");'
        h_file.append("\n\treturn message;\n\t}\n};")
        f.writelines(h_file)
        f.close()
    base = os.path.splitext(file)[0]
    os.rename(file, base+".h")

def calculate():
    js = read_file("After", "logic.js")
    html = read_file("After", "index.html")
    css = read_css("After", css_list)
    html1, html2 = edithtml(html)
    newhtml = writehtml(html1, html2, css, js)
    write_h(newhtml)

calculate()



