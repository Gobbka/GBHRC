"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const net = require("net");
const AuthServerMessageFactory_1 = require("./server/AuthServer/AuthServerMessageFactory");
const port = process.env.port || 1337;
const dataServer = new net.Server();
const cryptedServer = new net.Server();
cryptedServer.on("connection", (socket) => {
    console.log("CONNECTED: " + socket.remoteAddress);
    let buffer = AuthServerMessageFactory_1.default.create_new_crypted_message("ok");
    console.log(buffer);
    socket.write(buffer.get_buffer());
    socket.on("data", (data) => {
        console.log(data);
    });
    socket.on("error", () => {
    });
});
cryptedServer.listen(1337);
//# sourceMappingURL=server.js.map