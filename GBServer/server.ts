import * as net from "net"
const port = process.env.port || 1337

const dataServer = new net.Server()

const cryptedServer = new net.Server();

cryptedServer.on("connection", (socket) => {
    console.log("CONNECTED: " + socket.remoteAddress);
    socket.on("data", (data: Buffer) => {
        console.log(data);
    });
})

cryptedServer.listen(1337);
