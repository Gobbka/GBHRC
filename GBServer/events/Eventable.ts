import IEvent from "./IEvent";

export default class Eventable {
    private _events: IEvent[]

    protected constructor() {
        this._events = [];
    }

    protected register(event: IEvent) {
        this._events.push(event);
    }

    protected fire(event: IEvent, ...args) {
        for (let event in this._events) {
            
        }
    }
}