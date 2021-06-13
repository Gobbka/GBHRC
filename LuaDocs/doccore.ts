namespace Types{
    export class String implements IType{
        constructor() {
        }

        is_base():boolean{
            return true;
        }

        toString(): string {
            return "string"
        }
    }

    export class Number implements IType{
        is_base():boolean{
            return true;
        }

        toString(): string {
            return "int"
        }
    }

    export class Void implements IType{
        is_base():boolean{
            return true;
        }

        toString(): string {
            return "void"
        }
    }

    export class Bool implements IType{
        is_base():boolean{
            return true;
        }

        toString(): string {
            return "bool"
        }
    }

    export interface IType{
        is_base() : boolean;
        toString() : string;
    }
}

interface IMethodParam{
    type: Types.IType,
    name: string,
    description: string
}

interface IMethod {
    name:string,
    params: IMethodParam[],
    description: string,
    returns: Types.IType
}

namespace DocCore{
    export function get_methods() : IMethod[]{
        return [
            {
                name:"print",
                params:[
                    {
                        type: new Types.String(),
                        name: "string",
                        description:"string that needed to print"
                    }
                ],
                description:"prints string into console",
                returns: new Types.Void()
            },
            {
                name:"exit",
                params:[],
                description:"exit from application",
                returns: new Types.Void()
            },
            {
                name:"Player:move_by",
                params:[
                    {
                        type: new Types.Number(),
                        name: "x",
                        description:"string that needed to print"
                    },
                    {
                        type: new Types.Number(),
                        name: "y",
                        description:"string that needed to print"
                    }
                ],
                description:"move player",
                returns: new Types.Void()
            },
        ];
    }
}

function add_method(method:IMethod){
    let div = document.createElement("BUTTON")
    let html = `<b class="type">${method.returns}</b> ${method.name}(`
    let param_str: string[] = []
    for(let param of method.params){
        param_str.push(`<b class="type">${param.type}</b>`)
    }
    div.innerHTML = html + param_str.join(",") + ')';
    div.onclick = ()=>{
        open_method(method)
    }

    document.getElementById("method_list")?.appendChild(div);
}

function open_method(method:IMethod){
    let sign_wrapper = document.getElementById("signature")!;
    let desc_wrapper = document.getElementById("description_text")!;

    let html = `<span class="type">${method.returns}</span> <b>${method.name}</b>(`
    let param_str: string[] = []

    for(let param of method.params){
        param_str.push(`<span class="type">${param.type}</span> <span>${param.name}</span>`)
    }

    desc_wrapper.innerHTML = `${method.description}`

    sign_wrapper.innerHTML = html + param_str.join(",") + ')';
}

for(let method of DocCore.get_methods()){
    add_method(method);
}
