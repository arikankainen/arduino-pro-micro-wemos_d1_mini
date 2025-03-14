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
    font-family: 'Open Sans', sans-serif;
    -webkit-tap-highlight-color: transparent;
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
    min-height: 80px;
    resize: vertical;

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
    margin-bottom: 1rem;
}

.tab {
    font-size: 20px;
    font-weight: 800;
    text-decoration: none;
    text-transform: uppercase;
    letter-spacing: 3px;
    padding: 5px 15px;
    line-height: 1;
}

.active-tab {
    color: #bbb;
    border-bottom: 1px solid #bbb;
    margin-bottom: -1px;
}

.inactive-tab {
    color: #888;
}

.active-tab:hover {
    color: #ddd;
}

.inactive-tab:hover {
    color: #aaa;
}

.line {
    border-bottom: 1px solid #333;
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
    gap: 5px;
}

.preset-title {
    font-size: 14px;
    color: #888;
}

.preset-name-and-button {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
    width: 100%;
}

.fixed-width-font {
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
    gap: 10px;
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

.network-connected {
    background-color: #244424;
    color: #94c094;
    text-transform: uppercase;
    font-size: 10px;
    letter-spacing: 1px;
    padding: 2px 4px;
    border-radius: 3px;
}

.network-name {
    font-size: 14px;
    font-weight: 600;
}

.network-info {
    display: flex;
    gap: 5px;
    font-size: 12px;
    font-weight: 400;
    color: #888;
}

/*** WARNING BOXES ***/

.connection-button {
    border: none;
    border-radius: 3px;
    padding: 5px 10px;
    cursor: pointer;
    transition: background-color 0.15s;
}

.connect-button {
    background-color: #595;
    color: #cfc;
}

.disconnect-button {
    background-color: #955;
    color: #fcc;
}

.connect-button:hover {
    background-color: #6a6;
}

.disconnect-button:hover {
    background-color: #a66;
}

.connect-button:disabled {
    background-color: #363;
    color: #8a8;
}

.disconnect-button:disabled {
    background-color: #633;
    color: #a88;
}

.connect-button:disabled:hover {
    background-color: #363;
    color: #8a8;
}

.disconnect-button:disabled:hover {
    background-color: #633;
    color: #a88;
}

.connection-warning-box {
    display: flex;
    flex-direction: column;
    border-radius: 3px;
    padding: 10px;
    font-size: 14px;
}

.connect-warning-box {
    background-color: #222a22;
    border: 1px solid #464;
    color: #cfc;
}

.disconnect-warning-box {
    background-color: #2a2222;
    border: 1px solid #644;
    color: #fcc;
}

.connection-warning-box-top {
    display: flex;
    justify-content: space-between;
    align-items: center;
    gap: 10px;
    color: inherit;
}

.connection-warning-box-content {
    display: flex;
    flex-direction: column;
    gap: 10px;
    font-size: 12px;
    text-align: left;
    font-weight: 400;
    max-height: 500px;
    overflow: hidden;
    opacity: 1;
    transition: max-height 0.15s ease-in-out, opacity 0.15s ease-in-out;
}

.connection-warning-box-content-hidden {
    max-height: 0;
    opacity: 0;
}

.connection-warning-box-text {
    margin-top: 5px;
}

.connect-warning-box-text {
    color: #ada;
}

.disconnect-warning-box-text {
    color: #daa;
}

.chevron {
    width: 8px;
    height: 8px;
    transition: transform 0.15s ease-in-out, margin 0.15s ease-in-out;
}

.connect-chevron {
    border-right: 1px solid #cfc;
    border-bottom: 1px solid #cfc;
}

.disconnect-chevron {
    border-right: 1px solid #fcc;
    border-bottom: 1px solid #fcc;
}

.chevron-down {
    transform: rotate(45deg);
    margin-top: -5px;
}

.chevron-up {
    transform: rotate(-135deg);
    margin-bottom: -5px;
}

.chevron-container {
    display: flex;
    justify-content: center;
    align-items: center;
    padding: 8px 5px;
    cursor: pointer;
}

@media screen and (min-width: 768px) {
    #password {
        max-width: 300px;
    }

    .connection-warning-box {
        max-width: 300px;
    }
}

/****/

.editor-container {
    border: 1px solid #444;
    border-radius: 3px;
    overflow: hidden;
    width: 100%;
    height: auto;
}

.CodeMirror-hints {
    background: #222 !important;
    border: 1px solid #444 !important;
    color: #ddd !important;
    font-family: monospace;
    font-size: 14px;
    max-height: 600px !important;
}

.CodeMirror-hint {
    padding: 5px 10px !important;
    color: #eee !important;
}

.CodeMirror-hint-active {
    background: #303030 !important;
    color: #eee !important;
}

.CodeMirror * {
    font-family: 'Courier New', Courier, monospace;
}
</style>
        <link rel="preconnect" href="https://fonts.googleapis.com" />
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
        <link
            href="https://fonts.googleapis.com/css2?family=Open+Sans:ital,wght@0,300..800;1,300..800&display=swap"
            rel="stylesheet"
        />
        <link
            rel="stylesheet"
            href="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.65.15/codemirror.min.css"
        />
        <link
            rel="stylesheet"
            href="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.65.5/addon/hint/show-hint.min.css"
        />
        <link
            rel="stylesheet"
            href="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.65.15/theme/material-darker.min.css"
        />
        <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.65.5/codemirror.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.65.5/addon/hint/show-hint.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.65.5/addon/hint/javascript-hint.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.65.5/mode/javascript/javascript.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/codemirror/5.65.5/addon/hint/javascript-hint.min.js"></script>
    </head>

    <body>
        <main>
            <div class="tab-container">
                <a href="/" class="tab active-tab">Presets</a>
                <a href="/settings" class="tab inactive-tab">Settings</a>
            </div>

            <div id="presets-container"></div>
        </main>

        <script>
const editors = [];

async function savePreset(preset) {
    const content = editors[preset - 1].getValue();
    const data = JSON.stringify({ preset: preset.toString(), content });

    try {
        const response = await fetch('/save_preset', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: data,
        });

        await response.text();
    } catch (error) {
        console.error('Error:', error);
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
        editors[preset - 1].setValue(responseText);
    } catch (error) {
        console.error('Error:', error);
    }
}

function createPresetElement(preset) {
    const presetElement = document.createElement('div');
    presetElement.className = 'preset-container';

    const editorTitle = document.createElement('div');
    editorTitle.className = 'preset-title';
    editorTitle.innerHTML = `Preset ${preset}`;

    const editorContainer = document.createElement('div');
    editorContainer.className = 'editor-container';

    const textarea = document.createElement('textarea');
    textarea.id = `editor${preset}`;

    editorContainer.appendChild(textarea);

    const button = document.createElement('button');
    button.innerHTML = 'Save';
    button.onclick = () => savePreset(preset);

    presetElement.appendChild(editorTitle);
    presetElement.appendChild(editorContainer);
    presetElement.appendChild(button);

    return presetElement;
}

function createPresets() {
    const container = document.getElementById('presets-container');

    for (let i = 1; i <= 10; i++) {
        container.appendChild(createPresetElement(i));

        const keys = [
            'KEY_UP_ARROW',
            'KEY_DOWN_ARROW',
            'KEY_LEFT_ARROW',
            'KEY_RIGHT_ARROW',
            'KEY_LEFT_CTRL',
            'KEY_LEFT_SHIFT',
            'KEY_LEFT_ALT',
            'KEY_LEFT_GUI',
            'KEY_RIGHT_CTRL',
            'KEY_RIGHT_SHIFT',
            'KEY_RIGHT_ALT',
            'KEY_RIGHT_GUI',
            'KEY_TAB',
            'KEY_CAPS_LOCK',
            'KEY_BACKSPACE',
            'KEY_RETURN',
            'KEY_MENU',
            'KEY_INSERT',
            'KEY_DELETE',
            'KEY_HOME',
            'KEY_END',
            'KEY_PAGE_UP',
            'KEY_PAGE_DOWN',
            'KEY_NUM_LOCK',
            'KEY_KP_SLASH',
            'KEY_KP_ASTERISK',
            'KEY_KP_MINUS',
            'KEY_KP_PLUS',
            'KEY_KP_ENTER',
            'KEY_KP_1',
            'KEY_KP_2',
            'KEY_KP_3',
            'KEY_KP_4',
            'KEY_KP_5',
            'KEY_KP_6',
            'KEY_KP_7',
            'KEY_KP_8',
            'KEY_KP_9',
            'KEY_KP_0',
            'KEY_KP_DOT',
            'KEY_ESC',
            'KEY_F1',
            'KEY_F2',
            'KEY_F3',
            'KEY_F4',
            'KEY_F5',
            'KEY_F6',
            'KEY_F7',
            'KEY_F8',
            'KEY_F9',
            'KEY_F10',
            'KEY_F11',
            'KEY_F12',
            'KEY_PRINT_SCREEN',
            'KEY_SCROLL_LOCK',
            'KEY_PAUSE',
        ];

        const delays = [50, 100, 200, 500, 1000, 2000, 5000, 10000];

        const keyCommands = keys.map((key) => {
            return {
                text: `{ key: "${key}" },`,
                displayText: `{ key: "${key}" }`,
            };
        });

        const keyCommandsWithRepeat = keys.map((key) => {
            return {
                text: `{ key: "${key}", repeat: 2 },`,
                displayText: `{ key: "${key}", repeat: 2 }`,
            };
        });

        const delayCommands = delays.map((delay) => {
            return {
                text: `{ delay: "${delay}" },`,
                displayText: `{ key: "${delay}" }`,
            };
        });

        const textCommands = [
            {
                text: `{ text: "" },`,
                displayText: `{ text: "" }`,
            },
        ];

        let commands = [
            ...keyCommands,
            ...keyCommandsWithRepeat,
            ...delayCommands,
            ...textCommands,
        ];

        const editor = CodeMirror.fromTextArea(document.getElementById(`editor${i}`), {
            mode: 'javascript',
            theme: 'material-darker',
            lineNumbers: true,
            extraKeys: { 'Ctrl-Space': 'autocomplete' },
            hintOptions: {
                hint: function (cm) {
                    const cur = cm.getCursor();
                    const token = cm.getTokenAt(cur);
                    const word = token.string.trim();

                    list = commands.filter((cmd) =>
                        cmd.text.toLowerCase().includes(word.toLowerCase())
                    );

                    return {
                        list,
                        from: CodeMirror.Pos(cur.line, token.start),
                        to: CodeMirror.Pos(cur.line, token.end),
                    };
                },
                completeSingle: false,
                maxHeight: '600px',
            },
        });

        editors.push(editor);

        function resizeEditor() {
            const doc = editor.getDoc();
            const lineCount = doc.lineCount();
            const lineHeight = editor.defaultTextHeight();
            let height = lineCount * lineHeight + 20;
            if (height < 90) height = 90;

            editor.setSize(null, height);
        }

        editor.on('change', resizeEditor);
        resizeEditor();
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
