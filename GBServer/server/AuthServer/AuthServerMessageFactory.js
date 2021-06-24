"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const AuthServerMessage_1 = require("./AuthServerMessage");
class AuthServerMessageFactory {
    static create_new_crypted_message(message) {
        const header_size = 4 * 2; // sizeof int * 2
        const block_size = 12;
        const blocks_total_size = Math.ceil(message.length / block_size) * block_size;
        const final_buffer = Buffer.alloc(header_size + blocks_total_size);
        const message_buffer = Buffer.from(message);
        {
            const number_buffer = Buffer.alloc(4);
            number_buffer.writeUInt32LE(message.length, 0);
            for (let i = 0; i < 4; i++) {
                final_buffer[i * 2] = number_buffer[i];
                final_buffer.writeUInt8(Math.floor(Math.random() * 0xFF), i * 2 + 1);
            }
        }
        message_buffer.copy(final_buffer, header_size);
        for (let i = message_buffer.length + header_size; i < final_buffer.length; i++) {
            final_buffer[i] = Math.floor(Math.random() * 0xFF);
        }
        return new AuthServerMessage_1.default(final_buffer);
    }
}
exports.default = AuthServerMessageFactory;
//# sourceMappingURL=AuthServerMessageFactory.js.map