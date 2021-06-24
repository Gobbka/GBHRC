"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const net = require("net");
class AuthServer {
    constructor(port) {
        this._server = new net.Server();
        this._server.listen(port);
    }
}
exports.default = AuthServer;
//# sourceMappingURL=AuthServer.js.map