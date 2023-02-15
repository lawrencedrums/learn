// keep at it

// ownership: a memory management system with a set of rules
//            that the compiler checks

// Stack: all data stored on the stack must have a known, fixed size
// Heap: find a space in memory large enough for the new data

// ownership rules
// - Each value in rust has an owner
// - There can only be one owner at a time
// - When the owner goes out of scope, the value will be dropped

fn main() {
    let s1 = String::from("hey");
    // the below would move s1 from s2, invalidating the former
    // let s2 = s1
    //
    // to deep copy do the following
    let s2 = s1.clone();
    println!("s1 = {s1}, s2 = {s2}");

    // types with known sizes (int etc) can shallow copy
    // aka the types that implements the `Copy` trait
    let x = 5;
    let y = x;
    println!("x = {x}, y = {y}");

    takes_ownership(s2); // s2's value moved into the function
                         // ... and no longer valid here
    
    makes_copy(y); // x move into function
                   // but i32 is Copy, x still valid
    
    let s3 = gives_ownership(); // return value moves into s3
    
    let s4 = takes_and_gives_ownership(s3); // s2 moved into function
                                            // moves return value to s4

    let (s5, len) = get_length(s4);
    println!("The string \"{s5}\" has length {len}");
}

fn takes_ownership(s: String) {
    println!("{s}");
} // `s` goes out of scope and `drop` is called
  // the backing memory is freed

fn makes_copy(n: i32) {
    println!("{n}");
} // `n` goes out of scope, nothing special happens

fn gives_ownership() -> String {
    let s = String::from("take it");
    s
}

fn takes_and_gives_ownership(s: String) -> String {
    s
}

fn get_length(s: String) -> (String, usize) {
    let length = s.len();
    (s, length)
}
