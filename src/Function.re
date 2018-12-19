/**** Functions */

let f = (~a, ~b) => a + b;
let a = f(~a=1, ~b=2);
Js.log(a);

/* Needs types. If not, it won't show you error for types. */

let drawCircle: (~radius:float, ~color:string) => unit 
    = (~radius as r: float, ~color as c: string) => {
    Js.log({j|Drew a circle with radius, $r and color, $c|j})
}
drawCircle(~radius=3.66, ~color="Red");

let drawCircle2 = (~radius as r, ~color as c) => {
    Js.log({j|Drew a circle with radius, $r and color, $c|j})
}
drawCircle2(~radius=3.66, ~color="Red");
drawCircle2(~radius=2, ~color=(255, 255, 255));

/* What if I want to make a function that can both handle int and float together? 
Don't. 
Make 2 methods. That's why there are 3 substring methods. 
 */
/*
type number = [`int(int) | `float(float)];
let printValue = (r) => {
    switch(r) {
    | `int(v) => v
    | `float(v) => v
    }
}
let value = ref(0);
let drawCircle3 = (~radius as r:number, ~color as c) => {
    switch(r) {
    | `int(v) => value := v;
    | `float(v) => value := v;
    }
    Js.log({j|Drew a circle with radius, $value and color, $c|j})
}
drawCircle3(~radius=`float(3.66), ~color="Red");
drawCircle3(~radius=`int(2), ~color=(255, 255, 255));
*/

/* Use tuple to return multiple values */
let a = (a, b) => {
    (a + b, a - b, a * b, a / b, a mod b)
}

/* Curry */
let add = (x, y) => x + y;
let addFive = add(5);
let eleven = addFive(6);

/* Uncurry */
let add = (. x, y, z) => x + y + z;
/* let addFiveOops = add(5); */
/* let addFiveOops = add(5, 6, 7); */
let addFiveOops = add(. 5, 6, 7); /* <- . is required */

/* radius can be omitted */
let drawCircle3 = (~color, ~radius=?, ()) => {
    Js.log({j|color: $color|j})
    switch (radius) {
    | None => Js.log("startAt(1, 1)");
    | Some(r_) => Js.log({j|startAt($r_, $r_)|j});
    }
};
/* let redCircle = drawCircle3(~color="Red"); <- curried doesn't work. */
drawCircle3(~color="Red", ());

let payloadRadius: option(float) = Some(3.25);

let color = "Blue";
let result =
  switch (payloadRadius) {
  | None => drawCircle3(~color, ())
  | Some(r) => drawCircle3(~color, ~radius=r, ())
  };
let result = drawCircle3(~color, ~radius=?payloadRadius, ());

/**** Pipe first */

let f = x => x + 1;
let g = y => y * 2;

Js.log(4->f->g);
Js.log(4|>f|>g);

let f = (a, b) => a + b;
let g = (c, d) => c * d;

Js.log(4->f(5)->g(6));
Js.log(4|>f(5)|>g(6));

let f = (a, b) => a - b;
Js.log(4->f(5)); /* f(4, 5) */
Js.log(4|>f(5)); /* f(5, 4) */
Js.log(4->f(5, _)); /* == 4|>f(5)  <- When we don't want to use the first paramenter */

let add = (x, y, z) => x + y + z;
let addTo7 = (x) => add(3, x, 4);
Js.log(addTo7(7));

let addTo7 = add(3, _, 4);
Js.log(addTo7(7));
