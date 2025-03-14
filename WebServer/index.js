const editors = [];

async function savePreset(preset) {
    const content = editors[preset - 1].getValue();
    let data;

    try {
        const contentAsJavascript = eval(content);
        data = JSON.stringify({ preset: preset.toString(), content: contentAsJavascript });
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
