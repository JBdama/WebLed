import os
import codecs
css_list =[ "colorpicker.css",  "nav.css", "slider.css", "main.css"]         # List with all CSS filenames

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
            print(string1, "\n")
            print(string2)
            return string1, string2
            break

    #print(html_copy)

def writehtml(html1, html2, css_stora):
    with open(os.path.join("NodeMCU/lib", "test.txt"), "w") as f:
        #html = str(html).replace('\n', '\\n')

        html1 = str(html1).replace('"', "'")
        html1 = html1.splitlines()
        html2 = str(html2).replace('"', "'")
        html2 = html2.splitlines()
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
html = readhtml()
html1, html2 = edithtml(html)
css = readcss()
html = ""
css =  ""
writehtml(html1, html2, css)
testuiuiui = ".color-picker {  position: relative;}.color-indicator {  display: inline-block;  width: 100px;  height: 100px;  background-color: #fff;  border-radius: 30px;}#color-picker {  display: inline-block;  vertical-align: middle;  margin-left: 40px;}.fx_buttons {  background-color: rgb(78, 78, 78);  width: 10%;  height: 50%;  display: flex;  flex-direction: column;  justify-content: space-evenly;  border-style: solid;  border-radius: 20px;  border-color: #000;}.rgb_buttons {  background-color: rgb(78, 78, 78);  width: 10%;  height: 50%;  display: flex;  flex-direction: column;  justify-content: space-evenly;  border-style: solid;  border-radius: 20px;  border-color: #000;}.fx_buttons *{  background-color: #4CAF50; /* Green */  border: none;  border-radius: 30px;  color: white;  padding: 15px 32px;  text-align: center;  text-decoration: none;  font-size: 16px;  transition-duration: 0.3s;  margin: 10px;}.rgb_buttons *{  background-color: #fff; /* White */  border: solid;  border-radius: 30px;  color: #000;  padding: 15px 15px;  text-align: center;  text-decoration: none;  font-size: 16px;  transition-duration: 0.3s;  margin: 40px;}.rgb_buttons .inactive:hover {  background-color: #7e847f;  cursor: pointer; /* Pointer/hand icon */  }.fx_buttons .inactive:hover {background-color: #7ecf82;cursor: pointer; /* Pointer/hand icon */}.fx_buttons .active {background-color: rgb(19, 73, 10);}.rgb_buttons .active {  border-width: 5px;  border-color:dodgerblue ;}.left {  position: fixed;  top: 40%;  left: 20%;  transform: translate(-40%, -20%);}.right {  position: fixed;  top: 70%;  left: 80%;  transform: translate(-40%, -80%);}/*.fx_buttons > *:not(:last-child) {  margin: 10px;}*/.slidecontainer {  width: 100%; /* Width of the outside container */}/* The slider itself */.slider {  position: relative;  -webkit-appearance: none;  /* Override default CSS styles */  appearance: none;  width: 50%; /* Full-width */  height: 15px; /* Specified height */  border-radius: 5px;  background: #d3d3d3; /* Grey background */  outline: none; /* Remove outline */  opacity: 0.7; /* Set transparency (for mouse-over effects on hover) */  -webkit-transition: .2s; /* 0.2 seconds transition on hover */  transition: opacity .2s;}/* Mouse-over effects */.slider:hover {  opacity: 1; /* Fully shown on mouse-over */}/* The slider handle (use -webkit- (Chrome, Opera, Safari, Edge) and -moz- (Firefox) to override default look) */.slider::-webkit-slider-thumb {  -webkit-appearance: none; /* Override default look */  appearance: none;  width: 25px; /* Set a specific slider handle width */  height: 25px; /* Slider handle height */  border-radius: 50%;  background: #040e63; /* Green background */  cursor: pointer; /* Cursor on hover */}.slider::-moz-range-thumb {  width: 25px; /* Set a specific slider handle width */  height: 25px; /* Slider handle height */  border-radius: 50%  ;  background: #0636f5; /* Green background */  cursor: pointer; /* Cursor on hover */  rgb : rgb(189, 97, 58);}.slider-icon{	transform: translate(6px,3px);	color: #ddd;}.centered {  position: fixed;  top: 50%;  left: 50%;  transform: translate(-50%, -50%);}@font-face {	font-family: 'WIcons';	src: url(data:application/x-font-woff;charset=utf-8;base64,d09GRgABAAAAABMkAAsAAAAAEtgAAQACAAAAAAAAAAAAAAAAAAAAAAAAAABPUy8yAAABCAAAAGAAAABgD50AIWNtYXAAAAFoAAABBAAAAQTVan0qZ2FzcAAAAmwAAAAIAAAACAAAABBnbHlmAAACdAAADewAAA3sm6svT2hlYWQAABBgAAAANgAAADYb/Mf8aGhlYQAAEJgAAAAkAAAAJAcYA1FobXR4AAAQvAAAAHAAAABwZAAMiWxvY2EAABEsAAAAOgAAADowHizsbWF4cAAAEWgAAAAgAAAAIAAmAF1uYW1lAAARiAAAAXoAAAF62zUFRXBvc3QAABMEAAAAIAAAACAAAwAAAAMEAAGQAAUAAAKZAswAAACPApkCzAAAAesAMwEJAAAAAAAAAAAAAAAAAAAAARAAAAAAAAAAAAAAAAAAAAAAQAAA5BADM/80AMwDMwDMAAAAAQAAAAAAAAAAAAAAIAAAAAAAAwAAAAMAAAAcAAEAAwAAABwAAwABAAAAHAAEAOgAAAA2ACAABAAWAAEAIOA34DzgTOBm4I/gouDo4RbhOeGK4i3iPeKi4qbis+Lj4yXjM+NL45DjleQJ5BD//f//AAAAAAAg4DfgPOBM4Gbgj+Ci4OjhFuE54YriLeI94qLipuKz4uPjJeMz40vjj+OV5AnkEP/9//8AAf/jH80fyR+6H6EfeR9nHyIe9R7THoMd4R3SHW4dax1fHTAc7xziHMsciByEHBEcCwADAAEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAB//8ADwABAAAAAAAAAAAAAgAANzkBAAAAAAEAAAAAAAAAAAACAAA3OQEAAAAAAQAAAAAAAAAAAAIAADc5AQAAAAACANX/wAMrAsAACQASAAAlESERFAYjISImARUhNTM3MxczAQACADIj/qojMgIr/aqWKtYqlhUCAP4AIzIyAqNVVSsrAAEAkQAVA4ACUQAFAAAlARcBJzcBgAHEPP4A7zyNAcQ8/gDvPAAAAAACAFX/sQOrAsAAJABBAAABMhceARcWFRQHDgEHBg8BJyYnLgEnJjU0Nz4BNzYzMhYXPgEzAzY3PgE3NjU0JiMiBgcjLgEjIgYVFBceARcWHwECwDErKz8SExobX0NEUj4+UkRDXxsaExI/KysxOGUjI2U4vEw/PlgYGFVAMVYRUBFWMUBVGBhYPj9MBALAEhJAKyoyPDk4dT9ASzg4Sz9AdTg5PDIqK0ASEjApKTD9aUQ7OmcvLy5AVjksLDlWQC4vL2c6O0QFAAMAVf+VA6sC6wAcACAAJAAAATIXHgEXFhUUBw4BBwYjIicuAScmNTQ3PgE3NjMTESMREzUjFQIAWE5OdCEiIiF0Tk5YWE5OdCEiIiF0Tk5YK1ZWVgLrIiF0Tk5YWE5OdCEiIiF0Tk5YWE5OdCEi/YABAP8AAVVVVQAAAAACAID/wAOAAsAABAA2AAABESMRMxcWFx4BFxYVFAcOAQcGIyInLgEnJjU0Nz4BNzY3Fw4BFRQXHgEXFjMyNz4BNzY1NCYnAitWVs4fGRkjCgkeHmlGRVBQRUZpHh4JCiMZGR88MjwYF1E3Nj4+NjdRFxg8MwLA/lUBq10aICFKKSksUEVGaR4eHh5pRkVQLCkpSiEgGjwpeEY+NjdRFxgYF1E3Nj5GeCkAAAAAAgB0/6YDjALaAE4AWgAAARceAQ8BDgEvAQ4BDwEOASsBIiYvAS4BJwcGJi8BJjY/AS4BNTQ2NycuAT8BPgEfAT4BPwE+ATsBMhYfAR4BFzc2Fh8BFgYPAR4BFRQGBwUyNjU0JiMiBhUUFgMxVQYDBFIDDwdmDyMTDwELCKQICwEQEyIQZgcOBFIDAwVXAgECAVYGAwRSAw8HZg8jEw8BCwikCAsBEBMiEGYHDgRSAwMFVwIBAQH+zz9bWz8/W1sBGEQEDweNBwUCKQwUCGwICgoIbAgUDCkCBQeNBw8ERAoUCgoUCkQEDweNBwUCKQwUCGwICgoIbAgUDCkCBQeNBw8ERAoUCgoUCnJbPz9bWz8/WwAAAwArAAAD1QKAABsANwBDAAABMhceARcWFwYHDgEHBiMiJy4BJyYnNjc+ATc2EzI3PgE3NjU0Jy4BJyYjIgcOAQcGFRQXHgEXFhMyFhUUBiMiJjU0NgIAUElJei8vGxsvL3pJSVBQSUl6Ly8bGy8veklJUCwnJzoREBAROicnLCwnJzoREBAROicnLDVLSzU1S0sCgBgXVTs7RkY7O1UXGBgXVTs7RkY7O1UXGP3rEBE6JycsLCcnOhEQEBE6JycsLCcnOhEQAVVLNTVLSzU1SwAAAAACAKv/awNVAxUAGQAyAAABMhceARcWFRQGByc+ATU0Jy4BJyYjFSc3FRE1Fwc1IicuAScmNTQ2NxcOARUUFx4BFxYCAEc+Pl0bGhwZPg8PFBRGLi81q6urq0c+Pl0bGhwZPg8PFBRGLi8ClRobXT4+RzJcKD8aPSA1Ly5GFBSAq6qA/auAq6qAGhtdPj5HMlwoPxo9IDUvLkYUFAAIAFf/lwOrAukAAwAHAAsAFAAcACUALgBNAAABFwURHwEFERcnESUDDgEHJz4BNxUHDgEHIz4BNwMeARcHLgEnMxM3HgEXFS4BJwEUBw4BBwYHNTY3PgE3NjU0Jy4BJyYnNRYXHgEXFhUCLX7/AIJ+/wCCggEA1i5VIz0wc0DiHCQFVwcxJwgFJBw9JzEHV0Q9I1UuQHMwArkeHWdGRlA/NjZQFxYWF1A2Nj9QRkZnHR4Bnl7AAYBiXsABgGJi/oDAAVIFJBw9JzEHV4EjVS5AczD+xy5UJD0wc0D+4T0cJAVXBzEnAUpTSUpxJSQJVwgeHVs5OkFBOjlbHR4IVwkkJXFKSVMAAAABANUAFQMrAmsACwAAASERIxEhNSERMxEhAyv/AFb/AAEAVgEAARX/AAEAVgEA/wAAAAAABgBV/+sDgAKVAAsAEQAcACEAJgArAAA3NTMVIzUzNSM1MzUDNSM1MxUHNTMVBzMVIzU3IxMhFSE1ETUhFSERNSEVIVWAgFYrKysrVlaATEyATU3WAlX9qwJV/asCVf2rayqqKhYqFgGAgCqqgComWiomWgEAVlb9qlZWAQBWVgAFAFX/lQOrAusAHAA4AEQAUABYAAABMhceARcWFRQHDgEHBiMiJy4BJyY1NDc+ATc2MxEyNz4BNzY1NCcuAScmIyIHDgEHBhUUFx4BFxYTIiY1NDYzMhYVFAYhIiY1NDYzMhYVFAYTIiYnIQ4BIwIAWE5OdCEiIiF0Tk5YWU1OdCEiIiF0Tk1ZRz4+XRsaGhtdPj5HRz4+XRsaGhtdPj7cGiYmGhslJf67GyUlGxomJntLdRoBtBp1SwLrIiF0Tk5YWE5OdCEiIiF0Tk5YWE5OdCEi/QAaG10+PkdHPj5dGxoaG10+PkdHPj5dGxoBgCUbGiYmGhslJRsaJiYaGyX+6lRCQlQAAAABAQD/lQMrAusAIgAAATIXHgEXFhUUBw4BBwYjIiYnNjc+ATc2NTQnLgEnJic+ATMBgFhOTnQhIiIhdE5OWCJAHkE3N08WFxcWTzc3QR5AIgLrIiF0Tk5YWE5OdCEiCgoUKCdqQUFISEFBaicoFAoKAAAAAAMAHf9dA+MDIwAPACsAOAAAARcHFSMHJyM1Jzc1MzcXMwEyNz4BNzY1NCcuAScmIyIHDgEHBhUUFx4BFxYTMhYVFAYjIiY1NDYzA1WOjsiNjciOjsiNjcj+qzUvLkYUFBQURi4vNTUvLkYUFBQURi4vNUdkZEdHZGRHAc2NjciOjsiNjciOjv2rFBRGLi81NS8uRhQUFBRGLi81NS8uRhQUAatkR0dkZEdHZAAFAID/wAOAAsAAKAA0AEAATABYAAABMhceARcWFRQHDgEHBisBIgYVFBYXHgEVFAYjIicuAScmNTQ3PgE3NgMyNjU0JiMiBhUUFjcyNjU0JiMiBhUUFjMyNjU0JiMiBhUUFhcyNjU0JiMiBhUUFgIAUEVGaR4eERE5JycsTBomCQcICSUbUEVGaR4eHh5pRkWbGyUlGxomJpobJSUbGiYm8BomJhobJSWbGiYmGhslJQLAGxtcPj9GLCcnOhERJRsMFggJFgwbJR4eaUZFUFBFRmkeHv6AJRsbJSUbGyWrJRsaJiYaGyUlGxomJhobJaslGxslJRsbJQAAAAABASv/lQLVAusABwAAASEDMwERIxEBKwGqqqr+1oAC6/6q/gABgAHWAAAAAAQAgP+VA4ADFQADAAcAJwBEAAABFSE1ExEzEQEeARUUBw4BBwYjIicuAScmNTQ3PgE3NjMyFhc3HgEXATI3PgE3NjU0Jy4BJyYjIgcOAQcGFRQXHgEXFjMCgP8AVVYBASctHh5oRkZQUEZGaB4eHh5pRkVQRHoyPBEeDv6XPjY3URcYGBdRNzY+PjY3URcYGBdRNzY+AxVVVf3WAQD/AAEaMnpET0ZGaB4fHx5oRkZPUEZGaB4eLCg8DR4R/aoXGFE2Nj4+NzZRGBcXGFE2Nz4+NjZRGBcAAAkAK/+CA9UDKQADAAcACwAPABMAFwAzADcAOwAAAQcnNwMVIzUBFSM1BQcnNwM3FwcTMxUjATIXHgEXFhUUBw4BBwYjIicuAScmNTQ3PgE3NhM1MxUlNxcHASA8TT0pgAIAVgGUTTxMTDtNPCmAgP6rNS8uRhQUFBRGLi81NS8uRhQUFBRGLi8KVv5sTTxMAnE8TTz+wlVVAal+fqdNPE39ezxMPQGUVQEqFBRFLy81NS4vRRUUFBVFLy41NS8vRRQU/S1+fqdNPE0AAAIAgP+9A4AC6wAFAAoAAC0BFwkBNwUJAgcCAAE6Rv6A/oBFATv+gAGAAYBGKfU2/tUBKzWIASsBK/7VNgAAAAACAFX/lQOrAusAHAAoAAABMhceARcWFRQHDgEHBiMiJy4BJyY1NDc+ATc2MxMnNycHJwcXBxc3FwIAWE5OdCEiIiF0Tk5YWE5OdCEiIiF0Tk5Y1ZmZPJmZPJmZPJmZAusiIXROTlhYTk50ISIiIXROTlhYTk50ISL9vJmZPJmZPJmZPJmZAAAAAQCRABUDgAJRAAUAACUBFwEnNwGAAcQ8/gDvPY4Bwzz+AO88AAAAAAEBAACVAwAB0QAFAAABFwkBNxcCxDz/AP8APMQB0Tz/AAEAPMMAAAACAKv/lQNVAyMAJgA5AAABFhceARcWFRQHDgEHBiMiJy4BJyY1NDc+ATc2NwcUFjMyNjU0JjEDMjc+ATc2NTQmJw4BBw4BFRQWAkA/MzNJExQaG10+PkdHPj5dGxoJCSQaGSABWUJCUCBMKiUmNxAQDA0gbDk4QFEDIzI+P5FRUVZHPj5dGxsbG10+Pkc2MzRgLCwmD0JeXkJEiPzyEBE3JSYqLVYqLDcMC0Y0N08AAAIAVf/AA6sC6wAJABMAAAEHEyUFEyclGwEDFyc3LwEPARcHA6vpRv74/vhG6QEzeHh4oSuOu0lJuo0qAbbK/tSfnwEsyhoBG/7l/t9htnsQrawQe7cAAAABAAAAATMzF648mV8PPPUACwQAAAAAANx9KKMAAAAA3H0oowAA/10D4wMpAAAACAACAAAAAAAAAAEAAAMz/zQAAAQAAAAAAAPjAAEAAAAAAAAAAAAAAAAAAAAcBAAAAAAAAAAAAAAAAAAAAAQAANUEAACRBAAAVQQAAFUEAACABAAAdAQAACsEAACrBAAAVwQAANUEAABVBAAAVQQAAQAEAAAdBAAAgAQAASsEAACABAAAKwQAAIAEAABVBAAAkQQAAQAEAACrBAAAVQAAAAAACgAUAB4AQABUALgA9gFMAdYCQAKOAxIDLANsA/AEKgSABP4FFAWABeYGBgZKBl4GcgbKBvYAAAABAAAAHABbAAkAAAAAAAIAAAAAAAAAAAAAAAAAAAAAAAAADgCuAAEAAAAAAAEABgAAAAEAAAAAAAIABwBXAAEAAAAAAAMABgAzAAEAAAAAAAQABgBsAAEAAAAAAAUACwASAAEAAAAAAAYABgBFAAEAAAAAAAoAGgB+AAMAAQQJAAEADAAGAAMAAQQJAAIADgBeAAMAAQQJAAMADAA5AAMAAQQJAAQADAByAAMAAQQJAAUAFgAdAAMAAQQJAAYADABLAAMAAQQJAAoANACYd2xlZDEyAHcAbABlAGQAMQAyVmVyc2lvbiAxLjIAVgBlAHIAcwBpAG8AbgAgADEALgAyd2xlZDEyAHcAbABlAGQAMQAyd2xlZDEyAHcAbABlAGQAMQAyUmVndWxhcgBSAGUAZwB1AGwAYQByd2xlZDEyAHcAbABlAGQAMQAyRm9udCBnZW5lcmF0ZWQgYnkgSWNvTW9vbi4ARgBvAG4AdAAgAGcAZQBuAGUAcgBhAHQAZQBkACAAYgB5ACAASQBjAG8ATQBvAG8AbgAuAAAAAwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==) format('woff');}:root {	--c-x: #333;	--c-1: #111;	--c-f: #fff;	--c-2: #222;	--c-3: #333;	--c-4: #444;	--c-5: #555;	--c-6: #666;	--c-8: #888;	--c-b: #bbb;	--c-c: #ccc;	--c-e: #eee;	--c-d: #ddd;	--c-r: #831;	--t-b: 0.5;	--c-o: rgba(34, 34, 34, 0.9);	--c-tb : rgba(34, 34, 34, var(--t-b));	--c-tba: rgba(102, 102, 102, var(--t-b));	--c-tbh: rgba(51, 51, 51, var(--t-b));	/*following are internal*/	--th: 70px;	--tp: 70px;	--bh: 63px;	--tbp: 14px 14px 10px 14px;	--bbp: 9px 0 7px 0;	--bhd: none;	--bmt: 0px;}body {  background: var(--c-x);  justify-content: center;  align-items: center;}.wrapper {	position: fixed;	top: 0;	left: 0;	right: 0;	background: var(--c-tb);	z-index: 1;}.icons {	font-family: 'WIcons';	font-style: normal;	font-size: 24px;	line-height: 1;	display: inline-block;	margin: -2px 0 4px 0;}.tab {	background-color: transparent;	color: var(--c-d);}.tab-label {	margin: 0 0 -5px 0;	padding-bottom: 4px;}.sliderdisplay {	content:'';	position: absolute;	top: 13px; bottom: 13px;	left: 10px; right: 10px;	background: var(--c-4);	border-radius: 17px;	pointer-events: none;	z-index: -1;}.sliderwrap {	height: 30px;	width: 240px;	position: relative;}.hd {	display: var(--bhd);}#briwrap {	float: right;	margin-top: var(--bmt);}.tab button {	background-color: transparent;	float: left;	border: none;	transition: color 0.3s, background-color 0.3s;	font-size: 17px;	color: var(--c-c);}.top button {	padding: var(--tbp);}.tab button:hover {	background-color: var(--c-tbh);	color: var(--c-e);}.tab button.active {	background-color: var(--c-tba) !important;	color: var(--c-f);}.buttonwrap .active {	background-color: var(--c-6) !important;	color: var(--c-f);}#liveview {	height: 4px;	display: none;	width: 100%;	border: 0px;}"