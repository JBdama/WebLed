import os
import codecs
css_list =[ "colorpicker.css",  "nav.css", "slider.css", "main.css"]         # List with all CSS filenames
final = []

def read_file(path, file):
    with codecs.open(os.path.join(path, file), "r", encoding="utf-8") as f:
        content = str(f.read().replace('"', "'")).splitlines()
        content_list = [i.strip() for i in content]             # Create list that doesnt have spare Whitespaces in Strings
        f.close()
        return  content_list

def read_css(path, files):
    css = ""
    for c in files:
        content = read_file(path, c)
        for line in content:
            css += line
        css += "\n"
    #print(css)
    return css


def edithtml(html):
    html_copy = html.copy()    # Create copy to not iterate in
    for i, line in enumerate(html):
        if line == "<head>":
            half_one = html_copy[:i+1]
            half_two = html_copy[i+1+len(css_list):]    # +csscount because need to remove the remaining link includes
            half_two.pop()                          # Remove the </html> part 
            return half_one , half_two 

def writehtml(html1, html2, css, js):
    def write_list(content):
        final.append("".join(content))
    write_list(html1)
    #write_list(css)
    write_list(html2)
    write_list(js)
    with open(os.path.join("NodeMCU/src", "text.txt"), "w") as f:

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
    print(final)

def calculate():
    #print(os.getcwd())
    js = read_file("After", "logic.js")
    html = read_file("After", "index.html")
    css = read_css("After", css_list)
    html1, html2 = edithtml(html)
    #html1 = " "
    #html2 = " "
    test = ""
    #css =  ""
    writehtml(html1, html2, css, js)
calculate()

css = ""


#css = css.splitlines()
#css = "".join(css)
#print(css)
