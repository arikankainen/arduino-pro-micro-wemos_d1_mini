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

def generate_index_cpp_header():
    index_html = read_file("WebServer/index.html")
    styles_css = read_file("WebServer/styles.css")
    index_js = read_file("WebServer/index.js")
    
    if styles_css:
        index_html = index_html.replace('<link rel="stylesheet" href="styles.css" />', f"<style>\n{styles_css}\n</style>")

    if index_js:
        index_html = index_html.replace('<script src="index.js"></script>', f"<script>\n{index_js}\n</script>")

    cpp_content = '''#ifndef HTML_INDEX_H
#define HTML_INDEX_H

const char indexPage[] PROGMEM = R"rawliteral(
''' + index_html + '''
)rawliteral";

#endif // HTML_INDEX_H
'''
    return cpp_content

def generate_settings_cpp_header():
    settings_html = read_file("WebServer/settings.html")
    styles_css = read_file("WebServer/styles.css")
    settings_js = read_file("WebServer/settings.js")
    
    if styles_css:
        settings_html = settings_html.replace('<link rel="stylesheet" href="styles.css" />', f"<style>\n{styles_css}\n</style>")

    if settings_js:
        settings_html = settings_html.replace('<script src="settings.js"></script>', f"<script>\n{settings_js}\n</script>")

    cpp_content = '''#ifndef HTML_SETTINGS_H
#define HTML_SETTINGS_H

const char settingsPage[] PROGMEM = R"rawliteral(
''' + settings_html + '''
)rawliteral";

#endif // HTML_SETTINGS_H
'''
    return cpp_content

if __name__ == "__main__":
    index_content = generate_index_cpp_header()
    settings_content = generate_settings_cpp_header()

    with open("ESP8266/html_index.h", "w", encoding="utf-8") as output_file:
        output_file.write(index_content)
    print("Successfully generated 'html_index.h'")

    with open("ESP8266/html_settings.h", "w", encoding="utf-8") as output_file:
        output_file.write(settings_content)
    print("Successfully generated 'html_settings.h'")

