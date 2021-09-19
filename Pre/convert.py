import os
import codecs

def read_file(path, file):
    with codecs.open(os.path.join(path, file), "r", encoding="utf-8") as f:         # Read the file with UTF-8 encoding
        content = str(f.read().replace('"', "'")).splitlines()
        content_list = [i.strip() for i in content]                                 # Create list that doesnt have spare Whitespaces in Strings
        f.close()
    return  [i.strip() for i in content]
                                      
def cut_html(html, css_list, js_list):                                              # Function to split html
    for i, line in enumerate(html):
        if line == "</head>":                                                       # Find place to cut
            c = i  
            break
    return ["".join(html[3:c-1-len(css_list)])], ["".join(html[c+3:-2-len(js_list)])] # Head and body

def write_html(head_content, body_content, css_list, js):                           # Merge all parts together
    def expand(tag, content):                                                       # Function for generating <tag>content</tag> 'HTML content'
        return ["<"+tag+">"] + ["".join(x) for x in content] + ["</"+tag+">"]
    head = expand("head", head_content + [" <link rel='stylesheet'href='icon.css'><link rel='stylesheet'href='rain.css'>"])                 # CSS in head
    body = expand("body",body_content + expand("script", js))                       # JS in body
    return expand("html", head+body)                                                # Head and body in html

def write_h(path, file, html, css):                                                      # Create c++ class called "files" in file "text.h"
    file = os.path.join(path, file)
    with open(file, "w") as f:
        h_file = []
        h_file.append('const char message_html2[] PROGMEM = R"rawliteral(\n')  #  get_html()
        for line in html:
            h_file.append(line+ '\n')
        h_file.append(')rawliteral";\n')
        h_file.append('const char message_css[] PROGMEM = R"rawliteral(\n')  #  get_html()
        for c in css:
            h_file.append("".join(c)+"\n")
            #print(c, "\n")
        h_file.append(')rawliteral";\n')
        h_file.append('const char message_css2[] PROGMEM = R"rawliteral(\n')  #  get_html()
        h_file.append("".join(read_file("After", "main.css")))
        h_file.append(')rawliteral";\n')
        f.writelines(h_file)
        f.close()

def run(source, dest, name, html, css_list, js_list):                               # Runs script
    html = read_file(source, html)
    css = [read_file(source, c) for c in css_list]
    js = [read_file(source, j) for j in js_list]
    head, body = cut_html(html, css_list, js_list)
    file = write_html(head, body, css, js)
    write_h(dest, name, file, css)

if __name__ == "__main__":
    
    html = "index.html"
    css_list =[ "colorpicker.css",  "nav.css", "slider.css"]            # List with all CSS filenames
    js_list = [ "logic.js"]                                                         # List with all JS filenames
    source = "After"
    destination = "NodeMCU/src"
    name = "text.h"
    run(source, destination, name, html, css_list, js_list)



