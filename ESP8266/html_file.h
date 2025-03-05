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

input[type='text'],
textarea {
    background-color: #222;
    border: 1px solid #444;
    border-radius: 3px;
    padding: 5px;
}

textarea {
    width: 100%;
    height: 80px;

    scrollbar-color: #555 #333; /* For Firefox (thumb, track) */
}

textarea::-webkit-scrollbar-track {
    background: #333; /* Dark track */
}

textarea::-webkit-scrollbar-thumb {
    background: #555; /* Dark thumb (the draggable part) */
}

textarea::-webkit-scrollbar-thumb:hover {
    background: #777; /* Lighter thumb on hover */
}

textarea:focus,
input:focus {
    border-color: #666; /* Green border when focused */
    outline: none; /* Remove the default outline */
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

#response-log {
    background-color: #282828;
    color: #888;
    height: 150px;
    font-family: 'Courier New', Courier, monospace;
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

/*******/

#presets-container {
    display: flex;
    flex-direction: column;
    gap: 1rem;
}

.preset-container {
    display: flex;
    margin-top: 1rem;
    flex-direction: column;
    justify-content: flex-start;
    align-items: flex-start;
    gap: 1rem;
}

.preset-name-and-button {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
    width: 100%;
}
</style>
    </head>

    <body>
        <main>
            <h1>ESP8266 Web Server</h1>
            <button onclick="getNetworks()">Scan networks</button>

            <div id="presets-container"></div>

            <div id="response-container">
                <div id="response-title">Server response</div>
                <textarea id="response-log" readonly></textarea>
            </div>
        </main>

        <script>
async function savePreset(preset) {
    const content = document.getElementById('preset' + preset).value;
    const data = JSON.stringify({ preset: preset.toString(), content });

    try {
        const response = await fetch('/save_preset', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: data,
        });

        const responseText = await response.text();
        log(responseText);
    } catch (error) {
        console.error('Error:', error);
        log('Failed to save preset #' + preset);
    }
}

async function getPreset(preset) {
    const data = JSON.stringify({ preset: preset.toString() });

    try {
        const response = await fetch('/get_preset', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: data,
        });

        const responseText = await response.text();
        document.getElementById('preset' + preset).value = responseText;
    } catch (error) {
        console.error('Error:', error);
        log('Failed to load preset #' + preset);
    }
}

async function getNetworks() {
    try {
        const response = await fetch('/scan', {
            method: 'GET',
        });

        const responseJson = await response.json();
        console.log({ responseJson });
    } catch (error) {
        console.error('Error:', error);
        log('Failed to get networks');
    }
}

function log(newText) {
    const now = new Date();
    const day = String(now.getDate()).padStart(2, '0');
    const month = String(now.getMonth() + 1).padStart(2, '0');
    const year = now.getFullYear();
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    const formattedDate = `${day}.${month}.${year} ${hours}:${minutes}:${seconds}`;

    const textarea = document.getElementById('response-log');
    const lineBreak = textarea.value ? '\n' : '';
    const logEntry = `${lineBreak}[${formattedDate}] ${newText}`;
    textarea.value += logEntry;
    textarea.scrollTop = textarea.scrollHeight;
}

function createPresetElement(preset) {
    const presetElement = document.createElement('div');
    presetElement.className = 'preset-container';
    presetElement.innerHTML = `
        <div class="preset-name-and-button">
            <label for="preset${preset}">Preset #${preset}</label>
            <textarea id="preset${preset}" name="preset${preset}"></textarea>
        </div>

        <button onclick="savePreset(${preset})">Save</button>
    `;

    return presetElement;
}

function createPresets() {
    const presetsContainer = document.getElementById('presets-container');

    for (let i = 1; i <= 10; i++) {
        presetsContainer.appendChild(createPresetElement(i));
    }
}

(async () => {
    createPresets();

    for (let i = 1; i <= 10; i++) {
        await getPreset(i);
    }
})();
</script>
    </body>
</html>
)rawliteral";

#endif // HTML_FILE_H
