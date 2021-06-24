import IDataBase from "./IDataBase";

class IDBUser {
    // name
    protected n: string
    // token
    protected t: string
}

export class IUser extends IDBUser {
    get name() {
        return super.n;
    }
    set name(name: string) {
        super.n = name;
    }

    get token() {
        return super.t;
    }
    set token(new_value: string) {
        super.t = new_value;
    }
}

export default class UserDB extends IDataBase<IDBUser> {

}