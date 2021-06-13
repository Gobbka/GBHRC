"use strict";
var Types;
(function (Types) {
    class String {
        constructor() {
        }
        is_base() {
            return true;
        }
        toString() {
            return "string";
        }
    }
    Types.String = String;
    class Number {
        is_base() {
            return true;
        }
        toString() {
            return "int";
        }
    }
    Types.Number = Number;
    class Void {
        is_base() {
            return true;
        }
        toString() {
            return "void";
        }
    }
    Types.Void = Void;
    class Bool {
        is_base() {
            return true;
        }
        toString() {
            return "bool";
        }
    }
    Types.Bool = Bool;
})(Types || (Types = {}));
var DocCore;
(function (DocCore) {
    function get_methods() {
        return [
            {
                name: "print",
                params: [
                    {
                        type: new Types.String(),
                        name: "string",
                        description: "string that needed to print"
                    }
                ],
                description: "prints string into console",
                returns: new Types.Void()
            },
            {
                name: "exit",
                params: [],
                description: "exit from application",
                returns: new Types.Void()
            },
            {
                name: "Player:move_by",
                params: [
                    {
                        type: new Types.Number(),
                        name: "x",
                        description: "string that needed to print"
                    },
                    {
                        type: new Types.Number(),
                        name: "y",
                        description: "string that needed to print"
                    }
                ],
                description: "move player",
                returns: new Types.Void()
            },
        ];
    }
    DocCore.get_methods = get_methods;
})(DocCore || (DocCore = {}));
function add_method(method) {
    var _a;
    let div = document.createElement("BUTTON");
    let html = `<b class="type">${method.returns}</b> ${method.name}(`;
    let param_str = [];
    for (let param of method.params) {
        param_str.push(`<b class="type">${param.type}</b>`);
    }
    div.innerHTML = html + param_str.join(",") + ')';
    div.onclick = () => {
        open_method(method);
    };
    (_a = document.getElementById("method_list")) === null || _a === void 0 ? void 0 : _a.appendChild(div);
}
function open_method(method) {
    let sign_wrapper = document.getElementById("signature");
    let desc_wrapper = document.getElementById("description_text");
    let html = `<span class="type">${method.returns}</span> <b>${method.name}</b>(`;
    let param_str = [];
    for (let param of method.params) {
        param_str.push(`<span class="type">${param.type}</span> <span>${param.name}</span>`);
    }
    desc_wrapper.innerHTML = `${method.description}`;
    sign_wrapper.innerHTML = html + param_str.join(",") + ')';
}
for (let method of DocCore.get_methods()) {
    add_method(method);
}
