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
    border: 1px solid #247024;
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

.disconnect-button {
    background-color: #955;
    border: none;
    border-radius: 3px;
    color: #fcc;
    padding: 5px 10px;
    cursor: pointer;
    transition: background-color 0.15s;
}

.disconnect-button:hover {
    background-color: #a66;
}

.disconnect-button:active {
    transform: translateY(1px);
}

.disconnect-button:disabled {
    background-color: #633;
    color: #a88;
    cursor: default;
}

.disconnect-button:disabled:hover {
    background-color: #633;
    color: #a88;
}

.disconnect-button:disabled:active {
    transform: none;
}

.disconnect-button-primary-text {
    color: inherit;
    text-align: left;
}

.disconnect-button-secondary-text {
    font-size: 12px;
    color: #daa;
    text-align: left;
    font-weight: 400;
}

.warning-box {
    display: flex;
    flex-direction: column;
    background-color: #2a2222;
    border: 1px solid #644;
    border-radius: 3px;
    color: #fcc;
    padding: 10px;
    font-size: 14px;
}

.warning-box-top {
    display: flex;
    justify-content: space-between;
    align-items: center;
    gap: 10px;
    color: inherit;
}

.warning-box-content {
    display: flex;
    flex-direction: column;
    gap: 10px;
    font-size: 12px;
    color: #daa;
    text-align: left;
    font-weight: 400;
    max-height: 500px;
    overflow: hidden;
    opacity: 1;

    transition: max-height 0.15s ease-in-out, opacity 0.15s ease-in-out;
}

.warning-box-content-hidden {
    max-height: 0;
    opacity: 0;
}

.warning-box-text {
    color: inherit;
    margin-top: 5px;
}

.chevron {
    border-right: 1px solid #fcc;
    border-bottom: 1px solid #fcc;
    width: 8px;
    height: 8px;
    transition: transform 0.15s ease-in-out, margin 0.15s ease-in-out;
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
    .warning-box {
        max-width: 300px;
    }
}
</style>
        <link rel="preconnect" href="https://fonts.googleapis.com" />
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
        <link
            href="https://fonts.googleapis.com/css2?family=Open+Sans:ital,wght@0,300..800;1,300..800&display=swap"
            rel="stylesheet"
        />
    </head>

    <body>
        <main>
            <div class="tab-container">
                <a href="/" class="tab inactive-tab">Presets</a>
                <a href="/settings" class="tab active-tab">Settings</a>
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

            <div class="line"></div>

            <div class="warning-box">
                <div class="warning-box-top">
                    Disconnect from network
                    <div class="chevron-container" onclick="toggleDisconnectInfo()">
                        <div id="warning-box-chevron" class="chevron chevron-down"></div>
                    </div>
                </div>
                <div
                    id="warning-box-content"
                    class="warning-box-content warning-box-content-hidden"
                >
                    <div class="warning-box-text">
                        After disconnecting, you must set the device to Access Point mode and
                        re-establish your own connection to the device's access point network.
                    </div>

                    <button id="disconnect" class="disconnect-button" onclick="disconnect()">
                        Disconnect
                    </button>
                </div>
            </div>
        </main>

        <script>
let networks = [];
let selectedNetworkIndex = null;
let disconnectInfoVisible = false;

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
            <div class="network-name">${network.ssid}</div>
            <div class="network-info">
                Ch: ${network.channel},
                ${network.encryption},
                Signal: ${network.signalStrength}
            </div>
        </div>
        <div class="network-connected" style="display: ${
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

    const sortedNetworks = [...networks].sort((a, b) => b.signalStrengthDb - a.signalStrengthDb);

    sortedNetworks.forEach((network, index) => {
        container.appendChild(createNetworkElement(network, index));
    });
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

function toggleDisconnectInfo() {
    disconnectInfoVisible = !disconnectInfoVisible;
    const warningBoxContent = document.getElementById('warning-box-content');
    const warningBoxChevron = document.getElementById('warning-box-chevron');

    if (disconnectInfoVisible) {
        warningBoxContent.classList.remove('warning-box-content-hidden');

        warningBoxChevron.classList.remove('chevron-down');
        warningBoxChevron.classList.add('chevron-up');
    } else {
        warningBoxContent.classList.add('warning-box-content-hidden');

        warningBoxChevron.classList.remove('chevron-up');
        warningBoxChevron.classList.add('chevron-down');
    }
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
    //             signalStrengthDb: -89,
    //             signalStrengthQuality: 'Very Poor',
    //             encryption: 'WPA2',
    //             connected: false,
    //         },
    //         {
    //             ssid: 'family',
    //             channel: 1,
    //             signalStrength: '-86 dB (Very Poor)',
    //             signalStrengthDb: -86,
    //             signalStrengthQuality: 'Very Poor',
    //             encryption: 'WPA2',
    //             connected: false,
    //         },
    //         {
    //             ssid: 'DIRECT-73M2020 Series',
    //             channel: 6,
    //             signalStrength: '-47 dB (Excellent)',
    //             signalStrengthDb: -47,
    //             signalStrengthQuality: 'Excellent',
    //             encryption: 'WPA2',
    //             connected: false,
    //         },
    //         {
    //             ssid: 'BUFFALO',
    //             channel: 6,
    //             signalStrength: '-50 dB (Excellent)',
    //             signalStrengthDb: -50,
    //             signalStrengthQuality: 'Excellent',
    //             encryption: 'WPA2',
    //             connected: true,
    //         },
    //         {
    //             ssid: 'Koti_05CD',
    //             channel: 7,
    //             signalStrength: '-91 dB (Very Poor)',
    //             signalStrengthDb: -91,
    //             signalStrengthQuality: 'Very Poor',
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
