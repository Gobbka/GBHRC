import * as net from "net"

export default class AuthServer {
    private _server: net.Server;

    constructor(port: number) {
        this._server = new net.Server();
        this._server.listen(port);
    }
}