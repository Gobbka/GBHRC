"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Eventable_1 = require("../events/Eventable");
const fs = require("fs");
class DataBase extends Eventable_1.default {
    constructor() {
        super();
        this._data = [];
    }
    load_file(path) {
        this._file_path = path;
        this._data = JSON.parse(fs.readFileSync(path, { encoding: "utf-8" }));
    }
    push_item(item) {
        this._data.push(item);
    }
    save() {
        fs.writeFileSync(this._file_path, JSON.stringify(this._data));
    }
    select(comparator, count = 0xFFFFFF) {
        let data = [];
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
    create(item) {
        this.push_item(item);
        this.save();
    }
    update(comparator, item, update_count = 0xFFFFFF) {
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
    remove(comparator, delete_count = 0xFFFFFF) {
        throw new Error("not implemented");
    }
}
exports.default = DataBase;
//# sourceMappingURL=IDataBase.js.map