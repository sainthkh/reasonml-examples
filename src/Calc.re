Js.log("First number:");
let a = read_float();
Js.log("Second number:");
let b = read_float();
Js.log("Operation:");
let op = read_line();

let result: option(float) = 
    switch(op) {
    | "+" => Some(a +. b)
    | "-" => Some(a -. b)
    | "*" => Some(a *. b)
    | "/" => Some(a /. b)
    | "**" => Some(a ** b)
    | _ => None
    }

switch(result) {
| Some(number) => Js.log(number)
| None => Js.log("Error in operation")
}
