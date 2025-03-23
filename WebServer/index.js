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
