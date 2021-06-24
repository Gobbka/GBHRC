"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Eventable {
    constructor() {
        this._events = [];
    }
    register(event) {
        this._events.push(event);
    }
    fire(event, ...args) {
        for (let event in this._events) {
        }
    }
}
exports.default = Eventable;
//# sourceMappingURL=Eventable.js.map