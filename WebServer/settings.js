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
    `;

    return networkElement;
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
}

(async () => {
    getNetworks();

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
