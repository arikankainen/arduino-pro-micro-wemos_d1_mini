#ifndef HTML_INDEX_H
#define HTML_INDEX_H

const char indexPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <title>Presets</title>
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
input[type='password'],
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
    border-color: #666;
    outline: none;
}

textarea:disabled,
input:disabled {
    border-color: #444;
    background-color: #333;
    color: #666;
}

button {
    background-color: #555;
    border: none;
    border-radius: 3px;
    color: #ccc;
    padding: 5px 10px;
    cursor: pointer;
    transition: background-color 0.15s;
}

button:hover {
    background-color: #666;
}

button:active {
    transform: translateY(1px);
}

button:disabled {
    background-color: #333;
    color: #888;
    cursor: default;
}

button:disabled:hover {
    background-color: #333;
    color: #888;
}

button:disabled:active {
    transform: none;
}

.loader {
    align-self: center;
    width: 16px;
    height: 16px;
    border: 2px solid #aaa;
    border-bottom-color: transparent;
    border-radius: 50%;
    display: inline-block;
    box-sizing: border-box;
    animation: rotation 1s linear infinite;
}

@keyframes rotation {
    0% {
        transform: rotate(0deg);
    }
    100% {
        transform: rotate(360deg);
    }
}

.tab-container {
    display: flex;
    border-bottom: 1px solid #444;
}

.tab {
    font-size: 18px;
    font-weight: 500;
    text-decoration: none;
    text-transform: uppercase;
    letter-spacing: 4px;
    padding: 5px 15px;
    line-height: 1;
}

.active-tab {
    color: #bbb;
    border-bottom: 1px solid #bbb;
    margin-bottom: -1px;
    cursor: default;
}

.inactive-tab {
    color: #888;
}

.inactive-tab:hover {
    color: #aaa;
}

/*** PRESETS ***/

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

/*** SETTINGS ***/

#networks-container {
    display: flex;
    flex-direction: column;
    gap: 1rem;
}

.network-container {
    display: flex;
    justify-content: space-between;
    align-items: center;
    align-items: flex-start;
    background-color: #262626;
    padding: 0.5rem;
    border-radius: 5px;
    border: 1px solid #333;
    cursor: pointer;
    transition: background-color 0.15s, border-color 0.15s;
}

.network-container-details {
    display: flex;
    flex-direction: column;
    font-size: 14px;
    gap: 1px;
    pointer-events: none;
}

.network-container.selected {
    border: 1px solid #2b4e83;
    background-color: rgb(36, 44, 54);
}

.network-container-connected {
    border: 1px solid #247024;
    background-color: #244424;
    color: #94c094;
    text-transform: uppercase;
    font-size: 10px;
    letter-spacing: 1px;
    padding: 3px 5px;
    border-radius: 5px;
}
</style>
    </head>

    <body>
        <main>
            <div class="tab-container">
                <span class="tab active-tab">Presets</span>
                <a href="/settings" class="tab inactive-tab">Settings</a>
            </div>

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
    const container = document.getElementById('presets-container');

    for (let i = 1; i <= 10; i++) {
        container.appendChild(createPresetElement(i));
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

#endif // HTML_INDEX_H
