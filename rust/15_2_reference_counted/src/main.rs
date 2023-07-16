// in graphs, when multiple edges points to the same node,
// the node is owned by all of these edges

// the Rust type `Rc<T>` enablesa multiple ownership
enum List {
    Cons(i32, Rc<List>),
    Nil,
}

use crate::List::{Cons, Nil};
use std::rc::Rc;

fn main() {
    let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
    println!("Reference count after creating a: {}", Rc::strong_count(&a));

    let b = Cons(3, Rc::clone(&a));
    println!("Reference count after creating b: {}", Rc::strong_count(&a));
    {
        let c = Cons(4, Rc::clone(&a));
        println!("Reference count after creating c: {}", Rc::strong_count(&a));
    }
    println!("Reference count after c goes out of scope: {}", Rc::strong_count(&a));
}
