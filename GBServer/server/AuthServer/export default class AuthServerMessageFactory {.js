"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const AuthServerMessage_1 = require("./AuthServerMessage");
class AuthServerMessageFactory {
    static create_new_message(message) {
        const header_size = 4 * 2; // sizeof int * 2
        const block_size = 12;
        const final_buffer = Buffer.alloc(header_size + Math.ceil(message.length / block_size) * block_size);
        const message_buffer = Buffer.from(message);
        {
            const number_buffer = Buffer.alloc(4);
            number_buffer.writeUInt32LE(message.length, 0);
            for (let i = 0; i < 4; i++) {
                final_buffer[i * 2] = number_buffer[i];
                final_buffer.writeUInt8(Math.floor(Math.random() * 0xF), i * 2 + 1);
            }
        }
        message_buffer.copy(final_buffer, header_size);
        return new AuthServerMessage_1.default(final_buffer);
    }
}
exports.default = AuthServerMessageFactory;
//# sourceMappingURL=export default class AuthServerMessageFactory {.js.map