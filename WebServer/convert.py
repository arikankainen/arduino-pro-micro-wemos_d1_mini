import sys
import os

def read_file(file_path):
    """ Reads the content of a file and returns it as a string. """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read().strip()
    except FileNotFoundError:
        print(f"Warning: {file_path} not found!")
        return ""

def escape_quotes(content):
    """ Escapes quotes in the content for C++ raw literals. """
    return content.replace('\"', '\"')

def generate_cpp_header(html_content, css_content, js_content):
    """ Combines HTML, CSS, and JS into a single C++ header file. """
    
    if css_content:
        html_content = html_content.replace('<link rel="stylesheet" href="index.css" />', f"<style>\n{css_content}\n</style>")

    if js_content:
        html_content = html_content.replace('<script src="index.js"></script>', f"<script>\n{js_content}\n</script>")

    cpp_content = '''#ifndef HTML_FILE_H
#define HTML_FILE_H

const char htmlPage[] PROGMEM = R"rawliteral(
''' + html_content + '''
)rawliteral";

#endif // HTML_FILE_H
'''
    return cpp_content

if __name__ == "__main__":
    html_content = read_file("WebServer/index.html")
    css_content = read_file("WebServer/index.css")
    js_content = read_file("WebServer/index.js")

    cpp_content = generate_cpp_header(html_content, css_content, js_content)

    with open("ESP8266/html_file.h", "w", encoding="utf-8") as output_file:
        output_file.write(cpp_content)

    print("Successfully generated 'html_file.h'")
