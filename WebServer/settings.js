let selectedNetwork = null;

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

function createNetworkElement(network, index) {
    const networkElement = document.createElement('div');
    networkElement.onclick = () => selectNetwork(index);
    networkElement.className = 'network-container';
    networkElement.innerHTML = `
        <div class="network-container-details" onclick="selectNetwork(${index}, this)">
            <div style="display: flex; gap: 5px;">
                <div style="display: flex; flex-direction: column; gap: 2px;">    
                    <div style="text-align: right;">SSID:</div>
                    <div style="text-align: right;">Channel:</div>
                    <div style="text-align: right;">Signal:</div>
                    <div style="text-align: right;">Encryption:</div>
                </div>
                
                <div style="display: flex; flex-direction: column; gap: 2px;">    
                    <div><strong>${network.ssid}</strong></div>
                    <div><strong>${network.channel}</strong></div>
                    <div><strong>${network.signalStrength}</strong></div>
                    <div><strong>${network.encryption}</strong></div>
                </div>
            </div>
        </div>
    `;

    return networkElement;
}

function createPresets() {
    const container = document.getElementById('presets-container');

    for (let i = 1; i <= 10; i++) {
        container.appendChild(createPresetElement(i));
    }
}

function renderNetworks(networks) {
    const container = document.getElementById('networks-container');

    for (let i = 0; i < networks.length; i++) {
        container.appendChild(createNetworkElement(networks[i], i));
    }
}

function selectNetwork(index, element) {
    console.log({ index });
    const allNetworks = document.querySelectorAll('.network-container');
    allNetworks.forEach((network) => network.classList.remove('selected'));

    if (index !== selectedNetwork) {
        const selectedElement = allNetworks[index];
        if (selectedElement) {
            selectedElement.classList.add('selected');
        }
        selectedNetwork = index;
    } else {
        selectedNetwork = null;
    }
}

(async () => {
    createPresets();

    for (let i = 1; i <= 10; i++) {
        await getPreset(i);
    }

    const networks = {
        networks: [
            {
                ssid: 'family',
                channel: 1,
                signalStrength: '-89 dB (Very Poor)',
                encryption: 'WPA2',
            },
            {
                ssid: 'family',
                channel: 1,
                signalStrength: '-86 dB (Very Poor)',
                encryption: 'WPA2',
            },
            {
                ssid: 'DIRECT-73M2020 Series',
                channel: 6,
                signalStrength: '-47 dB (Excellent)',
                encryption: 'WPA2',
            },
            {
                ssid: 'BUFFALO',
                channel: 6,
                signalStrength: '-50 dB (Excellent)',
                encryption: 'WPA2',
            },
            {
                ssid: 'Koti_05CD',
                channel: 7,
                signalStrength: '-91 dB (Very Poor)',
                encryption: 'WPA2',
            },
        ],
    };

    renderNetworks(networks.networks);
})();
