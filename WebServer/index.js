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

        const macroCommands = [
            { text: 'macro_start', displayText: 'macro_start - Begin a new macro' },
            { text: 'macro_end', displayText: 'macro_end - End the macro' },
            { text: 'click', displayText: 'click - Simulates a mouse click' },
            { text: 'type_text', displayText: 'type_text - Type a string' },
            { text: 'delay(1000);', displayText: 'delay(ms) - Wait for X milliseconds' },
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

                    const commands = [
                        {
                            text: 'key.enter; ',
                            displayText: 'key.enter - Simulate Enter key press',
                        },
                        { text: 'key.left; ', displayText: 'key.left - Move left' },
                        { text: 'key.right; ', displayText: 'key.right - Move right' },
                        { text: 'delay.50; ', displayText: 'delay.50 - Pause for 50ms' },
                        { text: 'delay.100; ', displayText: 'delay.100 - Pause for 100ms' },
                        { text: 'delay.500; ', displayText: 'delay.500 - Pause for 500ms' },
                    ];

                    const list = commands.filter((cmd) => cmd.text.startsWith(token.string));
                    return {
                        list: list,
                        from: CodeMirror.Pos(cur.line, token.start),
                        to: CodeMirror.Pos(cur.line, token.end),
                    };
                },
                completeSingle: false, // Don't auto-select first suggestion
            },
        });

        CodeMirror.registerHelper('hint', 'javascript', function (editor) {
            const cursor = editor.getCursor();
            const token = editor.getTokenAt(cursor);

            // Suggest commands matching the current text
            const suggestions = macroCommands
                .filter((cmd) => cmd.text.startsWith(token.string))
                .map((cmd) => ({ text: cmd.text, displayText: cmd.displayText }));

            return {
                list: suggestions,
                from: CodeMirror.Pos(cursor.line, token.start),
                to: CodeMirror.Pos(cursor.from.line, token.end),
            };
        });

        // Attach the auto-complete to Ctrl+Space
        editor.setOption('extraKeys', {
            'Ctrl-Space': 'autocomplete',
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
