function sendFormData() {
    const macro1 = document.getElementById('macro1').value;

    const xhttp = new XMLHttpRequest();
    xhttp.open('POST', '/click', true);
    xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    xhttp.onload = function () {
        if (xhttp.status == 200) {
            document.getElementById('response-content').innerHTML = xhttp.responseText;
        }
    };

    const data = 'macro1=' + encodeURIComponent(macro1);
    xhttp.send(data);

    return false;
}
