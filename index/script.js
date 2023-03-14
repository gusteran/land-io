// const { createConnection } = require("net");

const socket = new WebSocket('localhost:8888');

socket.addEventListener('open', (event) => {
    socket.send('Hello Server!');
});

// Listen for messages
socket.addEventListener('message', (event) => {
    console.log('Message from server ', event.data);
});

function join(){
    socket.send('Join');
}
function close(){
    socket.send('Close');
}