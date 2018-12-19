/**** if-else */
/**
Note that there is no return. 
 */
let isGood = false;
let a = if (isGood) {
    "Good"
} else {
    "Bad"
}

let b = isGood ? "Good" : "Bad";

if(isGood) {
    Js.log("Good")
}

if(isGood) {
    Js.log("Good")
} else {
    ()
}

/* => Use pattern matching! */

/**** switch, pattern matching, destructuring */
/* 
specific first. 
when for if.
_ for others. fall-through case. Check Calc.re 
*/


/** List */
let myList = [1, 2, 3];

switch (myList) {
| [] => print_endline("Empty list")
| [a, ..._] => print_endline("list with the head value " ++ string_of_int(a))
};

/** Array */
let myArray = [|1, 2, 3|]
/* let myArray = [|"Hello", "World", "You" |] */

switch (myArray) {
| [|1, 2|] when a == "777" => Js.log("777~")
| [|1, 2|] => print_endline("This is an array with item 1 and 2")
| [||] => print_endline("This array has no element")
| _ => print_endline("This is an array")
};

/** Result and exception */
let theItem = 1;
switch (List.find((i) => i === theItem, myList)) {
| item => Js.log(item)
| exception Not_found => print_endline("No such item found!")
};

/** Tuple */
type animal = Dog | Cat | Bird;

let isBig = true;
let myAnimal = Dog;

let result = switch (isBig, myAnimal) {
| (true, Dog) => 1
| (true, Cat) => 2
| (true, Bird) => 3
| (false, Dog | Cat) => 4
| (false, Bird) => 5
};

/** Object and Module */
type answer = Yes | No | Maybe;
type workType = {
    fullTime: answer,
}
type job = Programmer(workType) | Doctor | Teacher;
type student = {
    name: string,
    job: job,
}

let s = {
    name: "Jane",
    job: Programmer({fullTime: Yes}),
};

let s2 = {
    name: "Bob",
    job: Programmer({fullTime: Maybe}),
}

let s3 = {
    name: "K",
    job: Doctor,
}

let ourGroup = (s) => {
    switch (s) {
    | {name: "Jane" | "Joe"} => Js.log("OK")
    | {name: "Bob", job: Programmer({fullTime: Yes | Maybe})} => Js.log("OK 2")
    | _ => Js.log("Not in our group")
    };
}

ourGroup(s);
ourGroup(s2);
ourGroup(s3);

/**** exception */

exception WrongInput(string);

let f: unit => string = () => {
    if (false) {
        "abc"
    } else {
        raise(WrongInput("++++"));
    }
}

let a = try(f()) {
| WrongInput(msg) => "Wrong: " ++ msg
}

switch(f()) {
| item => Js.log("Good: " ++ item)
| exception WrongInput(msg) => Js.log("Bad: " ++ msg)
}


/**** loop */

for(i in 1 to 3) {
    Js.log(i);
}

for(i in 3 downto 1) {
    Js.log(i)
}

let break = ref(false);

let j = ref(0);

while (! break^) {
    j := j^ + 1;
    Js.log(j^);
    if (j^ == 3) {
        break := true;
    }
}

/**** list, array methods */

/* Reason gave list a syntax sugar. [1, 2, 3] is conceptually equivalent to Head(1, Head(2, Head(3, Empty)))
-> [1, 2, 3] is compiled to [1, [2, [3, 0]]]
*/
/* reduce is fold_left, fold_right in ReasonML/OCaml */
let n = [1, 2];
let m = ["Hi", "Hello", "Good bye"];
Js.log(n)

let r = List.map((a) => a * 2, n)
Js.log(r);

List.iter((a) => Js.log(a + 15), n);
Js.log(List.for_all((a) => a < 10, n));
Js.log(List.exists((a) => a == 3, n));

let n = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

let r = List.fold_left((a, b) => a + b, 0, n);
Js.log(r);

Js.log(List.map(a => a * 2, 
    List.filter(a => a mod 2 == 0, n))
)
Js.log(n|>List.filter(a => a mod 2 == 0)|>List.map(a => a * 2));

/**** promise */

let myPromise = Js.Promise.make((~resolve, ~reject) => resolve(. 2));

myPromise
|> Js.Promise.then_(value => {
     Js.log(value);
     Js.Promise.resolve(value + 2);
   })
|> Js.Promise.then_(value => {
     Js.log(value);
     Js.Promise.resolve(value + 3);
   })
|> Js.Promise.catch(err => {
     Js.log2("Failure!!", err);
     Js.Promise.resolve(-2);
   });
