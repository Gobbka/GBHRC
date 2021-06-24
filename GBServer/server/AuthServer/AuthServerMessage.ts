export default class AuthServerMessage {
    private _buffer: Buffer;

    constructor(buffer: Buffer) {
        this._buffer = buffer;
    }

    get_buffer(): Buffer {
        return this._buffer;
    }
}