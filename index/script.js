const socket = new WebSocket('ws://localhost:8888');

socket.onopen = (event) => {
	console.log(event);
	socket.send("Here's some text that the server is urgently awaiting!");
};

socket.onmessage = (event) => {
	console.log(event.data);
}

function join(){
	socket.send("Join!");

}

function close(){
	socket.close();
}