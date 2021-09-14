import os
import codecs
css_list =[ "colorpicker.css",  "nav.css", "slider.css", "main.css"]         # List with all CSS filenames
js_list = [ "logic.js"]                                                      # List with all JS filenames

def read_file(path, file):
    with codecs.open(os.path.join(path, file), "r", encoding="utf-8") as f:  # Read the file with UTF-8 encoding
        content = str(f.read().replace('"', "'")).splitlines()
        content_list = [i.strip() for i in content]                          # Create list that doesnt have spare Whitespaces in Strings
        f.close()
    return  content_list
                                      
def cut_html(html): # Function to split html
    for i, line in enumerate(html):
        if line == "</head>":                                                # Find place to cut
            c = i
            break
    return ["".join(html[3:c-len(css_list)])], ["".join(html[c+3:-2-len(js_list)])] # Head and body

def write_html(head_content, body_content, css_list, js):                           # Merge all parts together
    def expand(tag, content):                                                       # Function for generating <tag>content</tag> 'HTML content'
        return ["<"+tag+">"] + ["".join(x) for x in content] + ["</"+tag+">"]
    head = expand("head", head_content + expand("style", css_list))                 # CSS in head
    body = expand("body",body_content + expand("script", js))                       # JS in body
    return expand("html", head+body)                                                # Head and body in html

def write_h(path, file, html):                                                      # Create c++ class called "files" in file "text.h"
    file = os.path.join(path, file)
    with open(file, "w") as f:
        h_file = []
        h_file.append("using namespace std;\nclass files {\n\tpublic:\n\tString get_html() {\n\t\tString message =")  # to get doc call get_html()
        for line in html:
            h_file.append('"'+line+'\\n "\n')
        h_file[1] = " F("+h_file[1]
        h_file[-1] = '"'+html[-1] + '");'
        h_file.append("\n\treturn message;\n\t}\n};")
        f.writelines(h_file)
        f.close()

def run(source, dest, name):                            # Runs script
    html = read_file(source, "index.html")
    css = [read_file(source, c) for c in css_list]
    js = [read_file(source, j) for j in js_list]
    head, body = cut_html(html)
    file = write_html(head, body, css, js)
    write_h(dest, name, file)

if __name__ == "__main__":
    source = "After"
    destination = "NodeMCU/src"
    name = "text.h"
    run(source, destination, name)



