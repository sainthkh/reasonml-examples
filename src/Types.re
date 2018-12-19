/*********************************/
/* NUMBER TYPES */

/**** Integers */
print_endline("Integers");

/* 
Declare variables with let. But they're not variables. 
They're constants (immutable)! 
*/
let a: int = 3;
let b: int = 4;
let c: int = a + b;
Js.log(c);

/* a = 32; <- It's impossible. Variables are immutable. */

/* Unary operators */
let c = -c;
Js.log(c);
let c = ~-c;
Js.log(c);

/* 
++, -- doesn't exist in ReasonML.
let b = b++;
let c = c--;

Use succ, pred. 
*/
let b2 = succ(b);
let b3 = pred(c);
Js.log(b2);
Js.log(b3);

/* You cannot use exponentiation operator with int. */
let c2 = float(a) ** float(b);
Js.log(c2);


/**** Floats */
print_endline("Floats");

let d: float = 3.14;
let e: float = 2.71;
let f: float = d +. e; /* Don't forget . after +! */
Js.log(f);

/* Don't forget . after each operators like -. *. /. */
let f2 = d -. e;
let f3 = d *. e;
let f4 = d /. e;
Js.log(f2);
Js.log(f3);
Js.log(f4);

let f = exp(2.0); /* e^x */
Js.log(f);
let f = e *. e;
Js.log(f);

/* other math functions
cos sin tan
log log10 -> log is natural logarithm
ceil floor
*/

/*
Numeric types aren't automatically converted to the biggest type. 
It's a manual job. 
 */
let g: float = (4.5: float) +. float(1);
Js.log(g) /* semicolon isn't required */

let h = int_of_float(4.5) + 30;
Js.log(h);

/**** String & Char */
/* 
ReasonML and OCaml uses the same documentation
* ReasonML String: https://reasonml.github.io/api/String.html
* OCaml String: https://caml.inria.fr/pub/docs/manual-ocaml/libref/String.html

Check OCaml vs. ReasonML: https://reasonml.github.io/docs/en/comparison-to-ocaml
 */

let i: string = "Hello, World";
let j: char = 'a'; /* char is compiled to number code. */
/* let j2: = '가'; non-ascii is invalid for char. */
Js.log(i ++ String.make(1, j));
Js.log(i ++ string_of_int(a));
Js.log(i ++ string_of_float(d));

let k: string = "7792";
Js.log(int_of_string(k) + 8);

let l: string = "3.1415";
Js.log(float_of_string(l) +. 5.0);

/* 
String Interpolation
The character should be j. If it were a or b or js, it won't work. 
*/
Js.log({j|String interpolation: $a $d $i $j|j}) 

/**
Other conversion functions: 
string_of_bool
bool_of_string
 */

/**
Use Js.String to use string methods.
*/

let m = Js.String.split("+", "1+2+3");
Js.log(m);
let n = Js.String.indexOf("a", "Harry");
Js.log(n);
let o = Js.String.includes("hi", "Hello, World");
Js.log(o);
/*
substr = substringToEnd: from to end
substrAtMost: from length
substring: from to
JS has no negative index. 
*/

/* // comments doesn't exist yet! */

/* print_endline vs. Js.log */
/* print_endline(a); -> it's invalid because print_endline only gets strings. */
Js.log(a); /* -> It's OK because Js.log is console.log */

/* === reference */
/* == structural equal, deep equal */

let p: bool = true;
let q = (1, 2) === (1, 2);
Js.log(q);
let r = (1, 2, 3);
let r2 = r;
Js.log(r === r2);
Js.log(1 == 1);
Js.log(1 === 1);


/**** Variants */
type animal = Dog | Cat | Bird;

let pet: animal = Dog;

type food = 
    | Pizza(string)
    | Noodle(string, int);

let s = Pizza("Combination");
Js.log(s);
let t = 
    switch(s) {
    | Pizza(name) => {j|Your pizza is $name|j}
    | Noodle(name, price) => {j|Your noodle is $name and price is $price|j}
    }
Js.log(t);

/*
Check more on Pervasives module for ints and floats: https://caml.inria.fr/pub/docs/manual-ocaml/libref/Pervasives.html
Check more on String and Js.String modules: 
https://caml.inria.fr/pub/docs/manual-ocaml/libref/String.html
https://bucklescript.github.io/bucklescript/api/Js.String.html
 */


 /**** Tuple */
/* Tuple has no module. So, it doesn't have its own documentation like List, Array. */
/* There are 2 methods for Pair: fst(first), snd(second) */
/* immutable, heterogenenous, fixed-size */

let u = (3, 4);
Js.log(fst(u)); /* 3 */
Js.log(snd(u)); /* 4 */

/* To get value, use destructuring */
let v = ("hello", 3, 6.25, [1, 2, 3]);
let (greeting, _, f, l) = v;
Js.log({j|$greeting $f $l|j})

/**** Record */

module School {
  type person = {
    age: int,
    name: string  
  }
}

let me: School.person = {
  age: 5,
  name: "Big Reason"
};
let me2 = School.{age: 20, name: "Big Reason"};
let me3 = {School.age: 20, name: "Big Reason"};

let name = me.name;

/* updates: mutable vs. immutable */
let meNextYear = {...me, age: me.age + 1};

type person = {
  name: string,
  mutable age: int
};
let baby = {name: "Baby Reason", age: 5};
baby.age = baby.age + 1; /* alter `baby`. Happy birthday! */

/* punning for let bindings and types */

type horsePower = {power: int, metric: bool};

let metric = true;
let someHorsePower = {power: 10, metric};
/* same as the value {power: 10, metric: metric}; */

type car = {name: string, horsePower};
/* same as the type {name: string, horsePower: horsePower}; */

/* types are important */

type person2 = {age: int, name: string};
type monster = {age: int, hasTentacles: bool};

let getAge = (entity) => entity.age; /* <- It's monster => int. Not person2 => int */

let kraken = {age: 9999, hasTentacles: true};
let me = {age: 5, name: "Baby Reason"};

getAge(kraken);
/* getAge(me); <- fails */


/**** Destructuring */

type leftOrRight =
  | Left(int)
  | Right(int);

let i = Left(1);

/* magic! */
let Left(v) | Right(v) = i;
Js.log(v);

let j = Right(2);
let Left(v2) | Right(v2) = j;
Js.log(v2);

/**** List, Array */
/*
List: https://caml.inria.fr/pub/docs/manual-ocaml/libref/List.html
Array: https://caml.inria.fr/pub/docs/manual-ocaml/libref/Array.html

tail-recursive: https://stackoverflow.com/questions/33923/what-is-tail-recursion
list: homogeneous, immutable, fast at prepending
array: homogeneous, fast update, fast random access, fixed-size (native)
*/

let li: list(int) = [1, 2, 3];
let li2 = [0, ...li];
Js.log(List.nth(li, 0));
Js.log(li->List.nth(0));

let ar: array(string) = [|"How", "are", "you"|];
Js.log(ar[0]);
/* ar[3] = "today"; <- out_of_bounds */


/* nth, filter, find */


/**** Null, Undefined, Option */

/* When you need null, use option(a') and Some/None */

let a: option(int) = Some(4);

/**** Other types */
/* Mutually dependent */
type student = {taughtBy: teacher}
and teacher = {students: list(student)};

/* Type temple template */
type coordinates('a) = ('a, 'a, 'a);

/* apply the coordinates "type function" and return the type (int, int, int) */
type intCoordinatesAlias = coordinates(int);

let buddy: intCoordinatesAlias = (10, 20, 20);

/* or, more commonly, write it inline */
let buddy: coordinates(float) = (10.5, 20.5, 20.5);


/**** Polymorphic Variants */