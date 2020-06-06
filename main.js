
const http = new XMLHttpRequest();
let ip = "";

let button = document.querySelector('.form__button');
let ipValue = document.querySelector('.form__ip');

function getIp() {
    ip = ipValue.value;
    console.log(ip);
}



function holdUp() {
    http.open("POST", `http://${ip}/arduino/move/forward`, true);
    http.send();
}

function holdLeft() {
    http.open("POST", `http://${ip}/arduino/move/left`, true);
    http.send();
}

function holdRight() {
    http.open("POST", `http://${ip}/arduino/move/right`, true);
    http.send();
}

function holdDown() {
    http.open("POST", `http://${ip}/arduino/move/backward`, true);
    http.send();
}

function releasedFunction() {
    http.open("POST", `http://${ip}/arduino/move/stop`, true);
    http.send();
}




