"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const net = require("net");
const UserDB_1 = require("./database/UserDB");
const AuthServerMessageFactory_1 = require("./server/AuthServer/AuthServerMessageFactory");
const port = process.env.port || 1337;
const dataServer = new net.Server();
const user_db = new UserDB_1.default();
const cryptedServer = new net.Server();
console.log(user_db.select((item) => item.token == "tokken"));
cryptedServer.on("connection", (socket) => {
    console.log("CONNECTED: " + socket.remoteAddress);
    socket.on("data", (data) => {
        let token = data.toString();
        console.log("New data", token);
        let user = user_db.select((user) => { return user.token == token; }, 1)[0];
        if (!user) {
            let buffer = AuthServerMessageFactory_1.default.create_new_crypted_message("you are fucking dumb nigger");
            socket.write(buffer.get_buffer());
            return;
        }
        let buffer = AuthServerMessageFactory_1.default.create_new_crypted_message(user.token);
        socket.write(buffer.get_buffer());
    });
    socket.on("error", () => {
    });
});
cryptedServer.listen(1337);
//# sourceMappingURL=server.js.map