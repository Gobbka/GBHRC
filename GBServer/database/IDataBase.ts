import Eventable from "../events/Eventable";
import * as fs from "fs"

export default class DataBase<T> extends Eventable{

    private _file_path: string;
    private _data: T[];

    constructor() {
        super();
        this._data = [];

    }

    load_file(path: string) {
        this._file_path = path;
        this._data = JSON.parse(
            fs.readFileSync(path, { encoding: "utf-8" })
        );
    }

    protected push_item(item: T) {
        this._data.push(item);
    }

    protected save() {
        fs.writeFileSync(this._file_path, JSON.stringify(this._data));
    }

    public select(comparator: (item:T) => boolean,count:number = 0xFFFFFF): T[] {
        let data: T[] = [];
        let found = 0;

        for (let item of this._data) {

            if (found > count)
                break;

            if (comparator(item)) {
                data.push(item);
                found++;
            }
        }

        return data;
    }

    public create(item: T) {
        this.push_item(item);
        this.save();
    }

    public update(comparator: (item: T) => boolean, item: T, update_count: number = 0xFFFFFF) {
        let updated = 0;

        for (let db_item of this._data) {

            if (updated > update_count)
                break;

            if (comparator(db_item)) {
                db_item = item;
                updated++;
            }
        }

        this.save();
    }

    
    public remove(comparator: (item:T) => boolean, delete_count: number = 0xFFFFFF) {
        throw new Error("not implemented");
    }
}