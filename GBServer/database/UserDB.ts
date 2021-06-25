import DataBase from "./IDataBase";

class IDBUser {
    constructor(user: IDBUser) {
        this.n = user.n;
        this.t = user.t;
    }
    // name
    protected n: string
    // token
    protected t: string
}

class DBUserAdapter {

    to_iuser(db_users: IDBUser[]): IUser[] {
        const iusers: IUser[] = [];

        for (let db_user of db_users) {
            let iuser = new IUser(db_user);
            iusers.push(iuser);
        }

        return iusers;
    }

}

export class IUser extends IDBUser {
    constructor(db_user: IDBUser) {
        super(db_user);
    }

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

export default class UserDB  {
    private _database: DataBase<IDBUser>
    private _user_adapter: DBUserAdapter;

    constructor() {
        this._database = new DataBase<IDBUser>();
        this._database.load_file("./database/tables/users.json");

        this._user_adapter = new DBUserAdapter();
    }

    select(comparator: (item: IUser) => boolean, count: number = 0xFFFFFF): IUser[] {
        return this._user_adapter.to_iuser(this._database.select(comparator, count));
    }
}