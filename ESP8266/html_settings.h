#ifndef HTML_SETTINGS_H
#define HTML_SETTINGS_H

const char settingsPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <title>Settings</title>
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
                <a href="/" class="tab inactive-tab">Presets</a>
                <span class="tab active-tab">Settings</span>
            </div>

            <div style="display: flex; gap: 1rem">
                <button id="refresh" onclick="getNetworks()">Refresh networks</button>
                <div id="refresh-loader"></div>
            </div>

            <div id="networks-container"></div>

            <div style="display: flex; gap: 1rem">
                <input
                    type="password"
                    id="password"
                    placeholder="Enter network password"
                    onkeyup="enableOrDisableConnectButton()"
                />
                <button id="connect" onclick="connect()">Connect</button>
                <div id="connect-loader"></div>
            </div>
        </main>

        <script>
let networks = [];
let selectedNetworkIndex = null;

async function getNetworks() {
    loading('refresh-loader', true);
    disabled('refresh', true);
    selectedNetworkIndex = null;

    try {
        const response = await fetch('/scan', {
            method: 'GET',
        });

        const responseJson = await response.json();
        networks = responseJson.networks;
        renderNetworks(networks);
    } catch (error) {
        setTimeout(() => alert(error), 300);
    } finally {
        loading('refresh-loader', false);
        disabled('refresh', false);
    }
}

async function connect() {
    loading('connect-loader', true);
    disabled('connect', true);
    disabled('password', true);
    const selectedNetwork = networks?.[selectedNetworkIndex];
    const ssid = selectedNetwork?.ssid;
    const password = document.getElementById('password').value;

    console.log({ ssid, password });

    try {
        const response = await fetch('/connect', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ network: selectedNetworkIndex }),
        });

        const responseJson = await response.json();
        alert(responseJson.message);
    } catch (error) {
        setTimeout(() => alert(error), 300);
    } finally {
        loading('connect-loader', false);
        disabled('connect', false);
        disabled('password', false);
    }
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
                    <div style="text-align: right;">Connected:</div>
                </div>
                
                <div style="display: flex; flex-direction: column; gap: 2px;">    
                    <div><strong>${network.ssid}</strong></div>
                    <div><strong>${network.channel}</strong></div>
                    <div><strong>${network.signalStrength}</strong></div>
                    <div><strong>${network.encryption}</strong></div>
                    <div><strong>${network.connected?.toString()}</strong></div>
                </div>
            </div>
        </div>
        <div class="network-container-connected" style="display: ${
            network.connected ? 'block' : 'none'
        };">Connected</div>
    `;

    return networkElement;
}

function enableOrDisableConnectButton() {
    const selectedNetwork = networks?.[selectedNetworkIndex];
    const ssid = selectedNetwork?.ssid;
    const password = document.getElementById('password').value;

    if (ssid && !!password?.trim()?.length) {
        disabled('connect', false);
    } else {
        disabled('connect', true);
    }
}

function loading(elementName, visible) {
    const container = document.getElementById(elementName);
    if (visible) container.classList.add('loader');
    else container.classList.remove('loader');
}

function disabled(elementName, disabled) {
    document.getElementById(elementName).disabled = disabled;
}

function renderNetworks(networks) {
    const container = document.getElementById('networks-container');
    container.innerHTML = '';

    for (let i = 0; i < networks.length; i++) {
        container.appendChild(createNetworkElement(networks[i], i));
    }
}

function selectNetwork(index) {
    const allNetworks = document.querySelectorAll('.network-container');
    allNetworks.forEach((network) => network.classList.remove('selected'));

    if (index !== selectedNetworkIndex) {
        const selectedElement = allNetworks[index];
        if (selectedElement) {
            selectedElement.classList.add('selected');
        }
        selectedNetworkIndex = index;
    } else {
        selectedNetworkIndex = null;
    }

    enableOrDisableConnectButton();
}

(async () => {
    getNetworks();
    enableOrDisableConnectButton();

    // const responseJson = {
    //     networks: [
    //         {
    //             ssid: 'family',
    //             channel: 1,
    //             signalStrength: '-89 dB (Very Poor)',
    //             encryption: 'WPA2',
    //             connected: false,
    //         },
    //         {
    //             ssid: 'family',
    //             channel: 1,
    //             signalStrength: '-86 dB (Very Poor)',
    //             encryption: 'WPA2',
    //             connected: false,
    //         },
    //         {
    //             ssid: 'DIRECT-73M2020 Series',
    //             channel: 6,
    //             signalStrength: '-47 dB (Excellent)',
    //             encryption: 'WPA2',
    //             connected: false,
    //         },
    //         {
    //             ssid: 'BUFFALO',
    //             channel: 6,
    //             signalStrength: '-50 dB (Excellent)',
    //             encryption: 'WPA2',
    //             connected: true,
    //         },
    //         {
    //             ssid: 'Koti_05CD',
    //             channel: 7,
    //             signalStrength: '-91 dB (Very Poor)',
    //             encryption: 'WPA2',
    //             connected: false,
    //         },
    //     ],
    // };

    // networks = responseJson.networks;
    // renderNetworks(networks);
})();
</script>
    </body>
</html>
)rawliteral";

#endif // HTML_SETTINGS_H
