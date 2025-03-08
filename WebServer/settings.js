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
    // getNetworks();
    enableOrDisableConnectButton();

    const responseJson = {
        networks: [
            {
                ssid: 'family',
                channel: 1,
                signalStrength: '-89 dB (Very Poor)',
                signalStrengthDb: -89,
                signalStrengthQuality: 'Very Poor',
                encryption: 'WPA2',
                connected: false,
            },
            {
                ssid: 'family',
                channel: 1,
                signalStrength: '-86 dB (Very Poor)',
                signalStrengthDb: -86,
                signalStrengthQuality: 'Very Poor',
                encryption: 'WPA2',
                connected: false,
            },
            {
                ssid: 'DIRECT-73M2020 Series',
                channel: 6,
                signalStrength: '-47 dB (Excellent)',
                signalStrengthDb: -47,
                signalStrengthQuality: 'Excellent',
                encryption: 'WPA2',
                connected: false,
            },
            {
                ssid: 'BUFFALO',
                channel: 6,
                signalStrength: '-50 dB (Excellent)',
                signalStrengthDb: -50,
                signalStrengthQuality: 'Excellent',
                encryption: 'WPA2',
                connected: true,
            },
            {
                ssid: 'Koti_05CD',
                channel: 7,
                signalStrength: '-91 dB (Very Poor)',
                signalStrengthDb: -91,
                signalStrengthQuality: 'Very Poor',
                encryption: 'WPA2',
                connected: false,
            },
        ],
    };

    networks = responseJson.networks;
    renderNetworks(networks);
})();
