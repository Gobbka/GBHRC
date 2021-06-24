"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.IUser = void 0;
const IDataBase_1 = require("./IDataBase");
class IDBUser {
}
class IUser extends IDBUser {
    get name() {
        return super.n;
    }
    set name(name) {
        super.n = name;
    }
    get token() {
        return super.t;
    }
    set token(new_value) {
        super.t = new_value;
    }
}
exports.IUser = IUser;
class UserDB extends IDataBase_1.default {
}
exports.default = UserDB;
//# sourceMappingURL=UserDB.js.map