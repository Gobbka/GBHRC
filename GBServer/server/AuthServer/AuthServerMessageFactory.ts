import AuthServerMessage from "./AuthServerMessage";


export default class AuthServerMessageFactory {
    static create_new_crypted_message(message: string): AuthServerMessage {

        const salt_size = 8;
        const header_size = 4 * 2 + salt_size; // sizeof int * 2 + 8 byte for salt
        const block_size = 12;
        const blocks_total_size = Math.ceil(message.length / block_size) * block_size;

        const final_buffer = Buffer.alloc(header_size + blocks_total_size);
        const message_buffer = Buffer.from(message);
        const salt_buffer = Buffer.alloc(8);

        {
            const number_buffer = Buffer.alloc(4);
            number_buffer.writeUInt32LE(message.length, 0);

            for (let i = 0; i < 4; i++) {
                final_buffer[i * 2] = number_buffer[i];
                final_buffer.writeUInt8(Math.floor(Math.random() * 0xFF), i*2+1);
            }

            salt_buffer.writeUInt32LE(Math.floor(Math.random() * 0xFFFFFFFF), 0);
            salt_buffer.writeUInt32LE(Math.floor(Math.random() * 0xFFFFFFFF), 4);
        }

        message_buffer.copy(final_buffer, header_size);
        salt_buffer.copy(final_buffer, header_size - salt_size);

        for (let i = 0, j = 0; i < message_buffer.length; i++, j = i % salt_size) {
            final_buffer[i + header_size] += salt_buffer[j];
        }

        for (let i = message_buffer.length + header_size; i < final_buffer.length; i++) {
            final_buffer[i] = Math.floor(Math.random() * 0xFF);
        }

        return new AuthServerMessage(final_buffer);
    }
}