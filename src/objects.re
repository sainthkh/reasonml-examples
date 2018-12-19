let a = {
    val age = 20;
    val name = "K";
    pub profile = name ++ string_of_int(age);
}

/* Js.log(a.age); <- vals are inaccessible */
Js.log(a#profile);

type tesla = {.
  drive: int => int
};

let obj: tesla = {
  val hasEnvy = ref(false);
  pub drive = (speed) => {
    this#enableEnvy(true);
    speed
  };
  pri enableEnvy = (envy) => hasEnvy := envy
};

type tesla2('a) = {
  ..
  drive: int => int
} as 'a;

let obj: tesla2({. drive: int => int, doYouWant: unit => bool}) = {
  val hasEnvy = ref(false);
  pub drive = (speed) => {
    this#enableEnvy(true);
    speed
  };
  pub doYouWant = () => hasEnvy^;
  pri enableEnvy = (envy) => hasEnvy := envy
};