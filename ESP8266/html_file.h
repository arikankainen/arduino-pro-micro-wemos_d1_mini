#ifndef HTML_FILE_H
#define HTML_FILE_H

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <title>ESP8266 Web Server</title>
        <meta
            name="viewport"
            content="width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=2"
        />
        <style>
* {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
    color: #ccc;
}

body {
    background-color: #222;
    color: #ccc;
    font-family: Arial, sans-serif;
}

html {
    padding: 1rem;
}

main {
    display: flex;
    flex-direction: column;
    gap: 1rem;
    width: 100%;
    max-width: 800px;
    justify-self: center;
}

#form-container {
    display: flex;
    margin-top: 1rem;
    flex-direction: column;
    justify-content: flex-start;
    align-items: flex-start;
    gap: 1rem;
}

input[type='text'],
input[type='checkbox'],
textarea {
    background-color: #222;
    border: 1px solid #444;
    border-radius: 3px;
}

textarea {
    width: 100%;
    height: 80px;
}

button {
    background-color: #555;
    border: none;
    border-radius: 3px;
    color: #ccc;
    padding: 5px 10px;
    cursor: pointer;
}

#response-container {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
    margin-top: 1rem;
    padding: 10px;
    border: 1px solid #444;
    background-color: #2a2a2a;
    border-radius: 5px;
}

#response-title {
    color: #bbb;
    font-weight: 600;
    font-size: 14px;
}

#response-content {
    white-space: pre;
    font-family: monospace;
    color: #999;
    font-size: 12px;
}

.flex-row {
    display: flex;
    flex-direction: row;
}

.flex-column {
    display: flex;
    flex-direction: column;
}

.gap-05 {
    gap: 0.5rem;
}

.gap-1 {
    gap: 1rem;
}

.align-center {
    align-items: center;
}

.justify-center {
    justify-content: center;
}

.w-100p {
    width: 100%;
}
</style>
    </head>

    <body>
        <main>
            <h1>ESP8266 Web Server</h1>

            <form onsubmit="return sendFormData();">
                <div id="form-container">
                    <div class="flex-column gap-05 w-100p">
                        <label for="macro1">Macro #1:</label>
                        <textarea id="macro1" name="macro1"></textarea>
                        <!-- <input type="text" id="textinput" name="textinput" /><br /><br /> -->
                    </div>

                    <button type="submit">Save</button>
                </div>
            </form>

            <div id="response-container">
                <div id="response-title">Server response</div>
                <div id="response-content">No response yet</div>
            </div>
        </main>

        <script>
function sendFormData() {
    const macro1 = document.getElementById('macro1').value;

    const xhttp = new XMLHttpRequest();
    xhttp.open('POST', '/click', true);
    xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    xhttp.onload = function () {
        if (xhttp.status == 200) {
            document.getElementById('response-content').innerHTML = xhttp.responseText;
        }
    };

    const data = 'macro1=' + encodeURIComponent(macro1);
    xhttp.send(data);

    return false;
}
</script>
    </body>
</html>
)rawliteral";

#endif // HTML_FILE_H
