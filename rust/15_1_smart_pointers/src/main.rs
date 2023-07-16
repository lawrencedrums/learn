// Pointers: a variable that contains an address in memory, i.e. &user_input
// Smart pointers: data structures that have additional metadata & capabilities,
//     e.g. `String`, `Vec<T>`
use crate::List::{Cons, Nil};
use std::ops::Deref;

enum List {
    Cons(i32, Box<List>),
    Nil,
}

// our own smart pointers
struct MyBox<T>(T);

impl<T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

impl<T> Deref for MyBox<T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

fn hello(name: &str) {
    println!("Hello {name}!");
}

fn main() {
    // recursive types
    // a value of a type that contain a value of the same type, i.e. list, dict
    // `box` have a known size therefor can enable recursive types
    let _ = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));

    // using Box<T> as a reference
    let x = 5;
    let y = Box::new(x);
    assert_eq!(5, x);
    assert_eq!(5, *y);

    let my_x = 10;
    let my_y = MyBox::new(my_x);
    assert_eq!(10, my_x);
    assert_eq!(10, *my_y);

    let m = MyBox::new(String::from("Lawrence"));
    hello(&m); // deref coercion turns `&MyBox<String>` into `&String`
} 
