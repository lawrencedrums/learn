fn main() {
    let s1 = String::from("hello");
    let len = calculate_length(&s1);
    println!("The length of '{}' is {}.", s1, len);

    let mut s2 = String::from("black"); // 
    push_string(&mut s2);
    println!("{s2}");

    // let ex1 = &mut s2;  This would cause an error because
    // let ex2 = &mut s2;  the same data can only be referenced once
   
    {
        let r1 = &mut s2; // once out of scope ...
    }
    let r2 = &mut s2; // ... a reference can be made again

    // the same value can't have a immutable reference
    // and a mutable reference at the same time ...
    let m = &s2;
    let n = &s2;
    println!("{m}+{n}");

    // ... unless the last usage of the value
    // occurs before a reference is introduced
    let l = &mut s2;
    println!("{l}");

    // a dangling pointer:
    // a pointer that references some memory
    // that may have been given to someone else
    let reference_to_nothing = dangle();
}

fn calculate_length(s: &String) -> usize { //s is a reference of a String
    s.len()
} // s goes out of scope, but since the function doesn't
  // have ownership, it is not dropped

fn push_string(s: &mut String) {
    s.push_str("nickel");
}

fn dangle() -> String { // `&String` returns a reference to a String
    let s = String::from("why"); // s is a new String
    s // `&s` return a reference to s
} // but here, s goes out of scope, and is dropped.
  // Its memory goes away. DANGER!
