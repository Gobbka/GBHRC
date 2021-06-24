import * as net from "net"
import UserDB, { IUser } from "./database/UserDB";
import AuthServerMessageFactory from "./server/AuthServer/AuthServerMessageFactory";
const port = process.env.port || 1337

const dataServer = new net.Server()

const cryptedServer = new net.Server();

cryptedServer.on("connection", (socket) => {
    console.log("CONNECTED: " + socket.remoteAddress);
    let buffer = AuthServerMessageFactory.create_new_crypted_message("ok");

    console.log(buffer);
    socket.write(buffer.get_buffer());


    socket.on("data", (data: Buffer) => {
        console.log("New data", data.toString());
        
    });

    socket.on("error", () => {

    })
})

cryptedServer.listen(1337);
