function sendFormData() {
    const textarea = document.getElementById('textarea').value;
    const checkbox = document.getElementById('checkbox').checked ? 'on' : 'off';

    const xhttp = new XMLHttpRequest();
    xhttp.open('POST', '/click', true);
    xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

    xhttp.onload = function () {
        if (xhttp.status == 200) {
            document.getElementById('response-content').innerHTML = xhttp.responseText;
        }
    };

    const data =
        'textarea=' + encodeURIComponent(textarea) + '&checkbox=' + encodeURIComponent(checkbox);
    xhttp.send(data);

    return false;
}
