module School = {
  type profession = Teacher | Director;

  let person1 = Teacher;
  let getProfession = (person) =>
    switch (person) {
    | Teacher => "A teacher"
    | Director => "A director"
    };
};

let p = {
  open School;
  getProfession(person1);
};

module BaseComponent = {
  let defaultGreeting = "Hello";
  let getAudience = (~excited) => excited ? "world!" : "world";
};

module ActualComponent = {
  /* the content is copied over */
  include BaseComponent;
  /* overrides BaseComponent.defaultGreeting */
  let defaultGreeting = "Hey";
  let render = () => defaultGreeting ++ " " ++ getAudience(~excited=true);
};

/* Call Types file and call Types.a */
/* Because of this rule, file names should start with a capital letter. */
/* And you can copy a file with include keyword. */
Js.log(Types.a); 

/* Defining module type and implementing it. */
module type EstablishmentType = {
  type profession;
  type x = string;
  let getProfession: profession => string;
};

module Company: EstablishmentType = {
  type profession = CEO | Designer | Engineer | CMO;
  type x = string;
  type person = {
      age: int,
      profession,
  }
  
  let people: list(person) = [];

  let getProfession = (person) => "";
  let person1 = {
      val age = 20;
  };
  let person2 = {
      val age = 30;
  };
};

module type BaseComponent2 = {
  let defaultGreeting: string;
  let getAudience: (~excited: bool) => string;
};

module type ActualComponent = {
  /* the BaseComponent signature is copied over */
  include BaseComponent2;
  let render: unit => string;
};

/** Extending basic type */
module type MyList = {
  include (module type of List);
  let myListFun: list('a) => list('a);
};

/** Functors */
/**
Rules:
Functors use the module keyword instead of let.
Functors take modules as arguments and return a module.
Functors require annotating arguments.
Functors must start with a capital letter (just like modules/signatures).
 */
module type Comparable = {
  type t;
  let equal: (t, t) => bool;
};

module MakeSet = (Item: Comparable) => {
  /* let's use a list as our naive backing data structure */
  type backingType = list(Item.t);
  let empty = [];
  let add = (currentSet: backingType, newItem: Item.t) : backingType =>
    /* if item exists */
    if (List.exists((x) => Item.equal(x, newItem), currentSet)) {
      currentSet /* return the same (immutable) set (a list really) */
    } else {
      [
        newItem,
        ...currentSet /* prepend to the set and return it */
      ]
    };
};

module IntPair = {
  type t = (int, int);
  let equal = ((x1, y1), (x2, y2)) => x1 == x2 && y1 == y2;
  let create = (x, y) => (x, y);
};

module SetOfIntPairs = MakeSet(IntPair);