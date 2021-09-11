import sys, os               # Import onto path
import codecs                # Import codes for html, css and js
this_folder = os.path.dirname(os.path.abspath(__file__))  #this line locates the script in the folder where it is stored
sys.path.append(os.path.abspath('../'))        # Add outer directory

content = ""

css_list =["main.css", "colorpicker.css",  "nav.css", "slider.css"]         # List with all CSS filenames

for css_file in css_list:                                                   # Join them together
    with open(css_file, "r") as f:
        content += f.read()
        f.close()


with open(os.path.join(this_folder, 'css.txt'), "w") as f:                   # Write final CSS file
        f.write(content)
        f.close()


