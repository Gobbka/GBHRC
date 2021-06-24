export default interface IEvent {
    listeners: (...args) => void;
}