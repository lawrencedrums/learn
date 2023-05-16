struct ImportantExcerpt<'a> {
    part: &'a str,
}

impl<'a> ImportantExcerpt<'a> {
    fn announce_and_return_part(&self, announcement: &str) -> &str {
        println!("Attention please: {}", announcement);
        self.part
    }
}

fn main() {
    // static lifetime references can live for the entirety of the program
    let s: &'static str = "I have a static lifetime.";

    let str1 = String::from("abcd");
    let str2 = "xyz";

    let result = longest(str1.as_str(), str2);
    println!("The longest string is {}", result);

    let novel = String::from("Call me Ishmael. Some years ago...");
    let first_sentence = novel.split('.').next().expect("Could not find a '.'");
    let i = ImportantExcerpt {
        part: first_sentence,
    };
}

fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

// &i32        - a reference
// &'a i32     - a reference with an explicit lifetime
// &'a mut i32 - a mutable reference with an explicit lifetime

// Lifetime Elision Rules:
// 1. the compiler assigns a lifetime parameter to each parameter that's a reference
// 2. if there is exactly one input lifetime parameter, that lifetime is assigned to all output
//    lifetime parameters
// 3. if there are multiple input lifetime params, but one of them is `&self` or `mut &self`, the
//    lifetime of `self` is assigned to all output lifetime params

