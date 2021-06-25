"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.IUser = void 0;
const IDataBase_1 = require("./IDataBase");
class IDBUser {
    constructor(user) {
        this.n = user.n;
        this.t = user.t;
    }
}
class DBUserAdapter {
    to_iuser(db_users) {
        const iusers = [];
        for (let db_user of db_users) {
            let iuser = new IUser(db_user);
            iusers.push(iuser);
        }
        return iusers;
    }
}
class IUser extends IDBUser {
    constructor(db_user) {
        super(db_user);
    }
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
class UserDB {
    constructor() {
        this._database = new IDataBase_1.default();
        this._database.load_file("./database/tables/users.json");
        this._user_adapter = new DBUserAdapter();
    }
    select(comparator, count = 0xFFFFFF) {
        return this._user_adapter.to_iuser(this._database.select(comparator, count));
    }
}
exports.default = UserDB;
//# sourceMappingURL=UserDB.js.map