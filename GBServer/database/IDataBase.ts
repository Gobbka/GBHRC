import Eventable from "../events/Eventable";
import * as fs from "fs"

export default abstract class IDataBase<T> extends Eventable{

    private _file_path: string;
    private _data: T[];

    constructor() {
        super();
        this._data = [];

    }

    protected load_file(path: string) {
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

    public select(comparator: (T) => boolean,count:number = 0xFFFFFF): T[] {
        let data: T[] = [];
        let found = 0;

        for (let item of this._data) {

            if (found > count)
                break;

            if (comparator(item))
                data.push(item);
        }

        return data;
    }

    public create(item: T) {
        this.push_item(item);
        this.save();
    }

    
    public remove(comparator: (T) => boolean, delete_count: number = 0xFFFFFF) {
        throw new Error("not implemented");
    }
}