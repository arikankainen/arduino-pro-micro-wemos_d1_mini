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

const KeyCodes = {
    KEY_LEFT_CTRL: 128,
    KEY_LEFT_SHIFT: 129,
    KEY_LEFT_ALT: 130,
    KEY_LEFT_GUI: 131,
    KEY_RIGHT_CTRL: 132,
    KEY_RIGHT_SHIFT: 133,
    KEY_RIGHT_ALT: 134,
    KEY_RIGHT_GUI: 135,
    KEY_TAB: 179,
    KEY_CAPS_LOCK: 193,
    KEY_BACKSPACE: 178,
    KEY_ENTER: 176,
    KEY_RETURN: 176,
    KEY_MENU: 237,
    KEY_INSERT: 209,
    KEY_DELETE: 212,
    KEY_HOME: 210,
    KEY_END: 213,
    KEY_PAGE_UP: 211,
    KEY_PAGE_DOWN: 214,
    KEY_UP_ARROW: 218,
    KEY_DOWN_ARROW: 217,
    KEY_LEFT_ARROW: 216,
    KEY_RIGHT_ARROW: 215,
    KEY_ESC: 177,
    KEY_F1: 194,
    KEY_F2: 195,
    KEY_F3: 196,
    KEY_F4: 197,
    KEY_F5: 198,
    KEY_F6: 199,
    KEY_F7: 200,
    KEY_F8: 201,
    KEY_F9: 202,
    KEY_F10: 203,
    KEY_F11: 204,
    KEY_F12: 205,
    KEY_NUM_LOCK: 219,
    KEY_KP_SLASH: 220,
    KEY_KP_ASTERISK: 221,
    KEY_KP_MINUS: 222,
    KEY_KP_PLUS: 223,
    KEY_KP_ENTER: 224,
    KEY_KP_1: 225,
    KEY_KP_2: 226,
    KEY_KP_3: 227,
    KEY_KP_4: 228,
    KEY_KP_5: 229,
    KEY_KP_6: 230,
    KEY_KP_7: 231,
    KEY_KP_8: 232,
    KEY_KP_9: 233,
    KEY_KP_0: 234,
    KEY_KP_DOT: 235,
};

function getKeyCode(key) {
    return KeyCodes[key] || key;
}

function getKeyName(code) {
    return Object.keys(KeyCodes).find((key) => KeyCodes[key] === code) || code;
}

const customStringify = (obj) => {
    const stringified = JSON.stringify(obj, null, 4);
    const formatted = stringified
        .replace(/\n\s*/g, ' ')
        .replace(/\}, \{/g, '},\n{')
        .replace(/\[\s+{/g, '[\n{')
        .replace(/}\s+]/g, '}\n]')
        .replace(/\{/g, '    {');

    return formatted;
};

async function savePreset(preset) {
    const content = editors[preset - 1].getValue();

    const jsonContent = (() => {
        if (content === '') return content;

        const contentWithoutTrailingCommas = content.replace(/,\s*}/g, '}').replace(/,\s*\]/g, ']');
        const json = JSON.parse(contentWithoutTrailingCommas);

        if (json === '') return json;
        if (!Array.isArray(json)) return json;

        return json.map((item) => {
            if ('key' in item) {
                return {
                    ...item,
                    key: getKeyCode(item.key),
                };
            }

            return item;
        });
    })();

    let data;

    try {
        data = JSON.stringify({ preset: preset.toString(), content: jsonContent });
        console.log(data);
    } catch (error) {
        console.error('Error:', error);
        alert('Invalid JSON: ' + error);
        return;
    }

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

        const jsonContent = (() => {
            if (responseText === '') return responseText;

            const responseJson = JSON.parse(responseText);
            if (responseJson === '') return responseJson;

            if (!Array.isArray(responseJson)) return responseJson;

            return responseJson.map((item) => {
                if ('key' in item) {
                    return {
                        ...item,
                        key: getKeyName(item.key),
                    };
                }

                return item;
            });
        })();

        if (jsonContent) editors[preset - 1].setValue(customStringify(jsonContent));
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

        const keys = Object.keys(KeyCodes);
        const delays = [50, 100, 200, 500, 1000];

        const keyCommands = keys.map((key) => {
            return {
                text: `"key": "${key}"`,
                displayText: `"key": "${key}"`,
            };
        });

        const delayCommands = delays.map((delay) => {
            return {
                text: `"delay": "${delay}"`,
                displayText: `"delay": "${delay}"`,
            };
        });

        const textCommands = [
            {
                text: `"text": ""`,
                displayText: `"text": ""`,
            },
        ];

        const additionalCommands = [
            {
                text: `"repeat": 2`,
                displayText: `"repeat": 2`,
            },
            {
                text: `"press": true`,
                displayText: `"press": true`,
            },
            {
                text: `"release": true`,
                displayText: `"release": true`,
            },
            {
                text: `"release": "all"`,
                displayText: `"release": "all"`,
            },
        ];

        let commands = [...keyCommands, ...additionalCommands, ...delayCommands, ...textCommands];

        const editor = CodeMirror.fromTextArea(document.getElementById(`editor${i}`), {
            mode: 'javascript',
            theme: 'material-darker',
            lineNumbers: true,
            tabSize: 4,
            indentWithTabs: false,
            indentUnit: 4,
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

        resizeEditor();
        editor.setValue('[\n    \n]');

        editor.setOption('extraKeys', {
            Tab: (cm) => {
                cm.replaceSelection('    ', 'end');
            },
            'Shift-Tab': 'indentLess',
            'Ctrl-Space': 'autocomplete',
        });

        editor.on('change', (cm, change) => {
            resizeEditor();

            if (change.origin === 'complete') {
                const cur = cm.getCursor();
                const lineContent = cm.getLine(cur.line);
                const insertedText = change.text.join('');
                const lineWasEmpty = lineContent.replace(insertedText, '').trim() === '';

                if (lineWasEmpty) {
                    const wrappedText = `    { ${insertedText} },`;

                    cm.replaceRange(
                        wrappedText,
                        { line: cur.line, ch: 0 },
                        { line: cur.line, ch: lineContent.length }
                    );

                    if (change.text.includes('"text": ""')) {
                        cm.setCursor(cur.line, wrappedText.length - 4);
                    } else {
                        cm.setCursor(cur.line, wrappedText.length);
                    }
                }
            }
        });
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
