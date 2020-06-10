 
const http = new XMLHttpRequest();
let ip = "";
 
const button = document.querySelector('.form__button');
const ipValue = document.querySelector('.form__ip');
const ipHeader = document.querySelector('.header__ip');
const pattern = new RegExp(`^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$`);
 
function getIp() {
    ip = ipValue.value;
    console.log(ip);
}
 
 
button.addEventListener('click', () => {
    if (pattern.test(`${ip}`)) {
        ipHeader.innerHTML = `Your ip: ${ip}`;
    } else {
        alert("Your IP is incorrect.");
    }
    
})
 
 
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
 