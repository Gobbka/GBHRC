import * as net from "net"
import UserDB, { IUser } from "./database/UserDB";
import AuthServerMessageFactory from "./server/AuthServer/AuthServerMessageFactory";
const port = process.env.port || 1337

const dataServer = new net.Server()
const user_db = new UserDB();
const cryptedServer = new net.Server();

console.log(user_db.select((item) => item.token == "tokken"));

cryptedServer.on("connection", (socket) => {
    console.log("CONNECTED: " + socket.remoteAddress);
    

    socket.on("data", (data: Buffer) => {
        let token = data.toString();
        console.log("New data", token);

        let user: IUser = user_db.select((user: IUser) => { return user.token == token }, 1)[0];

        if (!user) {
            let buffer = AuthServerMessageFactory.create_new_crypted_message("you are fucking dumb nigger");
            socket.write(buffer.get_buffer());
            return;
        }

        let buffer = AuthServerMessageFactory.create_new_crypted_message(user.token);
        socket.write(buffer.get_buffer());
    });

    socket.on("error", () => {

    })
})

cryptedServer.listen(1337);
