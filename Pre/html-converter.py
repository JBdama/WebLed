import sys, os               # Import onto path
import codecs                # Import codes for html, css and js
#import Cpp_header as cpp 
this_folder = os.path.dirname(os.path.abspath(__file__))  #this line locates the script in the folder where it is stored
sys.path.append('/home/julius/opt/WebMeb/WebLed-1/')        # Add outer directory

beginning = "<!--   \n   HTML_HELPER   \n      const char html_page[] = TO_STRING(   \n    <!-- -->"
ending = "<!-- ); // end of TO_STRING <!-- --> "
    
header = ""
def write_header(f): 
    f.writelines("Hier ist die C++ Implementierung \n")

def read():
    with codecs.open("index.html", 'r') as f:
        content = f.read()
        content = content.splitlines()
        content.insert(-3, "WÄÄÄÄÄÄ")
        f.close()
    #print("Hello")
    return content

def write(content):
    with open(os.path.join(this_folder, 'header.txt'), "w") as f:
        f.writelines(beginning)
        for line in content:
            f.writelines(line +"\n")
        f.writelines(ending)
        f.close()

def css_merge():
    content = ""
    css_list =["main.css", "colorpicker.css",  "nav.css", "slider.css"]         # List with all CSS filenames

    for css_file in css_list:                                                   # Join them together
        with open(css_file, "r") as f:
            content += f.read()
            f.close()

    with open(os.path.join(this_folder, 'css.txt'), "w") as f:                   # Write final CSS file
            f.write(content)
            f.close()

if __name__ == "__main__":
    #head = head()
    write(read())
    